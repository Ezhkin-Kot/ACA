#include <iostream>

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node *left;
        Node *right;
        Node *parent;

        Node(int val)
            : data(val),
              left(nullptr),
              right(nullptr),
              parent(nullptr) {}
    };

    Node *root;

    Node *findMin(Node *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node *deleteNode(Node *node, int key) {
        if (!node) {
            return node;
        }

        if (key < node->data) {
            node->left = deleteNode(node->left, key);
            if (node->left) {
                node->left->parent = node;
            }
        } else if (key > node->data) {
            node->right = deleteNode(node->right, key);
            if (node->right) {
                node->right->parent = node;
            }
        } else {
            // Node has no children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Node has one right child
            else if (!node->left) {
                Node *temp = node->right;
                temp->parent = node->parent;
                delete node;
                return temp;
            }
            // Node has one left child
            else if (!node->right) {
                Node *temp = node->left;
                temp->parent = node->parent;
                delete node;
                return temp;
            }
            // Node has two children
            else {
                Node *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
                if (node->right) {
                    node->right->parent = node;
                }
            }
        }
        return node;
    }

    void inOrder(Node *node) {
        if (node) {
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node *node) {
        if (node) {
            std::cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->data << " ";
        }
    }

    void clearTree(Node *node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree()
        : root(nullptr) {}

    ~BinarySearchTree() { clearTree(root); }

    void insert(int x) {
        Node *n = new Node(x);

        // Tree is empty
        if (!root) {
            root = n;
            return;
        }

        Node *curr = root;
        while (curr) {
            if (x > curr->data) { // Right branch
                if (curr->right) {
                    curr = curr->right;
                } else {
                    n->parent = curr;
                    curr->right = n;
                    break;
                }
            } else if (x < curr->data) { // Left branch
                if (curr->left) {
                    curr = curr->left;
                } else {
                    n->parent = curr;
                    curr->left = n;
                    break;
                }
            } else {
                delete n;
                std::cout << "Element " << x << " already exists.\n";
                break;
            }
        }
    }

    bool search(int key) {
        Node *curr = root;
        while (curr != nullptr && curr->data != key) {
            if (key < curr->data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return curr != nullptr;
    }

    void remove(int key) {
        if (search(key)) {
            root = deleteNode(root, key);
            std::cout << "Element " << key << " deleted.\n";
        } else {
            std::cout << "Element " << key << " not found.\n";
        }
    }

    void inOrderTraversal() { inOrder(root); }

    void preOrderTraversal() { preOrder(root); }

    void postOrderTraversal() { postOrder(root); }
};

int main() {
    BinarySearchTree tree;
    int choice = -1;
    int value;

    while (choice != 0) {
        std::cout << "Choose an option:\n"
                  << "1. Add element\n"
                  << "2. Delete element\n"
                  << "3. Search element\n"
                  << "4. Print tree (symmetric traversal)\n"
                  << "5. Print tree (direct traversal)\n"
                  << "6. Print tree (reverse traversal)\n"
                  << "0. Exit\n"
                  << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> value;
            tree.insert(value);
            break;
        case 2:
            std::cout << "Enter value: ";
            std::cin >> value;
            tree.remove(value);
            break;
        case 3:
            std::cout << "Enter value: ";
            std::cin >> value;
            if (tree.search(value)) {
                std::cout << "Element " << value << " found.\n";
            } else {
                std::cout << "Element " << value << " not found.\n";
            }
            break;
        case 4:
            std::cout << "Symmetric traversal: ";
            tree.inOrderTraversal();
            std::cout << "\n";
            break;
        case 5:
            std::cout << "Direct traversal: ";
            tree.preOrderTraversal();
            std::cout << "\n";
            break;
        case 6:
            std::cout << "Reverse traversal: ";
            tree.postOrderTraversal();
            std::cout << "\n";
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
