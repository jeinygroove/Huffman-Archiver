#ifndef HW_3_HUFFMAN_TEST_H
#define HW_3_HUFFMAN_TEST_H

#include "autotest.h"
#include "huffman_archiver.h"
#include <iostream>
#include <sstream>
#include <unordered_map>

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

class HuffmanTest : public Test {
public:
    void test_get_alphabet();

    void test_walk(std::string str, char ch);

    void test_end_to_end(std::string str);

    void test_write(std::string str);

    void test_read_buf(int number);

    void test_read_char(char ch);

    void runAllTests() override;

private:
    void count_data(const std::string &str, std::unordered_map<char, int> &data);

    std::size_t count_size(int num);
};


#endif //HW_3_HUFFMAN_TEST_H