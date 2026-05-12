= Красно-чёрное дерево

```cpp
#define BLACK 0
#define RED 1

class RBTree {
private:
    struct Node {
        int value;
        bool color; // 0 - black, 1 - red
        Node *left;
        Node *right;
        Node *parent;
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
```

== Затраты памяти

```cpp
struct Node {
    int value;    // 4 байта
    bool color;   // 1 байт
    Node *left;   // 8 байт
    Node *right;  // 8 байт
    Node *parent; // 8 байт
    Node(int value)
        : value(value),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(RED) {}
};
```

Данные одного узла дерева занимают 29 байт памяти в 64-битной архитектуре. Так как компилятор производит выравнивание данных в структурах, то все поля будут выравнены по 8 байт, и тогда реальный объём памяти для одного узла составит 32 байта.

Сложность всего бинарного дерева по памяти равна количеству узлов в этом дереве, то есть $O(n)$.

Для рекурсивных вызовов в алгоритмах обходов и удаления требуется стек вызовов, занимающий дополнительную память $O(h)$, где $h$ --- высота дерева.

== Сложность операций

=== Поиск элемента

```cpp
Node *findNode(Node *node, int value) {
    if (node == nil || value == node->value) // O(n)
        return node;
    // Рекурсивный поиск узла за O(h)
    return (value < node->value) ? findNode(node->left, value)
                                 : findNode(node->right, value);
}
```

Операция поиска требует прохода от корня до узла с искомым значением. Но в отличие от обычного дерева бинарного поиска, в красно-чёрном дереве его высота никогда не превышает $2 log_2 n$.

Следовательно, поиск элемента имеет сложность $O(log n)$ как в среднем, так и в худшем случае.

В лучшем случае, когда искомый элемент находится в корне, сложность операции составляет $O(1)$.

=== Вставка элемента и балансировка дерева

```cpp
// Правый поворот за O(1)
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

// Левый поворот за O(1)
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
        node->color = BLACK; // O(1)
    else
        insertCase2(node);
}

void insertCase2(Node *node) {
    if (node->parent->color == RED)
        insertCase3(node);
}

void insertCase3(Node *node) {
    Node *u = uncle(node);       // O(1)
    Node *g = grandparent(node); // O(1)

    if (u != nil && u->color == RED) {
        node->parent->color = BLACK; // O(1)
        u->color = BLACK;            // O(1)
        g->color = RED;              // O(1)
        insertCase1(g);              // Рекурсия за O(log n)
    } else {
        insertCase4(node);
    }
}

void insertCase4(Node *node) {
    Node *g = grandparent(node); // O(1)

    if (node == node->parent->right && node->parent == g->left) {
        rotateLeft(node->parent); // O(1)
        node = node->left;
    } else if (node == node->parent->left && node->parent == g->right) {
        rotateRight(node->parent); // O(1)
        node = node->right;
    }
    insertCase5(node);
}

void insertCase5(Node *node) {
    Node *g = grandparent(node); // O(1)
    node->parent->color = BLACK; // O(1)
    g->color = RED;              // O(1)

    if (node == node->parent->left && node->parent == g->left)
        rotateRight(g); // O(1)
    else
        rotateLeft(g); // O(1)
}

void insertNode(Node *prev, int value) {
    if (value < prev->value) {
        if (prev->left == nil) { // O(1)
            prev->left = new Node(value);
            prev->left->left = prev->left->right = nil;
            prev->left->parent = prev;
            insertCase1(prev->left);
        } else { // Рекурсия
            insertNode(prev->left, value);
        }
    } else if (value > prev->value) {
        if (prev->right == nil) { // O(1)
            prev->right = new Node(value);
            prev->right->left = prev->right->right = nil;
            prev->right->parent = prev;
            insertCase1(prev->right);
        } else { // Рекурсия
            insertNode(prev->right, value);
        }
    }
}
```

При вставке в красно-чёрном дереве сначала происходит поиск места для нового элемента, начиная от корня, за $O(log n)$, затем, если свойства красно-чёрного дерева были нарушены, происходит балансировка, которая состоит из двух основных операций: перекрашивание и повороты.

В худшем случае происходит перекрашивание узлов и подъём вверх по дереву до корня, что занимает $O(log n)$.

Также суммарно при вставке выполняется не более двух поворотов, каждый из которых занимает $O(1)$.
В итоге операция вставки имеет сложность $O(log n)$.

=== Удаление элемента и балансировка дерева

