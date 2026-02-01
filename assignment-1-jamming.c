#include <stdio.h>
typedef struct {
    int index;
    int start;
    int end;
    int smaller;
    int bigger;
} multiArr;

void mergeStart(multiArr arr[], int left, int middle, int right) {
    int sizeOne = middle - left + 1;
    int sizeTwo = right - middle;
    multiArr arrOne[sizeOne], arrTwo[sizeTwo];
    for(int i = 0; i < sizeOne; i++) arrOne[i] = arr[left + i];
    for(int j = 0; j < sizeTwo; j++) arrTwo[j] = arr[middle + 1 + j];
    int i = 0, j = 0, k = left;
    while(i < sizeOne && j < sizeTwo) {
        if(arrOne[i].start < arrTwo[j].start) arr[k++] = arrOne[i++];
        else arr[k++] = arrTwo[j++];
    }
    while(i < sizeOne) arr[k++] = arrOne[i++];
    while(j < sizeTwo) arr[k++] = arrTwo[j++];
}

void startTimesSort(multiArr arr[], int left, int right) {
    if(left >= right) return;
    int middle = left + (right - left)/2;
    startTimesSort(arr, left, middle);
    startTimesSort(arr, middle + 1, right);
    mergeStart(arr, left, middle, right);
}

void merge(multiArr arr[], int left, int middle, int right) {
    int sizeOne = middle - left + 1;
    int sizeTwo = right - middle;
    multiArr arrOne[sizeOne], arrTwo[sizeTwo];
    for(int i = 0; i < sizeOne; i++) arrOne[i] = arr[left + i];
    for(int j = 0; j < sizeTwo; j++) arrTwo[j] = arr[middle + 1 + j];
    int i = 0, j = 0, k = left;
    int rightCount = 0;
    while(i < sizeOne && j < sizeTwo) {
        if(arrOne[i].end < arrTwo[j].end) {
            arrOne[i].smaller += rightCount;
            arr[k++] = arrOne[i++];
        }
        else {
            arrTwo[j].bigger += (sizeOne - i);
            arr[k++] = arrTwo[j++];
            rightCount++;
        }
    }
    while(i < sizeOne) {
        arrOne[i].smaller += rightCount;
        arr[k++] = arrOne[i++];
    }
    while(j < sizeTwo) {
        arrTwo[j].bigger += (sizeOne - i);
        arr[k++] = arrTwo[j++];
    }
}

void mergeSort(multiArr arr[], int left, int right) {
    if(left >= right) return;
    int middle = left + (right - left)/2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);
    merge(arr, left, middle, right);
}

int main()
{
    int t, n;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%d", &n);
        multiArr arr[n];
        long long score[n];
        for(int j = 0; j < n; j++) {
            scanf("%d", &arr[j].start);
            scanf("%d", &arr[j].end);
            arr[j].smaller = 0;
            arr[j].bigger = 0;
            arr[j].index = j;
        }
        startTimesSort(arr, 0, n - 1);
        mergeSort(arr, 0, n - 1);
        for(int j = 0; j < n; j++) {
            int wins = arr[j].smaller, losses = arr[j].bigger, ties = n - 1 - wins - losses;
            score[arr[j].index] = (2 * wins) + ties;
        }
        for(int j = 0; j < n; j++) printf("%lld ", score[j]);
        printf("\n");
    }
    return 0;
}
