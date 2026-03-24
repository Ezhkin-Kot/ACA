#include <iostream>

class AVLTree {
private:
    struct Node {
        int value;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        Node(int value)
            : value(value),
              left(nullptr),
              right(nullptr),
              parent(nullptr),
              height(1) {}
    };

    Node *root;

    int height(Node *node) { return node ? node->height : 0; }

    void updateHeight(Node *node) {
        if (node)
            node->height =
                1 + std::max(height(node->left), height(node->right));
    }

    int balanceFactor(Node *node) {
        return node ? height(node->right) - height(node->left) : 0;
    }

    void rotateLeft(Node *node) {
        Node *child = node->right;
        node->right = child->left;

        if (node->right)
            node->right->parent = node;

        child->parent = node->parent;

        if (!node->parent)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        child->left = node;
        node->parent = child;

        updateHeight(node);
        updateHeight(child);
    }

    void rotateRight(Node *node) {
        Node *child = node->left;
        node->left = child->right;

        if (node->left)
            node->left->parent = node;

        child->parent = node->parent;

        if (!node->parent)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;

        child->right = node;
        node->parent = child;

        updateHeight(node);
        updateHeight(child);
    }

    void rebalance(Node *node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        // Right-Right
        if (bf > 1) {
            // Right-Left
            if (balanceFactor(node->right) < 0)
                rotateRight(node->right);
            rotateLeft(node);
        }
        // Left-Left
        else if (bf < -1) {
            // Left-Right
            if (balanceFactor(node->left) > 0)
                rotateLeft(node->left);
            rotateRight(node);
        }
    }

    void rebalanceUp(Node *node) {
        while (node) {
            Node *parent = node->parent;
            rebalance(node);
            node = parent;
        }
    }

    void insertNode(Node *prev, int value) {
        if (value < prev->value) {
            if (!prev->left) {
                prev->left = new Node(value);
                prev->left->parent = prev;
                rebalanceUp(prev);
            } else {
                insertNode(prev->left, value);
            }
        } else if (value > prev->value) {
            if (!prev->right) {
                prev->right = new Node(value);
                prev->right->parent = prev;
                rebalanceUp(prev);
            } else {
                insertNode(prev->right, value);
            }
        }
    }

    Node *findMin(Node *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    void deleteNode(Node *node) {
        if (!node)
            return;

        // Two children
        if (node->left && node->right) {
            Node *successor = findMin(node->right);
            node->value = successor->value;
            deleteNode(successor);
            return;
        }

        // One child
        Node *child = node->left ? node->left : node->right;
        Node *parent = node->parent;

        if (child)
            child->parent = parent;

        if (!parent) {
            root = child;
        } else if (node == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        delete node;

        rebalanceUp(parent);
    }

    Node *findNode(Node *node, int value) {
        if (!node || value == node->value)
            return node;
        return (value < node->value) ? findNode(node->left, value)
                                     : findNode(node->right, value);
    }

    void directBypass(Node *node) {
        if (node) {
            std::cout << node->value << "(h" << node->height << ")"
                      << (!node->parent ? "-root" : "") << " ";
            directBypass(node->left);
            directBypass(node->right);
        }
    }

    void clear(Node *node) {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree()
        : root(nullptr) {}

    ~AVLTree() { clear(root); }

    void insert(int value) {
        if (!root) {
            root = new Node(value);
        } else {
            insertNode(root, value);
        }
    }

    void remove(int value) {
        Node *node = findNode(root, value);
        if (node) {
            deleteNode(node);
            std::cout << "Element " << value << " deleted.\n";
        } else {
            std::cout << "Element " << value << " not found.\n";
        }
    }

    bool search(int value) { return findNode(root, value) != nullptr; }

    void directBypass() {
        directBypass(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree tree;
    int choice = -1;
    int value;

    while (choice != 0) {
        std::cout << "Choose an option:\n"
                  << "1. Add element\n"
                  << "2. Delete element\n"
                  << "3. Search element\n"
                  << "4. Print tree (direct traversal)\n"
                  << "0. Exit\n"
                  << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> value;
            tree.insert(value);
            std::cout << "Direct traversal:\n\n";
            tree.directBypass();
            break;
        case 2:
            std::cout << "Enter value: ";
            std::cin >> value;
            tree.remove(value);
            break;
        case 3:
            std::cout << "Enter value: ";
            std::cin >> value;
            if (tree.search(value))
                std::cout << "Element " << value << " found.\n";
            else
                std::cout << "Element " << value << " not found.\n";
            break;
        case 4:
            std::cout << "Direct traversal:\n\n";
            tree.directBypass();
            break;
        case 0:
            std::cout << "Exiting.\n";
            break;
        default:
            std::cout << "Invalid input.\n";
        }
    }

    return 0;
}
