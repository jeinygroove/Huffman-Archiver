#include "huffman_test.h"

void HuffmanTest::test_get_alphabet() {
    std::string str = "AABBAACCC";
    std::unordered_map<char, int> data;
    count_data(str, data);
    HuffTree tree(data);
    std::unordered_map<char, std::vector<bool>> alphabet = tree.get_alphabet();
    std::unordered_map<char, std::vector<bool>> ans_alphabet;
    ans_alphabet['A'] = {false};
    ans_alphabet['B'] = {true, false};
    ans_alphabet['C'] = {true, true};
    DO_CHECK(alphabet == ans_alphabet);
}

void HuffmanTest::test_walk(std::string str, char ch) {
    //std::string str = "PinkFloyd";
    std::unordered_map<char, int> data;
    count_data(str, data);
    HuffTree tree(data);
    std::unordered_map<char, std::vector<bool>> alphabet = tree.get_alphabet();
    std::pair<bool, char> res;
    tree.back_to_root();
    for (bool bit : alphabet[ch]) {
        res = tree.walk(bit);
    }
    DO_CHECK(res.first && res.second == ch);
}

void HuffmanTest::test_end_to_end(std::string str) {
    std::stringstream is, os;
    is << str;
    HuffmanArchiver h;
    h.zip(is, os);
    h.unzip(os, is);
    DO_CHECK(is.str() == str);
}

void HuffmanTest::test_write(std::string str) {
    std::stringstream is;
    BitWriter in(is);
    for (auto ch : str) {
        in.write(static_cast<int>(ch), 8);
    }
    DO_CHECK(is.str() == str);
}

void HuffmanTest::test_read_buf(int number) {
    std::stringstream os;
    BitReader in(os);
    os.write(reinterpret_cast<const char *>(&number), sizeof(int));
    int res = in.read_buf(count_size(number));
    DO_CHECK(res == number);
}

void HuffmanTest::test_read_char(char ch) {
    std::stringstream os;
    BitReader out(os);
    os << ch;
    char res = out.read_char();
    DO_CHECK(res == ch);
}

void HuffmanTest::runAllTests() {
    test_get_alphabet();
    test_walk("Pink Floyd", 'F');
    test_walk("Feel Invincible", 'i');
    test_walk("....", '.');
    test_end_to_end("Hello world!");
    test_end_to_end("");
    test_end_to_end("101000010101010001");
    test_end_to_end("FFFFFFFFFFFFFFFFFFFFFF");
    test_end_to_end("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_+=0123456789!@#$%^&*()~`[]{}");
    test_write("F");
    test_write("Earthquake");
    test_write("");
    test_read_buf(17);
    test_read_buf(2019);
    test_read_buf(15);
    test_read_char('S');
    test_read_char('\t');
}

void HuffmanTest::count_data(const std::string &str, std::unordered_map<char, int> &data) {
    for (const char &ch : str) {
        data[ch]++;
    }
}

std::size_t HuffmanTest::count_size(int num) {
    std::size_t i = 0;
    while (num != 0) {
        i++;
        num = (num >> 1);
    }
    return i;
}

