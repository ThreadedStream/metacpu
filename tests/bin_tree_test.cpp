#include <bin_tree.h>
#include <cassert>
#include <cstring>

static void compoundTest() {

    // inserting an element
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
    assert(node && "failed to insert a node into the tree");

    const char* kid2_name = "kid2";
    const uint8_t kid2_value = 0x71;
    auto node1 = insert(root, kid2_name, kid2_value);
    assert(node1 && "failed to insert a node into the tree");

    const char* kid3_name = "zigmund";
    const uint8_t kid3_value = 0x72;
    auto node2 = insert(root, kid3_name, kid3_value);
    assert(node2 && "failed to insert a node into the tree");

    const char* kid4_name = "watt";
    const uint8_t kid4_value = 0x73;
    auto node3 = insert(root, kid4_name, kid4_value);
    assert(node3 && "failed to insert a node into the tree");

    // finding an element
    auto node_twin = find(root, kid1_name);
    assert((node_twin && strcmp(node_twin->name, kid1_name) == 0) && "should have found a node");

    auto not_supposed_to_find_node = find(root, "ahalai-mahalai");
    assert(!not_supposed_to_find_node && "shouldn't have found a node");

    // in-order predecessor
//    Node* iop;
//    findIop(root, iop);
//    assert(strcmp(iop->name, kid2_name) == 0 && "should be a kid2");

    // in-order successor
    Node* ios;
    findIos(root, ios);
    assert(strcmp(ios->name, kid4_name) == 0 && "should be a kid4");

    // removing an element
    auto success = remove(root, "kid2");
    assert(success && "failed to remove an item");

    success = remove(root, "root");
    assert(success && "failed to remove an item");

}

int main(int argc, const char* argv[]) {
    compoundTest();
}
