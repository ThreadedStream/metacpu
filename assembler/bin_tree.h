#pragma once

#include <cstdint>
#include <cstdlib>
#include <errors.h>
#include <cstdio>

struct Node {
    const char *name; // 8
    Node *right; // 8
    Node *left; // 8
    uint8_t value; // 1
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

bool inline insert(Node *&root, const char *name, const uint8_t value) {
    if (!root) {
        root = allocateNode(name, value);
        if (!root) {
            fprintf(stderr, errors[FAILED_TO_ALLOCATE_MEMORY]);
            return false;
        }
        return true;
    }

    // try this iteratively
//    if (name > root->name) {
//        return insert(root->right, name, value);
//    } else{
//        return insert(root->left, name, value);
//    }


    // TODO(threadedstream): node's children do not update, inasmuch as the latter do not
    // possess any address (i.e nullptr), which makes it quite difficult to solve this problem
    // iteratively. However, it perfectly works in case with recursion.
    auto temp = root;

    while (temp) {
        if (name > temp->name) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }

    temp = allocateNode(name, value);
    if (!temp){
        fprintf(stderr, errors[FAILED_TO_ALLOCATE_MEMORY]);
        return false;
    }

    return true;
}


