#pragma once

#include <cstdint>
#include <cstdlib>
#include <errors.h>
#include <cstdio>
#include <cstring>

struct Node {
    const char *name; // 8
    Node *right; // 8
    Node *left; // 8
    uint8_t value; // 1
    bool    to_be_freed{false};

    inline void ingest(const Node& other) {
        name = other.name;
        value = other.value;
    }
};

static inline Node *allocateNode(const char *name, const uint8_t value) {
    Node *ptr = static_cast<Node *>(calloc(1, sizeof(Node)));
    if (!ptr) {
        return nullptr;
    }

    ptr->name = name;
    ptr->value = value;
    return ptr;
}

static inline Node *insert(Node *root, const char *name, const uint8_t value) {
    auto n = allocateNode(name, value);
    if (!n) {
        fputs(errors[FAILED_TO_ALLOCATE_MEMORY], stderr);
        return nullptr;
    }

    auto temp = root;

    Node *temp1 = nullptr;

    while (temp) {
        temp1 = temp;
        if (strcmp(name, root->name) < 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    if (!temp1) {
        temp1 = n;
    } else if (strcmp(name, temp1->name) < 0) {
        temp1->left = n;
    } else if (strcmp(name, temp1->name) > 0){
        temp1->right = n;
    } else {
        free(n);
        n = nullptr;
        return nullptr;
    }

    return temp1;
}

static Node *& find(Node *&root, const char *name) {
    if (root == nullptr) {
        // returning root because of a reference
        return root;
    }

    if (strcmp(name, root->name) > 0) {
        return find(root->right, name);
    } else if (strcmp(name, root->name) < 0) {
        return find(root->left, name);
    } else {
        return root;
    }
}

inline void findIop(Node *& node, Node*& pred) {
    // in-order predecessor is possible iff the left subtree of a given node exists
    if (!node->left) {
        return;
    }

    void* node_raw = (void*) node;

    node = node->left;
    pred = node;
    while (node && node->right) {
        pred = node->right;
        node = node->right;
    }

    node = (Node* ) node_raw;

    return;
}

// find in-order successor of a node
inline void findIos(Node *& node, Node*& succ) {
    // in-order successor is possible iff the right subtree of a given node exists
    if (!node->right) {
        return;
    }

    void *raw_node = (void*) node;

    node = node->right;

    // at that point, we traverse the right subtree to find a minimum element, i.e
    // we traverse down to a left-most leaf
    succ = node;
    while (node && node->left) {
        succ = node->left;
        node = node->left;
    }

    // restore node's passed-in address
    node = (Node* ) raw_node;

    return;
}

static inline bool remove(Node *&root, const char *name) {
    if (!root) {
        return false;
    }

    auto &node_to_delete = find(root, name);
    if (!node_to_delete) {
        return false;
    }

    // node_to_delete is a leaf
    if (!node_to_delete->right && !node_to_delete->left) {
        free(node_to_delete);
        node_to_delete = nullptr;
        return true;
    } else {
        // node_to_delete has a single right kid
        if (node_to_delete->right && !node_to_delete->left) {
            Node* iop;
            findIop(node_to_delete, iop);
            node_to_delete->ingest(*iop);
            iop->to_be_freed = true;
            return true;
        }

        // node_to_delete has a single left kid
        else if (node_to_delete->left && !node_to_delete->right) {
            Node* ios = nullptr;
            findIos(node_to_delete, ios);
            node_to_delete->ingest(*ios);
            ios->to_be_freed = true;
            return true;
        }

        // node_to_delete happens to be a happy father of two kids
        else {
            Node* iop;
            findIop(node_to_delete, iop);
            node_to_delete->ingest(*iop);
            iop->to_be_freed = true;
            return true;
        }
    }
}

//inline void destroyToBeFreed(Node*& root, void *root_saved_addr) {
//    if (root == nullptr) {
//        root = (Node*) root_saved_addr;
//        return;
//    }
//    destroyToBeFreed(root->left, root_saved_addr);
//    if (root->to_be_freed) {
//        free(root);
//        root = nullptr;
//    }
//    destroyToBeFreed(root->right, root_saved_addr);
//
//}