```cpp
void deleteCase1(Node *node) {
    if (node->parent == nil)
        return;
    deleteCase2(node);
}

void deleteCase2(Node *node) {
    Node *s = sibling(node); // O(1)

    if (s != nil && s->color == RED) {
        node->parent->color = RED; // O(1)
        s->color = BLACK;          // O(1)
        if (node == node->parent->left)
            rotateLeft(node->parent); // O(1)
        else
            rotateRight(node->parent); // O(1)
    }
    deleteCase3(node);
}

void deleteCase3(Node *node) {
    Node *s = sibling(node); // O(1)

    if (node->parent->color == BLACK && (s == nil || s->color == BLACK) &&
        (s == nil || s->left == nil || s->left->color == BLACK) &&
        (s == nil || s->right == nil || s->right->color == BLACK)) {
        if (s != nil)
            s->color = RED; // O(1)
        deleteCase1(node->parent); // Рекурсия за O(h)
    } else {
        deleteCase4(node);
    }
}

void deleteCase4(Node *node) {
    Node *s = sibling(node); // O(1)

    if (node->parent->color == RED && (s == nil || s->color == BLACK) &&
        (s == nil || s->left == nil || s->left->color == BLACK) &&
        (s == nil || s->right == nil || s->right->color == BLACK)) {
        if (s != nil)
            s->color = RED;          // O(1)
        node->parent->color = BLACK; // O(1)
    } else {
        deleteCase5(node);
    }
}

void deleteCase5(Node *node) {
    Node *s = sibling(node); // O(1)

    if (s != nil && s->color == BLACK) {
        if (node == node->parent->left &&
            (s->right == nil || s->right->color == BLACK) &&
            (s->left != nil && s->left->color == RED)) {
            s->color = RED;         // O(1)
            s->left->color = BLACK; // O(1)
            rotateRight(s);         // O(1)
        } else if (node == node->parent->right &&
                   (s->left == nil || s->left->color == BLACK) &&
                   (s->right != nil && s->right->color == RED)) {
            s->color = RED;          // O(1)
            s->right->color = BLACK; // O(1)
            rotateLeft(s);           // O(1)
        }
    }
    deleteCase6(node);
}

void deleteCase6(Node *node) {
    Node *s = sibling(node); // O(1)
    if (s == nil)            // O(1)
        return;

    s->color = node->parent->color; // O(1)
    node->parent->color = BLACK;    // O(1)

    if (node == node->parent->left) {
        if (s->right != nil)
            s->right->color = BLACK; // O(1)
        rotateLeft(node->parent);    // O(1)
    } else {
        if (s->left != nil)
            s->left->color = BLACK; // O(1)
        rotateRight(node->parent);  // O(1)
    }
}

void deleteNode(Node *node) {
    if (!node || node == nil) // O(1)
        return;

    // У узла два потомка
    if (node->left != nil && node->right != nil) {
        Node *successor = node->right; // O(1)
        while (successor->left != nil) // O(h)
            successor = successor->left;

        node->value = successor->value; // O(1)
        deleteNode(successor);          // Рекурсивный вызов за O(h)
        return;
    }

    // У узла один потомок
    if (node->left != nil || node->right != nil) {
        Node *ch = (node->left != nil) ? node->left : node->right; // O(1)
        replace(node);                                             // O(1)

        if (node->color == BLACK) {
            if (ch->color == RED)
                ch->color = BLACK; // O(1)
            else
                deleteCase1(ch); // O(h)
        }
        delete node; // O(1)
        return;
    }

    // У узла нет потомков
    if (node->color == BLACK)
        deleteCase1(node); // O(h)

    // Удаление связей за O(1)
    if (node->parent == nil) {
        root = nil;
    } else if (node == node->parent->left) {
        node->parent->left = nil;
    } else {
        node->parent->right = nil;
    }

    delete node; // O(1)
}

void replace(Node *node) {
    Node *ch = (node->left != nil) ? node->left : node->right; // O(1)
    ch->parent = node->parent;                                 // O(1)

    // Обновление указателей за O(1)
    if (node->parent == nil) {
        root = ch;
    } else if (node == node->parent->left) {
        node->parent->left = ch;
    } else {
        node->parent->right = ch;
    }
}
```

Поиск узла и его преемника занимает $O(log n)$, после чего выполняется балансировка дерева, которая в худшем случае занимает также $O(log n)$.

Таким образом операция удаления имеет сложность $O(log n)$.

=== Обход дерева

```cpp
void directBypass(Node *node) {
    if (node != nil) {
        std::cout << node->value << (node->color == RED ? "R" : "B")
                  << (node->parent == nil ? "-root" : "") << " "; // Вывод узла за O(1)
        directBypass(node->left);  // Рекурсивный вызов для левого поддерева
        directBypass(node->right); // Рекурсивный вызов для правого поддерева
    }
}

void clear(Node *node) {
    if (node == nil)
        return;
    clear(node->left);  // Рекурсивный вызов для левого поддерева
    clear(node->right); // Рекурсивный вызов для правого поддерева
    delete node;        // Удаление узла за O(1)
}
```

Обход дерева, а также его деструктор посещают каждый узел дерева ровно по одному разу, поэтому их временная сложность всегда составляет $O(n)$.
