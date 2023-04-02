---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data-structure/BIT.hpp
    title: Binary Index Tree
  - icon: ':heavy_check_mark:'
    path: data-structure/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/euler_tour.hpp
    title: "EulerTour(\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC)"
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n#line\
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
    \    }\n}; \n#line 1 \"data-structure/sparse_table.hpp\"\n/// @brief Sparse Table\n\
    /// @tparam T \u8981\u7D20\u306E\u578B\n/// @docs docs/data-structure/sparse_table.md\n\
    template<class T>\nclass sparse_table {\n    vector<T> vec;\n    vector<vector<T>>\
    \ table;\n    vector<int> look_up;\npublic:\n    sparse_table(int n) : vec(n)\
    \ {}\n    sparse_table(const vector<T>& vec) : vec(vec) { build(); }\n    void\
    \ set(int p, const T& v) { vec[p] = v; }\n    void build() {\n        int sz =\
    \ vec.size();\n        int log = 0;\n        while ((1 << log) <= sz) {\n    \
    \        log++;\n        }\n        table.assign(log, vector<T>(1 << log));\n\
    \        for (int i = 0; i < sz; i++) {\n            table[0][i] = vec[i];\n \
    \       }\n        for (int i = 1; i < log; i++) {\n            for (int j = 0;\
    \ j + (1 << i) <= (1 << log); j++) {\n                table[i][j] =\n        \
    \            min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);\n       \
    \     }\n        }\n        look_up.resize(sz + 1);\n        for (int i = 2; i\
    \ < look_up.size(); i++) {\n            look_up[i] = look_up[i >> 1] + 1;\n  \
    \      }\n    }\n\n    T prod(int l, int r) {\n        int b = look_up[r - l];\n\
    \        return min(table[b][l], table[b][r - (1 << b)]);\n    }\n};\n#line 2\
    \ \"graph/euler_tour.hpp\"\n\n///@brief EulerTour(\u30AA\u30A4\u30E9\u30FC\u30C4\
    \u30A2\u30FC)\nclass EulerTour {\n\tint n;\n\tgraph g;\n\tvector<int> tour;\n\t\
    vector<int> in, out, depth;\n    sparse_table<pair<int, int>> rmq;\npublic:\n\
    \    EulerTour(int n) :n(n), g(n), in(n, -1), out(n, -1), depth(n, -1), rmq(2\
    \ * n - 1) { tour.reserve(2 * n - 1); }\n\tvoid add_edge(int u, int v) {\n\t\t\
    g[u].emplace_back(v);\n\t\tg[v].emplace_back(u);\n\t}\n    graph get_graph(){return\
    \ g;}\n    vector<int> get_tour(){return tour;}\nprivate:\n    void dfs(int v,\
    \ int p = -1) {\n        in[v] = tour.size();\n        tour.emplace_back(v);\n\
    \        for (const auto& nv : g[v])if (nv != p) {\n            depth[nv] = depth[v]\
    \ + 1;\n            dfs(nv, v);\n            tour.emplace_back(v);\n        }\n\
    \        out[v] = tour.size() - 1;\n    }\npublic:\n    void build(int r = 0)\
    \ {\n        dfs(r);\n        for (int i = 0; i < tour.size(); i++) {\n      \
    \      rmq.set(i, { depth[tour[i]],tour[i] });\n        }\n        rmq.build();\n\
    \    }\n\n    pair<int, int> idx(int v) { return {in[v], out[v]}; }\n    int lca(int\
    \ v, int u) {\n        if (in[v] > in[u] + 1) { swap(u, v); }\n        return\
    \ rmq.prod(in[v], in[u] + 1).second;\n    }\n\n    int dist(int v,int u){\n  \
    \      int p = lca(v, u);\n        return depth[v] + depth[u] - 2 * depth[p];\n\
    \    }\n\n    bool is_in_subtree(int par,int v){return (in[par] <= in[v] && out[v]\
    \ <= out[par]);}\n};\n#line 5 \"test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp\"\
    \nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<ll> a(n);\n    for\
    \ (auto& aa : a) {\n        scanf(\"%lld\", &aa);\n    }\n\n    EulerTour g(n);\n\
    \    for (int i = 0; i < n - 1; i++) {\n        int v, u;\n        scanf(\"%d%d\"\
    , &v, &u);\n        g.add_edge(v, u);\n    }\n    g.build();\n\n    BIT<ll> seg(2\
    \ * n);\n    for (int v = 0; v < n; v++) {\n        auto [in, out] = g.idx(v);\n\
    \        seg.add(in, a[v]);\n        seg.add(out + 1, -a[v]);\n    }\n    while\
    \ (q--) {\n        int t;\n        scanf(\"%d\", &t);\n        if (t == 0) {\n\
    \            int v, x;\n            scanf(\"%d%d\", &v, &x);\n            auto\
    \ [in, out] = g.idx(v);\n            seg.add(in, x);\n            seg.add(out\
    \ + 1, -x);\n        } else {\n            int v, u;\n            scanf(\"%d%d\"\
    , &v, &u);\n            ll ans = 0;\n            int p_in = g.idx(g.lca(v, u)).first;\n\
    \            {\n                ans += seg.sum(p_in, g.idx(v).first + 1);\n  \
    \          }\n            {\n                ans += seg.sum(p_in + 1, g.idx(u).first\
    \ + 1);\n            }\n\n            printf(\"%lld\\n\", ans);\n        }\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    #include\"template.hpp\"\n#include\"data-structure/BIT.hpp\"\n#include\"graph/euler_tour.hpp\"\
    \nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<ll> a(n);\n    for\
    \ (auto& aa : a) {\n        scanf(\"%lld\", &aa);\n    }\n\n    EulerTour g(n);\n\
    \    for (int i = 0; i < n - 1; i++) {\n        int v, u;\n        scanf(\"%d%d\"\
    , &v, &u);\n        g.add_edge(v, u);\n    }\n    g.build();\n\n    BIT<ll> seg(2\
    \ * n);\n    for (int v = 0; v < n; v++) {\n        auto [in, out] = g.idx(v);\n\
    \        seg.add(in, a[v]);\n        seg.add(out + 1, -a[v]);\n    }\n    while\
    \ (q--) {\n        int t;\n        scanf(\"%d\", &t);\n        if (t == 0) {\n\
    \            int v, x;\n            scanf(\"%d%d\", &v, &x);\n            auto\
    \ [in, out] = g.idx(v);\n            seg.add(in, x);\n            seg.add(out\
    \ + 1, -x);\n        } else {\n            int v, u;\n            scanf(\"%d%d\"\
    , &v, &u);\n            ll ans = 0;\n            int p_in = g.idx(g.lca(v, u)).first;\n\
    \            {\n                ans += seg.sum(p_in, g.idx(v).first + 1);\n  \
    \          }\n            {\n                ans += seg.sum(p_in + 1, g.idx(u).first\
    \ + 1);\n            }\n\n            printf(\"%lld\\n\", ans);\n        }\n \
    \   }\n}"
  dependsOn:
  - template.hpp
  - data-structure/BIT.hpp
  - graph/euler_tour.hpp
  - data-structure/sparse_table.hpp
  isVerificationFile: true
  path: test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
  requiredBy: []
  timestamp: '2023-04-02 14:35:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
- /verify/test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp.html
title: test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
---