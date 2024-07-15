//2250944 谌乐俊杰//
#include <iostream>
using namespace std;

class MST {
private:
	int numApex; //顶点数
	int numSide; //边数
	char* apexName;//顶点命名
	int** Apex; //权重
	int** store; //最小生成树
	char start; //开始字母
	int start_num;//开始字母所代表的数字
public:
	MST();
	void createApex();
	void addSide();
	void createMinTree();
	void printMinTree();
};
MST::MST() {
	numApex = 0;
	numSide = 0;
}
//A选项，创建顶点
void MST::createApex() {
	char name;
	cout << "请输入顶点的个数:" ;
	while (1) {
		cin >> numApex;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (numApex >= 2) {
			break;
		}
		cout << "输入不符合题目要求，请重新输入顶点个数" << endl;
	}
	apexName = new char[numApex];
	cout << "请依次输入两个顶点及边" << endl;
	for (int i = 0; i < numApex; i++) {
		cin >> name;
		apexName[i] = name;
	}
	Apex = new int* [numApex];
	store = new int* [numApex];
	for (int i = 0; i < numApex; i++) {
		Apex[i] = new int[numApex]();
		store[i] = new int[numApex]();
	}
	cout << endl;
}
//B选项，创建边
void MST::addSide() {
	char side_a, side_b;
	int weight;
	cout << "请输入两个顶点及其边 :";
	cin >> side_a >> side_b >> weight;
	while (side_a != '?' && side_b != '?' && weight != 0) {
		int i = 0;
		int j = 0;
		while (apexName[i] != side_a) {
			i++;
		}
		while (apexName[j] != side_b) {
			j++;
		}
		Apex[i][j] = weight;
		Apex[j][i] = weight;
		cout << "请输入两个顶点及其边 :" ;
		cin >> side_a >> side_b >> weight;
	}
	cout << endl;
}
//C选项，生成最小生成树
void MST::createMinTree() {
	int count = 0;
	int* visited;
	visited = new int[numApex]();
	int minWeight = 0, tmpWeight = 0, newApexX = 0, newApexY = 0, mark = 0, startPos, high = 0;
	cout << "请输入起始顶点:";
	cin >> start;
	count++;

	// 找到起始顶点的位置
	for (int i = 0; i < numApex; i++){
		if (apexName[i] == start) {
			startPos = i;
			start_num = i;
			visited[startPos] = 1;
			break;
		}
    }
	

	while (count != numApex)
	{
		mark = 0;
		for (int i = 0; i < numApex; i++)
		{
			for (int j = 0; j < numApex; j++)
			{
				if (visited[i] == 1 && visited[j] == 0 && i != j && Apex[i][j] != 0)
				{
					if (mark == 0)
					{
						minWeight = Apex[j][i];
						mark = 1;
						newApexX = j;
						newApexY = i;
					}
					else
					{
						tmpWeight = Apex[j][i];
						if (tmpWeight < minWeight)
						{
							minWeight = tmpWeight;
							newApexX = j;
							newApexY = i;
						}
					}
				}
			}
		}
		visited[newApexX] = 1;
		store[newApexY][newApexX] = Apex[newApexY][newApexX];
		count++;
	}
	cout << "生成Prim最小生成树!" << endl;
	cout << endl;
}
//D选项，输出最小生成树
void MST::printMinTree() {
	cout << "最小生成树的顶点及其边为" << endl;
	cout << endl;
	int check = 0;
	int father;
	for (int j = 0; j < numApex; j++) {
		if (store[start_num][j] != 0) {
			cout << apexName[start_num] << "-(" << store[start_num][j] << ")->" << apexName[j] << "     ";
			father = j;
		}
	}
	check++;
	while (check != numApex) {
		for (int j = 0; j < numApex; j++) {
			if (store[father][j] != 0) {
				cout << apexName[father] << "-(" << store[father][j] << ")->" << apexName[j] << "     ";
				father = j;
			}
		}
		check++;
	}
	cout << endl;
}
//菜单
void menu()
{
	cout << "**           电网造价模拟系统            **" << endl;
	cout << "===========================================" << endl;
	cout << "**           A --- 创建电网顶点          **" << endl;
	cout << "**           B --- 添加电网的边          **" << endl;
	cout << "**           C --- 构造最小生成树        **" << endl;
	cout << "**           D --- 显示最小生成树        **" << endl;
	cout << "**           E --- 退出 程序             **" << endl;
	cout << "===========================================" << endl;
	cout << endl;
}

int main()
{
	char choice;
	MST Electricty;
	menu();
	while (1) {
		while (1) {
			cout << "请选择操作：";
			cin >> choice;
			if (choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D' || choice == 'E' ||
				choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd' || choice == 'e') {
				break;
			}
			cout << "选项输入错误，请重新输入" << endl;
		}
		if (choice == 'E' || choice == 'e') {
			break;
		}
		else {
			switch (choice) {
			case 'A':
				Electricty.createApex();
				break;
			case 'a':
				Electricty.createApex();
				break;
			case 'B':
				Electricty.addSide();
				break;
			case 'b':
				Electricty.addSide();
				break;
			case'C':
				Electricty.createMinTree();
				break;
			case 'c':
				Electricty.createMinTree();
				break;
			case'D':
				Electricty.printMinTree();
				break;
			case'd':
				Electricty.printMinTree();
				break;
			}
		}
	}
	return 0;
}
