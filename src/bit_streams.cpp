#include "bit_streams.h"

BitWriter::BitWriter(std::ostream &os) : _os(os) {
    _buf = 0;
    _curBit = 0;
}

void BitWriter::write(int data, std::size_t length) {
    for (std::size_t i = 0; i < length; ++i) {
        int bit = (data >> i) & 1;
        _buf |= (bit << _curBit);
        _curBit++;
        if (_curBit == BITS_IN_BYTE) {
            _os.write((const char*)&_buf, 1);
            _curBit = 0;
            _buf = 0;
        }
    }
}

BitWriter::~BitWriter() {
    if (_curBit > 0) {
        _os.write(reinterpret_cast<const char*>(&_buf), 1);
    }
}

BitReader::BitReader(std::istream &is) : _is(is){
    _buf = 0;
    _curBit = BITS_IN_BYTE;
}

int BitReader::read_buf(std::size_t length) {
    int res = 0;
    for (std::size_t i = 0; i < length; ++i) {
        int bit = read_bit();
        res |= (bit << i);
    }
    return res;
}

char BitReader::read_char() {
    int res = read_buf(BITS_IN_BYTE);
    return static_cast<char>(res);
}

bool BitReader::read_bit() {
    if (_curBit == BITS_IN_BYTE) {
        _is.read(reinterpret_cast<char *>(&_buf), 1);
        _curBit = 0;
    }
    _curBit++;
    return (bool)(_buf & (1 << (_curBit - 1)));
}