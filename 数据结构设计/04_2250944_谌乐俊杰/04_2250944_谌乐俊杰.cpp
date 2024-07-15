// 2250944 ���ֿ��� //
#include <iostream>
using namespace std;

class Queen {
private:
    int* queensStack;  // ����һ��ջ���������
    int stackSize;     // ջ�Ĵ�С
    int stackIndex;    // ����ջ�Ķ���
public:
    int count = 0;

    Queen(int size);//���캯��
    ~Queen();//��������

    void Add(int x, int y);
    bool IsLegal(int row, int column);
    void SetQueen(int currentColumn, int QueenNumber);
    void PrintSolutions(int QueenNumber);
    void ClearSolutions();
};

Queen::Queen(int size) : stackSize(size), stackIndex(-1) {
    queensStack = new int[2 * size];  // һ���У�һ����
}

Queen::~Queen() {
    delete[] queensStack;
}
//���ʺ��λ����Ϣ��ӵ�ջ��
void Queen::Add(int x, int y) {
    stackIndex++;
    queensStack[stackIndex * 2] = x;
    queensStack[stackIndex * 2 + 1] = y;
}
//���ʺ�λ���Ƿ�Ϸ�
bool Queen::IsLegal(int row, int column) {
    for (int i = 0; i <= stackIndex; i++) {
        int currentRow = queensStack[i * 2];
        int currentCol = queensStack[i * 2 + 1];
        if (row == currentRow || column == currentCol ||
            abs(row - currentRow) == abs(column - currentCol)) {
            return false;  //��ͬ�У���ͬ�У�ͬһб��
        }
    }
    return true;
}
//�ݹ����ûʺ�λ��
void Queen::SetQueen(int currentColumn, int QueenNumber) {
    if (currentColumn == QueenNumber) {
        count++;
        PrintSolutions(QueenNumber);
        return;
    }

    for (int row = 0; row < QueenNumber; row++) {
        if (IsLegal(row, currentColumn)) {
            Add(row, currentColumn);
            SetQueen(currentColumn + 1, QueenNumber);
            stackIndex--;  //���߻ʺ�
        }
    }
}
//��ӡ�ⷨ
void Queen::PrintSolutions(int QueenNumber) {
    int** chessboard = new int* [QueenNumber];
    for (int i = 0; i < QueenNumber; i++) {
        chessboard[i] = new int[QueenNumber];
        for (int j = 0; j < QueenNumber; j++) {
            chessboard[i][j] = 0;
        }
    }

    for (int i = 0; i <= stackIndex; i++) {
        int currentRow = queensStack[i * 2];
        int currentCol = queensStack[i * 2 + 1];
        chessboard[currentRow][currentCol] = 1;
    }

    cout << "�ⷨ " << count << ":" << endl;
    for (int i = 0; i < QueenNumber; i++) {
        for (int j = 0; j < QueenNumber; j++) {
            if (chessboard[i][j] == 1) {
                cout << "X ";
            }
            else {
                cout << "O ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < QueenNumber; i++) {
        delete[] chessboard[i];
    }
    delete[] chessboard;
}

//��սⷨ
void Queen::ClearSolutions() {
    stackIndex = -1;
}

int main() {
    int QueenNumber;
    cout << "����N*N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�У�ͬһ�У�ͬһб���ϣ�" << endl;
    cout << endl;
    cout << "������ʺ�ĸ�����";
    while (1) {
        cin >> QueenNumber;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (QueenNumber > 0) {
            break;
        }
        cout << "����������������� ";
    }

    Queen QueenChess(QueenNumber);
    QueenChess.SetQueen(0, QueenNumber);
    cout << "����" << QueenChess.count << "�ֽⷨ" << endl;

    return 0;
}