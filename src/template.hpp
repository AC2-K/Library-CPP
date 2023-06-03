#pragma once
#include <bits/stdc++.h>
#define rep(i, N) for (int i = 0; i < (N); i++)
#define all(x) (x).begin(), (x).end()
#define popcount(x) __popcount(x)
using i128 = __int128_t;
using ll = long long;
using ld = long double;
using graph = std::vector<std::vector<int>>;
using P = std::pair<int, int>;
constexpr int inf = 1e9;
constexpr ll infl = 1e18;
constexpr ld eps = 1e-6;
const long double pi = acos(-1);
constexpr uint64_t MOD = 1e9 + 7;
constexpr uint64_t MOD2 = 998244353;
constexpr int dx[] = {1, 0, -1, 0};
constexpr int dy[] = {0, 1, 0, -1};
template <typename T1, typename T2> constexpr inline bool chmax(T1& a, T2 b) {
    return a < b && (a = b, true);
}
template <typename T1, typename T2> constexpr inline bool chmin(T1& a, T2 b) {
    return a > b && (a = b, true);
}