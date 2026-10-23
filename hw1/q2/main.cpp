#include <iostream>
#include <sstream>

using namespace std;
long long sum = 0;
void  merge(int arr[],int arr_index[], int left, int mid, int right);
void  mergeSort(int arr[], int arr_index[], int left, int right);

void merge(int arr[],int arr_index[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    long long sum_left = 0;
    long L[n1];
    long R[n2];
    long long R_index[n2];
    long  L_index[n1];

    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
        L_index[i] = arr_index[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        R_index[j] = arr_index[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    for (int m = 0; m < n1; m++) {
        sum_left += L_index[m];
    }

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            arr_index[k] = L_index[i];
            sum_left -= L_index[i];
            i++;
        } else {
            if (sum_left < 0) {
                cout << sum_left << endl;
            }
            arr[k] = R[j];
            arr_index[k] = R_index[j];
            long long a = n1 - i;
            long long index = R_index[j] * a;
            //for (int m = i; m < n1; m++) {
            if (index < 0) {
                cout << index << endl;
            }
            sum += index - sum_left;
            //}
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        arr_index[k] = L_index[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        arr_index[k] = R_index[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int arr_index[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr,arr_index, left, mid);
        mergeSort(arr,arr_index, mid + 1, right);

        merge(arr,arr_index, left, mid, right);
    }
}

int main() {
    int n;
    cin >> n;

    int arr[n] , arr_index[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr_index[i] = i;
    }
    mergeSort(arr,arr_index, 0, n - 1);
    cout << sum << endl;

    return 0;

}
