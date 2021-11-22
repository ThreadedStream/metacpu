#include <bin_tree.h>
#include <cassert>
#include <cstring>

#define CLEANUP_ASSERT(n, cond) \
if (!(cond)) {                  \
    free(n);                    \
    n = nullptr;                \
    assert(false);              \
}

static void testNode(Node* subject, const char* expectedName, const uint8_t expectedVal,
                     Node* expectedParent) {

    assert(subject != nullptr && "node is nullptr!!!");
    CLEANUP_ASSERT(subject, strcmp(subject->name, expectedName) == 0);
    CLEANUP_ASSERT(subject, subject->value == expectedVal);
    CLEANUP_ASSERT(subject, subject->parent == expectedParent);
}

static void compoundTest() {

    // inserting an element
    Node *root = nullptr;
    const char *name = "root";
    const uint8_t value = 0x69;
    root = insert(root, name, value);
    testNode(root, name, value, nullptr);

    const char* kid1_name = "kid1";
    const uint8_t kid1_value = 0x70;
    const auto kid1 = insert(root, kid1_name, kid1_value);
    testNode(kid1, kid1_name, kid1_value, root);

    const char* kid2_name = "kid2";
    const uint8_t kid2_value = 0x71;
    const auto kid2 = insert(root, kid2_name, kid2_value);
    testNode(kid2, kid2_name, kid2_value, kid1);

    Node* kid2_succ{nullptr};
    findIos(kid2, kid2_succ);
    assert(kid2_succ && "should have found a successor of kid2");
    assert(kid2_succ == root && "kid2's successor must be the root");

    const char* kid3_name = "zigmund";
    const uint8_t kid3_value = 0x72;
    const auto kid3 = insert(root, kid3_name, kid3_value);
    testNode(kid3, kid3_name, kid3_value, root);

    Node* kid3_succ{nullptr};
    findIos(kid3, kid3_succ);
    assert(!kid3_succ && "kid3 does not have a successor");

    const char* kid4_name = "watt";
    const uint8_t kid4_value = 0x73;
    const auto kid4 = insert(root, kid4_name, kid4_value);
    testNode(kid4, kid4_name, kid4_value, kid3);

    // finding an element
    auto supposed_to_find = find(root, kid1_name);
    assert(supposed_to_find && "find() supposed to find this node");
    assert(strcmp(supposed_to_find->name, kid1_name) == 0 && "names should have matched");

    auto not_supposed_to_find = find(root, "ahalai-mahalai");
    assert(!not_supposed_to_find && "should not have found a node");

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
