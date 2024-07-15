#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

int list_number;

class Student {
public:
    int num;//表示学生考号
    char name[100];//表示学生姓名
    char gender[10];//表示学生性别
    int age;//表示学生年龄
    char position[100];//表示学生报考类别
    Student* next;//链表结点的指针域

    Student(int num, const char* name, const char* gender, int age, const char* position) : num(num), age(age), next(nullptr) {
        strncpy(this->name, name, sizeof(this->name));
        this->name[sizeof(this->name) - 1] = '\0';
        strncpy(this->gender, gender, sizeof(this->gender));
        this->gender[sizeof(this->gender) - 1] = '\0';
        strncpy(this->position, position, sizeof(this->position));
        this->position[sizeof(this->position) - 1] = '\0';
    }//具有默认参数的构造函数
};

class ExamSystem {
private:
    Student* head;//链表的头指针
public:
    ExamSystem() : head(nullptr) {}

    void AddStudent(int num, const char* name, const char* gender, int age, const char* position) {
        Student* new_student = new Student(num, name, gender, age, position);
        if (!head) {
            head = new_student;
        }
        else {
            Student* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_student;
        }
    }
    //打印函数
    void PrintList() {
        cout << "考号    姓名    性别    年龄    报考类别" << endl;
        Student* current = head;
        while (current) {
            cout << setiosflags(ios::left);
            cout << setw(8) << current->num << setw(8) << current->name << setw(8) << current->gender << setw(8) << current->age
                << setw(8) << current->position << endl;
            current = current->next;
        }
    }
    //判断是否找到所要找的考号所对应的学生
    bool search(int search_num) {
        bool judge = true;
        Student* current = head;
        while (current) {
            if (current->num == search_num) {
                judge = false;
                break;
            }
            current = current->next;
        }
        return judge;
    }
    //选项一：插入考生
    void Choiceone() {
        int place;
        int num;
        char name[100];
        char gender[10];
        int age;
        char position[100];
        cout << "请输入您要插入的考生的位置：";
        while (1) {
            cin >> place;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：位置必须为数字，请重新输入" << endl;
            }
            else {
                if (place >= 1 && place <= list_number + 1) {
                    break;
                }
                else {
                    cout << "错误：位置超出规定范围，请重新输入" << endl;
                }
            }
        }
        int judge = 0;
        cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别" << endl;
        while (1) {
            cin >> num;
            cin >> name;
            cin >> gender;
            cin >> age;
            cin >> position;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                if (num >= 0 && (strcmp(gender, "男") == 0 || strcmp(gender, "女") == 0) && age > 0 && search(num)) {
                    judge = 1;
                }
                else {
                    cin.ignore(10000, '\n');
                }
            }

