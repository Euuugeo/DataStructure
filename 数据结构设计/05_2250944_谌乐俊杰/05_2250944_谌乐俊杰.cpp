// 2250944 谌乐俊杰 //
#include <iostream>
#include <fstream>

const int MAX_CHARACTERS = 1000;  // 定义字符数组的最大长度

using namespace std;

// 函数声明
bool openFile(const char* fileName, ifstream& fileStream);
void saveTextToFile(const char* fileName, const char* content);
int searchKeywordInFile(ifstream& fileStream, const char* keyword);

int main() {
    char fileName[MAX_CHARACTERS];
    cout << "请输入文件名: ";
    cin.getline(fileName, MAX_CHARACTERS);

    ifstream inputFile;
    if (!openFile(fileName, inputFile)) {
        cerr << "无法打开文件 " << fileName << endl;
        return 1;
    }

    char content[MAX_CHARACTERS];
    cout << "请输入一段英文:" << endl;
    cin.getline(content, MAX_CHARACTERS);

    // 将输入的文本保存到文件中
    saveTextToFile("src.txt", content);

    char keyword[MAX_CHARACTERS];
    cout << "请输入要检索的关键字: ";
    cin >> keyword;

    int keywordCount = searchKeywordInFile(inputFile, keyword);

    cout << "在源文件中共检索到: " << keywordCount << "个关键字\"" << keyword << "\"" << endl;

    inputFile.close();

    cout << "Press any key to continue...";
    cin.ignore();  // 等待用户按键
    return 0;
}

// 函数定义

bool openFile(const char* fileName, ifstream& fileStream) {
    fileStream.open(fileName);
    return fileStream.is_open();
}

void saveTextToFile(const char* fileName, const char* content) {
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << content << endl;
        outputFile.close();
        cout << "文本已保存在文本文件\"" << fileName << "\"中。"<< endl;
    }
    else {
        cerr << "无法创建文件\"" << fileName << "\"" << endl;
    }
}

int searchKeywordInFile(ifstream& fileStream, const char* keyword) {
    int keywordCount = 0;
    char line[MAX_CHARACTERS];
    cout << "显示源文件\"src.txt\"" << endl;
    fileStream.clear();  // 清除文件流的错误状态
    fileStream.seekg(0, ios::beg);  // 将文件指针移到文件开头
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
