#ifndef HW_3_HUFFMAN_ARCHIVER_H
#define HW_3_HUFFMAN_ARCHIVER_H

#include "bit_streams.h"
#include "huffman_tree.h"
#include "huffman_exception.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

class HuffmanArchiver {
public:
    HuffmanArchiver();

    void zip(std::istream &in, std::ostream &out);

    void unzip(std::istream &in, std::ostream &out);

    std::vector<std::size_t> info();

private:
    static const int ALPHABET_SIZE = 16;
    static const int BITS_IN_SIZE_T = 64;
    static const int BITS_IN_INT = 32;

    void count_data(std::istream &in);

    static std::vector<bool> get_full_code(std::vector<bool> code, int length);

    static std::vector<bool> decode_full_code(std::vector<bool> full_code);

    std::size_t num_of_symbols_in = 0;
    std::size_t num_of_symbols_out = 0;
    std::size_t used_additional_bytes = 0;
    std::unordered_map<char, int> _data;
};

#endif //HW_3_HUFFMAN_ARCHIVER_H
