#ifndef HW_3_BIT_STREAMS_H
#define HW_3_BIT_STREAMS_H

#include <iostream>

static const int BITS_IN_BYTE = 8;

class BitWriter {
public:
    explicit BitWriter(std::ostream &os);

    ~BitWriter();

    void write(int data, std::size_t length);

private:
    std::ostream &_os;
    unsigned char _buf;
    int _curBit;
};

class BitReader {
public:
    explicit BitReader(std::istream &is);

    int read_buf(std::size_t length);

    char read_char();

private:
    bool read_bit();

    std::istream &_is;
    unsigned char _buf;
    int _curBit;
};

#endif //HW_3_BIT_STREAMS_H
