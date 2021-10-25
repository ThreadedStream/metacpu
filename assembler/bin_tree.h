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

inline Node* insert(Node *&root, const char *name, const uint8_t value) {
    auto n = allocateNode(name, value);
    if (!n) {
        fputs(errors[FAILED_TO_ALLOCATE_MEMORY], stderr);
        return nullptr;
    }

    auto temp = root;

    Node* temp1 = nullptr;

    while (temp) {
        temp1 = temp;
        if (name < temp->name) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    if (!temp1) {
        temp1 = n;
    } else if (name < temp1->name) {
        temp1->left = n;
    } else {
        temp1->right = n;
    }

    return temp1;
}

bool inline remove(Node*& root, const char* name) {
    if (!root) {
        return false;
    }
    if (name > root->name) {
        return remove(root->right, name);
    } else if (name < root->name) {
        return remove(root->left, name);
    } else {
        free(root);
    }
}

void findPred(Node* root, Node*& pred, const char* name) {
    if (root == nullptr) {
        pred = nullptr;
        return;
    }

    auto temp = root->left;

    decltype(temp) temp1 = nullptr;
    while (temp) {
        temp1 = temp;
        temp = temp->right;
    }

    pred = temp1;
}