//2250944 ���ֿ���//
#include <iostream>
#include <cstring> 

#define Empty -1
#define MaxSize 50

using namespace std;

// ����ջ��
class Stack {
private:
    int Capacity;
    int TopofStack;
    char* array;

public:
    // ���캯������ʼ��ջ
    Stack(int capacity) : Capacity(capacity), TopofStack(Empty) {
        array = new char[Capacity];
    }
    // �ж�ջ�Ƿ�Ϊ��
    bool IsEmpty() const;
    // �ж�ջ�Ƿ���
    bool IsFull() const;
    // ��ջ����
    void Push(char x);
    // ��ȡջ��Ԫ�أ�����ջ
    bool Top(char& element) const;
    // ��ջ����
    void Pop(char& element);
};

// �ж�ջ�Ƿ�Ϊ��
bool Stack::IsEmpty() const {
    return TopofStack == Empty;
}

// �ж�ջ�Ƿ���
bool Stack::IsFull() const {
    return TopofStack == Capacity - 1;
}

// ��ջ����
void Stack::Push(char x) {
    if (IsFull()) {
        cout << "Stack is full..." << endl;
    }
    else
        array[++TopofStack] = x;
}

// ��ȡջ��Ԫ�أ�����ջ
bool Stack::Top(char& element) const {
    if (!IsEmpty()) {
        element = array[TopofStack];
        return true;
    }
    else {
        cout << "empty\t";
        return false;
    }
}

// ��ջ����
void Stack::Pop(char& element) {
    if (IsEmpty())
        cout << "Stack is empty..." << endl;
    else
        element = array[TopofStack--];
}

// ��������������
class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    char data;

    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// �������ڹ�����������ջ��
class TreeStack {
private:
    int TopofStack;
    TreeNode** array;

public:
    // ���캯������ʼ��ջ
    TreeStack(int capacity) : TopofStack(-1) {
        array = new TreeNode * [capacity];
    }
    // ����ջ��Ԫ��
    TreeNode* Top() const;
    // ��ջ����
    void Push(TreeNode* node);
    // ��ջ����
    TreeNode* Pop();
    // �ж�ջ�Ƿ�Ϊ��
    bool IsEmpty() const;
};
// ����ջ��Ԫ��
TreeNode* TreeStack::Top() const {
    return array[TopofStack];
}
// ��ջ����
void TreeStack::Push(TreeNode* node) {
    array[++TopofStack] = node;
}

// ��ջ����
TreeNode* TreeStack::Pop() {
    return array[TopofStack--];
}

// �ж�ջ�Ƿ�Ϊ��
bool TreeStack::IsEmpty() const {
    return TopofStack == -1;
}

// ������ʽת���Ͷ�����������
class ExpressionConverter {
private:
    Stack S1;
    TreeStack S2;

public:
    // ���캯������ʼ��ջ
    ExpressionConverter(int size) : S1(size), S2(size) {}
    // ����׺���ʽת��Ϊ��׺���ʽ
    void Translate(const char a[], char b[]);
    // ���ݺ�׺���ʽ����������
    TreeNode* BuildTree(char b[]);
};
// ����׺���ʽת��Ϊ��׺���ʽ
void ExpressionConverter::Translate(const char a[], char b[]) {
    char ch, element = '\0';
    int i = 0, j = 0;
    ch = a[i++];

    while (ch != '\0') {
        switch (ch) {
        case '(':
            S1.Push(ch);
            break;
        case ')':
            while (S1.Top(element) && element != '(') {
                S1.Pop(element);
                b[j++] = element;
            }
            S1.Pop(element);
            break;
        case '+':
        case '-':
            while (!S1.IsEmpty() && S1.Top(element) && element != '(') {
                S1.Pop(element);
                b[j++] = element;
            }
            S1.Push(ch);
            break;
        case '*':
        case '/':
            while (!S1.IsEmpty() && S1.Top(element) && (element == '/' || element == '*' || element == '^')) {
                S1.Pop(element);
                b[j++] = element;
            }
            S1.Push(ch);
            break;
        case '^':
            while (!S1.IsEmpty() && S1.Top(element) && element == '^') {
                S1.Pop(element);
                b[j++] = element;
            }
            S1.Push(ch);
            break;
        case ' ':
            break;
        default:
            while (ch >= 'a' && ch <= 'z' || (ch >= '0' && ch <= '9')) {
                b[j++] = ch;
                ch = a[i++];
            }
            i--;
        }
        ch = a[i++];
    }

    while (!S1.IsEmpty()) {
        S1.Pop(element);
        b[j++] = element;
    }

    b[j] = '\0';
}

// ���ݺ�׺���ʽ����������
TreeNode* ExpressionConverter::BuildTree(char b[]) {
    TreeNode* p;
    int i = 0;

    while (b[i] != '\0') {
        if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/' || b[i] == '^') {
            p = new TreeNode(b[i]);
            p->right = S2.Pop();
            p->left = S2.Pop();
            S2.Push(p);
            i++;
        }
        else {
            p = new TreeNode(b[i]);
            p->left = nullptr;
            p->right = nullptr;
            S2.Push(p);
            i++;
        }
    }

    return S2.Pop();
}
// ������ʽ������
class ExpressionTraversal {
public:
    // ǰ�����������
    static void Preorder(TreeNode* p) {
        if (p != nullptr) {
            cout << p->data;
            Preorder(p->left);
            Preorder(p->right);
        }
    }

    // �������������
    static void Inorder(TreeNode* p) {
        if (p != nullptr) {
            Inorder(p->left);
            cout << p->data;
            Inorder(p->right);
        }
    }

    // �������������
    static void Postorder(TreeNode* p) {
        if (p != nullptr) {
            Postorder(p->left);
            Postorder(p->right);
            cout << p->data;
        }
    }
};

int main() {
    char a[MaxSize], b[MaxSize];

    cout << "��������ʽ:  ";
    cin.getline(a, MaxSize);
    ExpressionConverter converter(MaxSize);
    converter.Translate(a, b);
    TreeNode* root = converter.BuildTree(b);

    cout << endl;
    cout << "�������ʽ:    ";
    ExpressionTraversal::Preorder(root);
    cout << endl;
    cout << endl;
    cout << "��׺���ʽ:    ";
    ExpressionTraversal::Inorder(root);
    cout << endl;
    cout << endl;
    cout << "�沨�����ʽ:  ";
    ExpressionTraversal::Postorder(root);
    cout << endl;

    return 0;
}
