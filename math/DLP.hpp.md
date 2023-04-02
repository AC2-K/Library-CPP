---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/gcd.hpp
    title: math/gcd.hpp
  - icon: ':heavy_check_mark:'
    path: math/mod_pow.hpp
    title: "mod pow(\u7E70\u308A\u8FD4\u3057\u30CB\u4E57\u6CD5)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
    title: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/math/DLP.md
    document_title: "Discrete Logarithm(\u96E2\u6563\u5BFE\u6570)"
    links: []
  bundledCode: "#line 2 \"math/mod_pow.hpp\"\ntemplate <class T, class U = T>\nconstexpr\
    \ T mod_pow(T base, T exp, T mod){\n    U ans = 1;\n    base %= mod;\n    while\
    \ (exp) {\n        if (exp & 1) {\n            ans *= base;\n            ans %=\
    \ mod;\n        }\n        base *= base;\n        base %= mod;\n        exp >>=\
    \ 1;\n    }\n    return ans;\n}\n///@brief mod pow(\u7E70\u308A\u8FD4\u3057\u30CB\
    \u4E57\u6CD5)\n#line 2 \"math/gcd.hpp\"\ntemplate<typename T>\nconstexpr inline\
    \ T _gcd(T a, T b) {\n    assert(a >= 0 && b >= 0);\n    if (a == 0 || b == 0)\
    \ return a + b;\n    int d = min(__builtin_ctzll(a), __builtin_ctzll(b));\n  \
    \  a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n    while (a != b) {\n\
    \        if (a == 0 || b == 0) {\n            return a + b;\n        }\n     \
    \   if (a > b) {\n            a -= b;\n            a >>= __builtin_ctzll(a);\n\
    \        }else{\n            b -= a;\n            b >>= __builtin_ctzll(b);\n\
    \        }\n    }\n\n    return a << d;\n}\ntemplate<typename T>\nconstexpr inline\
    \ T ext_gcd(T a, T b, T &x, T &y) {\n    x = 1, y = 0;\n    T nx = 0, ny = 1;\n\
    \    while(b) {\n        T q = a / b;\n        tie(a, b) = make_pair(b, a % b);\n\
    \        tie(x, nx) = make_pair(nx, x - nx*q);\n        tie(y, ny) = make_pair(ny,\
    \ y - ny*q);\n    }\n    return a;\n}\n#line 4 \"math/DLP.hpp\"\ninline ll dlp(ll\
    \ x, ll y, ll p) {\n    if (y == 1 || p == 1) {\n        return 0;\n    }\n  \
    \  if (x == 0) {\n        if (y == 0) {\n            return 1;\n        }\n  \
    \      else {\n            return -1;\n        }\n    }\n    ll m = sqrt(p) +\
    \ 1;\n    unordered_map<ll, int> mp;\n    ll xm = mod_pow(x, m, p);\n    ll add\
    \ = 0, g, k = 1 % p;\n    while ((g = _gcd(x, p)) > 1) {\n        if (y == k)return\
    \ add;\n        if (y % g)return -1;\n        y /= g, p /= g, add++;\n       \
    \ k = (k * (x / g)) % p;\n    }\n    ll pr = y;\n    for (int j = 0; j <= m; j++)\
    \ {\n        mp[pr] = j;\n        (pr *= x) %= p;\n    }\n    pr = k;\n    for\
    \ (int i = 1; i <= m; i++) {\n        (pr *= xm) %= p;\n        if (mp.find(pr)\
    \ != mp.end()) {\n            int j = mp[pr];\n            return m * i - j +\
    \ add;\n        }\n    }\n    return -1;\n}\n\n///@brief Discrete Logarithm(\u96E2\
    \u6563\u5BFE\u6570)\n///@docs docs/math/DLP.md\n"
  code: "#pragma once\n#include\"math/mod_pow.hpp\"\n#include\"math/gcd.hpp\"\ninline\
    \ ll dlp(ll x, ll y, ll p) {\n    if (y == 1 || p == 1) {\n        return 0;\n\
    \    }\n    if (x == 0) {\n        if (y == 0) {\n            return 1;\n    \
    \    }\n        else {\n            return -1;\n        }\n    }\n    ll m = sqrt(p)\
    \ + 1;\n    unordered_map<ll, int> mp;\n    ll xm = mod_pow(x, m, p);\n    ll\
    \ add = 0, g, k = 1 % p;\n    while ((g = _gcd(x, p)) > 1) {\n        if (y ==\
    \ k)return add;\n        if (y % g)return -1;\n        y /= g, p /= g, add++;\n\
    \        k = (k * (x / g)) % p;\n    }\n    ll pr = y;\n    for (int j = 0; j\
    \ <= m; j++) {\n        mp[pr] = j;\n        (pr *= x) %= p;\n    }\n    pr =\
    \ k;\n    for (int i = 1; i <= m; i++) {\n        (pr *= xm) %= p;\n        if\
    \ (mp.find(pr) != mp.end()) {\n            int j = mp[pr];\n            return\
    \ m * i - j + add;\n        }\n    }\n    return -1;\n}\n\n///@brief Discrete\
    \ Logarithm(\u96E2\u6563\u5BFE\u6570)\n///@docs docs/math/DLP.md"
  dependsOn:
  - math/mod_pow.hpp
  - math/gcd.hpp
  isVerificationFile: false
  path: math/DLP.hpp
  requiredBy: []
  timestamp: '2023-04-02 12:04:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_judge/math/Discrete_Logarithm.test.cpp
documentation_of: math/DLP.hpp
layout: document
redirect_from:
- /library/math/DLP.hpp
- /library/math/DLP.hpp.html
title: "Discrete Logarithm(\u96E2\u6563\u5BFE\u6570)"
---
## 概要
$x,y,p$に対して、$x^n\equiv y \bmod p$なる最小の**非負整数**$n$を求めます。ただし、存在しない場合は$-1$をreturnします。

## 使い方
```cpp
long long dlp(long long x,long long y,long long p)
```
上のやつを解きます

- 計算量:$O(\sqrt p)$
- 制約:
    - $0\leq x,y <p$
    - $x,y\in\mathbb{Z}$
    - $p\in\mathbb{N}$
    - $0^0=1$と定めている