#include <iostream>

#define BLACK 0
#define RED 1

class RBTree {
private:
    struct Node {
        int value;
        Node *left;
        Node *right;
        Node *parent;
        bool color; // 0 - black, 1 - red
        Node(int value)
            : value(value),
              left(nullptr),
              right(nullptr),
              parent(nullptr),
              color(RED) {}
    };

    Node *root;
    Node *nil; // Sentinel node for leafs

    Node *grandparent(Node *node) {
        if (node->parent != nil && node->parent->parent != nil)
            return node->parent->parent;
        return nil;
    }

    Node *uncle(Node *node) {
        Node *g = grandparent(node);
        if (g == nil)
            return nil;
        return (node->parent == g->left) ? g->right : g->left;
    }

    Node *sibling(Node *node) {
        if (node && node->parent && node->parent != nil) {
            return (node == node->parent->left) ? node->parent->right
                                                : node->parent->left;
        }
        return nil;
    }

    void rotateLeft(Node *node) {
        Node *child = node->right;
        node->right = child->left;

        if (node->right != nil)
            node->right->parent = node;

        child->parent = node->parent;

        if (node->parent == nil)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        child->left = node;
        node->parent = child;
    }

    void rotateRight(Node *node) {
        Node *child = node->left;
        node->left = child->right;

        if (node->left != nil)
            node->left->parent = node;

        child->parent = node->parent;

        if (node->parent == nil)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;

        child->right = node;
        node->parent = child;
    }

    void insertCase1(Node *node) {
        if (node->parent == nil)
            node->color = BLACK;
        else
            insertCase2(node);
    }

    void insertCase2(Node *node) {
        if (node->parent->color == RED)
            insertCase3(node);
    }

    void insertCase3(Node *node) {
        Node *u = uncle(node);
        Node *g = grandparent(node);

        if (u != nil && u->color == RED) {
            node->parent->color = BLACK;
            u->color = BLACK;
            g->color = RED;
            insertCase1(g);
        } else {
            insertCase4(node);
        }
    }

    void insertCase4(Node *node) {
        Node *g = grandparent(node);

        if (node == node->parent->right && node->parent == g->left) {
            rotateLeft(node->parent);
            node = node->left;
        } else if (node == node->parent->left && node->parent == g->right) {
            rotateRight(node->parent);
            node = node->right;
        }
        insertCase5(node);
    }

    void insertCase5(Node *node) {
        Node *g = grandparent(node);
        node->parent->color = BLACK;
        g->color = RED;

        if (node == node->parent->left && node->parent == g->left)
            rotateRight(g);
        else
            rotateLeft(g);
    }

    void insertNode(Node *prev, int value) {
        if (value < prev->value) {
            if (prev->left == nil) {
                prev->left = new Node(value);
                prev->left->left = prev->left->right = nil;
                prev->left->parent = prev;
                insertCase1(prev->left);
            } else {
                insertNode(prev->left, value);
            }
        } else if (value > prev->value) {
            if (prev->right == nil) {
                prev->right = new Node(value);
                prev->right->left = prev->right->right = nil;
                prev->right->parent = prev;
                insertCase1(prev->right);
            } else {
                insertNode(prev->right, value);
            }
        }
    }

    void deleteCase1(Node *node) {
        if (node->parent == nil)
            return; // Node is root, nothing to do
        deleteCase2(node);
    }

    void deleteCase2(Node *node) {
        Node *s = sibling(node);

        if (s != nil && s->color == RED) {
            node->parent->color = RED;
            s->color = BLACK;
            if (node == node->parent->left)
                rotateLeft(node->parent);
            else
                rotateRight(node->parent);
        }
        deleteCase3(node);
    }

    void deleteCase3(Node *node) {
        Node *s = sibling(node);

        if (node->parent->color == BLACK && (s == nil || s->color == BLACK) &&
            (s == nil || s->left == nil || s->left->color == BLACK) &&
            (s == nil || s->right == nil || s->right->color == BLACK)) {
            if (s != nil)
                s->color = RED;
            deleteCase1(node->parent);
        } else {
            deleteCase4(node);
        }
    }

