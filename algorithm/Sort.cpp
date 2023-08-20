//
// Created by yangzilong on 2022/7/6.
//

#include "Sort.h"

void PrintArray(int* arr, int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void InsertSort(int* arr , int n, int source_overload) {
    // n是数组元素的个数
    for(int i = 1; i < n; ++i) {
        int num = *(arr+i);
        for(int j = i-1; j >=0; j--) {
            if(*(arr+j) > num) {
                *(arr+j+1) = *(arr+j);
                if(j == 0) {
                    arr[0] = num;
                    break;
                }
            }
            else {
                *(arr+j+1) = num;
                break;  // 表示此趟排序结束
            }
        }
    }
}

// 直接插入排序
void InsertSort(int arr[], int n)
{
    if(n == 0) {
        return;
    }
    int current = 0;
    for(int i = 0; i < n - 1; ++i) {
        current = arr[i + 1];     // 要插入的新元素，且[0, i]是有序序列
        int preIndex = i;   // 从preIndex处开始向前扫描
        while(preIndex >= 0 && arr[preIndex] > current) {
            arr[preIndex + 1] = arr[preIndex];
            --preIndex;
        }
        arr[preIndex + 1] = current;
    }
// 23819
//    for(int i = 1; i < n; ++i) {
//        int newNum = arr[i];
//        // i下标是新元素，在[0,i-1]下标中进行从后向前的扫描，找到合适的位置进行插入
//        for(int j = i - 1; j >= 0; --j) {
//            if(arr[j] > newNum) {
//                arr[j + 1] = arr[j];  // 当第一次比较时，这里直接他妈的把新要插入的元素覆盖了
//                if(j == 0) {
//                    arr[0] = newNum;    // 直接将新元素插入到0下标处
//                }
//            }
//            else {
//                arr[j + 1] = newNum;   // 新元素插入到合适的位置
//                break;
//            }
//        }
//    }
////////
//    for(int i = 0; i < n-1; ++i)
//    {
//        int end = i; // [0,end] 为有序数组
//        int tmp = arr[end+1];  // 将下标为end+1的元素插入到前面的数组中
//        while(end>=0)
//        {
//            if(tmp < arr[end])
//            {
//                arr[end+1] = arr[end];
//            }
//            else
//            {
//                break;
//            }
//            end--;
//        }
//        arr[end+1] = tmp;
//    }
}

// new23819
void ShellSort(int *arr, int n) {
    int current = 0;   // 存储每次要新插入的元素
    int gap = n / 2;   // 增量：每隔gap的元素分为一组，一组内进行直接插入排序~
    while(gap > 0) {
        // 下面的for循环是一次的，对所有分组进行直接插入排序
        for(int i = gap; i < n; ++i) {
            current = arr[i];    // 此时要插入的新元素
            int preIndex = i - gap;
            while(preIndex >= 0 && arr[preIndex] > current) {
                arr[preIndex + gap] = arr[preIndex];
                preIndex -= gap;
            }
            arr[preIndex + gap] = current;
        }
        gap /= 2;   // 减小缩量~
    }
}

// old，懒得看了，写的很丑
//void ShellSort(int* arr,int n, int source_overload)
//{
//    int gap = 3;
//    while(gap>=1){
//        for(int j = 0; j < gap; ++j) {
//            // 这是一次全排序，间距为gap
//            for (int i = j; i <= n - gap - 1; i+=gap) {
//                int end = i;
//                int tmp = arr[i + gap];
//                while (end >= 0) {
//                    if (tmp < arr[end]) {
//                        arr[end + gap] = arr[end];
//                    } else {
//                        break;
//                    }
//                    end -= gap;
//                }
//                arr[end + gap] = tmp;
//            }
//        }
//        gap -= 1;
//    }
//}
//void ShellSort(int* arr,int n)
//{
//    // 主要是针对数据量大的时候。
//    int gap = n;
//    // gap>1时为预排序，gap==1时为直接插入排序。
//    while(gap > 1){
//        gap = gap / 3 + 1;
//        // 这是一次全排序，间距为gap，当gap变为1时，就是直接插入排序了。结果为完全有序。
//        for(int i = 0; i <= n-gap-1; ++i) {
//            int end = i;
//            int tmp = arr[i+gap];
//            while(end >= 0) {
//                if(tmp < arr[end]) {
//                    arr[end + gap] = arr[end];
//                }else{
//                    break;
//                }
//                end-=gap;
//            }
//            arr[end+gap] = tmp;
//        }
//    }
//}
void SelectSort(int* arr, int n) {
    // 直接选择排序
    // 选择n-1次即可，最后只剩一个元素是不需要
    for(int i = 0; i < n; ++i) {
        int minIndex = i;
        for(int j = i; j < n; ++j) {   // 从[i, n-1]选择
            if(arr[j] < arr[minIndex])  minIndex = j;
        }
        // minIndex是[i, n-1]里面最小的元素的下标
        if(i != minIndex)
            std::swap(arr[minIndex], arr[i]);
    }
}

//void SelectSort(int* arr, int n) {
//    int left = 0, right = n-1;
//    while(left < right) {
//        int min = left;
//        int max = left;
//        for(int i = left+1; i <= right; ++i) {
//            if(arr[i] < arr[min]) min = i;
//            if(arr[i] > arr[max]) max = i;
//        }
//        swap(arr[left],arr[min]);
//        // 如果left和max重叠，则需要修正 防止情况 9 1 6 6 6 6 6
//        if(max == left) {
//            max = min;
//        }
//        swap(arr[right],arr[max]);
//        left++;
//        right--;
//    }
//}

// 23819
void BubbleSort(int* arr, int n) {
    // 外层for是次数，一共n-1次冒泡即可
    for(int i = 0; i < n - 1; ++i) {
        bool flag = false;
        // ↓ 一次冒泡
        for(int j = 0; j < n - 1 - i; ++j) {
            if(arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if(!flag) break;
    }
}

//void BubbleSort(int* arr, int n) {
//    for(int i = 0; i < n-1; i++) {
//        bool flag = true;
//        for(int j = 0; j < n-1-i; j++) {
//            if(arr[j] > arr[j+1]) {
//                swap(arr[j], arr[j+1]);
//                flag = false;
//            }
//        }
//        if(flag) {
//            break;
//        }
//    }
//}
// 我们选择的枢纽是begin位置，所以下方函数使得begin，mid，end三处最终begin为中间值
void optimize(int *arr, int begin, int end) {
    int mid = ((end - begin) >> 1) + begin;
    if(arr[mid] > arr[end]) {
        std::swap(arr[mid], arr[end]);
    }
    if(arr[begin] < arr[mid]) {
        std::swap(arr[begin], arr[mid]);
    }
    if(arr[begin] > arr[end]) {
        std::swap(arr[begin], arr[end]);
    }
}
//  Hoare 版本
void QuickSortHoare(int* arr, int begin, int end) {  // [begin, end]
    if(end - begin <= 12) {
        return InsertSort(arr + begin, end - begin + 1);
    }
    optimize(arr, begin, end);   // 调用之后begin下标处的值为中间值，优化
    int left = begin;
    int right = end;
    int keyIndex = begin;  // 设置下标是因为后面要交换数据
    while(left < right) {
        // 右边找小
        while(left < right && arr[right] >= arr[keyIndex]) {
            right--;
        }
        // 左边找大
        while(left < right && arr[left] <= arr[keyIndex]) {
            left++;
        }
        // 这里不管是否left<right都交换，等于也无妨。
        swap(arr[left], arr[right]);
    }
    // 这里出循环之后，一定符合left == right。
    swap(arr[keyIndex],arr[left]);
    // 单趟排序结束，此时left下标处的值为枢纽值，左边小于它，右边大于它
    // [begin, left-1] left [left+1, end]
    if(left - 1 > begin)
        QuickSortHoare(arr,begin,left-1);
    if(left + 1 < end)
        QuickSortHoare(arr,left+1,end);
}
// 挖坑法  真的很简单啊....
void QuickSortPit(int* arr,int begin, int end) { // [begin, end]
    int left = begin, right = end;  // left和right为范围，因为最后还要使用begin和end进行递归。
    int key = arr[left];  // arr[key] 保存元素值而不是下标是因为left下标的值会被改变。单趟排序的最后要把这个元素值放入最后一个坑中。
    while(left < right) {
        // 右边找小，填入坑中
        while(left < right && arr[right] >= key) {
            right--;
        }
        arr[left] = arr[right];
        // 左边找大， 填入坑中
        while(left < right && arr[left] <= key) {
            left++;
        }
        arr[right] = arr[left];
    }
    arr[left] = key; // 这个时候其实left right都是一样的。
    // 下面的left就是最终的key值所在位置。
    if(left-1>begin)
        QuickSortPit(arr,begin,left-1);
    if(left+1<end)
        QuickSortPit(arr,left+1,end);
}
int GetMiddleIndex(int* arr, int begin, int end) { // 注意，写的是左闭右闭的版本 [begin,end]
    int mid = (begin+end)/2;
    if(arr[begin] < arr[end]) {
        if(arr[mid] < arr[begin]) {
            return begin;
        }else if(arr[end] < arr[mid]) {
            return end;
        }else {
            return mid;
        }
    }else {
        if(arr[begin] < arr[mid]) {
            return begin;
        }else if(arr[end] > arr[mid]) {
            return end;
        }else {
            return mid;
        }
    }
}
// 前后指针法
void QuickSortPtr(int* arr, int begin, int end) {  // [begin, end]
    if(end - begin > 12) {
        int prev = begin;
        int cur = begin + 1;
        // 三数取中
        int mid = GetMiddleIndex(arr, begin, end);
        swap(arr[mid], arr[begin]);
        // 三数取中结束
        int keyIndex = begin; // 这里保存下标而不是元素值，是因为最后要进行一次交换操作。
        while (cur <= end) {
            // 前方为真才++prev。
//            if (arr[cur] < arr[keyIndex] && ++prev != cur) {
//                swap(arr[prev], arr[cur]);
//            }
            if(arr[cur] < arr[keyIndex]) {
                ++prev;
                swap(arr[cur], arr[prev]);
            }
            // 小于key值，就处理。处理完移动cur
            // 不小于key值，直接移动cur。
            ++cur;
        }
        swap(arr[keyIndex], arr[prev]);
        // 此时prev就是那个分割线，并且这是一种前闭后开的形式
        if (prev - 1 > begin) {
            QuickSortPtr(arr, begin, prev-1);
        }
        if (prev + 1 < end) {
            QuickSortPtr(arr, prev + 1, end);
        }
    }else {
        InsertSort(arr+begin, end-begin+1);
    }
}

// 23820
// 快排改非递归用循环很难，可以在堆上创建数据结构：栈 来模拟递归过程。(因为堆很大
void QuickSortNoRecursionStack(int* arr, int begin, int end)  // recursion  [begin, end]
{
    stack<int> st;
    st.push(end);
    st.push(begin);
    while(!st.empty()) {
        int bg = st.top(), left = bg;
        st.pop();
        int ed = st.top(), right = ed;
        st.pop();
        optimize(arr, left, right);
        int keyIndex = left;
        while(left < right) {
            while(left < right && arr[right] >= arr[keyIndex]) {
                --right;
            }
            while(left < right && arr[left] <= arr[keyIndex]) {
                ++left;
            }
            std::swap(arr[left], arr[right]);
        }
        std::swap(arr[left], arr[keyIndex]);
        // 单趟排序结束，接下来处理左右子区间，先压右，再压左，先取左，后取右。
        if(left + 1 < ed) {  // [left + 1, ed]
            st.push(ed);
            st.push(left + 1);
        }
        if(left - 1 > bg) {    // [bg, left - 1]
            st.push(left - 1);
            st.push(bg);
        }
    }
}

void QuickSortNoRecursionQueue(int* arr, int begin, int end) {
    queue<int> que;
    que.push(begin);
    que.push(end);
    while(!que.empty()) {
        int bg = que.front(), left = bg;
        que.pop();
        int ed = que.front(), right = ed;
        que.pop();
        optimize(arr, left, right);
        int keyIndex = left;
        while(left < right) {
            while(left < right && arr[right] >= arr[keyIndex]) {
                --right;
            }
            while(left < right && arr[left] <= arr[keyIndex]) {
                ++left;
            }
            std::swap(arr[left], arr[right]);
        }
        std::swap(arr[left], arr[keyIndex]);
        // 单趟排序结束，接下来处理左右子区间
        if(left - 1 > bg) {    // [bg, left - 1]
            que.push(bg);
            que.push(left - 1);
        }
        if(left + 1 < ed) {  // [left + 1, ed]
            que.push(left + 1);
            que.push(ed);
        }
    }
}
// old
// 快排改非递归用循环很难，可以在堆上创建数据结构：栈 来模拟递归过程。(因为堆很大
//void QuickSortNoRecursionStack(int* arr, int begin, int end)  // recursion  [begin, end]
//{
//    stack<int> st;
//    st.push(end);
//    st.push(begin);
//    while(!st.empty()) {
//        int left = st.top();
//        st.pop();
//        int right = st.top();
//        st.pop();
//        // 这里就是一个全新的范围，进行单趟排序即可。
//        int prev = left;
//        int cur = left+1;
//        int mid = GetMiddleIndex(arr,left,right);
//        swap(arr[left], arr[mid]);
//        int keyIndex = left;
//        while(cur <= right) {
//            if(arr[cur] < arr[keyIndex] && ++prev != cur) {
//                swap(arr[prev], arr[cur]);
//            }
//            cur++;
//        }
//        swap(arr[keyIndex], arr[prev]);
//        // 单趟排序结束
//        // [begin, prev-1] prev [prev+1, end]
//        if(prev+1 < right) {
//            st.push(right);
//            st.push(prev+1);
//        }
//        if(prev-1 > left) {
//            st.push(prev-1);
//            st.push(left);
//        }
//    }
//}
//void QuickSortNoRecursionQueue(int* arr, int begin, int end) {
//    queue<int> q;
//    q.push(begin);
//    q.push(end);
//    while(!q.empty()) {
//        int left = q.front();
//        q.pop();
//        int right = q.front();
//        q.pop();
//        int prev = left;
//        int cur = left+1;
//        int mid = GetMiddleIndex(arr,left,right);
//        swap(arr[left], arr[mid]);
//        int keyIndex = left;
//        while(cur <= right) {
//            if(arr[cur] < arr[keyIndex] && ++prev != cur) {
//                swap(arr[prev], arr[cur]);
//            }
//            ++cur;
//        }
//        swap(arr[keyIndex], arr[prev]);
//        // 单趟完成
//        // [left, prev-1] prev [prev+1, right]
//        if(prev-1 > left) {
//            q.push(left);
//            q.push(prev-1);
//        }
//        if(prev+1 < right) {
//            q.push(prev+1);
//            q.push(right);
//        }
//    }
//}
void _MergeSort(int* arr, int begin, int end, int* tmp) { // [begin, end]
    if(begin >= end) { // 保证至少有两个元素，才需要排序。一个即为有序。
        return;
    }
    int mid = (begin+end)/2;
    // 这里的操作是将左右子区间变为有序。
    // [begin, mid] [mid+1, end] 分治递归，让子区间有序。
    _MergeSort(arr, begin, mid, tmp);
    _MergeSort(arr, mid+1, end, tmp);
    // 归并，arr中左右子区间有序了，归并到tmp中对应位置，再拷贝回来。
    int begin1 = begin, end1 = mid;
    int begin2 = mid+1, end2 = end;
    int index = begin;
    while(begin1 <= end1 && begin2 <= end2) {
        if(arr[begin1] < arr[begin2]) {
            tmp[index++] = arr[begin1++];
        }else {
            tmp[index++] = arr[begin2++];
        }
    }
    while(begin1 <= end1) {
        tmp[index++] = arr[begin1++];
    }
    while(begin2 <= end2) {
        tmp[index++] = arr[begin2++];
    }
    // 此时，左右子区间合并到了tmp的对应位置上。再拷贝回arr即可
    memcpy(arr+begin, tmp+begin, (end-begin+1)*sizeof(int));
}

void MergeSort(int* arr, int n) {
    int* tmp = (int*)malloc(n*sizeof(int));
    if(tmp == nullptr) {
        cout<<"MergeSort::malloc fail"<<endl;
        exit(-1);
    }
    _MergeSort(arr, 0, n-1, tmp);
    free(tmp);
}

void MergeSortNoRecursion(int* arr, int n) {
    int* tmp = (int*)malloc(n*sizeof(int));
    if(tmp == nullptr) {
        cout<<"MergeSortNoRecursion::malloc fail"<<endl;
        exit(-1);
    }
    int gap = 1;
    while(gap < n) {
        for(int i = 0; i < n; i += 2 * gap) {  // 2*gap是一组排完序的个数，到下一组了。
            // [i, i+gap-1] [i+gap, i+2*gap-1]  对这两个范围内的数据进行排序。
            // begin1=i不可能越界，只有end1，begin2，end2可能越界。
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;

            //越界检查，修改后其实还是基于下面的归并逻辑以及memcpy的位置。
            if(end1 >= n) {
                end1 = n - 1;
                // 右区域数组改为不存在的范围，从而下面的逻辑就只会把[begin1, end1]拷贝到tmp中
                begin2 = n;
                end2 = n-1;
            }else if(begin2 >= n) {
                // 右区域数组越界，只需要把[begin1, end1]拷贝到tmp中即可。
                begin2 = n;
                end2 = n-1;
            }else if(end2 >= n) {
                // 这种情况，比如一共10个元素，此时gap为8，则表示这是最后一次归并
                // 那么只有end2越界，此时需要归并，只是一个不对称的归并而已
                end2 = n-1;
            }

            // 对[i, i+gap-1] [i+gap, i+2*gap-1]范围内进行归并
            int index = begin1;
            while (begin1 <= end1 && begin2 <= end2) {
                if (arr[begin1] < arr[begin2]) {
                    tmp[index++] = arr[begin1++];
                } else {
                    tmp[index++] = arr[begin2++];
                }
            }
            while(begin1 <= end1) {
                tmp[index++] = arr[begin1++];
            }
            while(begin2 <= end2) {
                tmp[index++] = arr[begin2++];
            }
        }
        // 全部归并完，再全部拷贝回去。
        memcpy(arr, tmp, n*sizeof(int));
        gap *= 2;
    }
    free(tmp);
}

void MergeSortNoRecursion2(int* arr, int n) {
    int* tmp = (int*)malloc(n*sizeof(int));
    if(tmp == nullptr) {
        cout<<"MergeSortNoRecursion::malloc fail"<<endl;
        exit(-1);
    }
    int gap = 1;
    while(gap < n) {
        for(int i = 0; i < n; i += 2 * gap) {  // 2*gap是一组排完序的个数，到下一组了。
            // [i, i+gap-1] [i+gap, i+2*gap-1]  对这两个范围内的数据进行排序。
            // begin1=i不可能越界，只有end1，begin2，end2可能越界。
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;

            //越界检查，修改后其实还是基于下面的归并逻辑以及memcpy的位置。
            if(end1 >= n) {
                break;
            }else if(begin2 >= n) {
                break;
            }else if(end2 >= n) {
                // 这种情况，比如一共10个元素，此时gap为8，则表示这是最后一次归并
                // 那么只有end2越界，此时需要归并，只是一个不对称的归并而已
                end2 = n-1;
            }
            int copyNum = end2 - begin1 + 1;
            // 对[i, i+gap-1] [i+gap, i+2*gap-1]范围内进行归并
            int index = begin1;
            while (begin1 <= end1 && begin2 <= end2) {
                if (arr[begin1] < arr[begin2]) {
                    tmp[index++] = arr[begin1++];
                } else {
                    tmp[index++] = arr[begin2++];
                }
            }
            while(begin1 <= end1) {
                tmp[index++] = arr[begin1++];
            }
            while(begin2 <= end2) {
                tmp[index++] = arr[begin2++];
            }
            memcpy(arr+i, tmp+i, copyNum*sizeof(int));
        }
        // 全部归并完，再全部拷贝回去。
        gap *= 2;
    }
    free(tmp);
}

// 时间复杂度：O(Max(Range, N))
// 空间复杂度：O(Range);
void CountSort(int* arr, int n) {
    int min = arr[0];
    int max = arr[0];
    for(int i = 0; i < n; ++i) {
        if(arr[i] < min) {
            min = arr[i];
        }
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    int num = max - min + 1;
    int* count = (int*)malloc(sizeof(int) * num);

    for(int i = 0; i < num; ++i) {
        count[i] = 0;
    }
    for(int i = 0; i < n; ++i) {
        count[arr[i]-min]++;
    }
    int index = 0;
    for(int i = 0; i < num; ++i) {
        while(count[i]--) {
            arr[index++] = i+min;  // !!!!
        }
    }
}