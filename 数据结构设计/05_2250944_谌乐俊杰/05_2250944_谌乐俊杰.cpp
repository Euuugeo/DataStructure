// 2250944 ���ֿ��� //
#include <iostream>
#include <fstream>

const int MAX_CHARACTERS = 1000;  // �����ַ��������󳤶�

using namespace std;

// ��������
bool openFile(const char* fileName, ifstream& fileStream);
void saveTextToFile(const char* fileName, const char* content);
int searchKeywordInFile(ifstream& fileStream, const char* keyword);

int main() {
    char fileName[MAX_CHARACTERS];
    cout << "�������ļ���: ";
    cin.getline(fileName, MAX_CHARACTERS);

    ifstream inputFile;
    if (!openFile(fileName, inputFile)) {
        cerr << "�޷����ļ� " << fileName << endl;
        return 1;
    }

    char content[MAX_CHARACTERS];
    cout << "������һ��Ӣ��:" << endl;
    cin.getline(content, MAX_CHARACTERS);

    // ��������ı����浽�ļ���
    saveTextToFile("src.txt", content);

    char keyword[MAX_CHARACTERS];
    cout << "������Ҫ�����Ĺؼ���: ";
    cin >> keyword;

    int keywordCount = searchKeywordInFile(inputFile, keyword);

    cout << "��Դ�ļ��й�������: " << keywordCount << "���ؼ���\"" << keyword << "\"" << endl;

    inputFile.close();

    cout << "Press any key to continue...";
    cin.ignore();  // �ȴ��û�����
    return 0;
}

// ��������

bool openFile(const char* fileName, ifstream& fileStream) {
    fileStream.open(fileName);
    return fileStream.is_open();
}

void saveTextToFile(const char* fileName, const char* content) {
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << content << endl;
        outputFile.close();
        cout << "�ı��ѱ������ı��ļ�\"" << fileName << "\"�С�"<< endl;
    }
    else {
        cerr << "�޷������ļ�\"" << fileName << "\"" << endl;
    }
}

int searchKeywordInFile(ifstream& fileStream, const char* keyword) {
    int keywordCount = 0;
    char line[MAX_CHARACTERS];
    cout << "��ʾԴ�ļ�\"src.txt\"" << endl;
    fileStream.clear();  // ����ļ����Ĵ���״̬
    fileStream.seekg(0, ios::beg);  // ���ļ�ָ���Ƶ��ļ���ͷ
    while (fileStream.getline(line, MAX_CHARACTERS)) {
        char* pos = line;
        while ((pos = strstr(pos, keyword)) != nullptr) {
            keywordCount++;
            pos += strlen(keyword);
        }
        cout << line << endl;
    }
    return keywordCount;
}
