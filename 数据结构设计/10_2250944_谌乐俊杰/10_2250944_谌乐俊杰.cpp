//2250944 ���ֿ���//
#include <iostream>
#include <ctime>
using namespace std;

class SortCompare {
public:
    SortCompare(int arraySize) {
        data = new int[arraySize];
        for (int i = 0; i < arraySize; ++i) {
            data[i] = rand();
        }
    }//���������

    void test(int Sort, double& sortTime, long long& exchangeCount,int N) {
        clock_t start = clock();

        switch (Sort) {
        case 1:
            bubbleSort(exchangeCount,N);
            break;
        case 2:
            chooseSort(exchangeCount,N);
            break;
        case 3:
            insertSort(exchangeCount,N);
            break;
        case 4:
            shellSort(exchangeCount,N);
            break;
        case 5:
            quickSort(exchangeCount,0,N-1);
            break;
        case 6:
            heapSort(exchangeCount,N);
            break;
        case 7:
            exchangeCount=mergeSort(0,N-1);
            break;
        case 8:
            radixSort(exchangeCount,N);
            break;
        default:
            break;
        }

        clock_t end = clock();
        sortTime = (double)(end - start) / CLOCKS_PER_SEC;
    }
private:
    int *data;
    void bubbleSort(long long& exchangeCount,int array_size)
    {
        for (int i = 1; i < array_size; i++) {
            for (int j = 0; j < array_size-i; j++) {
                if (data[j] > data[j + 1]) {
                    int buffer = data[j + 1];
                    data[j + 1] = data[j];
                    data[j] = buffer;
                }
                exchangeCount++;
            }
        }
    }
    void chooseSort(long long& exchangeCount, int array_size) {
        for (int i = 0; i < array_size - 1; i++) {
            int min = i;
            for (int j = i+1; j <array_size; j++) {
                if (data[min] > data[j]) {
                    min = j;
                }
                exchangeCount++;
            }
            if (min != i) {
                swap(data[i], data[min]);
            }
        }
    }
    void insertSort(long long& exchangeCount, int array_size)
    {
        for (int i = 1; i < array_size; i++)
        {
            for (int j = i - 1; j >= 0 && data[j] > data[j + 1]; j--)
            {
                swap(data[j], data[j + 1]);
                exchangeCount++;
            }
        }
    }
    void shellSort(long long& exchangeCount,int array_size) {
        int h = 1;
        while (h < array_size / 3) {
            h = 3 * h + 1;
        }

        while (h >= 1) {
            for (int i = h; i < array_size; ++i) {
                for (int j = i; j - h >= 0 && data[j] < data[j - h]; j -= h) {
                    swap(data[j - h], data[j]);
                    ++exchangeCount;
                }
            }
            h /= 3;
        }
    }
    // ѡ�����һ��Ԫ����Ϊ�����㣬����С�ڷ������Ԫ���ƶ�����࣬���ڷ������Ԫ���ƶ����Ҳ�
    int partition(long long& exchangeCount, int low, int high) {
        int pivot = data[high]; // ѡ�����һ��Ԫ����Ϊ������
        int i = low - 1; // ��ʼ��С�ڷ����������

        // �������飬��С�ڷ������Ԫ���Ƶ����
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                swap(data[i], data[j]);
                exchangeCount++;
            }
        }

        // ���������Ƶ���ȷ��λ��
        swap(data[i + 1], data[high]);
        exchangeCount++;
        return i + 1;
    }

    // ��������������
    void quickSort(long long& exchangeCount, int low, int high) {
        if (low < high) {
            // �ҵ��������λ��
            int pivotIndex = partition(exchangeCount, low, high);

            // �ݹ�Է����������Ҳ���������������
            quickSort(exchangeCount, low, pivotIndex - 1);
            quickSort(exchangeCount, pivotIndex + 1, high);
        }
    }
    void heapify(long long& exchangeCount, int n, int i) {
        int largest = i;
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;

        if (left_child < n && data[left_child] > data[largest]) {
            largest = left_child;
        }

        if (right_child < n && data[right_child] > data[largest]) {
            largest = right_child;
        }

        if (largest != i) {
            swap(data[i], data[largest]);
            ++exchangeCount;
            heapify(exchangeCount, n, largest);
        }
    }

    void heapSort(long long& exchangeCount, int n) {
        // ��������
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(exchangeCount, n, i);
        }

        // �𲽽����Ԫ���Ƶ�����ĩβ
        for (int i = n - 1; i > 0; i--) {
            swap(data[0], data[i]);  // �����Ѷ��͵�ǰ���һ��Ԫ��
            ++exchangeCount;
            heapify(exchangeCount, i, 0);    // ���¹������ѣ��ų�������Ĳ���
        }
    }
    int merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        int comparisons = 0; // ��¼�Ƚϴ���

        // ������ʱ�������洢���������ֵ�Ԫ��
        int *leftArr=new int [n1];
        int *rightArr=new int [n2];

        // �����ݸ��Ƶ���ʱ���� leftArr �� rightArr ��
        for (int i = 0; i < n1; i++) {
            leftArr[i] = data[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = data[mid + 1 + j];
        }

        // �ϲ�����������ʱ���鵽 arr
        int i = 0; // ��ʼ�������������
        int j = 0; // ��ʼ�������������
        int k = left; // ��ʼ���ϲ������������

        while (i < n1 && j < n2) {
            comparisons++;
            if (leftArr[i] <= rightArr[j]) {
                data[k] = leftArr[i];
                i++;
            }
            else {
               data[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // ����������ʣ���Ԫ�ظ��Ƶ� arr
        while (i < n1) {
            data[k] = leftArr[i];
            i++;
            k++;
        }

        // ����������ʣ���Ԫ�ظ��Ƶ� arr
        while (j < n2) {
            data[k] = rightArr[j];
            j++;
            k++;
        }

        return comparisons;
    }

    int mergeSort(int left, int right) {
        int comparisons = 0;

        if (left < right) {
            int mid = left + (right - left) / 2;

            // �ݹ���������������
            comparisons += mergeSort(left, mid);
            comparisons += mergeSort(mid + 1, right);

            // �ϲ�����õ�����������
            comparisons += merge(left, mid, right);
        }

        return comparisons;
    }
    // Ѱ�������е����ֵ
    int getMax(int n) {
        int max = data[0];
        // �����������ҵ����ֵ
        for (int i = 1; i < n; i++) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        // �������ֵ
        return max;
    }

    // �����鰴��ָ��λ��exp�����м�������
    void countSort(int n, int exp) {
        const int RANGE = 10; // ���ַ�Χ��0��9��
        int *output=new int [n]; // ����������ڴ洢������Ԫ��
        int count[RANGE] = { 0 }; // �������ڴ洢ÿ�����ֵĳ��ִ���

        // ͳ��ÿ��������ָ��λ��exp���ĳ��ִ���
        for (int i = 0; i < n; i++) {
            count[(data[i] / exp) % RANGE]++;
        }

        // ���¼��������Դ洢ÿ����������������е�ʵ��λ��
        for (int i = 1; i < RANGE; i++) {
            count[i] += count[i - 1];
        }

        // ���ݼ��������е�λ�ù����������
        for (int i = n - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % RANGE] - 1] = data[i];
            count[(data[i] / exp) % RANGE]--;
        }

        // ��������Ԫ�ش�������鸴�ƻ�ԭ����
        for (int i = 0; i < n; i++) {
            data[i] = output[i];
        }
    }

    // ������ִ�л�������
    void radixSort(long long& exchangeCount, int n) {
        int max = getMax(n); // Ѱ�������е����ֵ

        // �������ֵ�ÿ��λ��exp��
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countSort(n, exp); // �Ե�ǰλ���м�������
        }
    }

};

