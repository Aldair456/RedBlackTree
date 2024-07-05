#include <iostream>
#include <vector>
#include "RedBlackTree.h"

void testInsertAndBalance() {
    RedBlackTree tree;
    std::vector<int> keys = {30, 20, 40, 10, 25, 35, 50};

    for (int key : keys) {
        tree.insert(key);
    }

    // Verifica que todos los nodos estén presentes
    for (int key : keys) {
        Node* result = tree.search(key);
        if (result != nullptr && result->data == key) {
            std::cout << "Insert and Balance test passed for " << key << std::endl;
        } else {
            std::cout << "Insert and Balance test failed for " << key << std::endl;
        }
    }
}

void testSearchFunction() {
    RedBlackTree tree;
    std::vector<int> keys = {30, 20, 40, 10, 25, 35, 50};

    for (int key : keys) {
        tree.insert(key);
    }

    for (int key : keys) {
        Node* result = tree.search(key);
        if (result != nullptr && result->data == key) {
            std::cout << "Search test passed for " << key << std::endl;
        } else {
            std::cout << "Search test failed for " << key << std::endl;
        }
    }

    // Verifica búsqueda de nodos no existentes
    std::vector<int> nonExistentKeys = {5, 15, 55};
    for (int key : nonExistentKeys) {
        Node* result = tree.search(key);
        if (result == nullptr) {
            std::cout << "Search test passed for non-existent key " << key << std::endl;
        } else {
            std::cout << "Search test failed for non-existent key " << key << std::endl;
        }
    }
}
void testInsertAndDeleteAlternating() {
    RedBlackTree tree;

    // Inserta y elimina nodos alternadamente
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.remove(20);
    tree.insert(40);
    tree.remove(10);
    tree.insert(50);

    // Verifica que los nodos correctos estén presentes
    std::vector<int> expectedKeys = {30, 40, 50};
    for (int key : expectedKeys) {
        Node* result = tree.search(key);
        if (result != nullptr && result->data == key) {
            std::cout << "Insert and Delete Alternating test passed for " << key << std::endl;
        } else {
            std::cout << "Insert and Delete Alternating test failed for " << key << std::endl;
        }
    }

    // Verifica que los nodos eliminados no estén presentes
    std::vector<int> deletedKeys = {10, 20};
    for (int key : deletedKeys) {
        Node* result = tree.search(key);
        if (result == nullptr) {
            std::cout << "Insert and Delete Alternating test passed for deleted key " << key << std::endl;
        } else {
            std::cout << "Insert and Delete Alternating test failed for deleted key " << key << std::endl;
        }
    }
}

void runAllTests() {
    testInsertAndBalance();
    testSearchFunction();
    testInsertAndDeleteAlternating();

}

int main() {
    runAllTests();
    return 0;
}
