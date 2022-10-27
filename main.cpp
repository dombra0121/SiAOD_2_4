#include <iostream>
#include <windows.h>
#include <iomanip>

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
    if (p != nullptr) {
        inorder(p->left);
        cout << p->key << " ";
        inorder(p->right);
    }
}

int height_tree(node *p) {              // Поиск высоты дерева
    if (p == nullptr) return 0;
    else if (p->left == nullptr && p->right == nullptr) return 0;
    else if (height_tree(p->left) > height_tree(p->right)) {
        return height_tree(p->left) + 1;
    } else {
        return height_tree(p->right) + 1;
    }
}

int search_value(node *p, int k, int counter = 0) {      // Поиск длины пути от корня до заданного значения
    if (p->key == k) return counter;
    else if (k < p->key) return search_value(p->left, k, counter + 1);
    else if (k > p->key) return search_value(p->right, k, counter + 1);
    else return -1;
}

void print_tree(node *p, int level = 0) {                   // Обычный вывод дерева
    cout << endl << setfill('-') << setw(4 * level) << p->key;
    if (p->left) print_tree(p->left, level + 1);
    if (p->right) print_tree(p->right, level + 1);
}

void menu() {
    cout << "\nВведите операцию выполнения программы:" << endl;
    cout << "0 - Вывод дерева;\n1 - Вывод дерева с помощью симметричного обхода;\n2 - Вставка элемента;\n3 - Поиск длины от корня до заданного "
            "значения;\n4 - Поиск высоты дерева;\n5 - Завершение работы программы;\nВвод: ";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    node *p = nullptr;
    int n;
    int s;
    cout << "Введите размер AVL-дерева: ";
    cin >> n;
    cout << "Введите целочисленные ключи для элементов AVL-дерева:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "-й элемент: ";
        cin >> s;
        p = insert(p, s);
    }
    menu();
    int operation;
    cin >> operation;
    while (true) {
        if (operation == 0) print_tree(p);
        else if (operation == 1) inorder(p);
        else if (operation == 2) {
            int c;
            cout << "Введите целочисленный ключ вставляемого элемента: ";
            cin >> c;
            insert(p,c);
        }
        else if (operation == 3) {
            int c;
            cout << "Введите ключ элемента, до которого необходимо найти длину пути от корня: ";
            cin >> c;
            if (search_value(p, c) == -1) cout << "Данное значение отсутствует в дереве";
            else cout << endl << "Длина искомого пути: " << search_value(p, c);
        }
        else if (operation == 4) {
            cout << "Высота дерева равна " << height_tree(p);
        }
        else if (operation == 5) {
            cout << "Программа завершила свою работу!";
            break;
        }
        menu();
        cin >> operation;
    }
    return 0;
}
