//2250944 谌乐俊杰//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

struct TreeNode {
    char name[10];
    TreeNode* firstChild;
    TreeNode* nextSibling;
    TreeNode() {
        firstChild = NULL;
        nextSibling = NULL;
    }
    TreeNode(char s[10]) {
        strcpy(name, s);
        firstChild = NULL;
        nextSibling = NULL;
    }
};

class Tree {
private:
    TreeNode* root, * current;
public:
    Tree() {
        root = current = NULL;
    }
    void BulidRoot(char s[10]) {
        root = new TreeNode(s);
    }
    //找人
    int Find(TreeNode* p, char target[10]) {
        int result = 0;
        if (strcmp(p->name, target) == 0) {
            result = 1;
            current = p;
        }
        else {
            TreeNode* q = p->firstChild;
            while (q != NULL) {
                if (Find(q, target)) {
                    result = 1;
                    break;
                }
                q = q->nextSibling;
            }
        }
        return result;
    }
    //建立子女
    void BuildSon(char(*p)[10], int number) {
        for (int i = 0; i < number; i++) {
            if (i == 0 && current->firstChild == NULL) {
                current->firstChild = new TreeNode(p[i]);
                current = current->firstChild;  
            }
            else {
                if (current->nextSibling == NULL) {
                    current->nextSibling = new TreeNode(p[i]);
                }
                current = current->nextSibling; 
            }
        }
    }
    //找子女
    void FindSon(char target[10]) {
        if (Find(root, target) == 0) {
            cout << "无子女" << endl;
        }
        else {
            cout << current->name << "的第一代子孙是";
            TreeNode* temp = current->firstChild;
            while (temp != NULL) {
                cout << temp->name << "  ";
                temp = temp->nextSibling;
            }
        }
        cout << endl;
    }
    //加子女
    void AddSon(char target[10], char son[10]) {
        Find(root, target);
        if (current->firstChild == NULL) {
            current->firstChild = new TreeNode(son);
            current = current->firstChild;
        }
        else {
            current = current->firstChild;
            current->nextSibling = new TreeNode(son);
            current = current->nextSibling;
        }
    }
    void FindRoot() {
        cout << "此家谱的祖先是" << root->name << endl;
    }
    //选项A：建立家庭
    void ChoiceA() {
        char s[10];
        char houdai[10];
        char(*p)[10];
        int number;

        cout << "请输入要建立家庭的人的姓名：";
        cin >> s;
        if (!Find(root, s)) {
            cout << "未找到对应的人物" << endl;
            return;
        }

        cout << "请输入" << s << "的儿女的个数：";
        cin >> number;

        // 分配足够的内存以存储所有子女的姓名
        p = new char[number][10];

        cout << "请依次输入" << s << "儿女的姓名：";
        for (int i = 0; i < number; i++) {
            cin >> houdai;
            strcpy(p[i], houdai);
        }

        BuildSon(p, number);
        FindSon(s);
        cout << endl;
        // 记得在不再使用之前分配的内存时进行释放
        delete[] p;
    }
    //选项B：添加人
    void ChoiceB() {
        char target[10];
        char son[10];
        cout << "请输入要添加儿子（或女儿）的人的姓名：";
        cin >> target;
        if (!Find(root, target)) {
            cout << "未找到对应的人物" << endl;
            return;
        }
        cout << "请输入" << target << "新添加的儿子或女儿的姓名：";
        cin >> son;
        AddSon(target, son);
        FindSon(target);
        cout << endl;
    }
    //选项C：解散家庭
    void ChoiceC() {
        char target[10];
        cout << "请输入要解散家庭的人的姓名：";
        cin >> target;
        if (!Find(root, target)) {
            cout << "未找到对应的人物" << endl;
            return;
        }
        cout << "要解散家庭的人是" << current->name << endl;
        if (current->firstChild == NULL) {
            cout << "他已经没有家庭了" << endl;
        }
        else {
            FindSon(target);
            current->firstChild = NULL;
        }
        cout << endl;
    }
    void ChoiceD() {
        char former[10];
        char now[10];
        cout << "请输入需要修改姓名的人的目前姓名：";
        cin >> former;
        if (!Find(root, former)) {
            cout << "未找到对应的人物" << endl;
            return;
        }
        cout << "请输入修改后的姓名：";
        cin >> now;
        strcpy(current->name, "");
        strcpy(current->name, now);
        cout << former << "已更名为" << current->name << endl;
        cout << endl;
    }
};
//目录
void menu()
{
    cout << endl;
    cout << "**              家谱管理系统                     **" << endl;
    cout << "===================================================" << endl;
    cout << "**           请选择要执行的操作                    " << endl;
    cout << "**              A --- 完善家谱                   **" << endl;
    cout << "**              B --- 添加家族成员               **" << endl;
    cout << "**              C --- 解散局部家庭               **" << endl;
    cout << "**              D --- 更加家族成员姓名           **" << endl;
    cout << "**              E --- 退出程序                   **" << endl;
    cout << "===================================================" << endl;
}

int main()
{
    Tree Family;
    menu();
    char s[10];
    cout << "首先建立一个家谱！" << endl;
    cout << "请输入祖先的姓名：";
    cin >> s;
    Family.BulidRoot(s);
    Family.FindRoot();
    while (1) {
        char choice;
        while (1) {
            cout << "请选择要执行的操作：";
            cin >> choice;
            cin.ignore(10000, '\n');
            if (choice == 'A' || choice == 'a' || choice == 'B' || choice == 'b' || choice == 'C' ||
                choice == 'c' || choice == 'D' || choice == 'd' || choice == 'E' || choice == 'e') {
                break;
            }
            cout << "不符要求，请重新输入" << endl;
        }
        if (choice == 'A' || choice == 'a') {
            Family.ChoiceA();
        }
        else if (choice == 'B' || choice == 'b') {
            Family.ChoiceB();
        }
        else if (choice == 'C' || choice == 'c') {
            Family.ChoiceC();
        }
        else if (choice == 'D' || choice == 'd') {
            Family.ChoiceD();
        }
        else if (choice == 'E' || choice == 'e') {
            break;
        }
    }
    return 0;
}
