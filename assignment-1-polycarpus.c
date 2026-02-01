#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
long long stack[1000000];
long long top = -1;
bool isEmpty() {
    return top < 0;
}

void push(int data) {
    if(top > 999998) return;
    top++;
    stack[top] = data;
}

void pop() {
    if(isEmpty()) return;
    top--;
}

long long myTop() {
    if(isEmpty()) return -1;
    return stack[top];
}

void resetStack() {
    top = -1;
}

int main()
{
    long long test, num;
    scanf("%lld", &test);
    for(long long a = 0; a < test; a++) {
        scanf("%lld", &num);
        long long arr[num];
        for(long long b = 0; b < num; b++) {
            scanf("%lld", &arr[b]);
        }
        resetStack();
        long long prevGreater[num];
        long long nextGreater[num];
        long long currMax = 0;
        for(int i = 0; i < num; i++) {
            currMax = 0;
            while(!isEmpty() && arr[i] > arr[myTop()]) {
                if(arr[myTop()] > currMax) currMax = arr[myTop()];
                pop();
            }
            nextGreater[i] = currMax;
            push(i);
        }
        resetStack();
        for(int i = num - 1; i > -1; i--) {
            currMax = 0;
            while(!isEmpty() && arr[i] > arr[myTop()]) {
                if(arr[myTop()] > currMax) currMax = arr[myTop()];
                pop();
            }
            prevGreater[i] = currMax;
            push(i);
        }
        long long maxAns = 0;
        for(int i = 0; i < num; i++) {
            if(nextGreater[i] < 1 || prevGreater[i] < 1) {
                continue;
            } 
            else {
                long long val = (1LL) * arr[i] * (nextGreater[i] + prevGreater[i]);
                if(val > maxAns) maxAns = val;
            }
        }
        printf("%lld\n", maxAns);
        resetStack();
    }
    return 0;
}
