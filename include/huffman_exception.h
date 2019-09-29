#ifndef HW_3_HUFFMAN_EXCEPTION_H
#define HW_3_HUFFMAN_EXCEPTION_H

#include <exception>
#include <string>

class HuffmanException : public std::exception {
public:
    explicit HuffmanException(const std::string &msg) noexcept;

    const char *what() const noexcept override;

private:
    std::string _msg;
};

#endif //HW_3_HUFFMAN_EXCEPTION_H
