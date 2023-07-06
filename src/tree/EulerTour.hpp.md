---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data-structure/sparse_table.hpp
    title: SparseTable
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/GRL/5_C.test.cpp
    title: test/AOJ/GRL/5_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
    title: test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Vertex_add_Subtree_Sum.test.cpp
    title: test/yosupo_judge/data_structure/Vertex_add_Subtree_Sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/tree/Lowest_Common_Ancestor_RMQ.test.cpp
    title: test/yosupo_judge/tree/Lowest_Common_Ancestor_RMQ.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/tree/EulerTour.md
    document_title: Euler Tour
    links: []
  bundledCode: "#line 2 \"src/tree/EulerTour.hpp\"\n#include <utility>\n#line 2 \"\
    src/data-structure/sparse_table.hpp\"\n#include <numeric>\n#include <vector>\n\
    namespace kyopro {\n\n/**\n * @brief SparseTable\n */\ntemplate <class T, auto\
    \ op> class sparse_table {\n    std::vector<T> vec;\n    std::vector<std::vector<T>>\
    \ table;\n    std::vector<int> look_up;\n\npublic:\n    constexpr explicit sparse_table(int\
    \ n) : vec(n) {}\n    constexpr explicit sparse_table(const std::vector<T>& vec)\
    \ : vec(vec) {\n        build();\n    }\n    void set(int p, const T& v) { vec[p]\
    \ = v; }\n    void build() {\n        int sz = vec.size();\n        int log =\
    \ 0;\n        while ((1 << log) <= sz) {\n            log++;\n        }\n    \
    \    table.assign(log, std::vector<T>(1 << log));\n        for (int i = 0; i <\
    \ sz; i++) {\n            table[0][i] = vec[i];\n        }\n        for (int i\
    \ = 1; i < log; i++) {\n            for (int j = 0; j + (1 << i) <= (1 << log);\
    \ j++) {\n                table[i][j] =\n                    op(table[i - 1][j],\
    \ table[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n        look_up.resize(sz\
    \ + 1);\n        for (int i = 2; i < (int)look_up.size(); i++) {\n           \
    \ look_up[i] = look_up[i >> 1] + 1;\n        }\n    }\n\n    T fold(int l, int\
    \ r) const {\n        int b = look_up[r - l];\n        return op(table[b][l],\
    \ table[b][r - (1 << b)]);\n    }\n};\n};  // namespace kyopro\n\n/**\n * @docs\
    \ docs/data-structure/sparse_table.md\n */\n#line 4 \"src/tree/EulerTour.hpp\"\
    \nnamespace kyopro {\n\n/**\n * @brief Euler Tour\n */\nclass EulerTour {\n  \
    \  int n;\n    std::vector<std::vector<int>> g;\n    std::vector<int> tour;\n\
    \    std::vector<int> in, out, depth;\n\n    struct get_min_pair {\n        using\
    \ value_t = std::pair<int, int>;\n        static value_t op(value_t x, value_t\
    \ y) { return std::min(x, y); }\n    };\n\n    sparse_table<get_min_pair::value_t,\
    \ get_min_pair::op> rmq;\n\npublic:\n    explicit EulerTour(int n)\n        :\
    \ n(n), g(n), in(n, -1), out(n, -1), depth(n, -1), rmq(2 * n - 1) {\n        tour.reserve(2\
    \ * n - 1);\n    }\n    void add_edge(int u, int v) {\n        g[u].emplace_back(v);\n\
    \        g[v].emplace_back(u);\n    }\n    const std::vector<std::vector<int>>&\
    \ get_graph() const { return g; }\n    const std::vector<int>& get_tour() const\
    \ { return tour; }\n    int get_depth(int v) const { return depth[v]; }\n\n  \
    \  void build(int r = 0) {\n        auto dfs = [&](const auto& self, int v, int\
    \ p) -> void {\n            in[v] = tour.size();\n            tour.emplace_back(v);\n\
    \            for (auto nv : g[v]) {\n                if (nv != p) {\n        \
    \            depth[nv] = depth[v] + 1;\n                    self(self, nv, v);\n\
    \                    tour.emplace_back(v);\n                }\n            }\n\
    \            out[v] = tour.size() - 1;\n        };\n        dfs(dfs, r, -1);\n\
    \        for (int i = 0; i < (int)tour.size(); i++) {\n            rmq.set(i,\
    \ {depth[tour[i]], tour[i]});\n        }\n        rmq.build();\n    }\n\n    std::pair<int,\
    \ int> idx(int v) const { return {in[v], out[v]}; }\n    int lca(int v, int u)\
    \ const {\n        if (in[v] > in[u] + 1) {\n            std::swap(u, v);\n  \
    \      }\n        return rmq.fold(in[v], in[u] + 1).second;\n    }\n\n    int\
    \ dist(int v, int u) const {\n        int p = lca(v, u);\n        return depth[v]\
    \ + depth[u] - 2 * depth[p];\n    }\n\n    bool is_in_subtree(int par, int v)\
    \ const {\n        return (in[par] <= in[v] && out[v] <= out[par]);\n    }\n};\n\
    };  // namespace kyopro\n\n/**\n * @docs docs/tree/EulerTour.md\n */\n"
  code: "#pragma once\n#include <utility>\n#include \"../data-structure/sparse_table.hpp\"\
    \nnamespace kyopro {\n\n/**\n * @brief Euler Tour\n */\nclass EulerTour {\n  \
    \  int n;\n    std::vector<std::vector<int>> g;\n    std::vector<int> tour;\n\
    \    std::vector<int> in, out, depth;\n\n    struct get_min_pair {\n        using\
    \ value_t = std::pair<int, int>;\n        static value_t op(value_t x, value_t\
    \ y) { return std::min(x, y); }\n    };\n\n    sparse_table<get_min_pair::value_t,\
    \ get_min_pair::op> rmq;\n\npublic:\n    explicit EulerTour(int n)\n        :\
    \ n(n), g(n), in(n, -1), out(n, -1), depth(n, -1), rmq(2 * n - 1) {\n        tour.reserve(2\
    \ * n - 1);\n    }\n    void add_edge(int u, int v) {\n        g[u].emplace_back(v);\n\
    \        g[v].emplace_back(u);\n    }\n    const std::vector<std::vector<int>>&\
    \ get_graph() const { return g; }\n    const std::vector<int>& get_tour() const\
    \ { return tour; }\n    int get_depth(int v) const { return depth[v]; }\n\n  \
    \  void build(int r = 0) {\n        auto dfs = [&](const auto& self, int v, int\
    \ p) -> void {\n            in[v] = tour.size();\n            tour.emplace_back(v);\n\
    \            for (auto nv : g[v]) {\n                if (nv != p) {\n        \
    \            depth[nv] = depth[v] + 1;\n                    self(self, nv, v);\n\
    \                    tour.emplace_back(v);\n                }\n            }\n\
    \            out[v] = tour.size() - 1;\n        };\n        dfs(dfs, r, -1);\n\
    \        for (int i = 0; i < (int)tour.size(); i++) {\n            rmq.set(i,\
    \ {depth[tour[i]], tour[i]});\n        }\n        rmq.build();\n    }\n\n    std::pair<int,\
    \ int> idx(int v) const { return {in[v], out[v]}; }\n    int lca(int v, int u)\
    \ const {\n        if (in[v] > in[u] + 1) {\n            std::swap(u, v);\n  \
    \      }\n        return rmq.fold(in[v], in[u] + 1).second;\n    }\n\n    int\
    \ dist(int v, int u) const {\n        int p = lca(v, u);\n        return depth[v]\
    \ + depth[u] - 2 * depth[p];\n    }\n\n    bool is_in_subtree(int par, int v)\
    \ const {\n        return (in[par] <= in[v] && out[v] <= out[par]);\n    }\n};\n\
    };  // namespace kyopro\n\n/**\n * @docs docs/tree/EulerTour.md\n */"
  dependsOn:
  - src/data-structure/sparse_table.hpp
  isVerificationFile: false
  path: src/tree/EulerTour.hpp
  requiredBy: []
  timestamp: '2023-05-15 08:00:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/GRL/5_C.test.cpp
  - test/yosupo_judge/tree/Lowest_Common_Ancestor_RMQ.test.cpp
  - test/yosupo_judge/data_structure/Vertex_Add_Path_Sum.test.cpp
  - test/yosupo_judge/data_structure/Vertex_add_Subtree_Sum.test.cpp
