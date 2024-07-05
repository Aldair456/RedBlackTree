#include "RedBlackTree.h"


void RedBlackTree::rotateLeft(Node *&node) {
    Node* node_right = node->right;
    node->right = node_right->left;

    if (node->right != nullptr)
        node->right->parent = node;

    node_right->parent = node->parent;

    if (node->parent == nullptr)
        root = node_right;
    else if (node == node->parent->left)
        node->parent->left = node_right;
    else
        node->parent->right = node_right;

    node_right->left = node;
    node->parent = node_right;
}
RedBlackTree::~RedBlackTree() {
    // Llamar a una función auxiliar para eliminar todos los nodos
    deleteTree(root);
}
void RedBlackTree::deleteTree(Node *node) {
    if (node == nullptr) {
        return;
    }

    // Eliminar recursivamente los hijos izquierdo y derecho
    deleteTree(node->left);
    deleteTree(node->right);

    // Eliminar el nodo actual
    delete node;
}
void RedBlackTree::rotateRight(Node *&node) {
    Node* node_left = node->left;
    node->left = node_left->right;

    if (node->left != nullptr)
        node->left->parent = node;

    node_left->parent = node->parent;

    if (node->parent == nullptr)
        root = node_left;
    else if (node == node->parent->left)
        node->parent->left = node_left;
    else
        node->parent->right = node_left;

    node_left->right = node;
    node->parent = node_left;
}

void RedBlackTree::fixViolation(Node *node) {
    Node* parent_node = nullptr;
    Node* grand_parent_node = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent_node = node->parent;
        grand_parent_node = node->parent->parent;

        if (parent_node == grand_parent_node->left) {
            Node* uncle_node = grand_parent_node->right;

            if (uncle_node != nullptr && uncle_node->color == RED) {
                grand_parent_node->color = RED;
                parent_node->color = BLACK;
                uncle_node->color = BLACK;
                node = grand_parent_node;
            } else {
                if (node == parent_node->right) {
                    rotateLeft(parent_node);
                    node = parent_node;
                    parent_node = node->parent;
                }

                rotateRight(grand_parent_node);
                std::swap(parent_node->color, grand_parent_node->color);
                node = parent_node;
            }
        } else {
            Node* uncle_node = grand_parent_node->left;

            if (uncle_node != nullptr && uncle_node->color == RED) {
                grand_parent_node->color = RED;
                parent_node->color = BLACK;
                uncle_node->color = BLACK;
                node = grand_parent_node;
            } else {
                if (node == parent_node->left) {
                    rotateRight(parent_node);
                    node = parent_node;
                    parent_node = node->parent;
                }

                rotateLeft(grand_parent_node);
                std::swap(parent_node->color, grand_parent_node->color);
                node = parent_node;
            }
        }
    }

    root->color = BLACK;
}

void RedBlackTree::BSTInsert(Node *&root, Node *node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    if (node->data < root->data) {
        if (root->left != nullptr)
            BSTInsert(root->left, node);
        else {
            root->left = node;
            node->parent = root;
        }
    } else if (node->data > root->data) {
        if (root->right != nullptr)
            BSTInsert(root->right, node);
        else {
            root->right = node;
            node->parent = root;
        }
    }
}

void RedBlackTree::DeleteViolation(Node *&node, Node *parent) {
   while (node != root && (node == nullptr || node->color == BLACK)) {
        if (node == parent->left) {
            Node *sibling = parent->right;

            if (sibling == nullptr) {
                break;
            }

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateLeft(parent);
                sibling = parent->right;
            }

            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = parent->parent;  // Actualización del padre
            } else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = parent->right;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right != nullptr)
                    sibling->right->color = BLACK;
                rotateLeft(parent);
                node = root;
                break;  // Salir del bucle una vez que se alcanza la raíz
            }
        } else {
            Node *sibling = parent->left;

            if (sibling == nullptr) {
                break;
            }

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateRight(parent);
                sibling = parent->left;
            }

            if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                (sibling->left == nullptr || sibling->left->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = parent->parent;  // Actualización del padre
            } else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = parent->left;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left != nullptr)
                    sibling->left->color = BLACK;
                rotateRight(parent);
                node = root;
                break;  // Salir del bucle una vez que se alcanza la raíz
            }
        }
    }

    if (node != nullptr)
        node->color = BLACK;
}

void RedBlackTree::transplant(Node *node, Node *node_change) {
    if (node->parent == nullptr)
        root = node_change;
    else if (node == node->parent->left)
        node->parent->left = node_change;
    else
        node->parent->right = node_change;

    if (node_change != nullptr)
        node_change->parent = node->parent;
}
void RedBlackTree::deleteNode(Node *node) {
    if (node == nullptr)
        return;

    Node *node_successor;
    Node *node_evaluate;
    Color node_original_color = node->color;

    if (node->left == nullptr && node->right == nullptr) {
        // Caso 1: El nodo no tiene hijos
        node_evaluate = nullptr;
        if (node == root)
            root = nullptr;  // Si es la raíz, se establece a nullptr
        else
            transplant(node, node_evaluate);
    } else if (node->left == nullptr || node->right == nullptr) {
        // Caso 2: El nodo tiene solo un hijo
        node_evaluate = (node->left != nullptr) ? node->left : node->right;
        transplant(node, node_evaluate);
    } else {
        // Caso 3: El nodo tiene dos hijos
        node_successor = minimum(node->right);
        node_original_color = node_successor->color;
        node_evaluate = node_successor->right;

        if (node_successor->parent == node) {
            if (node_evaluate != nullptr)
                node_evaluate->parent = node_successor;
        } else {
            transplant(node_successor, node_successor->right);
            node_successor->right = node->right;
            if (node_successor->right != nullptr)
                node_successor->right->parent = node_successor;
        }

        transplant(node, node_successor);
        node_successor->left = node->left;
        if (node_successor->left != nullptr)
            node_successor->left->parent = node_successor;
        node_successor->color = node->color;
    }

    delete node;  // Liberar la memoria del nodo eliminado

    // Verificar y corregir las violaciones del árbol rojo-negro después de la eliminación
    if (node_original_color == BLACK) {
        Node *parent = (node_evaluate != nullptr) ? node_evaluate->parent : nullptr;
        DeleteViolation(node_evaluate, parent);
    }
}




Node* RedBlackTree::search(Node *root, int key) {
    if (root == nullptr || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void RedBlackTree::insert(int data) {
    Node* node = new Node(data);
    BSTInsert(root, node);

    fixViolation(node);
}

void RedBlackTree::remove(int data) {
    Node *node = search(root, data);
    if (node == nullptr) {
        std::cout << "No está la clave en el árbol" << std::endl;
        return;
    }

    deleteNode(node);
}

Node* RedBlackTree::search(int key) {
    return search(root, key);
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
