#include <bin_tree.h>
#include <cassert>
#include <cstring>

static void testInsert() {
    Node *root = nullptr;
    const char *name = "root";
    const uint8_t value = 0x69;
    root = insert(root, name, value);
    assert(root && "failed to insert a root");
    assert(strcmp(root->name, name) == 0 && "root->name and name do not match");
    assert(root->value == value && "root->value and value do not match");

    const char* kid1_name = "kid1";
    const uint8_t kid1_value = 0x70;
    auto node = insert(root, kid1_name, kid1_value);
    // sanity check that root's address has been properly restored
    assert(node && "failed to insert a node into the tree");

    const char* kid2_name = "kid2";
    const uint8_t kid2_value = 0x71;
    auto node1 = insert(root, kid2_name, kid2_value);
    assert(node1 && "failed to insert a node into the tree");

    Node* pred;
    findPred(root, pred, "")

    free(node1);
    free(node);
    free(root);
    root = nullptr;
    node = nullptr;
    node1 = nullptr;
}

int main(int argc, const char* argv[]) {
    testInsert();
}
