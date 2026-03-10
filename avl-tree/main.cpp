#include <algorithm>
#include <iostream>

class AVLTree {
private:
    struct Node {
        int data;
        Node *left;
        Node *right;
        Node *parent;
        int height;

        Node(int val)
            : data(val),
              left(nullptr),
              right(nullptr),
              parent(nullptr),
              height(1) {}
    };

    Node *root;

    int getHeight(Node *node) { return node ? node->height : 0; }

    int getBalance(Node *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node *node) {
        if (node) {
            node->height =
                1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node *rotateRight(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2) {
            T2->parent = y;
        }
        x->parent = y->parent;
        y->parent = x;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2) {
            T2->parent = x;
        }
        y->parent = x->parent;
        x->parent = y;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *balanceNode(Node *node) {
        updateHeight(node);
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *findMin(Node *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node *insertNode(Node *node, int key, Node *parent = nullptr) {
        if (!node) {
            Node *newNode = new Node(key);
            newNode->parent = parent;
            return newNode;
        }

        if (key < node->data) {
            node->left = insertNode(node->left, key, node);
        } else if (key > node->data) {
            node->right = insertNode(node->right, key, node);
        } else {
            return node; // Duplicate keys not allowed
        }

        return balanceNode(node);
    }

    Node *deleteNode(Node *node, int key) {
        if (!node) {
            return node;
        }

        if (key < node->data) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->data) {
            node->right = deleteNode(node->right, key);
        } else {
            if (!node->left || !node->right) {
                Node *temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node) {
            return node;
        }
        return balanceNode(node);
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

    void printHelper(Node *node, std::string indent, bool last) {
        if (node != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "     ";
            } else {
                std::cout << "L----";
                indent += "|    ";
            }

            std::cout << node->data << " (h:" << node->height << ")"
                      << std::endl;

            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
    }

public:
    AVLTree()
        : root(nullptr) {}

    ~AVLTree() { clearTree(root); }

    void insert(int x) {
        if (search(x)) {
            std::cout << "Element " << x << " already exists.\n";
            return;
        }
        root = insertNode(root, x);
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

    void display() {
        if (root) {
            printHelper(root, "", true);
        } else {
            std::cout << "Tree is empty." << std::endl;
        }
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
                  << "4. Print tree (symmetric traversal)\n"
                  << "5. Print tree (direct traversal)\n"
                  << "6. Print tree (reverse traversal)\n"
                  << "7. Display tree structure\n"
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
        case 7:
            tree.display();
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
