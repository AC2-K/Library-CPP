#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include<iostream>
#include "../../../src/stream.hpp"
#include"../../../src/math/rho.hpp"
int main(){
    int q;
    kyopro::readint(q);
    while (q--) {
        uint64_t x;
        kyopro::readint(x);
        const auto pf = kyopro::rho::factorize(x);
        kyopro::putint(pf.size());
        for (auto p : pf){
            kyopro::putint(p);
        }
    }
}