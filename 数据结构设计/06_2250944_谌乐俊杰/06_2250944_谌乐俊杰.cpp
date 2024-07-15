//2250944 ���ֿ���//
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
    //����
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
    //������Ů
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
    //����Ů
    void FindSon(char target[10]) {
        if (Find(root, target) == 0) {
            cout << "����Ů" << endl;
        }
        else {
            cout << current->name << "�ĵ�һ��������";
            TreeNode* temp = current->firstChild;
            while (temp != NULL) {
                cout << temp->name << "  ";
                temp = temp->nextSibling;
            }
        }
        cout << endl;
    }
    //����Ů
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
        cout << "�˼��׵�������" << root->name << endl;
    }
    //ѡ��A��������ͥ
    void ChoiceA() {
        char s[10];
        char houdai[10];
        char(*p)[10];
        int number;

        cout << "������Ҫ������ͥ���˵�������";
        cin >> s;
        if (!Find(root, s)) {
            cout << "δ�ҵ���Ӧ������" << endl;
            return;
        }

        cout << "������" << s << "�Ķ�Ů�ĸ�����";
        cin >> number;

        // �����㹻���ڴ��Դ洢������Ů������
        p = new char[number][10];

        cout << "����������" << s << "��Ů��������";
        for (int i = 0; i < number; i++) {
            cin >> houdai;
            strcpy(p[i], houdai);
        }

        BuildSon(p, number);
        FindSon(s);
        cout << endl;
        // �ǵ��ڲ���ʹ��֮ǰ������ڴ�ʱ�����ͷ�
        delete[] p;
    }
    //ѡ��B�������
    void ChoiceB() {
        char target[10];
        char son[10];
        cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
        cin >> target;
        if (!Find(root, target)) {
            cout << "δ�ҵ���Ӧ������" << endl;
            return;
        }
        cout << "������" << target << "����ӵĶ��ӻ�Ů����������";
        cin >> son;
        AddSon(target, son);
        FindSon(target);
        cout << endl;
    }
    //ѡ��C����ɢ��ͥ
    void ChoiceC() {
        char target[10];
        cout << "������Ҫ��ɢ��ͥ���˵�������";
        cin >> target;
        if (!Find(root, target)) {
            cout << "δ�ҵ���Ӧ������" << endl;
            return;
        }
        cout << "Ҫ��ɢ��ͥ������" << current->name << endl;
        if (current->firstChild == NULL) {
            cout << "���Ѿ�û�м�ͥ��" << endl;
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
        cout << "��������Ҫ�޸��������˵�Ŀǰ������";
        cin >> former;
        if (!Find(root, former)) {
            cout << "δ�ҵ���Ӧ������" << endl;
            return;
        }
        cout << "�������޸ĺ��������";
        cin >> now;
        strcpy(current->name, "");
        strcpy(current->name, now);
        cout << former << "�Ѹ���Ϊ" << current->name << endl;
        cout << endl;
    }
};
//Ŀ¼
void menu()
{
    cout << endl;
    cout << "**              ���׹���ϵͳ                     **" << endl;
    cout << "===================================================" << endl;
    cout << "**           ��ѡ��Ҫִ�еĲ���                    " << endl;
    cout << "**              A --- ���Ƽ���                   **" << endl;
    cout << "**              B --- ��Ӽ����Ա               **" << endl;
    cout << "**              C --- ��ɢ�ֲ���ͥ               **" << endl;
    cout << "**              D --- ���Ӽ����Ա����           **" << endl;
    cout << "**              E --- �˳�����                   **" << endl;
    cout << "===================================================" << endl;
}

int main()
{
    Tree Family;
    menu();
    char s[10];
    cout << "���Ƚ���һ�����ף�" << endl;
    cout << "���������ȵ�������";
    cin >> s;
    Family.BulidRoot(s);
    Family.FindRoot();
    while (1) {
        char choice;
        while (1) {
            cout << "��ѡ��Ҫִ�еĲ�����";
            cin >> choice;
            cin.ignore(10000, '\n');
            if (choice == 'A' || choice == 'a' || choice == 'B' || choice == 'b' || choice == 'C' ||
                choice == 'c' || choice == 'D' || choice == 'd' || choice == 'E' || choice == 'e') {
                break;
            }
            cout << "����Ҫ������������" << endl;
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
