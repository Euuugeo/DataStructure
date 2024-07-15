//2250944 谌乐俊杰//
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
    }//随机生成数

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
    // 选择最后一个元素作为分区点，并将小于分区点的元素移动到左侧，大于分区点的元素移动到右侧
    int partition(long long& exchangeCount, int low, int high) {
        int pivot = data[high]; // 选择最后一个元素作为分区点
        int i = low - 1; // 初始化小于分区点的索引

        // 遍历数组，将小于分区点的元素移到左侧
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                swap(data[i], data[j]);
                exchangeCount++;
            }
        }

        // 将分区点移到正确的位置
        swap(data[i + 1], data[high]);
        exchangeCount++;
        return i + 1;
    }

    // 快速排序主函数
    void quickSort(long long& exchangeCount, int low, int high) {
        if (low < high) {
            // 找到分区点的位置
            int pivotIndex = partition(exchangeCount, low, high);

            // 递归对分区点左侧和右侧的子数组进行排序
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
        // 构建最大堆
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(exchangeCount, n, i);
        }

        // 逐步将最大元素移到数组末尾
        for (int i = n - 1; i > 0; i--) {
            swap(data[0], data[i]);  // 交换堆顶和当前最后一个元素
            ++exchangeCount;
            heapify(exchangeCount, i, 0);    // 重新构建最大堆，排除已排序的部分
        }
    }
    int merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        int comparisons = 0; // 记录比较次数

        // 创建临时数组来存储左右两部分的元素
        int *leftArr=new int [n1];
        int *rightArr=new int [n2];

        // 将数据复制到临时数组 leftArr 和 rightArr 中
        for (int i = 0; i < n1; i++) {
            leftArr[i] = data[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = data[mid + 1 + j];
        }

        // 合并左右两个临时数组到 arr
        int i = 0; // 初始化左数组的索引
        int j = 0; // 初始化右数组的索引
        int k = left; // 初始化合并后数组的索引

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

        // 将左数组中剩余的元素复制到 arr
        while (i < n1) {
            data[k] = leftArr[i];
            i++;
            k++;
        }

        // 将右数组中剩余的元素复制到 arr
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

            // 递归排序左右两部分
            comparisons += mergeSort(left, mid);
            comparisons += mergeSort(mid + 1, right);

            // 合并排序好的左右两部分
            comparisons += merge(left, mid, right);
        }

        return comparisons;
    }
    // 寻找数组中的最大值
    int getMax(int n) {
        int max = data[0];
        // 遍历数组以找到最大值
        for (int i = 1; i < n; i++) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        // 返回最大值
        return max;
    }

    // 对数组按照指定位（exp）进行计数排序
    void countSort(int n, int exp) {
        const int RANGE = 10; // 数字范围（0到9）
        int *output=new int [n]; // 输出数组用于存储排序后的元素
        int count[RANGE] = { 0 }; // 数组用于存储每个数字的出现次数

        // 统计每个数字在指定位（exp）的出现次数
        for (int i = 0; i < n; i++) {
            count[(data[i] / exp) % RANGE]++;
        }

        // 更新计数数组以存储每个数字在输出数组中的实际位置
        for (int i = 1; i < RANGE; i++) {
            count[i] += count[i - 1];
        }

        // 根据计数数组中的位置构建输出数组
        for (int i = n - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % RANGE] - 1] = data[i];
            count[(data[i] / exp) % RANGE]--;
        }

        // 将排序后的元素从输出数组复制回原数组
        for (int i = 0; i < n; i++) {
            data[i] = output[i];
        }
    }

    // 对数组执行基数排序
    void radixSort(long long& exchangeCount, int n) {
        int max = getMax(n); // 寻找数组中的最大值

        // 遍历数字的每个位（exp）
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countSort(n, exp); // 对当前位进行计数排序
        }
    }

};

void menu(int& N) {
    cout << "**             排序算法比较             **" << endl;
    cout << "==========================================" << endl;
    cout << "**             1---冒泡排序             **" << endl;
    cout << "**             2---选择排序             **" << endl;
    cout << "**             3---直接插入排序         **" << endl;
    cout << "**             4---希尔排序             **" << endl;
    cout << "**             5---快速排序             **" << endl;
    cout << "**             6---堆排序               **" << endl;
    cout << "**             7---归并排序             **" << endl;
    cout << "**             8---基数排序             **" << endl;
    cout << "**             9---退出程序             **" << endl;
    cout << "==========================================" << endl;
    while (1) {
        cout << "请输入要产生的随机数的个数：";
        cin >> N;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (N >= 1) {
            break;
        }
        cout << "输入不符合题意，请重新输入" << endl;
    }
}

int main()
{
    srand((unsigned int)time(NULL));
   
    int N;
    int Sort;
    double sortTime = 0;
    long long exchangeCount = 0;
    char sortName[8][20] = { "冒泡排序","选择排序","直接插入排序","希尔排序","快速排序","堆排序","归并排序","基数排序" };
    menu(N);
    while (true) {
        SortCompare SortCompare(N);
        while (1) {
            cout << "请选择排序算法:";
            cin >> Sort;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else if (Sort >= 1&&Sort<=9) {
                break;
            }
            cout << "输入不符合题意，请重新输入" << endl;
        }
        if (Sort == 9) {
            break;
        }

        SortCompare.test(Sort, sortTime, exchangeCount,N);
        cout << sortName[Sort-1] << " 所用时间: " << sortTime << "秒" << endl;

        if (Sort == 7) {
            cout << sortName[Sort-1] << " 比较次数: " << exchangeCount << endl;
        }
        else {
            cout << sortName[Sort-1] << " 交换次数: " << exchangeCount << endl;
        }

        // 重置
        sortTime = 0.0;
        exchangeCount = 0;
    }
    return 0;
}