    void deleteCase4(Node *node) {
        Node *s = sibling(node);

        if (node->parent->color == RED && (s == nil || s->color == BLACK) &&
            (s == nil || s->left == nil || s->left->color == BLACK) &&
            (s == nil || s->right == nil || s->right->color == BLACK)) {
            if (s != nil)
                s->color = RED;
            node->parent->color = BLACK;
        } else {
            deleteCase5(node);
        }
    }

    void deleteCase5(Node *node) {
        Node *s = sibling(node);

        if (s != nil && s->color == BLACK) {
            if (node == node->parent->left &&
                (s->right == nil || s->right->color == BLACK) &&
                (s->left != nil && s->left->color == RED)) {
                s->color = RED;
                s->left->color = BLACK;
                rotateRight(s);
            } else if (node == node->parent->right &&
                       (s->left == nil || s->left->color == BLACK) &&
                       (s->right != nil && s->right->color == RED)) {
                s->color = RED;
                s->right->color = BLACK;
                rotateLeft(s);
            }
        }
        deleteCase6(node);
    }

    void deleteCase6(Node *node) {
        Node *s = sibling(node);
        if (s == nil)
            return;

        s->color = node->parent->color;
        node->parent->color = BLACK;

        if (node == node->parent->left) {
            if (s->right != nil)
                s->right->color = BLACK;
            rotateLeft(node->parent);
        } else {
            if (s->left != nil)
                s->left->color = BLACK;
            rotateRight(node->parent);
        }
    }

    void deleteNode(Node *node) {
        if (!node || node == nil)
            return;

        // Node with two children
        if (node->left != nil && node->right != nil) {
            Node *successor = node->right;
            while (successor->left != nil)
                successor = successor->left;

            node->value = successor->value;
            deleteNode(successor);
            return;
        }

        // Node with one child
        if (node->left != nil || node->right != nil) {
            Node *ch = (node->left != nil) ? node->left : node->right;
            replace(node);

            if (node->color == BLACK) {
                if (ch->color == RED)
                    ch->color = BLACK;
                else
                    deleteCase1(ch);
            }
            delete node;
            return;
        }

        // Node is leaf
        if (node->color == BLACK)
            deleteCase1(node);

        // Node is root
        if (node->parent == nil) {
            root = nil;
        } else if (node == node->parent->left) {
            node->parent->left = nil;
        } else {
            node->parent->right = nil;
        }

        delete node;
    }

    void replace(Node *node) {
        Node *ch = (node->left != nil) ? node->left : node->right;
        ch->parent = node->parent;

        if (node->parent == nil) {
            root = ch;
        } else if (node == node->parent->left) {
            node->parent->left = ch;
        } else {
            node->parent->right = ch;
        }
    }

    Node *findNode(Node *node, int value) {
        if (node == nil || value == node->value)
            return node;
        return (value < node->value) ? findNode(node->left, value)
                                     : findNode(node->right, value);
    }

    void directBypass(Node *node) {
        if (node != nil) {
            std::cout << node->value << (node->color == RED ? "R" : "B")
                      << (node->parent == nil ? "-root" : "") << " ";
            directBypass(node->left);
            directBypass(node->right);
        }
    }

    void clear(Node *node) {
        if (node == nil)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    RBTree() {
        nil = new Node(0);
        nil->color = BLACK;
        nil->left = nil->right = nil->parent = nullptr;
        root = nil;
    }

    ~RBTree() {
        clear(root);
        delete nil;
    }

    void insert(int value) {
        if (root == nil) {
            root = new Node(value);
            root->color = BLACK;
            root->left = root->right = nil;
            root->parent = nil;
        } else {
            insertNode(root, value);
        }
    }

    Node *find(int value) { return findNode(root, value); }

    void remove(int value) {
        Node *node = find(value);
        if (node != nil) {
            deleteNode(node);
            std::cout << "Element " << value << " deleted.\n";
        } else {
            std::cout << "Element " << value << " not found.\n";
        }
    }

    bool search(int value) { return find(value) != nil; }

    void directBypass() {
        directBypass(root);
        std::cout << std::endl;
    }
};

int main() {
    RBTree tree;
    int choice = -1;
    int value;

    while (choice != 0) {
        std::cout << "Choose an option:\n"
                  << "1. Add element\n"
                  << "2. Delete element\n"
                  << "3. Search element\n"
                  << "4. Print tree (symmetric traversal)\n"
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
