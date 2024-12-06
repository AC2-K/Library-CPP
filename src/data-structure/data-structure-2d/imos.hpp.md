---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data-structure/data-structure-2d/cumulative-sum.hpp
    title: "\u4E8C\u6B21\u5143\u7D2F\u7A4D\u548C"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/DSL/5_B.test.cpp
    title: test/AOJ/DSL/5_B.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u6B21\u5143imos\u6CD5"
    links: []
  bundledCode: "#line 2 \"src/data-structure/data-structure-2d/cumulative-sum.hpp\"\
    \n#include <vector>\nnamespace kyopro {\ntemplate <typename T> class cumulative_sum_2d\
    \ {\n    std::vector<std::vector<T>> dat;\n    std::vector<std::vector<T>> s;\n\
    \npublic:\n    const int h;\n    const int w;\n\n    cumulative_sum_2d(int h,\
    \ int w)\n        : h(h),\n          w(w),\n          dat(h, std::vector<T>(w,\
    \ T())),\n          s(h + 1, std::vector<T>(w + 1, T())) {}\n    void build()\
    \ {\n        for (int i = 0; i < h; ++i) {\n            for (int j = 0; j < w;\
    \ ++j) {\n                s[i + 1][j + 1] =\n                    s[i][j + 1] +\
    \ s[i + 1][j] - s[i][j] + dat[i][j];\n            }\n        }\n    }\n    T sum(int\
    \ i1, int j1, int i2, int j2) {\n        return s[i2][j2] - s[i1][j2] - s[i2][j1]\
    \ + s[i1][j1];\n    }\n\n    std::vector<T>& operator[](int i) { return dat[i];\
    \ }\n};\n};  // namespace kyopro\n\n/**\n * @brief \u4E8C\u6B21\u5143\u7D2F\u7A4D\
    \u548C\n */\n#line 3 \"src/data-structure/data-structure-2d/imos.hpp\"\nnamespace\
    \ kyopro {\ntemplate <typename T> class imos_2d {\n    cumulative_sum_2d<T> d;\n\
    \npublic:\n    const int h;\n    const int w;\n\n    imos_2d(int h, int w) : h(h),\
    \ w(w), d(h + 1, w + 1) {}\n    void add(int i1, int j1, int i2, int j2, T v)\
    \ {\n        d[i1][j1] += v, d[i2][j2] += v;\n        d[i1][j2] -= v, d[i2][j1]\
    \ -= v;\n    }\n    T at(int i, int j) { return d.sum(0, 0, i + 1, j + 1); }\n\
    \n    void build() { d.build(); }\n};\n};  // namespace kyopro\n\n/**\n * @brief\
    \ \u4E8C\u6B21\u5143imos\u6CD5\n */\n"
  code: "#pragma once\n#include \"../data-structure-2d/cumulative-sum.hpp\"\nnamespace\
    \ kyopro {\ntemplate <typename T> class imos_2d {\n    cumulative_sum_2d<T> d;\n\
    \npublic:\n    const int h;\n    const int w;\n\n    imos_2d(int h, int w) : h(h),\
    \ w(w), d(h + 1, w + 1) {}\n    void add(int i1, int j1, int i2, int j2, T v)\
    \ {\n        d[i1][j1] += v, d[i2][j2] += v;\n        d[i1][j2] -= v, d[i2][j1]\
    \ -= v;\n    }\n    T at(int i, int j) { return d.sum(0, 0, i + 1, j + 1); }\n\
    \n    void build() { d.build(); }\n};\n};  // namespace kyopro\n\n/**\n * @brief\
    \ \u4E8C\u6B21\u5143imos\u6CD5\n */"
  dependsOn:
  - src/data-structure/data-structure-2d/cumulative-sum.hpp
  isVerificationFile: false
  path: src/data-structure/data-structure-2d/imos.hpp
  requiredBy: []
  timestamp: '2023-10-22 20:25:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/DSL/5_B.test.cpp
documentation_of: src/data-structure/data-structure-2d/imos.hpp
layout: document
redirect_from:
- /library/src/data-structure/data-structure-2d/imos.hpp
- /library/src/data-structure/data-structure-2d/imos.hpp.html
title: "\u4E8C\u6B21\u5143imos\u6CD5"
---