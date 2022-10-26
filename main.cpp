#include <iostream>
#include <windows.h>

using namespace std;

struct node {                   // структура для представления узлов дерева
    int key;                    // ключ
    unsigned int height;        // высота поддерева с корнем в данном узле
    node *left;                 // указатель на левое поддерево
    node *right;                // указатель на правое поддерево

    node(int k) {
        key = k;
        left = right = 0;
        height = 1;
    }
};

unsigned int height(node *p) {              // Возврат высоты
    return p ? p->height : 0;
}

int bfactor(node *p) {                      // Вычисление разности между высотами левого и правого поддерева
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {                   // Восстановление корректного значения поля height заданного узла
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) {                // Правый поворот вокруг p
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) {                 // Левый поворот вокруг q
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) {                    // Балансировка узла p
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0) {
            p->right = rotateright(p->right);
        }
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0) {
            p->left = rotateleft(p->left);
        }
        return rotateright(p);
    }
    return p; // Балансировка не нужна
}

node *insert(node *p, int k) {              // вставка ключа k в дерево с корнем p
    if (!p) return new node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void inorder(node *p) {                    // Симметричный обход
    if (p != NULL) {
        inorder(p->left);
        cout << p->key << " ";
        inorder(p->right);
    }
}

int height_tree(node *p) {              // Поиск высоты дерева
    if (p == NULL) return 0;
    else if (p->left == NULL && p->right == NULL) return 0;
    else if (height_tree(p->left) > height_tree(p->right)) {
        return height_tree(p->left) + 1;
    } else {
        return height_tree(p->right) + 1;
    }
}

int search_value(node *p, int k) {      // Поиск длины пути от корня до заданного значения
    if (p->key == k) return 0;
    else if (k < p->key) return search_value(p->left, k) + 1;
    else return search_value(p->right, k) + 1;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    node *p = NULL;
    int n;
    int s;
    int sum = 0;
    for (int i = 0; i < 6; i++) {
        cin >> s;
        p = insert(p, s);
    }
    inorder(p);
    cout << endl << search_value(p, 8);
    return 0;
}
