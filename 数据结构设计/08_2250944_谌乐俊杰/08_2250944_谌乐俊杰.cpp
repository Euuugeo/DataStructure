//2250944 ���ֿ���//
#include <iostream>
using namespace std;

class MST {
private:
	int numApex; //������
	int numSide; //����
	char* apexName;//��������
	int** Apex; //Ȩ��
	int** store; //��С������
	char start; //��ʼ��ĸ
	int start_num;//��ʼ��ĸ�����������
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
//Aѡ���������
void MST::createApex() {
	char name;
	cout << "�����붥��ĸ���:" ;
	while (1) {
		cin >> numApex;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (numApex >= 2) {
			break;
		}
		cout << "���벻������ĿҪ�����������붥�����" << endl;
	}
	apexName = new char[numApex];
	cout << "�����������������㼰��" << endl;
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
//Bѡ�������
void MST::addSide() {
	char side_a, side_b;
	int weight;
	cout << "�������������㼰��� :";
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
		cout << "�������������㼰��� :" ;
		cin >> side_a >> side_b >> weight;
	}
	cout << endl;
}
//Cѡ�������С������
void MST::createMinTree() {
	int count = 0;
	int* visited;
	visited = new int[numApex]();
	int minWeight = 0, tmpWeight = 0, newApexX = 0, newApexY = 0, mark = 0, startPos, high = 0;
	cout << "��������ʼ����:";
	cin >> start;
	count++;

	// �ҵ���ʼ�����λ��
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
	cout << "����Prim��С������!" << endl;
	cout << endl;
}
//Dѡ������С������
void MST::printMinTree() {
	cout << "��С�������Ķ��㼰���Ϊ" << endl;
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
//�˵�
void menu()
{
	cout << "**           �������ģ��ϵͳ            **" << endl;
	cout << "===========================================" << endl;
	cout << "**           A --- ������������          **" << endl;
	cout << "**           B --- ��ӵ����ı�          **" << endl;
	cout << "**           C --- ������С������        **" << endl;
	cout << "**           D --- ��ʾ��С������        **" << endl;
	cout << "**           E --- �˳� ����             **" << endl;
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
			cout << "��ѡ�������";
			cin >> choice;
			if (choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D' || choice == 'E' ||
				choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd' || choice == 'e') {
				break;
			}
			cout << "ѡ�������������������" << endl;
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
