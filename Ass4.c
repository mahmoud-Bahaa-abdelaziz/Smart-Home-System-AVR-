#include <stdio.h>

// Function to calculate factorial
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate nPr
long long nPr(int n, int r) {
    return factorial(n) / factorial(n - r);
}

// Function to calculate nCr
long long nCr(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int main() {
    int n, r;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter r: ");
    scanf("%d", &r);

    if (r > n) {
        printf("Invalid input! r must be <= n\n");
    } else {
        printf("nPr(%d, %d) = %lld\n", n, r, nPr(n, r));
        printf("nCr(%d, %d) = %lld\n", n, r, nCr(n, r));
    }

    return 0;
}
