#include <iostream>
#include <fstream>
#include "../include/huffman_archiver.h"

int main(int argc, char *argv[]) {
    std::vector<std::size_t> info;
    if (argc < 6) {
        std::cout << "Not enough arquments, need 6!" << std::endl;
        return 0;
    }

    bool f = false;
    std::string cmd = argv[1], file_in, file_out;
    if (std::string(argv[2]) == "-f") {
        file_in = argv[3];
        if (std::string(argv[4]) == "-o") {
            file_out = argv[5];
        } else {
            f = true;
        }
    } else {
        f = true;
    }

    if (f) {
        std::cout << "Invalid arguments!" << std::endl;
        return 0;
    }
    std::ifstream cin;
    std::ofstream cout;

    try {
        cin.open(file_in);
        cout.open(file_out);
        if (!cin) {
            throw std::runtime_error("Could not open file " + file_in);
        }
        if (!cout) {
            throw std::runtime_error("Could not open file " + file_out);
        }
    } catch (std::exception &e) {
        std::cout << e.what() << "!\n";
        return 0;
    }

    HuffmanArchiver h;
    if (cmd == "-c") {
        try {
            h.zip(cin, cout);
        } catch (HuffmanException &e) {
            std::cout << e.what() << std::endl;
            return 0;
        } catch (std::exception &e) {
            std::cout << "Standart exception: " << e.what() << std::endl;
            return 0;
        }
    } else if (cmd == "-u") {
        try {
            h.unzip(cin, cout);
        } catch (HuffmanException &e) {
            std::cout << e.what() << std::endl;
            return 0;
        } catch (std::exception &e) {
            std::cout << "Standart exception: " << e.what() << std::endl;
            return 0;
        }
    } else {
        std::cout << "Unknown command '"<< cmd << "'!" << std::endl;
        return 0;
    }

    info = h.info();
    for (auto n : info) {
        std::cout << n << std::endl;
    }
    cin.close();
    cout.close();
    return 0;
}
