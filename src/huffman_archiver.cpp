#include "huffman_archiver.h"

void HuffmanArchiver::zip(std::istream &cin, std::ostream &cout) {
    count_data(cin);
    HuffTree h_tree(_data);
    std::vector<bool> full_code;

    std::unordered_map<char, std::vector<bool>> alphabet;
    alphabet = h_tree.get_alphabet();
    int full_code_size = h_tree.get_full_code_size();

    BitWriter out(cout);

    out.write(static_cast<int>(num_of_symbols_in), BITS_IN_SIZE_T);
    out.write(full_code_size, BITS_IN_INT);
    out.write(static_cast<int>(alphabet.size()), ALPHABET_SIZE);
    for (const auto &i : alphabet) {
        out.write(i.first, BITS_IN_BYTE);
        full_code = get_full_code(i.second, full_code_size);
        for (bool bit : full_code) {
            out.write(bit, 1);
        }
    }

    used_additional_bytes = BITS_IN_SIZE_T + ALPHABET_SIZE + alphabet.size() * (BITS_IN_BYTE + full_code_size)
                            + BITS_IN_INT;
    used_additional_bytes /= BITS_IN_BYTE;

    char c;
    while (cin.read(&c, 1)) {
        for (bool bit : alphabet[c]) {
            out.write(bit, 1);
        }
        num_of_symbols_out += alphabet[c].size();
    }
    num_of_symbols_out = (num_of_symbols_out + 7) / 8;
}

std::vector<bool> HuffmanArchiver::get_full_code(std::vector<bool> code, int length) {
    std::vector<bool> res(length, true);
    std::size_t i = 0;
    std::reverse(code.begin(), code.end());
    for (bool bit : code) {
        res[i] = bit;
        i++;
    }
    res[i] = false;
    return res;
}

void HuffmanArchiver::unzip(std::istream &cin, std::ostream &cout) {
    HuffTree tree;
    std::vector<bool> code;

    BitReader in(cin);

    num_of_symbols_out = static_cast<std::size_t>(in.read_buf(BITS_IN_SIZE_T));
    int full_code_size = in.read_buf(BITS_IN_INT);
    auto size = static_cast<std::size_t>(in.read_buf(ALPHABET_SIZE));

    char ch;
    for (std::size_t i = 0; i < size; i++) {
        code.clear();
        ch = in.read_char();
        for (int j = 0; j < full_code_size; j++) {
            code.push_back(static_cast<bool>(in.read_buf(1)));
        }
        std::reverse(code.begin(), code.end());
        code = decode_full_code(code);
        tree.add_code(ch, code);
    }

    used_additional_bytes = BITS_IN_SIZE_T + ALPHABET_SIZE + size * (BITS_IN_BYTE + full_code_size)
                            + BITS_IN_INT;
    used_additional_bytes /= BITS_IN_BYTE;

    bool bit;
    std::pair<bool, char> node;
    tree.back_to_root();
    std::size_t i = 0;
    while (i < num_of_symbols_out) {
        bit = (bool) in.read_buf(1);
        node = tree.walk(bit);
        if (node.first) {
            cout.write(reinterpret_cast<const char *>(&node.second), 1);
            tree.back_to_root();
            i++;
        }
    }
    num_of_symbols_in = static_cast<std::size_t >(cin.tellg()) - used_additional_bytes;
}

std::vector<bool> HuffmanArchiver::decode_full_code(std::vector<bool> full_code) {
    std::vector<bool> code;
    auto it = full_code.begin();
    while (*it == 1) {
        it++;
    }
    it++;
    for (; it != full_code.end(); it++) {
        code.push_back(*it);
    }
    return code;
}

void HuffmanArchiver::count_data(std::istream &in) {
    char c;
    while (in.read(&c, 1)) {
        _data[c]++;
        num_of_symbols_in++;
    }
    in.clear();
    in.seekg(0, in.beg);
}

std::vector<std::size_t> HuffmanArchiver::info() {
    return {num_of_symbols_in, num_of_symbols_out, used_additional_bytes};
}

HuffmanArchiver::HuffmanArchiver() {
    num_of_symbols_in = 0;
    num_of_symbols_out = 0;
    used_additional_bytes = 0;
}
