---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data-structure/dsu.hpp
    title: Disjoint Set(Union find)
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
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/yosupo_judge/data_structure/UnionFind.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#line 2 \"template.hpp\"\
    \n#include<bits/stdc++.h>\nusing namespace std;\n#define rep(i, N)  for(int i=0;i<(N);i++)\n\
    #define all(x) (x).begin(),(x).end()\n#define popcount(x) __builtin_popcount(x)\n\
    using i128=__int128_t;\nusing ll = long long;\nusing ld = long double;\nusing\
    \ graph = vector<vector<int>>;\nusing P = pair<int, int>;\nconstexpr int inf =\
    \ 1e9;\nconstexpr ll infl = 1e18;\nconstexpr ld eps = 1e-6;\nconst long double\
    \ pi = acos(-1);\nconstexpr uint64_t MOD = 1e9 + 7;\nconstexpr uint64_t MOD2 =\
    \ 998244353;\nconstexpr int dx[] = { 1,0,-1,0 };\nconstexpr int dy[] = { 0,1,0,-1\
    \ };\ntemplate<class T>static constexpr inline void chmax(T&x,T y){if(x<y)x=y;}\n\
    template<class T>static constexpr inline void chmin(T&x,T y){if(x>y)x=y;}\n#line\
    \ 1 \"data-structure/dsu.hpp\"\n/// @brief Disjoint Set(Union find)\n/// @docs\
    \ docs/data-structure/dsu.md\nclass DSU {\nprivate:\n    vector<int> find, rank;\n\
    public:\n    DSU(int n) : find(n, -1), rank(n, 1) {}\n\n    int root(int x) {\n\
    \        if (find[x] < 0) {\n            return x;\n        }\n        else {\n\
    \            return find[x] = root(find[x]);\n        }\n    }\n    bool same(int\
    \ x, int y) {\n        return root(x) == root(y);\n    }\n\n    int merge(int\
    \ x, int y) {\n        x = root(x), y = root(y);\n        if (x == y) return x;\n\
    \        if (rank[x] < rank[y]) swap(x, y);\n        if (rank[x] == rank[y]) rank[x]++;\
    \ \n        find[x] += find[y];\n        find[y] = x;\n        return x;\n   \
    \ }\n\n    int size(int x) {\n        return -find[root(x)];\n    }\n\n    inline\
    \ int group_size() {\n        int c = 0;\n        for (int v = 0; v < find.size();\
    \ v++) {\n            if (find[v] < 0) {\n                c++;\n            }\n\
    \        }\n        return c;\n    }\n};\n#line 5 \"test/yosupo_judge/data_structure/UnionFind.test.cpp\"\
    \nint main() {\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    DSU dsu(n);\n\
    \    while (q--) {\n        int t, x, y;\n        scanf(\"%d%d%d\", &t, &x, &y);\n\
    \        if (t == 0) {\n            dsu.merge(x, y);\n        }\n        else\
    \ {\n            if (dsu.same(x, y))puts(\"1\");\n            else puts(\"0\"\
    );\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"template.hpp\"\n#include \"data-structure/dsu.hpp\"\nint main() {\n    int\
    \ n, q;\n    scanf(\"%d%d\", &n, &q);\n    DSU dsu(n);\n    while (q--) {\n  \
    \      int t, x, y;\n        scanf(\"%d%d%d\", &t, &x, &y);\n        if (t ==\
    \ 0) {\n            dsu.merge(x, y);\n        }\n        else {\n            if\
    \ (dsu.same(x, y))puts(\"1\");\n            else puts(\"0\");\n        }\n   \
    \ }\n}"
  dependsOn:
  - template.hpp
  - data-structure/dsu.hpp
  isVerificationFile: true
  path: test/yosupo_judge/data_structure/UnionFind.test.cpp
  requiredBy: []
  timestamp: '2023-03-30 16:15:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/data_structure/UnionFind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/data_structure/UnionFind.test.cpp
- /verify/test/yosupo_judge/data_structure/UnionFind.test.cpp.html
title: test/yosupo_judge/data_structure/UnionFind.test.cpp
---