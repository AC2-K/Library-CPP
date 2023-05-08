---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/GRL/1_A.test.cpp
    title: test/AOJ/GRL/1_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/graph/Shortest_Path.test.cpp
    title: test/yosupo_judge/graph/Shortest_Path.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/tree/Tree_Diameter.test.cpp
    title: test/yosupo_judge/tree/Tree_Diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/graph/dijkstra.md
    document_title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
    links: []
  bundledCode: "#line 2 \"src/graph/dijkstra.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\nnamespace\
    \ kyopro {\n\n/**\n * @brief \u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\n*/\n\
    class dijkstra {\n    std::vector<long long> dist;\n    std::vector<int> trace;\n\
    \    const int n;\n    int s;\n    struct edge {\n        const int to;\n    \
    \    const long long cost;\n        constexpr edge(int to, long long cost) : to(to),\
    \ cost(cost) {}\n    };\n\npublic:\n    using graph = std::vector<std::vector<edge>>;\n\
    \nprivate:\n    graph g;\n\npublic:\n    dijkstra(int n) : n(n), g(n) {}\n   \
    \ dijkstra(const graph& g) : n(g.size()), g(g) {}\n    void add_edge(int from,\
    \ int to, long long cost) {\n        assert(0 <= from && from < n);\n        assert(0\
    \ <= to && to < n);\n        assert(cost >= 0);\n        g[from].emplace_back(to,\
    \ cost);\n    }\n    void build(int _s) {\n        assert(0 <= _s && _s < n);\n\
    \        std::swap(s, _s);\n\n        trace.assign(n, -1), dist.assign(n, (long\
    \ long)1e18);\n        std::priority_queue<std::pair<long long, int>,\n      \
    \                      std::vector<std::pair<long long, int>>,\n             \
    \               std::greater<std::pair<long long, int>>>\n            que;\n \
    \       que.emplace(0, s);\n        dist[s] = 0;\n        trace[s] = s;\n    \
    \    while (!que.empty()) {\n            auto [d, v] = que.top();\n          \
    \  que.pop();\n            if (dist[v] != d) {\n                continue;\n  \
    \          }\n\n            for (auto [nv, c] : g[v]) {\n                if (dist[v]\
    \ + c < dist[nv]) {\n                    dist[nv] = dist[v] + c;\n           \
    \         trace[nv] = v;\n                    que.emplace(dist[nv], nv);\n   \
    \             }\n            }\n        }\n    }\n    \n    const std::vector<long\
    \ long>& get_dist() const { return dist; }\n    \n    std::pair<long long, std::vector<int>>\
    \ shortest_path(int to) {\n        assert(0 <= to && to < n);\n        if (dist[to]\
    \ >= (long long)1e18) return {};\n        int cur = to;\n        std::vector<int>\
    \ path;\n        while (cur != trace[cur]) {\n            path.emplace_back(cur);\n\
    \            cur = trace[cur];\n        }\n        path.emplace_back(s);\n   \
    \     std::reverse(path.begin(), path.end());\n        return {dist[to], path};\n\
    \    }\n};\n};  // namespace kyopro\n\n/**\n * @docs docs/graph/dijkstra.md\n\
    */\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <queue>\n\
    #include <utility>\n#include <vector>\nnamespace kyopro {\n\n/**\n * @brief \u30C0\
    \u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\n*/\nclass dijkstra {\n    std::vector<long\
    \ long> dist;\n    std::vector<int> trace;\n    const int n;\n    int s;\n   \
    \ struct edge {\n        const int to;\n        const long long cost;\n      \
    \  constexpr edge(int to, long long cost) : to(to), cost(cost) {}\n    };\n\n\
    public:\n    using graph = std::vector<std::vector<edge>>;\n\nprivate:\n    graph\
    \ g;\n\npublic:\n    dijkstra(int n) : n(n), g(n) {}\n    dijkstra(const graph&\
    \ g) : n(g.size()), g(g) {}\n    void add_edge(int from, int to, long long cost)\
    \ {\n        assert(0 <= from && from < n);\n        assert(0 <= to && to < n);\n\
    \        assert(cost >= 0);\n        g[from].emplace_back(to, cost);\n    }\n\
    \    void build(int _s) {\n        assert(0 <= _s && _s < n);\n        std::swap(s,\
    \ _s);\n\n        trace.assign(n, -1), dist.assign(n, (long long)1e18);\n    \
    \    std::priority_queue<std::pair<long long, int>,\n                        \
    \    std::vector<std::pair<long long, int>>,\n                            std::greater<std::pair<long\
    \ long, int>>>\n            que;\n        que.emplace(0, s);\n        dist[s]\
    \ = 0;\n        trace[s] = s;\n        while (!que.empty()) {\n            auto\
    \ [d, v] = que.top();\n            que.pop();\n            if (dist[v] != d) {\n\
    \                continue;\n            }\n\n            for (auto [nv, c] : g[v])\
    \ {\n                if (dist[v] + c < dist[nv]) {\n                    dist[nv]\
    \ = dist[v] + c;\n                    trace[nv] = v;\n                    que.emplace(dist[nv],\
    \ nv);\n                }\n            }\n        }\n    }\n    \n    const std::vector<long\
    \ long>& get_dist() const { return dist; }\n    \n    std::pair<long long, std::vector<int>>\
    \ shortest_path(int to) {\n        assert(0 <= to && to < n);\n        if (dist[to]\
    \ >= (long long)1e18) return {};\n        int cur = to;\n        std::vector<int>\
    \ path;\n        while (cur != trace[cur]) {\n            path.emplace_back(cur);\n\
    \            cur = trace[cur];\n        }\n        path.emplace_back(s);\n   \
    \     std::reverse(path.begin(), path.end());\n        return {dist[to], path};\n\
    \    }\n};\n};  // namespace kyopro\n\n/**\n * @docs docs/graph/dijkstra.md\n\
    */"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2023-05-08 03:51:35+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/GRL/1_A.test.cpp
  - test/yosupo_judge/graph/Shortest_Path.test.cpp
  - test/yosupo_judge/tree/Tree_Diameter.test.cpp
documentation_of: src/graph/dijkstra.hpp
layout: document
redirect_from:
- /library/src/graph/dijkstra.hpp
- /library/src/graph/dijkstra.hpp.html
title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
---