            if (judge == 1) {
                // 使用search函数来检查考号是否已存在于系统中
                if (!search(num)) {
                    cout << "输入不符合要求，请重新输入" << endl;
                }
                else {
                    break;
                }
            }
            else {
                cout << "输入不符合要求，请重新输入" << endl;
            }
        }
        Student* new_student = new Student(num, name, gender, age, position);
        Student* current = head;
        if (place == 1) {
            new_student->next = head;
            head = new_student;
        }
        else {
            for (int i = 1; i < place - 1; i++) {
                current = current->next;
            }
            new_student->next = current->next;
            current->next = new_student;
        }
        list_number++;
        for (unsigned int i = 0; i < strlen(name); i++) {
            name[i] = { '\0' };
        }
        for (unsigned int i = 0; i < strlen(name); i++) {
            gender[i] = { '\0' };
        }
        for (unsigned int i = 0; i < strlen(name); i++) {
            position[i] = { '\0' };
        }
    }
    //选项二：删除考生
    void Choicetwo() {
        int delete_num;
        cout << "请输入您要删除考生的考号：";
        while (1) {
            cin >> delete_num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：考号必须为数字，请重新输入" << endl;
            }
            else {
                break;
            }
        }
        if (head && head->num == delete_num) {
            Student* del = head;
            head = del->next;
            delete del;
            return; // Exit the function
        }

        Student* current = head;
        while (current->next) {
            if (current->next->num == delete_num) {
                Student* del = current->next;
                current->next = del->next;
                delete del;
                return; // Exit the function
            }
            current = current->next;
        }

        cout << "未找到该考生的信息：" << delete_num << endl;
    }
    //选项三：查找考生
    void Choicethree() {
        int search_num;
        cout << "请输入您要查找考生的考号：";
        while (1) {
            cin >> search_num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：search_num必须为数字，请重新输入" << endl;
            }
            else {
                break;
            }
        }
        if (head && head->num == search_num) {
            Student* sea = head;
            cout << "考号    姓名    性别    年龄    报考类别" << endl;
            cout << setw(8) << sea->num << setw(8) << sea->name << setw(8) << sea->gender << setw(8) << sea->age
                << setw(8) << sea->position << endl;
            return; // Exit the function
        }

        Student* current = head;
        while (current->next) {
            if (current->next->num == search_num) {
                Student* sea = current->next;
                cout << "考号    姓名    性别    年龄    报考类别" << endl;
                cout << setw(8) << sea->num << setw(8) << sea->name << setw(8) << sea->gender << setw(8) << sea->age
                    << setw(8) << sea->position << endl;
                return; // Exit the function
            }
            current = current->next;
        }

        cout << "未找到该考生的信息：" << search_num << endl;
    }
    //选项四：修改信息
    void Choicefour() {
        int place;
        int num;
        char name[100];
        char gender[10];
        int age;
        char position[100];
        cout << "请输入您要修改的位置：";
        while (1) {
            cin >> place;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：位置必须为数字，请重新输入" << endl;
            }
            else {
                if (place >= 1 && place <= list_number ) {
                    break;
                }
                else {
                    cout << "错误：位置超出规定范围，请重新输入" << endl;
                    cin.ignore(10000, '\n');
                }
            }
        }
        int judge = 0;
        cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别" << endl;
        while (1) {
            cin >> num;
            cin >> name;
            cin >> gender;
            cin >> age;
            cin >> position;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                if (num >= 0 && (strcmp(gender, "男") == 0 || strcmp(gender, "女") == 0) && age > 0) {
                    judge = 1;
                }
                else {
                    cin.ignore(10000, '\n');
                }
            }

            if (judge == 1) {
                break;
            }
            else {
                cout << "输入不符合要求，请重新输入" << endl;
            }
        }
        Student* current = head;
        for (int i = 1; i < place; i++) {
            current = current->next;
        }
        current->num = num;
        strncpy(current->name, name, sizeof(current->name));
        current->name[sizeof(current->name) - 1] = '\0';
        strncpy(current->gender, gender, sizeof(current->gender));
        current->gender[sizeof(current->gender) - 1] = '\0';
        current->age = age;
        strncpy(current->position, position, sizeof(current->position));
        current->position[sizeof(current->position) - 1] = '\0';
        // 清除输入缓冲区
        cin.ignore(10000, '\n');
    }
    //选项五：统计所有的男性or女性
    void Choicefive() {
        bool sex;
        cout << "您要查询男性还是女性？（男性为1，女性为0）";
        while (1) {
            cin >> sex;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：输入不符合要求，请重新输入" << endl;
            }
            else {
                if (sex == 1 || sex == 0) {
                    break;
                }
                else {
                    cout << "错误：输入不符合要求，请重新输入" << endl;
                }
            }
        }
        bool found = false; // 用于标记是否找到匹配的考生

        Student* current = head;
        while (current) {
            if ((sex == 1 && strcmp(current->gender, "男") == 0) || (sex == 0 && strcmp(current->gender, "女") == 0)) {
                if (found == false) {
                    cout << "考号    姓名    性别    年龄    报考类别" << endl;
                }
                cout << setw(8) << current->num << setw(8) << current->name << setw(8) << current->gender << setw(8) << current->age
                    << setw(8) << current->position << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            if (sex == 1) {
                cout << "未找到男性考生" << endl;
            }
            else {
                cout << "未找到女性考生" << endl;
            }
        }
    }
};
//建立考生信息系统
void AddStudentInfo(ExamSystem& ExamStudentSystem) {
    int num;
    char name[100];
    char gender[10];
    int age;
    char position[100];
    cout << "首先请建立考生信息系统" << endl;
    cout << "请输入考生人数：" << endl;
    while (1) {
        cin >> list_number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "错误：number必须为数字，请重新输入" << endl;
        }
        else {
            if (list_number >= 1) {
                break;
            }
            else {
                cout << "错误：number超出规定范围，请重新输入" << endl;
            }
        }
    }
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别" << endl;
    for (int i = 0; i < list_number; i++) {
        int judge = 0;
        while (1) {
            cin >> num;
            cin >> name;
            cin >> gender;
            cin >> age;
            cin >> position;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                if (num >= 0 && (strcmp(gender, "男") == 0 || strcmp(gender, "女") == 0) && age > 0 && ExamStudentSystem.search(num)) {
                    judge = 1;
                }
                else {
                    cin.ignore(10000, '\n');
                }
            }

            if (judge == 1) {
                // 使用search函数来检查考号是否已存在于系统中
                if (!ExamStudentSystem.search(num)) {
                    cout << "错误：考号已存在，请从第" << i + 1 << "行重新输入" << endl;
                }
                else {
                    break;
                }
            }
            else {
                cout << "输入不符合要求，请从第" << i + 1 << "行重新输入" << endl;
            }
        }
        ExamStudentSystem.AddStudent(num, name, gender, age, position);
        for (unsigned int i = 0; i < strlen(name); i++) {
            name[i] = { '\0' };
        }
        for (unsigned int i = 0; i < strlen(name); i++) {
            gender[i] = { '\0' };
        }
        for (unsigned int i = 0; i < strlen(name); i++) {
            position[i] = { '\0' };
        }
    }
}
//目录
void MainMenu(ExamSystem& examSystem) {
    int choice;
    while (1) {
        cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作" << endl;
        cout << "请选择您要进行的操作：";

        while (1) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "错误：number必须为数字，请重新输入" << endl;
            }
            else {
                if (choice >= 0 && choice <= 5) {
                    break;
                }
                else {
                    cout << "错误：choice超出规定范围，请重新输入" << endl;
                    cin.ignore(10000, '\n');
                }
            }
        }

        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            examSystem.Choiceone();
            examSystem.PrintList();
        }
        if (choice == 2) {
            examSystem.Choicetwo();
            examSystem.PrintList();
        }
        if (choice == 3) {
            examSystem.Choicethree();
        }
        if (choice == 4) {
            examSystem.Choicefour();
            examSystem.PrintList();
        }
        if (choice == 5) {
            examSystem.Choicefive();
        }
    }
}
int main()
{
    ExamSystem ExamStudentSystem;
    AddStudentInfo(ExamStudentSystem);
    ExamStudentSystem.PrintList();
    MainMenu(ExamStudentSystem);
    return 0;
}