---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/convolution/min_plus_convolution_convex_convex.hpp
    title: Min Plus Convolution(Convex, Convex)
  - icon: ':heavy_check_mark:'
    path: src/internal/type_traits.hpp
    title: src/internal/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: src/stream.hpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B"
  - icon: ':heavy_check_mark:'
    path: src/template.hpp
    title: src/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
  bundledCode: "#line 1 \"test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp\"\
    \n#define PROBLEM \\\n    \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#line 2 \"src/convolution/min_plus_convolution_convex_convex.hpp\"\n#include\
    \ <limits>\n#include <numeric>\n#include <utility>\n#include <vector>\n#line 2\
    \ \"src/internal/type_traits.hpp\"\n#include <iostream>\n#line 5 \"src/internal/type_traits.hpp\"\
    \n#include <typeinfo>\n#include <cstdint>\n\nnamespace kyopro {\nnamespace internal\
    \ {\ntemplate <typename... Args> struct first_enabled {};\n\ntemplate <typename\
    \ T, typename... Args>\nstruct first_enabled<std::enable_if<true, T>, Args...>\
    \ {\n    using type = T;\n};\ntemplate <typename T, typename... Args>\nstruct\
    \ first_enabled<std::enable_if<false, T>, Args...>\n    : first_enabled<Args...>\
    \ {};\ntemplate <typename T, typename... Args> struct first_enabled<T, Args...>\
    \ {\n    using type = T;\n};\n\ntemplate <typename... Args>\nusing first_enabled_t\
    \ = typename first_enabled<Args...>::type;\n\ntemplate <int dgt, std::enable_if_t<dgt\
    \ <= 128>* = nullptr> struct int_least {\n    using type = first_enabled_t<std::enable_if<dgt\
    \ <= 8, std::int8_t>,\n                                 std::enable_if<dgt <=\
    \ 16, std::int16_t>,\n                                 std::enable_if<dgt <= 32,\
    \ std::int32_t>,\n                                 std::enable_if<dgt <= 64, std::int64_t>,\n\
    \                                 std::enable_if<dgt <= 128, __int128_t>>;\n};\n\
    \ntemplate <int dgt, std::enable_if_t<dgt <= 128>* = nullptr> struct uint_least\
    \ {\n    using type = first_enabled_t<std::enable_if<dgt <= 8, std::uint8_t>,\n\
    \                                 std::enable_if<dgt <= 16, std::uint16_t>,\n\
    \                                 std::enable_if<dgt <= 32, std::uint32_t>,\n\
    \                                 std::enable_if<dgt <= 64, std::uint64_t>,\n\
    \                                 std::enable_if<dgt <= 128, __uint128_t>>;\n\
    };\n\ntemplate <int dgt> using int_least_t = typename int_least<dgt>::type;\n\
    template <int dgt> using uint_least_t = typename uint_least<dgt>::type;\n\ntemplate\
    \ <typename T>\nusing double_size_uint_t = uint_least_t<2 * std::numeric_limits<T>::digits>;\n\
    \ntemplate <typename T>\nusing double_size_int_t = int_least_t<2 * std::numeric_limits<T>::digits>;\n\
    \nstruct modint_base {};\ntemplate <typename T> using is_modint = std::is_base_of<modint_base,\
    \ T>;\ntemplate <typename T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    \n\n// is_integral\ntemplate <typename T>\nusing is_integral_t =\n    std::enable_if_t<std::is_integral_v<T>\
    \ || std::is_same_v<T, __int128_t> ||\n                   std::is_same_v<T, __uint128_t>>;\n\
    };  // namespace internal\n};  // namespace kyopro\n\n/*\n * @ref https://qiita.com/kazatsuyu/items/f8c3b304e7f8b35263d8\n\
    \ */\n#line 7 \"src/convolution/min_plus_convolution_convex_convex.hpp\"\n\nnamespace\
    \ kyopro {\ntemplate <typename T>\nstd::vector<T> min_plus_convolution_convex_convex(const\
    \ std::vector<T>& a,\n                                                  std::vector<T>&\
    \ b) {\n    constexpr T INF = std::numeric_limits<T>::max() / 2;\n    const int\
    \ n = a.size();\n    const int m = b.size();\n    const T A0 = INF;\n    const\
    \ T B0 = INF;\n\n    std::vector<T> da(n);\n    std::vector<T> db(m);\n    for\
    \ (int i = 1; i < n; ++i) da[i] = a[i] - a[i - 1];\n    for (int i = 1; i < m;\
    \ ++i) db[i] = b[i] - b[i - 1];\n    da[0] = a[0] - INF, db[0] = b[0] - INF;\n\
    \n    std::vector<T> ds;\n    ds.reserve(da.size() + db.size());\n    for (int\
    \ ia = 0, ib = 0; ia < n || ib < m;) {\n        if (ia == (int)da.size()) {\n\
    \            ds.emplace_back(db[ib++]);\n        } else if (ib == m) {\n     \
    \       ds.emplace_back(da[ia++]);\n        } else {\n            if (da[ia] >\
    \ db[ib]) {\n                ds.emplace_back(db[ib++]);\n            } else {\n\
    \                ds.emplace_back(da[ia++]);\n            }\n        }\n    }\n\
    \n    std::vector<T> res(n + m - 1);\n    T sum = ds[0];\n    for (int k = 1;\
    \ k < (int)ds.size(); ++k) {\n        sum += ds[k];\n        res[k - 1] = sum\
    \ + A0 + B0;\n    }\n    return res;\n}\n};  // namespace kyopro\n\n/**\n * @brief\
    \ Min Plus Convolution(Convex, Convex)\n */\n#line 2 \"src/stream.hpp\"\n#include\
    \ <ctype.h>\n#include <stdio.h>\n#include <string>\n#line 6 \"src/stream.hpp\"\
    \n\nnamespace kyopro {\n\ninline void single_read(char& c) {\n    c = getchar_unlocked();\n\
    \    while (isspace(c)) c = getchar_unlocked();\n}\ntemplate <typename T, internal::is_integral_t<T>*\
    \ = nullptr>\ninline void single_read(T& a) {\n    a = 0;\n    bool is_negative\
    \ = false;\n    char c = getchar_unlocked();\n    while (isspace(c)) {\n     \
    \   c = getchar_unlocked();\n    }\n    if (c == '-') is_negative = true, c =\
    \ getchar_unlocked();\n    while (isdigit(c)) {\n        a = 10 * a + (c - '0');\n\
    \        c = getchar_unlocked();\n    }\n    if (is_negative) a *= -1;\n}\ntemplate\
    \ <typename T, internal::is_modint_t<T>* = nullptr>\ninline void single_read(T&\
    \ a) {\n    long long x;\n    single_read(x);\n    a = T(x);\n}\ninline void single_read(std::string&\
    \ str) noexcept {\n    char c = getchar_unlocked();\n    while (isspace(c)) c\
    \ = getchar_unlocked();\n    while (!isspace(c)) {\n        str += c;\n      \
    \  c = getchar_unlocked();\n    }\n}\ntemplate<typename T>\ninline void read(T&\
    \ x) noexcept {single_read(x);}\ntemplate <typename Head, typename... Tail>\n\
    inline void read(Head& head, Tail&... tail) noexcept {\n    single_read(head),\
    \ read(tail...);\n}\n\ninline void single_write(char c) noexcept { putchar_unlocked(c);\
    \ }\ntemplate <typename T, internal::is_integral_t<T>* = nullptr>\ninline void\
    \ single_write(T a) noexcept {\n    if (!a) {\n        putchar_unlocked('0');\n\
    \        return;\n    }\n    if constexpr (std::is_signed_v<T>) {\n        if\
    \ (a < 0) putchar_unlocked('-'), a *= -1;\n    }\n    constexpr int d = std::numeric_limits<T>::digits10;\n\
    \    char s[d + 1];\n    int now = d + 1;\n    while (a) {\n        s[--now] =\
    \ (char)'0' + a % 10;\n        a /= 10;\n    }\n    while (now <= d) putchar_unlocked(s[now++]);\n\
    }\ntemplate <typename T, internal::is_modint_t<T>* = nullptr>\ninline void single_write(T\
    \ a) noexcept {\n    single_write(a.val());\n}\ninline void single_write(const\
    \ std::string& str) noexcept {\n    for (auto c : str) {\n        putchar_unlocked(c);\n\
    \    }\n}\ntemplate <typename T> inline void write(T x) noexcept { single_write(x);\
    \ }\ntemplate <typename Head, typename... Tail>\ninline void write(Head head,\
    \ Tail... tail) noexcept {\n    single_write(head);\n    putchar_unlocked(' ');\n\
    \    write(tail...);\n}\ntemplate <typename... Args> inline void put(Args... x)\
    \ noexcept {\n    write(x...);\n    putchar_unlocked('\\n');\n}\n};  // namespace\
    \ kyopro\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B\n */\n#line 2 \"src/template.hpp\"\
    \n#include <bits/stdc++.h>\n#define rep(i, n) for (int i = 0; i < (n); i++)\n\
    #define all(x) std::begin(x), std::end(x)\n#define popcount(x) __builtin_popcountll(x)\n\
    using i128 = __int128_t;\nusing ll = long long;\nusing ld = long double;\nusing\
    \ graph = std::vector<std::vector<int>>;\nusing P = std::pair<int, int>;\nconstexpr\
    \ int inf = std::numeric_limits<int>::max() / 2;\nconstexpr ll infl = std::numeric_limits<ll>::max()\
    \ / 2;\nconst long double pi = acosl(-1);\nconstexpr uint64_t MOD = 1e9 + 7;\n\
    constexpr uint64_t MOD2 = 998244353;\nconstexpr int dx[] = {1, 0, -1, 0, 1, -1,\
    \ -1, 1, 0};\nconstexpr int dy[] = {0, 1, 0, -1, 1, 1, -1, -1, 0};\ntemplate <typename\
    \ T1, typename T2> constexpr inline bool chmax(T1& a, T2 b) {\n    return a <\
    \ b && (a = b, true);\n}\ntemplate <typename T1, typename T2> constexpr inline\
    \ bool chmin(T1& a, T2 b) {\n    return a > b && (a = b, true);\n}\n#line 7 \"\
    test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp\"\
    \n\nusing namespace std;\nusing namespace kyopro;\n\nint main() {\n    int n,\
    \ m;\n    read(n, m);\n    vector a(n, 0LL), b(m, 0LL);\n    rep(i, n) read(a[i]);\n\
    \    rep(i, m) read(b[i]);\n    vector c = min_plus_convolution_convex_convex(a,\
    \ b);\n    rep(i, n + m - 1) put(c[i]);\n}\n"
  code: "#define PROBLEM \\\n    \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#include \"../../../src/convolution/min_plus_convolution_convex_convex.hpp\"\
    \n#include \"../../../src/stream.hpp\"\n#include \"../../../src/template.hpp\"\
    \n\nusing namespace std;\nusing namespace kyopro;\n\nint main() {\n    int n,\
    \ m;\n    read(n, m);\n    vector a(n, 0LL), b(m, 0LL);\n    rep(i, n) read(a[i]);\n\
    \    rep(i, m) read(b[i]);\n    vector c = min_plus_convolution_convex_convex(a,\
    \ b);\n    rep(i, n + m - 1) put(c[i]);\n}"
  dependsOn:
  - src/convolution/min_plus_convolution_convex_convex.hpp
  - src/internal/type_traits.hpp
  - src/stream.hpp
  - src/template.hpp
  isVerificationFile: true
  path: test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
  requiredBy: []
  timestamp: '2023-12-09 01:32:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
- /verify/test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp.html
title: test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
---