
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "BinFile.h"

using namespace std;

vector<string> unlocked_bootloader_screens{"logo_unlocked", "orange1", "orange2", "yellow1"};

void print_usage(void) {
    cout << "Usage: moto-bootlogo [-f] [-i <png>] <logo.bin>" << endl;
    cout << endl;
    cout << "  -f        Fixup bootlogo. Replace the 'unlocked bootloader' logo" << endl;
    cout << "            with the original one." << endl;
    cout << "  -i <png>  Insert a PNG image <png> as the new bootlogo." << endl;
    cout << "            Note this implies '-f'. The PNG image's size must not" << endl;
    cout << "            exceed the restrictions on the size of the binary file." << endl;
    cout << endl;
}

bool in_vector(const string &value, const vector<string> &vec) {
    return find(vec.begin(), vec.end(), value) != vec.end();
}

int main(int argc, char *argv[]) {
    // require at least 2 arguments
    if (argc < 2) {
        print_usage();
        return 1;
    }

    // read options
    char c;
    bool fixup = false;
    string png = "";
    while ((c = getopt(argc, argv, "fi:")) != -1) {
        switch (c) {
            case 'i':
                png = optarg;
                // do not break
            case 'f':
                fixup = true;
                break;
            default:
                print_usage();
                return 1;
        }
    }

    string filename = argv[argc - 1];

    if (fixup) {
        // generate filename
        string filenameOut = filename;
        string ext = "";
        int index = filename.rfind(".");
        if (index >= 0) {
            ext = filename.substr(index);
            filenameOut = filename.substr(0, index);
        }
        filenameOut = filenameOut.append("-custom").append(ext);

        // copy original file
        ifstream infile(filename.c_str(), ios::binary);
        ofstream outfile(filenameOut.c_str(), ios::trunc|ios::binary);
        outfile << infile.rdbuf();
        filename = filenameOut;
        cout << "Created '" << filename << "'" << endl;
     }

    // create BinFile
    BinFile *bin = new BinFile(filename);

    // parse (and thus verify) BinFile
    map<string, BinHeader*> headers = bin->get_headers();
    int size = headers.size();
    cout << "Found " << size << " image" << (size == 1 ? "" : "s") << "." << endl;

    // first insert the PNG as this changes the header
    if (!png.empty()) {
        if (!bin->replace_image("logo_boot", png)) {
            cerr << "Failed replacing boot logo with '" << png << "'" << endl;
            delete bin;
            return 1;
        }
        cout << "Replaced boot logo successfully!" << endl;
    } 

    // create PNG images
    for (map<string, BinHeader*>::const_iterator it = headers.begin(), end = headers.end(); it != end; ++it) {
        string tag = it->first;
        BinHeader *header = it->second;
        BinImage *image = header->get_image();
        image->create_png(tag.append(".png"));
    }

    if (fixup) {
        for (map<string, BinHeader*>::const_iterator it = headers.begin(), end = headers.end(); it != end; ++it) {
            if (in_vector(it->first, unlocked_bootloader_screens)) {
                if (!bin->replace_image(it->first, "logo_boot.png")) {
                    // reset boot logo
                    cerr << "Failed fixing boot logo" << endl;
                    delete bin;
                    return 1;
                }
                cout << "Replaced \'" << it->first << "\'" << endl;
            }
            
        }
        cout << "Fixed boot logo!" << endl;
        exit(0);
    }  

    // exit
    delete bin;
    return 0;
}
