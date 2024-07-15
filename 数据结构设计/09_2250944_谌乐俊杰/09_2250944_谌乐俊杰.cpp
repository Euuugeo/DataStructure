//2250944 谌乐俊杰//
#include <iostream>
#include <stdlib.h>
using namespace std;

struct BSTNode {
    int data;
    BSTNode* left, * right;
    BSTNode() :left(NULL), right(NULL) {}
    BSTNode(const int d, BSTNode* L = NULL, BSTNode* R = NULL) : data(d), left(L), right(R) {}
    ~BSTNode() {}
};
class BST {
public:
    BST() :root(NULL), lastfound(NULL) {}
    ~BST() {};
    BSTNode* Search(const int x, BSTNode* ptr);
    bool Insert(const int& e1, BSTNode*& ptr); 
    void judge(const int& e1);
    void InOrder(BSTNode* T);
    void PrintAll();
    void Find(const int x);
private:
    BSTNode* root;
    BSTNode* lastfound;
};
//递归地在二叉搜索树中搜索一个值
BSTNode* BST::Search(const int x, BSTNode* ptr) {
    if (ptr == NULL) {
        return NULL;
    }
    else if (x < ptr->data) {
        return Search(x, ptr->left);
    }
    else if (x > ptr->data) {
        return Search(x, ptr->right);
    }
    else {
        lastfound = ptr;
        return ptr;
    }
}
//递归地将一个值插入到二叉搜索树中
bool BST::Insert(const int& e1, BSTNode*& ptr) {
    if (ptr == NULL) {
        ptr = new BSTNode(e1);
        if (ptr == NULL) {
            cerr << "Out of Space" << endl;
            exit(1);
        }
        return true;
    }
    else if (e1 < ptr->data) {
        return Insert(e1, ptr->left);
    }
    else if (e1 > ptr->data) {
        return Insert(e1, ptr->right);
    }
    else {
        return false;
    }
}
//将一个值插入到二叉搜索树中，并在值已存在时打印消息
void BST::judge(const int& e1) {
    if (!Insert(e1, root)) {
        cout << "The input key(" << e1 << ") is already in the tree!" << endl;
    }
}
//对二叉搜索树进行中序遍历
void BST::InOrder(BSTNode* T) {
    if (T != NULL) {
        InOrder(T->left);
        cout << T->data << "->";
        InOrder(T->right);
    }
}
//按排序顺序打印二叉搜索树的所有元素
void BST::PrintAll() {
    cout << "Bsort_Tree is:" << endl;
    InOrder(root);
    cout << endl;
    cout << endl;
}
//在二叉搜索树中搜索一个值，并打印成功或失败的消息
void BST::Find(const int x) {
    if (Search(x, root)) {
        cout << "search success!" << endl;
    }
    else {
        cout << x << " not exist!" << endl;
    }
}
//目录
void menu() {
    cout << "**                二叉排序树                **" << endl;
    cout << "==============================================" << endl;
    cout << "**            1 --- 建立二叉排序树          **" << endl;
    cout << "**            2 --- 插入元素                **" << endl;
    cout << "**            3 --- 查询元素                **" << endl;
    cout << "**            4 --- 退出程序                **" << endl;
    cout << "==============================================" << endl;
}

int main() {
    char choice;
    BST Tree;
    menu();
    while (1) {
        cout << "Please select:  ";
        cin >> choice;
        cin.ignore(10000, '\n');
        if (choice == '1') {
            cout << "Please input keys to create Bsort_Tree :  " << endl;
            int num;
            char ch;
            while (1) {
                cin >> num;
                if (num > 0) {
                    Tree.judge(num);
                }
                ch = getchar();
                if (ch == '\n') {
                    break;
                }
            }
            Tree.PrintAll();
        }
        else if (choice == '2') {
            int num;
            while (1) {
                cout << "Please input key which inserted :  ";
                cin >> num;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else if (num > 0) {
                    break;
                }
                cout << "输入不符要求，请重试..." << endl;
            }
            Tree.judge(num);
            Tree.PrintAll();
        }
        else if (choice == '3') {
            int num;
            while (1) {
                cout << "Please input key which searched :";
                cin >> num;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else if (num > 0) {
                    break;
                }
                cout << "输入不符要求，请重试..." << endl;
            }
            Tree.Find(num);
            cout << endl;
        }
        else if (choice == '4') {
            break;
        }
        else {
            cout << "输入不符要求，请重试..." << endl;
            cout << endl;
        }
    }
    return 0;
}
