=== AVL дерево

```cpp
class AVLTree {
private:
    struct Node {
        int value;
        int height;
        Node *left;
        Node *right;
        Node *parent;
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
```

== Затраты памяти

```cpp
struct Node {
    int value;   // 4 байта
    int height;  // 4 байта
    Node *left;  // 8 байт
    Node *right; // 8 байт
    Node *parent;
    Node(int value)
        : value(value),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(1) {}
};
```

Данные одного узла дерева занимают 32 байта памяти в 64-битной архитектуре.

Сложность всего бинарного дерева по памяти равна количеству узлов в этом дереве, то есть $O(n)$.

Для рекурсивных вызовов в алгоритмах обходов и удаления требуется стек вызовов, занимающий дополнительную память $O(h)$, где $h$ --- высота дерева. Так как AVL дерево сбалансировано, то эта дополнительная память ограничивается $O(log n)$.

== Сложность операций

=== Поиск элемента

```cpp
Node *findNode(Node *node, int value) {
    if (!node || value == node->value) // O(1)
        return node;
    // Рекурсивный поиск узла за O(h)
    return (value < node->value) ? findNode(node->left, value)
                                 : findNode(node->right, value);
}
```

Операция поиска требует прохода от корня до узла с искомым значением. Благодаря балансировке в AVL дереве высота ограничивается $log_2 n$.

Следовательно, поиск элемента имеет сложность $O(log n)$ как в среднем, так и в худшем случае.

В лучшем случае, когда искомый элемент находится в корне, сложность операции составляет $O(1)$.

=== Балансировка дерева

```cpp
// O(1)
void updateHeight(Node *node) {
    if (node)
        node->height =
            1 + std::max(height(node->left), height(node->right));
}

// O(1)
void rotateLeft(Node *node) {
    Node *child = node->right; // O(1)
    node->right = child->left; // O(1)

    if (node->right)
        node->right->parent = node; // O(1)

    child->parent = node->parent; // O(1)

    if (!node->parent)
        root = child; // O(1)
    else if (node == node->parent->left)
        node->parent->left = child; // O(1)
    else
        node->parent->right = child; // O(1)

    child->left = node;   // O(1)
    node->parent = child; // O(1)

    updateHeight(node);  // O(1)
    updateHeight(child); // O(1)
}

// O(1)
void rotateRight(Node *node) {
    Node *child = node->left;  // O(1)
    node->left = child->right; // O(1)

    if (node->left)
        node->left->parent = node; // O(1)

    child->parent = node->parent; // O(1)

    if (!node->parent)
        root = child; // O(1)
    else if (node == node->parent->right)
        node->parent->right = child; // O(1)
    else
        node->parent->left = child; // O(1)

    child->right = node;  // O(1)
    node->parent = child; // O(1)

    updateHeight(node);  // O(1)
    updateHeight(child); // O(1)
}

void rebalance(Node *node) {
    updateHeight(node);           // O(1)
    int bf = balanceFactor(node); // O(1)

    if (bf > 1) {
        if (balanceFactor(node->right) < 0)
            rotateRight(node->right); // O(1)
        rotateLeft(node);             // O(1)
    }
    else if (bf < -1) {
        if (balanceFactor(node->left) > 0)
            rotateLeft(node->left); // O(1)
        rotateRight(node);          // O(1)
    }
}
```

Все повороты и обновление высот выполняются за $O(1)$, так как просто меняют указатели.

=== Вставка элемента

```cpp
// O(log n)
void rebalanceUp(Node *node) {
    while (node) { // Цикл до корня за O(log n)
        Node *parent = node->parent; // O(1)
        rebalance(node);             // Балансировка одного узла за O(1)
        node = parent;               // O(1)
    }
}

void insertNode(Node *prev, int value) {
    if (value < prev->value) {
        if (!prev->left) {
            prev->left = new Node(value); // O(1)
            prev->left->parent = prev;    // O(1)
            // Балансировка до корня и обновление высот за O(log n)
            rebalanceUp(prev);
        } else {
            insertNode(prev->left, value); // Рекурсия за O(log n)
        }
    } else if (value > prev->value) {
        if (!prev->right) {
            prev->right = new Node(value); // O(1)
            prev->right->parent = prev;    // O(1)
            // Балансировка до корня и обновление высот за O(log n)
            rebalanceUp(prev);
        } else {
            insertNode(prev->right, value); // Рекурсия за O(log n)
        }
    }
}
```

При вставке в AVL дереве сначала происходит поиск места для нового элемента, начиная от корня, что занимает $O(log n)$. После добавления узла происходит проход от узла вверх до корня дерева с пересчётом высот каждого узла и балансировкой при перевесе одного из поддеревьев.

Суммарно операция вставки в AVL дереве имеет сложность $O(log n)$.

=== Удаление элемента

```cpp
void deleteNode(Node *node) {
    if (!node) // O(1)
        return;

    // У узла два потомка
    if (node->left && node->right) {
        Node *successor = findMin(node->right); // O(log n)
        node->value = successor->value;         // O(1)
        deleteNode(successor);                  // Рекурсивный вызов за O(log n)
        return;
    }

    // У узла один или ни одного потомка
    Node *child = node->left ? node->left : node->right; // O(1)
    Node *parent = node->parent;                         // O(1)

    if (child)
        child->parent = parent; // O(1)

    if (!parent) {
        root = child; // O(1)
    } else if (node == parent->left) {
        parent->left = child; // O(1)
    } else {
        parent->right = child; // O(1)
    }

    delete node; // O(1)

    // Балансировка до корня и обновление высот за O(log n)
    rebalanceUp(parent);
}
```

Поиск узла для удаления занимает $O(log n)$. Поиск его преемника (минимального узла в правом поддереве), если у узла было два потомка, занимает также $O(log n)$. После удаления узла происходит балансировка с подъёмом по всему дереву, пересчётом высот узлов и поворотами, если баланс нарушен, что также суммарно занимает $O(log n)$.

Таким образом операция удаления имеет сложность $O(log n)$.

=== Обход дерева

```cpp
void directBypass(Node *node) {
    if (node) {
        std::cout << node->value << "(h" << node->height << ")"
                  << (!node->parent ? "-root" : "") << " "; // Вывод узла за O(1)
        directBypass(node->left);  // Рекурсивный вызов для левого поддерева
        directBypass(node->right); // Рекурсивный вызов для правого поддерева
    }
}

void clear(Node *node) {
    if (!node)
        return;
    clear(node->left);  // Рекурсивный вызов для левого поддерева
    clear(node->right); // Рекурсивный вызов для правого поддерева
    delete node;        // Удаление узла
}
```

Обход дерева, а также его деструктор посещают каждый узел дерева ровно по одному разу, поэтому их временная сложность всегда составляет $O(n)$.