void menu(int& N) {
    cout << "**             �����㷨�Ƚ�             **" << endl;
    cout << "==========================================" << endl;
    cout << "**             1---ð������             **" << endl;
    cout << "**             2---ѡ������             **" << endl;
    cout << "**             3---ֱ�Ӳ�������         **" << endl;
    cout << "**             4---ϣ������             **" << endl;
    cout << "**             5---��������             **" << endl;
    cout << "**             6---������               **" << endl;
    cout << "**             7---�鲢����             **" << endl;
    cout << "**             8---��������             **" << endl;
    cout << "**             9---�˳�����             **" << endl;
    cout << "==========================================" << endl;
    while (1) {
        cout << "������Ҫ������������ĸ�����";
        cin >> N;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (N >= 1) {
            break;
        }
        cout << "���벻�������⣬����������" << endl;
    }
}

int main()
{
    srand((unsigned int)time(NULL));
   
    int N;
    int Sort;
    double sortTime = 0;
    long long exchangeCount = 0;
    char sortName[8][20] = { "ð������","ѡ������","ֱ�Ӳ�������","ϣ������","��������","������","�鲢����","��������" };
    menu(N);
    while (true) {
        SortCompare SortCompare(N);
        while (1) {
            cout << "��ѡ�������㷨:";
            cin >> Sort;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (Sort >= 1&&Sort<=9) {
                break;
            }
            cout << "���벻�������⣬����������" << endl;
        }
        if (Sort == 9) {
            break;
        }

        SortCompare.test(Sort, sortTime, exchangeCount,N);
        cout << sortName[Sort-1] << " ����ʱ��: " << sortTime << "��" << endl;

        if (Sort == 7) {
            cout << sortName[Sort-1] << " �Ƚϴ���: " << exchangeCount << endl;
        }
        else {
            cout << sortName[Sort-1] << " ��������: " << exchangeCount << endl;
        }

        // ����
        sortTime = 0.0;
        exchangeCount = 0;
    }
    return 0;
}