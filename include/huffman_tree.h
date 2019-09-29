#ifndef HW_3_HUFFMAN_TREE_H
#define HW_3_HUFFMAN_TREE_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <deque>
#include <tuple>

class HuffTree {
public:
    HuffTree();

    explicit HuffTree(const std::unordered_map<char, int> &data);

    void add_code(char data, std::vector<bool> code);

    std::unordered_map<char, std::vector<bool>> get_alphabet();

    std::pair<bool, char> walk(bool branch);

    void back_to_root() noexcept;

    int get_full_code_size();

private:
    class TreeNode {
    public:
        TreeNode() noexcept = default;

        explicit TreeNode(char data, int freq, std::unique_ptr<TreeNode> l,
                          std::unique_ptr<TreeNode> r, bool is_leaf) noexcept;

        char _data = ' ';
        int _freq = 0;
        std::unique_ptr<TreeNode> _left, _right;
        bool _is_leaf = true;
    };

    TreeNode *curr_node = nullptr;
    std::unique_ptr<TreeNode> root;
};

#endif //HW_3_HUFFMAN_TREE_H
