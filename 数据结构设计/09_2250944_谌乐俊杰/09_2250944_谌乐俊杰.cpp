//2250944 ���ֿ���//
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
//�ݹ���ڶ���������������һ��ֵ
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
//�ݹ�ؽ�һ��ֵ���뵽������������
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
//��һ��ֵ���뵽�����������У�����ֵ�Ѵ���ʱ��ӡ��Ϣ
void BST::judge(const int& e1) {
    if (!Insert(e1, root)) {
        cout << "The input key(" << e1 << ") is already in the tree!" << endl;
    }
}
//�Զ��������������������
void BST::InOrder(BSTNode* T) {
    if (T != NULL) {
        InOrder(T->left);
        cout << T->data << "->";
        InOrder(T->right);
    }
}
//������˳���ӡ����������������Ԫ��
void BST::PrintAll() {
    cout << "Bsort_Tree is:" << endl;
    InOrder(root);
    cout << endl;
    cout << endl;
}
//�ڶ���������������һ��ֵ������ӡ�ɹ���ʧ�ܵ���Ϣ
void BST::Find(const int x) {
    if (Search(x, root)) {
        cout << "search success!" << endl;
    }
    else {
        cout << x << " not exist!" << endl;
    }
}
//Ŀ¼
void menu() {
    cout << "**                ����������                **" << endl;
    cout << "==============================================" << endl;
    cout << "**            1 --- ��������������          **" << endl;
    cout << "**            2 --- ����Ԫ��                **" << endl;
    cout << "**            3 --- ��ѯԪ��                **" << endl;
    cout << "**            4 --- �˳�����                **" << endl;
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
                cout << "���벻��Ҫ��������..." << endl;
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
                cout << "���벻��Ҫ��������..." << endl;
            }
            Tree.Find(num);
            cout << endl;
        }
        else if (choice == '4') {
            break;
        }
        else {
            cout << "���벻��Ҫ��������..." << endl;
            cout << endl;
        }
    }
    return 0;
}
