= Бинарное дерево поиска

```cpp
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
```

== Затраты памяти

```cpp
struct Node {
    int data;     // 4 байта
    Node *left;   // 8 байт
    Node *right;  // 8 байт
    Node *parent; // 8 байт

    Node(int val)
        : data(val),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
};
```

Данные одного узла дерева занимают 28 байт памяти в 64-битной архитектуре. Так как компилятор производит выравнивание данных в структурах, то все поля будут выставлены по 8 байт, и тогда реальный объём памяти для одного узла составит 32 байта.

Сложность всего бинарного дерева по памяти равна количеству узлов в этом дереве, то есть $O(n)$.

Для рекурсивных вызовов в алгоритмах обходов и удаления требуется стек вызовов, занимающий дополнительную память $O(h)$, где $h$ --- высота дерева.

== Сложность операций

=== Поиск и вставка элемента

```cpp
void insert(int x) {
    Node *n = new Node(x); // O(1)

    if (!root) { // O(1)
        root = n;
        return;
    }

    Node *curr = root;
    while (curr) { // O(h), где h --- высота дерева
        if (x > curr->data) {
            if (curr->right) {
                curr = curr->right;
            } else {
                n->parent = curr;
                curr->right = n;
                break;
            }
        } else if (x < curr->data) {
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

    // O(h), где h --- высота дерева
    while (curr != nullptr && curr->data != key) {
        if (key < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr != nullptr;
}
```

Обе операции в среднем случае проходят путь от корня до листа.

В лучшем и среднем случае дерево является сбалансированным, то есть его высота $h = log_2 n$, соответственно временная сложность вставки составляет $O(log n)$.

Сложность поиска в среднем случае также равна $O(log n)$, но в лучшем, когда искомый элемент в корне, может занимать всего $O(1)$.

В худшем случае бинарное дерево вырождается в список, где высота $h = n$, соответственно временная сложность возрастает до $O(n)$.

=== Удаление узла

```cpp
Node *deleteNode(Node *node, int key) {
    if (!node) { // O(1)
        return node;
    }

    // Поиск узла за O(h)
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
        // Узел не имеет детей (лист) - O(1)
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        // Узел имеет одного ребёнка - O(1)
        else if (!node->left) {
            Node *temp = node->right;
            temp->parent = node->parent;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Node *temp = node->left;
            temp->parent = node->parent;
            delete node;
            return temp;
        }
        // Узел имеет двух потомков
        else {
            Node *temp = findMin(node->right); // Поиск минимума за O(h)
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data); // Рекурсия - O(h)
            if (node->right) {
                node->right->parent = node;
            }
        }
    }
    return node;
}
```

Трудоёмкость складывается из поиска узла и возможного поиска его преемника (минимального узла в правом поддереве).

В лучшем и среднем случаях сложность удаления составляет $O(log n)$, а в худшем $O(n)$.

=== Обходы дерева

```cpp
void inOrder(Node *node) {
    if (node) {
        inOrder(node->left);            // Рекурсивный вызов для левого поддерева
        std::cout << node->data << " "; // Вывод узла за O(1)
        inOrder(node->right);           // Рекурсивный вызов для правого поддерева
    }
}

void preOrder(Node *node) {
    if (node) {
        std::cout << node->data << " "; // Вывод узла за O(1)
        preOrder(node->left);           // Рекурсивный вызов для левого поддерева
        preOrder(node->right);          // Рекурсивный вызов для правого поддерева
    }
}

void postOrder(Node *node) {
    if (node) {
        postOrder(node->left);          // Рекурсивный вызов для левого поддерева
        postOrder(node->right);         // Рекурсивный вызов для правого поддерева
        std::cout << node->data << " "; // Вывод узла за O(1)
    }
}
```

Все виды обходов, а также деструктор дерева `clearTree` посещают каждый узел дерева ровно по одному разу, поэтому их временная сложность всегда составляет $O(n)$.

== Особенности

Сложность операций поиска, вставки и удаления элементов в бинарном дереве зависят от его высоты, поэтому работа с деревом происходит тем быстрее, чем лучше оно сбалансировано. В случае обычного бинарного дерева поиска без механизмов балансировки его эффективность зависит от порядка добавления элементов.

Симметричный обход дерева позволяет получить все его элементы в отсортированном по возрастанию порядке за $O(n)$.
