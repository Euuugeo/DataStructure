// 2250944 谌乐俊杰 //
#include <iostream>
using namespace std;

class Queen {
private:
    int* queensStack;  // 构建一个栈来存放棋子
    int stackSize;     // 栈的大小
    int stackIndex;    // 跟踪栈的顶部
public:
    int count = 0;

    Queen(int size);//构造函数
    ~Queen();//析构函数

    void Add(int x, int y);
    bool IsLegal(int row, int column);
    void SetQueen(int currentColumn, int QueenNumber);
    void PrintSolutions(int QueenNumber);
    void ClearSolutions();
};

Queen::Queen(int size) : stackSize(size), stackIndex(-1) {
    queensStack = new int[2 * size];  // 一个行，一个列
}

Queen::~Queen() {
    delete[] queensStack;
}
//将皇后的位置信息添加到栈中
void Queen::Add(int x, int y) {
    stackIndex++;
    queensStack[stackIndex * 2] = x;
    queensStack[stackIndex * 2 + 1] = y;
}
//检查皇后位置是否合法
bool Queen::IsLegal(int row, int column) {
    for (int i = 0; i <= stackIndex; i++) {
        int currentRow = queensStack[i * 2];
        int currentCol = queensStack[i * 2 + 1];
        if (row == currentRow || column == currentCol ||
            abs(row - currentRow) == abs(column - currentCol)) {
            return false;  //相同行，相同列，同一斜线
        }
    }
    return true;
}
//递归设置皇后位置
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
            stackIndex--;  //移走皇后
        }
    }
}
//打印解法
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

    cout << "解法 " << count << ":" << endl;
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

//清空解法
void Queen::ClearSolutions() {
    stackIndex = -1;
}

int main() {
    int QueenNumber;
    cout << "现有N*N的棋盘，放入N个皇后，要求所有皇后不在同一行，同一列，同一斜线上：" << endl;
    cout << endl;
    cout << "请输入皇后的个数：";
    while (1) {
        cin >> QueenNumber;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (QueenNumber > 0) {
            break;
        }
        cout << "输入错误，请重新输入 ";
    }

    Queen QueenChess(QueenNumber);
    QueenChess.SetQueen(0, QueenNumber);
    cout << "共有" << QueenChess.count << "种解法" << endl;

    return 0;
}