#include <stdio.h>
#include <string>

class Image
{
public:
    Image(const char* buf, uint32_t w, uint32_t h, uint32_t fmt)
    : _buf(buf)
    , _width(w)
    , _height(h)
    , _format(fmt)
    {}

private:
    std::string _buf;
    uint32_t    _width;
    uint32_t    _height;
    uint32_t    _format;

};


int main(int argc, char* argv[])
{

    return 0;
}