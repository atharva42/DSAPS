#include <iostream>
using namespace std;

const int MOD = 1000000007;

int countPossibilities(int N, int stockPrices[]) {
    int lis[N]= {1};  // Initialize LIS array
    int ways[N]= {1}; // Initialize ways array

    // for (int i = 0; i < N; i++) {
    //     lis[i] = 1;
    //     ways[i] = 1;
    // }

    int maxLIS = 1;

    for (int i = 1; i < N; i++) {
        int maxLISj = 0;
        int freq = 0;

        for (int j = 0; j < i; j++) {
            if (stockPrices[j] <= stockPrices[i]) {
                if (lis[j] > maxLISj) {
                    maxLISj = lis[j];
                }
            }
        }

        lis[i] = maxLISj + 1;

        if (maxLIS < lis[i]) {
            maxLIS = lis[i];
        }

        for (int j = 0; j < i; j++) {
            if (stockPrices[j] <= stockPrices[i] && lis[j] == maxLISj) {
                freq += ways[j];
                freq %= MOD;
            }
        }

        ways[i] = (freq == 0) ? 1 : freq;
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (lis[i] == maxLIS) {
            count += ways[i];
            count %= MOD;
        }
    }

    return count;
}

int main() {
    int N;
    cin >> N;
    int stockPrices[N];

    for (int i = 0; i < N; i++) {
        cin >> stockPrices[i];
    }

    int possibilities = countPossibilities(N, stockPrices);

    cout << possibilities << endl;

    return 0;
}
