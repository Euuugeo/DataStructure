//2250944 谌乐俊杰 //
#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;//头结点

public:
    CircularLinkedList() : head(nullptr) {}
    //插入函数
    void insert(int value) {
        Node* Newnode= new Node(value);
        if (!head) {
            head = Newnode;
            head->next = head;
        }
        else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            Newnode->next = head;
            current->next = Newnode;
        }
    }
    //杀人函数
    void kill(int N, int S, int M, int K) {
        Node* current = head;

        for (int i = 1; i < S; i++) {
            current = current->next;
        }
        for (int i = 1; i <= N - K; i++) {
            for (int j = 1; j < M; j++) {
                current = current->next;
            }
            cout << "第" << i << "个死者的位置是" << current->data << endl;

            // 将死者的位置从链表中移除
            Node* prev = current;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = current->next;

            current = current->next;
        }
        cout << "剩余人数:" <<  K << endl;
        cout << "剩余生者的位置是: ";
        current = head;
        int i = 0;
        while (1) {
            if (i ==  K) {
                break;
            }
            cout << current->data << "  ";
            current = current->next;
            if (current == head) {
                break;
            }
            i++;
        }
        cout << endl;
    }
};
//输入函数
void Input(CircularLinkedList& Group,int&N,int&S,int &M,int &K) {
    
    cout << "现有N人围在一圈，从第S个人开始依次报数，报N的人出局，再由下一个人开始报数，如此循环，直到剩下K个人为止" << endl;
    cout << "请输入生死游戏的总人数N:    ";
    while (1) {
        cin >> N;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "错误：请输入数字" << endl;
        }
        else {
            if (N >= 1) {
                break;
            }
            else {
                cout << "错误：N超出规定范围，请重新输入" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }

    cout << "请输入游戏开始的位置S:      ";
    while (1) {
        cin >> S;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "错误：请输入数字" << endl;
        }
        else {
            if (S >= 1 && S <= N) {
                break;
            }
            else {
                cout << "错误：N超出规定范围，请重新输入" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }
    cout << "请输入死亡数字M:            ";
    while (1) {
        cin >> M;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "错误：请输入数字" << endl;
        }
        else {
            if (M >= 1 && M <= N) {
                break;
            }
            else {
                cout << "错误：M超出规定范围，请重新输入" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }
    cout << "请输入剩余生者人数K:        ";
    while (1) {
        cin >> K;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "错误：请输入数字" << endl;
        }
        else {
            if (K >= 1 && K <= N) {
                break;
            }
            else {
                cout << "错误：M超出规定范围，请重新输入" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }
}
int main()
{
    CircularLinkedList Group;
    int N;
    int S;
    int M;
    int K;
    Input(Group, N, S, M, K);//输入
    for (int i = 1; i <= N; i++) {
        Group.insert(i);//插入
    }
    Group.kill(N, S, M, K);//杀人
}