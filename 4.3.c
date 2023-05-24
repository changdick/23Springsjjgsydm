#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000
long long ans = 0;
long long merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long count = 0;
    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += (mid - i);
        }
    }
    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    return count;
}

long long merge_sort_and_count(int arr[], int temp[], int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        count += merge_sort_and_count(arr, temp, left, mid);
        count += merge_sort_and_count(arr, temp, mid + 1, right);
        count += merge_and_count(arr, temp, left, mid + 1, right);
    }
    return count;
}

long long get_inversions(int arr[], int n) {
    int *temp = (int*)malloc(sizeof(int) * n);
    long long count = merge_sort_and_count(arr, temp, 0, n - 1);
    free(temp);
    return count;
}

int main() {
    int n;
    int arr[MAXSIZE];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    ans = get_inversions(arr, n);
    printf("%lld\n", ans);
    return 0;
}