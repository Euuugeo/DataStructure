//2250944 ���ֿ��� //
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
    Node* head;//ͷ���

public:
    CircularLinkedList() : head(nullptr) {}
    //���뺯��
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
    //ɱ�˺���
    void kill(int N, int S, int M, int K) {
        Node* current = head;

        for (int i = 1; i < S; i++) {
            current = current->next;
        }
        for (int i = 1; i <= N - K; i++) {
            for (int j = 1; j < M; j++) {
                current = current->next;
            }
            cout << "��" << i << "�����ߵ�λ����" << current->data << endl;

            // �����ߵ�λ�ô��������Ƴ�
            Node* prev = current;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = current->next;

            current = current->next;
        }
        cout << "ʣ������:" <<  K << endl;
        cout << "ʣ�����ߵ�λ����: ";
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
//���뺯��
void Input(CircularLinkedList& Group,int&N,int&S,int &M,int &K) {
    
    cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������N���˳��֣�������һ���˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;
    cout << "������������Ϸ��������N:    ";
    while (1) {
        cin >> N;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "��������������" << endl;
        }
        else {
            if (N >= 1) {
                break;
            }
            else {
                cout << "����N�����涨��Χ������������" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }

    cout << "��������Ϸ��ʼ��λ��S:      ";
    while (1) {
        cin >> S;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "��������������" << endl;
        }
        else {
            if (S >= 1 && S <= N) {
                break;
            }
            else {
                cout << "����N�����涨��Χ������������" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }
    cout << "��������������M:            ";
    while (1) {
        cin >> M;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "��������������" << endl;
        }
        else {
            if (M >= 1 && M <= N) {
                break;
            }
            else {
                cout << "����M�����涨��Χ������������" << endl;
                cin.ignore(10000, '\n');
            }
        }
    }
    cout << "������ʣ����������K:        ";
    while (1) {
        cin >> K;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "��������������" << endl;
        }
        else {
            if (K >= 1 && K <= N) {
                break;
            }
            else {
                cout << "����M�����涨��Χ������������" << endl;
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
    Input(Group, N, S, M, K);//����
    for (int i = 1; i <= N; i++) {
        Group.insert(i);//����
    }
    Group.kill(N, S, M, K);//ɱ��
}