#pragma once

#include <vector>
#include <memory>
#include <string>

namespace BST {
    /**
     * The liked tree is a binary search tree that uses nodes liked togeather forming a tree to store
     * and quckly index data. Unlike the Linked tree this one does not delete its content when it is deleted.
    */
    template<typename T>
    class LinkedTreeReleased {
        public: struct Node {
            std::unique_ptr<Node> zero_node;
            std::unique_ptr<Node> one_node;
            T* data;
        };


        private: Node root;

        // Inserts `data` into the tree at the index idx
        public: void insert(const char* idx, const size_t idx_size, T data);
        public: void insert(const char* idx, const size_t idx_size, T* data);
        // gets the data at a current tree idx
        public: T* get(const char* idx, const size_t idx_size);
        // gets the data at a current tree idx and releases it from deletion handler
        public: T* getAndRelease(const char* idx, const size_t idx_size);
        // remove removed the data at the current location
        public: void remove(const char* idx, const size_t idx_size);

        public: void print();

        private: std::vector<std::pair<std::string, bool>> get_print_node(std::string key, const Node* node);
        private: void clean_tree(const char* idx, const size_t& idx_size);
        private: Node* follow_node_to_end(const char* idx, const size_t& idx_size);
        private: Node* get_or_add_node(std::unique_ptr<Node>& node_ptr);
        private: Node* get_next_node(Node& current_node, const bool descision);
        private: bool get_nth_bit(const char*& arr, const size_t& bit);
    };
}

template<typename T>
inline void BST::LinkedTreeReleased<T>::insert(const char* idx_arr, const size_t idx_size, T data) {
    this->insert(idx_arr, idx_size, new T(data));
}

template<typename T>
inline void BST::LinkedTreeReleased<T>::insert(const char* idx_arr, const size_t idx_size, T* data) {
    this->follow_node_to_end(idx_arr, idx_size)->data = data;
}

template<typename T>
inline T* BST::LinkedTreeReleased<T>::get(const char* idx_arr, const size_t idx_size) {
    return this->follow_node_to_end(idx_arr, idx_size)->data;
}

template<typename T>
inline T* BST::LinkedTreeReleased<T>::getAndRelease(const char* idx_arr, const size_t idx_size) {
    return this->follow_node_to_end(idx_arr, idx_size)->data;
}

template<typename T>
inline void BST::LinkedTreeReleased<T>::remove(const char* idx, const size_t idx_size) {
    this->follow_node_to_end(idx, idx_size)->data = nullptr;
    this->clean_tree(idx, idx_size);
}

template<typename T>
inline void BST::LinkedTreeReleased<T>::print() {
    std::vector<std::pair<std::string, bool>> elements = this->get_print_node("", &(this->root));
    size_t size = 0;
    for (const std::pair<std::string, bool> element : elements) {
        size = std::max(size, element.first.length());
    }
    for (const std::pair<std::string, bool> element : elements) {
        std::cout << element.first;
        for (size_t idx=element.first.length(); idx<size; idx++) {
            std::cout << " ";
        }
        std::cout << "\t" << element.second << std::endl;
    }
}


template<typename T>
std::vector<std::pair<std::string, bool>> BST::LinkedTreeReleased<T>::get_print_node(std::string key, const Node* node) {
    std::vector<std::pair<std::string, bool>> out;
    
    out.push_back({
        key,
        node->data != nullptr
    });

    if (node->zero_node.get() != nullptr) {
        std::vector<std::pair<std::string, bool>> zeroArea = this->get_print_node(key + "0", node->zero_node.get());
        out.insert(out.end(), zeroArea.begin(), zeroArea.end());
    }
    if (node->one_node.get() != nullptr) {
        std::vector<std::pair<std::string, bool>> oneArea = this->get_print_node(key + "1", node->one_node.get());
        out.insert(out.end(), oneArea.begin(), oneArea.end());
    }
    return out;
}

template<typename T>
inline void BST::LinkedTreeReleased<T>::clean_tree(const char* arr, const size_t& idx_size) {
    Node* currentNode = &(this->root);
    Node* topNode = currentNode;
    bool topDirection = this->get_nth_bit(arr, 0);

    for (size_t idx=0; idx<idx_size-1; idx++) {
        bool direction = this->get_nth_bit(arr, idx);
        currentNode = this->get_next_node(*currentNode, direction);
        if (currentNode->data != nullptr) {
            topNode = currentNode;
            topDirection = direction;
        }
    }

    currentNode = this->get_next_node(*currentNode, this->get_nth_bit(arr, idx_size-1));
    if (currentNode->one_node.get() != nullptr || currentNode->zero_node.get() != nullptr) {
        return;
    }
    
    if (topDirection) {
        topNode->one_node.reset();
    }
    else {
        topNode->zero_node.reset();
    }
}

template<typename T>
inline typename BST::LinkedTreeReleased<T>::Node* BST::LinkedTreeReleased<T>::follow_node_to_end(const char* arr, const size_t& idx_size) {
    Node* currentNode = &(this->root);
    for (size_t idx=0; idx<idx_size; idx++) {
        currentNode = this->get_next_node(*currentNode, this->get_nth_bit(arr, idx));
    }
    return currentNode;
}

template<typename T>
inline typename BST::LinkedTreeReleased<T>::Node* BST::LinkedTreeReleased<T>::get_or_add_node(std::unique_ptr<Node>& node_ptr) {
    if (node_ptr.get() == nullptr) {
        node_ptr.reset(new Node);
    }
    return node_ptr.get();
}

template<typename T>
inline typename BST::LinkedTreeReleased<T>::Node* BST::LinkedTreeReleased<T>::get_next_node(Node& current_node, bool descision) {
    if (descision) {
        return this->get_or_add_node(current_node.one_node);
    }
    return this->get_or_add_node(current_node.zero_node);
}

template<typename T>
inline bool BST::LinkedTreeReleased<T>::get_nth_bit(const char*& arr, const size_t& bit) {
    char byte = arr[bit/8];
    return (byte >> (bit % 8)) & 1; 
}