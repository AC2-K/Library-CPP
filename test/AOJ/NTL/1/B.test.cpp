#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B"

#include "template.hpp"
#include "math/mod_pow.hpp"
#line 3 "main.cpp"
int main(){
    int n,m;
    cin>>n>>m;
    cout<<mod_pow(n,m,MOD)<<'\n';
}
