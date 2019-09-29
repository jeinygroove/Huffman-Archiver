#include "../include/huffman_exception.h"

HuffmanException::HuffmanException(const std::string &msg) noexcept : _msg(msg) {
}

const char *HuffmanException::what() const noexcept {
    return _msg.c_str();
}
