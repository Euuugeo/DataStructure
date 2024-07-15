#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

int list_number;

class Student {
public:
    int num;//��ʾѧ������
    char name[100];//��ʾѧ������
    char gender[10];//��ʾѧ���Ա�
    int age;//��ʾѧ������
    char position[100];//��ʾѧ���������
    Student* next;//�������ָ����

    Student(int num, const char* name, const char* gender, int age, const char* position) : num(num), age(age), next(nullptr) {
        strncpy(this->name, name, sizeof(this->name));
        this->name[sizeof(this->name) - 1] = '\0';
        strncpy(this->gender, gender, sizeof(this->gender));
        this->gender[sizeof(this->gender) - 1] = '\0';
        strncpy(this->position, position, sizeof(this->position));
        this->position[sizeof(this->position) - 1] = '\0';
    }//����Ĭ�ϲ����Ĺ��캯��
};

class ExamSystem {
private:
    Student* head;//�����ͷָ��
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
    //��ӡ����
    void PrintList() {
        cout << "����    ����    �Ա�    ����    �������" << endl;
        Student* current = head;
        while (current) {
            cout << setiosflags(ios::left);
            cout << setw(8) << current->num << setw(8) << current->name << setw(8) << current->gender << setw(8) << current->age
                << setw(8) << current->position << endl;
            current = current->next;
        }
    }
    //�ж��Ƿ��ҵ���Ҫ�ҵĿ�������Ӧ��ѧ��
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
    //ѡ��һ�����뿼��
    void Choiceone() {
        int place;
        int num;
        char name[100];
        char gender[10];
        int age;
        char position[100];
        cout << "��������Ҫ����Ŀ�����λ�ã�";
        while (1) {
            cin >> place;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "����λ�ñ���Ϊ���֣�����������" << endl;
            }
            else {
                if (place >= 1 && place <= list_number + 1) {
                    break;
                }
                else {
                    cout << "����λ�ó����涨��Χ������������" << endl;
                }
            }
        }
        int judge = 0;
        cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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
                if (num >= 0 && (strcmp(gender, "��") == 0 || strcmp(gender, "Ů") == 0) && age > 0 && search(num)) {
                    judge = 1;
                }
                else {
                    cin.ignore(10000, '\n');
                }
            }

            if (judge == 1) {
                // ʹ��search��������鿼���Ƿ��Ѵ�����ϵͳ��
                if (!search(num)) {
                    cout << "���벻����Ҫ������������" << endl;
                }
                else {
                    break;
                }
            }
            else {
                cout << "���벻����Ҫ������������" << endl;
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
    //ѡ�����ɾ������
    void Choicetwo() {
        int delete_num;
        cout << "��������Ҫɾ�������Ŀ��ţ�";
        while (1) {
            cin >> delete_num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "���󣺿��ű���Ϊ���֣�����������" << endl;
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

        cout << "δ�ҵ��ÿ�������Ϣ��" << delete_num << endl;
    }
    //ѡ���������ҿ���
    void Choicethree() {
        int search_num;
        cout << "��������Ҫ���ҿ����Ŀ��ţ�";
        while (1) {
            cin >> search_num;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "����search_num����Ϊ���֣�����������" << endl;
            }
            else {
                break;
            }
        }
        if (head && head->num == search_num) {
            Student* sea = head;
            cout << "����    ����    �Ա�    ����    �������" << endl;
            cout << setw(8) << sea->num << setw(8) << sea->name << setw(8) << sea->gender << setw(8) << sea->age
                << setw(8) << sea->position << endl;
            return; // Exit the function
        }

        Student* current = head;
        while (current->next) {
            if (current->next->num == search_num) {
                Student* sea = current->next;
                cout << "����    ����    �Ա�    ����    �������" << endl;
                cout << setw(8) << sea->num << setw(8) << sea->name << setw(8) << sea->gender << setw(8) << sea->age
                    << setw(8) << sea->position << endl;
                return; // Exit the function
            }
            current = current->next;
        }

        cout << "δ�ҵ��ÿ�������Ϣ��" << search_num << endl;
    }
    //ѡ���ģ��޸���Ϣ
    void Choicefour() {
        int place;
        int num;
        char name[100];
        char gender[10];
        int age;
        char position[100];
        cout << "��������Ҫ�޸ĵ�λ�ã�";
        while (1) {
            cin >> place;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "����λ�ñ���Ϊ���֣�����������" << endl;
            }
            else {
                if (place >= 1 && place <= list_number ) {
                    break;
                }
                else {
                    cout << "����λ�ó����涨��Χ������������" << endl;
                    cin.ignore(10000, '\n');
                }
            }
        }
        int judge = 0;
        cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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
                if (num >= 0 && (strcmp(gender, "��") == 0 || strcmp(gender, "Ů") == 0) && age > 0) {
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
                cout << "���벻����Ҫ������������" << endl;
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
        // ������뻺����
        cin.ignore(10000, '\n');
    }
    //ѡ���壺ͳ�����е�����orŮ��
    void Choicefive() {
        bool sex;
        cout << "��Ҫ��ѯ���Ի���Ů�ԣ�������Ϊ1��Ů��Ϊ0��";
        while (1) {
            cin >> sex;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "�������벻����Ҫ������������" << endl;
            }
            else {
                if (sex == 1 || sex == 0) {
                    break;
                }
                else {
                    cout << "�������벻����Ҫ������������" << endl;
                }
            }
        }
        bool found = false; // ���ڱ���Ƿ��ҵ�ƥ��Ŀ���

        Student* current = head;
        while (current) {
            if ((sex == 1 && strcmp(current->gender, "��") == 0) || (sex == 0 && strcmp(current->gender, "Ů") == 0)) {
                if (found == false) {
                    cout << "����    ����    �Ա�    ����    �������" << endl;
                }
                cout << setw(8) << current->num << setw(8) << current->name << setw(8) << current->gender << setw(8) << current->age
                    << setw(8) << current->position << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            if (sex == 1) {
                cout << "δ�ҵ����Կ���" << endl;
            }
            else {
                cout << "δ�ҵ�Ů�Կ���" << endl;
            }
        }
    }
};
//����������Ϣϵͳ
void AddStudentInfo(ExamSystem& ExamStudentSystem) {
    int num;
    char name[100];
    char gender[10];
    int age;
    char position[100];
    cout << "�����뽨��������Ϣϵͳ" << endl;
    cout << "�����뿼��������" << endl;
    while (1) {
        cin >> list_number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "����number����Ϊ���֣�����������" << endl;
        }
        else {
            if (list_number >= 1) {
                break;
            }
            else {
                cout << "����number�����涨��Χ������������" << endl;
            }
        }
    }
    cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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
                if (num >= 0 && (strcmp(gender, "��") == 0 || strcmp(gender, "Ů") == 0) && age > 0 && ExamStudentSystem.search(num)) {
                    judge = 1;
                }
                else {
                    cin.ignore(10000, '\n');
                }
            }

            if (judge == 1) {
                // ʹ��search��������鿼���Ƿ��Ѵ�����ϵͳ��
                if (!ExamStudentSystem.search(num)) {
                    cout << "���󣺿����Ѵ��ڣ���ӵ�" << i + 1 << "����������" << endl;
                }
                else {
                    break;
                }
            }
            else {
                cout << "���벻����Ҫ����ӵ�" << i + 1 << "����������" << endl;
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
//Ŀ¼
void MainMenu(ExamSystem& examSystem) {
    int choice;
    while (1) {
        cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������" << endl;
        cout << "��ѡ����Ҫ���еĲ�����";

        while (1) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "����number����Ϊ���֣�����������" << endl;
            }
            else {
                if (choice >= 0 && choice <= 5) {
                    break;
                }
                else {
                    cout << "����choice�����涨��Χ������������" << endl;
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