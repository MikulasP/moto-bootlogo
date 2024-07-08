#ifndef BINHEADER_H
#define BINHEADER_H

#include "BinFile.h"
#include "BinImage.h"

using namespace std;

class BinFile;
class BinImage;

class BinHeader
{
public:
    BinHeader(size_t offset, size_t size, size_t g, BinImage *image, string name);
    ~BinHeader();
    BinImage *get_image(void);
    size_t get_g(void);
    size_t get_offset(void);
    size_t get_size(void);
    void update_size(void);
    string get_name(void) const;

private:
    string _name;
    size_t _g;
    size_t _offset;
    size_t _size;
    BinImage *_image;
};

#endif
