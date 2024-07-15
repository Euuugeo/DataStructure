//2250944 谌乐俊杰//
#include <iostream>
#include <cstring> 

#define Empty -1
#define MaxSize 50

using namespace std;

// 定义栈类
class Stack {
private:
    int Capacity;
    int TopofStack;
    char* array;

public:
    // 构造函数，初始化栈
    Stack(int capacity) : Capacity(capacity), TopofStack(Empty) {
        array = new char[Capacity];
    }
    // 判断栈是否为空
    bool IsEmpty() const;
    // 判断栈是否满
    bool IsFull() const;
    // 入栈操作
    void Push(char x);
    // 获取栈顶元素，不出栈
    bool Top(char& element) const;
    // 出栈操作
    void Pop(char& element);
};

// 判断栈是否为空
bool Stack::IsEmpty() const {
    return TopofStack == Empty;
}

// 判断栈是否满
bool Stack::IsFull() const {
    return TopofStack == Capacity - 1;
}

// 入栈操作
void Stack::Push(char x) {
    if (IsFull()) {
        cout << "Stack is full..." << endl;
    }
    else
        array[++TopofStack] = x;
}

// 获取栈顶元素，不出栈
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

// 出栈操作
void Stack::Pop(char& element) {
    if (IsEmpty())
        cout << "Stack is empty..." << endl;
    else
        element = array[TopofStack--];
}

// 定义二叉树结点类
class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    char data;

    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// 定义用于构建二叉树的栈类
class TreeStack {
private:
    int TopofStack;
    TreeNode** array;

public:
    // 构造函数，初始化栈
    TreeStack(int capacity) : TopofStack(-1) {
        array = new TreeNode * [capacity];
    }
    // 返回栈顶元素
    TreeNode* Top() const;
    // 入栈操作
    void Push(TreeNode* node);
    // 出栈操作
    TreeNode* Pop();
    // 判断栈是否为空
    bool IsEmpty() const;
};
// 返回栈顶元素
TreeNode* TreeStack::Top() const {
    return array[TopofStack];
}
// 入栈操作
void TreeStack::Push(TreeNode* node) {
    array[++TopofStack] = node;
}

// 出栈操作
TreeNode* TreeStack::Pop() {
    return array[TopofStack--];
}

// 判断栈是否为空
bool TreeStack::IsEmpty() const {
    return TopofStack == -1;
}

// 定义表达式转换和二叉树构建类
class ExpressionConverter {
private:
    Stack S1;
    TreeStack S2;

public:
    // 构造函数，初始化栈
    ExpressionConverter(int size) : S1(size), S2(size) {}
    // 将中缀表达式转换为后缀表达式
    void Translate(const char a[], char b[]);
    // 根据后缀表达式构建二叉树
    TreeNode* BuildTree(char b[]);
};
// 将中缀表达式转换为后缀表达式
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

// 根据后缀表达式构建二叉树
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
// 定义表达式遍历类
class ExpressionTraversal {
public:
    // 前序遍历二叉树
    static void Preorder(TreeNode* p) {
        if (p != nullptr) {
            cout << p->data;
            Preorder(p->left);
            Preorder(p->right);
        }
    }

    // 中序遍历二叉树
    static void Inorder(TreeNode* p) {
        if (p != nullptr) {
            Inorder(p->left);
            cout << p->data;
            Inorder(p->right);
        }
    }

    // 后序遍历二叉树
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

    cout << "请输入表达式:  ";
    cin.getline(a, MaxSize);
    ExpressionConverter converter(MaxSize);
    converter.Translate(a, b);
    TreeNode* root = converter.BuildTree(b);

    cout << endl;
    cout << "波兰表达式:    ";
    ExpressionTraversal::Preorder(root);
    cout << endl;
    cout << endl;
    cout << "中缀表达式:    ";
    ExpressionTraversal::Inorder(root);
    cout << endl;
    cout << endl;
    cout << "逆波兰表达式:  ";
    ExpressionTraversal::Postorder(root);
    cout << endl;

    return 0;
}
