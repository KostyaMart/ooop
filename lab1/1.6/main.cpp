#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* root, int val);
    TreeNode* remove(TreeNode* root, int val, int mechanism);
    TreeNode* findMin(TreeNode* root);
    bool search(TreeNode* root, int val);
    void inorderTraversal(TreeNode* root);
    void preorderTraversal(TreeNode* root);
    void postorderTraversal(TreeNode* root);
    void printPath(TreeNode* root, int val);

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val);
    void remove(int val, int mechanism);
    bool search(int val);
    void inorder();
    void preorder();
    void postorder();
    void run();
};

TreeNode* BinarySearchTree::insert(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    }
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }

    return root;
}

void BinarySearchTree::insert(int val) {
    root = insert(root, val);
}

TreeNode* BinarySearchTree::remove(TreeNode* root, int val, int mechanism) {
    if (root == nullptr) {
        return root;
    }

    if (val < root->data) {
        root->left = remove(root->left, val, mechanism);
    }
    else if (val > root->data) {
        root->right = remove(root->right, val, mechanism);
    }
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        if (mechanism == 1) {
            TreeNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data, mechanism);
        }
        else if (mechanism == 2) {
            TreeNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data, mechanism);
        }
    }

    return root;
}

void BinarySearchTree::remove(int val, int mechanism) {
    root = remove(root, val, mechanism);
}

TreeNode* BinarySearchTree::findMin(TreeNode* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

bool BinarySearchTree::search(TreeNode* root, int val) {
    if (root == nullptr) {
        return false;
    }

    if (val == root->data) {
        return true;
    }
    else if (val < root->data) {
        return search(root->left, val);
    }
    else {
        return search(root->right, val);
    }
}

bool BinarySearchTree::search(int val) {
    return search(root, val);
}

void BinarySearchTree::inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

void BinarySearchTree::inorder() {
    inorderTraversal(root);
    std::cout << std::endl;
}

void BinarySearchTree::preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void BinarySearchTree::preorder() {
    preorderTraversal(root);
    std::cout << std::endl;
}

void BinarySearchTree::postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    std::cout << root->data << " ";
}

void BinarySearchTree::postorder() {
    postorderTraversal(root);
    std::cout << std::endl;
}

void BinarySearchTree::printPath(TreeNode* root, int val) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data;

    if (val == root->data) {
        return;
    }
    else if (val < root->data) {
        std::cout << " ";
        printPath(root->left, val);
    }
    else {
        std::cout << " ";
        printPath(root->right, val);
    }
}

void BinarySearchTree::run() {
    while (true) {
        std::cout << "Binary Search Tree Menu:" << std::endl;
        std::cout << "1. Додати елемент" << std::endl;
        std::cout << "2. Видалити елемент (стандартний механiзм)" << std::endl;
        std::cout << "3. Видалити елемент (замiна найменшим елементом пiддерева)" << std::endl;
        std::cout << "4. Пошук елемента" << std::endl;
        std::cout << "5. Обход дерева (inorder)" << std::endl;
        std::cout << "6. Обход дерева (preorder)" << std::endl;
        std::cout << "7. Обход дерева (postorder)" << std::endl;
        std::cout << "8. Пошук за шляхом в деревi" << std::endl;
        std::cout << "9. Вихiд" << std::endl;
        std::cout << "Оберiть опцiю: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int val;
            std::cout << "Введiть значення для додавання: ";
            std::cin >> val;
            insert(val);
            std::cout << val << " додано до дерева." << std::endl;
            break;
        }
        case 2: {
            int val;
            std::cout << "Введiть значення для видалення: ";
            std::cin >> val;
            if (search(val)) {
                remove(val, 1);
                std::cout << val << " видалено з дерева." << std::endl;
            }
            else {
                std::cout << val << " не знайдено у деревi." << std::endl;
            }
            break;
        }
        case 3: {
            int val;
            std::cout << "Введіть значення для видалення: ";
            std::cin >> val;
            if (search(val)) {
                remove(val, 2);
                std::cout << val << " видалено з дерева." << std::endl;
            }
            else {
                std::cout << val << " не знайдено у деревi." << std::endl;
            }
            break;
        }
        case 4: {
            int val;
            std::cout << "Введiть значення для пошуку: ";
            std::cin >> val;
            if (search(val)) {
                std::cout << val << " знайдено у деревi." << std::endl;
            }
            else {
                std::cout << val << " не знайдено у деревi." << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "Результат обходу дерева (inorder): ";
            inorder();
            break;
        }
        case 6: {
            std::cout << "Результат обходу дерева (preorder): ";
            preorder();
            break;
        }
        case 7: {
            std::cout << "Результат обходу дерева (postorder): ";
            postorder();
            break;
        }
        case 8: {
            int val;
            std::cout << "Введiть значення для пошуку за шляхом: ";
            std::cin >> val;
            std::cout << "Шлях до " << val << ": ";
            printPath(root, val);
            std::cout << std::endl;
            break;
        }
        case 9:
            std::cout << "Дякую за використання дерева бiнарного пошуку!" << std::endl;
            return;
        default:
            std::cout << "Невiрний вибiр. Спробуйте ще раз." << std::endl;
            break;
        }
    }
}

int main() {
    BinarySearchTree tree;
    setlocale(LC_ALL, "");
    tree.run();
    return 0;
}