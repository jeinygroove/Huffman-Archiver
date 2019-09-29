#include "huffman_tree.h"
#include "huffman_exception.h"

HuffTree::TreeNode::TreeNode(char data, int freq, std::unique_ptr<TreeNode> l,
                             std::unique_ptr<TreeNode> r, bool is_leaf) noexcept
        : _data(data), _freq(freq), _left(std::move(l)), _right(std::move(r)), _is_leaf(is_leaf) {
}

HuffTree::HuffTree() {
    root = std::make_unique<TreeNode>(TreeNode());
}

HuffTree::HuffTree(const std::unordered_map<char, int> &data) {
    auto comp = [](const std::unique_ptr<TreeNode> &l, const std::unique_ptr<TreeNode> &r) -> bool {
        return (l->_freq > r->_freq);
    };

    std::priority_queue<std::unique_ptr<TreeNode>,
            std::vector<std::unique_ptr<TreeNode>>,
            decltype(comp)> MinHeap(comp);

    for (auto i : data) {
        MinHeap.push(std::make_unique<TreeNode>(TreeNode(i.first, i.second, nullptr, nullptr, true)));
    }
    std::size_t size = data.size();
    while (size > 1) {
        std::unique_ptr<TreeNode> l(std::move(const_cast<std::unique_ptr<TreeNode> &>(MinHeap.top())));
        MinHeap.pop();

        std::unique_ptr<TreeNode> r(std::move(const_cast<std::unique_ptr<TreeNode> &>(MinHeap.top())));
        MinHeap.pop();

        int freq = l->_freq + r->_freq;
        MinHeap.push(std::make_unique<TreeNode>(TreeNode(' ', freq, std::move(l), std::move(r), false)));
        size--;
    }
    if (!MinHeap.empty()) {
        std::unique_ptr<TreeNode> top(std::move(const_cast<std::unique_ptr<TreeNode> &>(MinHeap.top())));
        MinHeap.pop();
        if (data.size() == 1) {
            int freq = top->_freq;
            root = std::make_unique<TreeNode>(TreeNode(' ', freq, std::move(top),
                                                       nullptr, false));
        } else {
            root = std::move(const_cast<std::unique_ptr<TreeNode> &>(top));
        }
    }
}

void HuffTree::add_code(char data, std::vector<bool> code) {
    back_to_root();
    for (bool bit : code) {
        if (bit) {
            if (!curr_node->_right) {
                curr_node->_is_leaf = false;
                curr_node->_right = std::make_unique<TreeNode>(TreeNode());
            }
            curr_node = curr_node->_right.get();
        } else {
            if (!curr_node->_left) {
                curr_node->_is_leaf = false;
                curr_node->_left = std::make_unique<TreeNode>(TreeNode());
            }
            curr_node = curr_node->_left.get();
        }
    }
    curr_node->_data = data;
    curr_node->_is_leaf = true;
}

std::unordered_map<char, std::vector<bool>> HuffTree::get_alphabet() {
    std::unordered_map<char, std::vector<bool>> alphabet;

    if (root) {
        std::vector<bool> code = {};
        std::stack<std::pair<TreeNode *, std::vector<bool>>> s;
        s.push({root.get(), code});
        while (!s.empty()) {
            TreeNode *node;
            std::tie(node, code) = s.top();
            s.pop();
            if (node->_is_leaf) {
                alphabet[node->_data] = code;
            }
            if (node->_left) {
                code.push_back(false);
                s.push({node->_left.get(), code});
                code.pop_back();
            }
            if (node->_right) {
                code.push_back(true);
                s.push({node->_right.get(), code});
                code.pop_back();
            }
        }
    }
    return alphabet;
}


std::pair<bool, char> HuffTree::walk(bool branch) {
    if (branch) {
        if (!curr_node->_right) {
            throw HuffmanException("Incorrect Huffman tree! (Check your input file for correctness!)");
        }
        curr_node = curr_node->_right.get();
    } else {
        if (!curr_node->_left) {
            throw HuffmanException("Incorrect Huffman tree! (Check your input file for correctness!)");
        }
        curr_node = curr_node->_left.get();
    }
    return {curr_node->_is_leaf, curr_node->_data};
}

void HuffTree::back_to_root() noexcept {
    curr_node = root.get();
}

int HuffTree::get_full_code_size() {
    int padding = 2, res = 0;
    back_to_root();
    if (!root) {
        return 1;
    }
    std::deque<std::pair<const TreeNode *, int>> q;
    int d = 0;
    const TreeNode *node = root.get();
    q.emplace_back(node, d);
    while (!q.empty()) {
        std::tie(node, d) = q.front();
        res = std::max(d, res);
        q.pop_front();
        if (node->_left) {
            q.emplace_back(node->_left.get(), d + 1);
        }
        if (node->_right) {
            q.emplace_back(node->_right.get(), d + 1);
        }
    }
    return res + padding;
}
