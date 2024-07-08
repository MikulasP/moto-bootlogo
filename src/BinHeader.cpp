#include "BinHeader.h"

BinHeader::BinHeader(size_t offset, size_t size, size_t g, BinImage *image, string name)
{
    _offset = offset;
    _size = size;
    _g = g;
    _image = image;
    _name = name;
}

BinHeader::~BinHeader()
{
    if (_image) {
        delete _image;
        _image = NULL;
    }
}

BinImage *BinHeader::get_image(void)
{
    return _image;
}

size_t BinHeader::get_g(void)
{
    return _g;
}

size_t BinHeader::get_offset(void)
{
    return _offset;
}

size_t BinHeader::get_size(void)
{
    return _size;
}

void BinHeader::update_size(void)
{
    _size = _image->get_size();
}

string BinHeader::get_name(void) const {
    return _name;
}