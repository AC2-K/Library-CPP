---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data-structure/BIT.hpp
    title: Binary Index Tree
  - icon: ':heavy_check_mark:'
    path: template.hpp
    title: template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n#line\
    \ 2 \"template.hpp\"\n#include<bits/stdc++.h>\nusing namespace std;\n#define rep(i,\
    \ N)  for(int i=0;i<(N);i++)\n#define all(x) (x).begin(),(x).end()\n#define popcount(x)\
    \ __builtin_popcount(x)\nusing i128=__int128_t;\nusing ll = long long;\nusing\
    \ ld = long double;\nusing graph = vector<vector<int>>;\nusing P = pair<int, int>;\n\
    constexpr int inf = 1e9;\nconstexpr ll infl = 1e18;\nconstexpr ld eps = 1e-6;\n\
    const long double pi = acos(-1);\nconstexpr uint64_t MOD = 1e9 + 7;\nconstexpr\
    \ uint64_t MOD2 = 998244353;\nconstexpr int dx[] = { 1,0,-1,0 };\nconstexpr int\
    \ dy[] = { 0,1,0,-1 };\ntemplate<class T>static constexpr inline void chmax(T&x,T\
    \ y){if(x<y)x=y;}\ntemplate<class T>static constexpr inline void chmin(T&x,T y){if(x>y)x=y;}\n\
    #line 1 \"data-structure/BIT.hpp\"\n/// @brief Binary Index Tree\n/// @tparam\
    \ T \u8981\u7D20\u306E\u578B\n/// @tparam SumT \"\u548C\u304C\" \u53CE\u307E\u308B\
    \u3088\u3046\u306A\u578B\n/// @docs docs/data-structure/BIT.md\ntemplate<typename\
    \ T,typename SumT = T>\nclass BIT {\n\tvector<SumT> bit;\n\tint n;\npublic:\n\
    \    BIT(int n) :n(n), bit(n + 1, T()) {}\n\tvoid add(int p, const T& w) {\n\t\
    \tp++;\n\t\tfor (int x = p; x <= n; x += x & -x) {\n\t\t\tbit[x] += w;\n\t\t}\n\
    \t}\n\n\tSumT sum(int p)const {\n\t\tT s = 0;\n\n\t\tfor (int x = p; x > 0; x\
    \ -= x & -x) {\n\t\t\ts += bit[x];\n\t\t}\n\t\treturn s;\n\t}\n\n\tSumT sum(int\
    \ l, int r)const {\n\t\treturn sum(r) - sum(l);\n\t}\n\n    \n    int lower_bound(SumT\
    \ w)const {\n        if (w <= 0)return 0;\n\n        int x = 0;\n        int k\
    \ = 1;\n        while (k < n)k <<= 1;\n        for (; k > 0; k >>= 1) {\n    \
    \        if (x + k <= n && bit[x + k] < w) {\n                w -= bit[x + k];\n\
    \                x += k;\n            }\n        }\n\n        return x + 1;\n\
    \    }\n}; \n#line 4 \"test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp\"\
    \nint main() {\n    int n, q;\n    cin >> n >> q;\n    BIT<ll, ll> seg(n);\n \
    \   rep(i,n){\n        int a;\n        scanf(\"%d\", &a);\n        seg.add(i,\
    \ a);\n    }\n\n    while (q--) {\n        int t;\n        scanf(\"%d\", &t);\n\
    \        if (t == 0) {\n            int p, x;\n            scanf(\"%d%d\", &p,\
    \ &x);\n            seg.add(p, x);\n        } else {\n            int l, r;\n\
    \            scanf(\"%d%d\", &l, &r);\n            printf(\"%lld\\n\", seg.sum(l,\
    \ r));\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    #include\"template.hpp\"\n#include\"data-structure/BIT.hpp\"\nint main() {\n \
    \   int n, q;\n    cin >> n >> q;\n    BIT<ll, ll> seg(n);\n    rep(i,n){\n  \
    \      int a;\n        scanf(\"%d\", &a);\n        seg.add(i, a);\n    }\n\n \
    \   while (q--) {\n        int t;\n        scanf(\"%d\", &t);\n        if (t ==\
    \ 0) {\n            int p, x;\n            scanf(\"%d%d\", &p, &x);\n        \
    \    seg.add(p, x);\n        } else {\n            int l, r;\n            scanf(\"\
    %d%d\", &l, &r);\n            printf(\"%lld\\n\", seg.sum(l, r));\n        }\n\
    \    }\n}"
  dependsOn:
  - template.hpp
  - data-structure/BIT.hpp
  isVerificationFile: true
  path: test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp
  requiredBy: []
  timestamp: '2023-04-02 12:04:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp
- /verify/test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp.html
title: test/yosupo_judge/data_structure/Point_Add_Range_Sum_BIT.test.cpp
---