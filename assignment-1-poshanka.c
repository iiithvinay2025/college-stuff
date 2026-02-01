#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

long long dq[1000005];
int l, r, cnt;

bool isempty() {
    return cnt == 0;
}

void pushr(long long num) {
    dq[r++] = num;
    cnt++;
}

void popl() {
    l++;
    cnt--;
}

void popr() {
    r--;
    cnt--;
}

void resetDQ() {
    l = 0;
    r = 0;
    cnt = 0;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        long long k;
        scanf("%d %lld", &n, &k);

        long long arr[n];
        for(int i = 0; i < n; i++) scanf("%lld", &arr[i]);

        long long prefix[n + 1];
        prefix[0] = 0;
        for(int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }

        int ans = INT_MAX;
        resetDQ();

        for(int i = 0; i <= n; i++) {
            while(!isempty() && prefix[i] - prefix[dq[l]] >= k) {
                if(i - dq[l] < ans) ans = i - dq[l];
                popl();
            }

            while(!isempty() && prefix[dq[r - 1]] >= prefix[i]) popr();

            pushr(i);
        }

        if(ans == INT_MAX) printf("-1\n");
        else printf("%d\n", ans);
    }
    return 0;
}
