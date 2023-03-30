#define PROBLEM "https://yukicoder.me/problems/no/3030"
#include"template.hpp"
#include"math/miller.hpp"
int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        uint64_t xi;
        scanf("%lld", &xi);
        printf("%lld ", xi);
        if (prime::miller::is_prime(xi)) {
            puts("1");
        } else {
            puts("0");
        }
    }
}