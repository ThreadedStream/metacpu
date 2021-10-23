#include <bin_tree.h>
#include <cassert>
#include <cstring>

static void test_insert() {
    Node *root = nullptr;
    const char *name = "pwn_government";
    const uint8_t value = 0x69;
    auto success = insert(root, name, value);
    assert(success && "failed to insert a root");
    assert(strcmp(root->name, name) == 0 && "root->name and name do not match");
    assert(root->value == value && "root->value and value do not match");


    const char* kid1_name = "print";
    const uint8_t kid1_value = 0x70;
    success = insert(root, kid1_name, kid1_value);
    assert(success && "failed to insert a first kid");
    // sanity check that root's address has been properly restored
    assert(strcmp(root->name, name) == 0 && "root->name and name do not match");
    assert(root->value == value && "root->value and value do not match");

    free(root->right);
    root->right = nullptr;
    free(root->left);
    root->left = nullptr;
    free(root);
    root = nullptr;
}


int main(int argc, const char* argv[]) {
    test_insert();
}
