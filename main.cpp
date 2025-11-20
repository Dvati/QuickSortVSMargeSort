#include <bits/stdc++.h>
#include <ctime>
#include <chrono>

using namespace std;

template<typename T>
using v = vector<T>;

template<typename T>
void quickSort(v<T>& container, int left = 0, int right = -1) {
    if (right == -1) right = container.size() - 1;
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    if (container[mid] < container[left]) swap(container[left], container[mid]);
    if (container[right] < container[left]) swap(container[left], container[right]);
    if (container[right] < container[mid]) swap(container[mid], container[right]);
    
    T pivot = container[mid];
    swap(container[mid], container[right - 1]);
    
    int i = left;
    int j = right - 1;
    
    while (true) {
        while (container[++i] < pivot);
        while (container[--j] > pivot);
        if (i >= j) break;
        swap(container[i], container[j]);
    }
    
    swap(container[i], container[right - 1]);
    
    quickSort(container, left, i - 1);
    quickSort(container, i + 1, right);
}

template<typename T>
void mergeSort(v<T>& container, int left = 0, int right = -1) {
    if (right == -1) right = container.size() - 1;
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    mergeSort(container, left, mid);
    mergeSort(container, mid + 1, right);
    
    v<T> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (container[i] <= container[j]) {
            temp[k++] = container[i++];
        } else {
            temp[k++] = container[j++];
        }
    }
    
    while (i <= mid) temp[k++] = container[i++];
    while (j <= right) temp[k++] = container[j++];
    
    for (int idx = 0; idx < k; idx++) {
        container[left + idx] = temp[idx];
    }
}

int main() {
    srand(time(0));  
    
    int size;
    cout << "array size: ";
    cin >> size;
    
    const int NUM_TESTS = 1000;
    double totalQuickTime = 0.0;
    double totalMergeTime = 0.0;
    
    for (int test = 0; test < NUM_TESTS; test++) {
        v<int> nums(size);
        for (int i = 0; i < size; i++) {
            nums[i] = rand() % 1000 + 1;
        }
        
        v<int> nums1 = nums;
        auto start1 = chrono::high_resolution_clock::now();
        quickSort(nums1);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration1 = end1 - start1;
        totalQuickTime += duration1.count();
        
        v<int> nums2 = nums;
        auto start2 = chrono::high_resolution_clock::now();
        mergeSort(nums2);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration2 = end2 - start2;
        totalMergeTime += duration2.count();
    }
    
    double avgQuickTime = totalQuickTime / NUM_TESTS;
    double avgMergeTime = totalMergeTime / NUM_TESTS;
    
    cout << "\nResults after " << NUM_TESTS << " tests:\n";
    cout << "Average QuickSort time: " << avgQuickTime << " sec" << endl;
    cout << "Average MergeSort time: " << avgMergeTime << " sec" << endl;
    system("pause");
    return 0;
}