documentation_of: src/tree/EulerTour.hpp
layout: document
redirect_from:
- /library/src/tree/EulerTour.hpp
- /library/src/tree/EulerTour.hpp.html
title: Euler Tour
---
## 概要

EulerTourを扱います。\
EulerTourを使うことで、木に関する様々なクエリを $O(\log n),O(1)$ で処理することが出来ます。\
代表的なものだと

- Lowest Common Ancestor
- 木上の $2$ 頂点間の距離

はクエリごと $O(1)$ で処理できます。これらはメソッドに用意しています。\
また、BITやSegmentTreeと併用することで以下の問題がクエリごと $O(\log n)$ で処理できます。

- [Vertex Add Path Sum](https://judge.yosupo.jp/problem/vertex_add_path_sum)
- [Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)

## コンストラクタ

```cpp
kyopro::EulerTour tour(int n)
```

$n$ 頂点のグラフを生成します。この時点では辺は張られていません。

### 計算量

- $O(n)$

## add_edge

```cpp
void add_edge(int a,int b)
```

$a,b$ の間に無向辺を張ります。

### 制約

- $0\leq a,b < n$

### 計算量

- $O(1)$

## build

```cpp
void build(int r)
```

頂点 $r$ を根として前処理を行います。デフォルトでは頂点 $0$ が根です。

### 制約

- $0\leq r < n$
- **これが呼び出される時点で $T$ は木**

### 計算量

- $O(n\log n)$

## lca

```cpp
int lca(int a,int b)
```

頂点 $a,b$ のLowest Common Ancestor(最小共通祖先)を返します。

### 制約

- $0\leq a,b < n$

### 計算量

- $O(1)$

## dist

```cpp
int dist(int a,int b)
```

頂点 $a,b$ の距離(最短経路長)を返します。

### 制約

- $0\leq a,b < n$

### 計算量

- $O(1)$

## idx

```cpp
std::pair<int,int> idx(int v)
```

EulerTour順に辿ったときの

- 最初に $v$ を訪れる時刻
- $v$ の部分木を抜ける時の時刻

をそれぞれ`first`,`second`に詰めて返します。

### 制約

- $0\leq v < n$

### 計算量

- $O(1)$

## is_in_subtree

```cpp
bool is_in_subtree(int a,int b)
```

$b$ が $a$ の部分木に含まれるか判定します。\
$a=b$ の場合は`true`です。

### 制約

- $0\leq a,b < n$

### 計算量

- $O(1)$