---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/DSL/2_D_lazy.test.cpp
    title: test/AOJ/DSL/2_D_lazy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/AOJ/DSL/2_E_lazy.test.cpp
    title: test/AOJ/DSL/2_E_lazy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
    title: test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/data-structure/lazy_segtree.md
    document_title: "Segment Tree with Lazy Propagation(\u9045\u5EF6\u8A55\u4FA1\u30BB\
      \u30B0\u30E1\u30F3\u30C8\u6728)"
    links: []
  bundledCode: "#line 2 \"src/data-structure/lazy_segtree.hpp\"\n#include <vector>\n\
    #include <cassert>\nnamespace kyopro {\n/// @brief Segment Tree with Lazy Propagation(\u9045\
    \u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\ntemplate <class S,\n\
    \          class F,\n          S (*op)(S, S),\n          S (*e)(),\n         \
    \ F (*comp)(F, F),\n          F (*id)(),\n          S (*mapping)(S, F)>\nclass\
    \ lazy_segtree {\n    int sz;\n    std::vector<S> dat;\n    std::vector<F> lz;\n\
    \n  public:\n    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}\n\
    \    lazy_segtree(const std::vector<S>& a)\n        : dat(4 * a.size(), e()),\
    \ lz(4 * a.size(), id()) {\n        int x = 1;\n        while (a.size() > x) {\n\
    \            x <<= 1;\n        }\n        sz = x;\n        for (int i = 0; i <\
    \ a.size(); i++) {\n            set(i, a[i]);\n        }\n        build();\n \
    \   }\n\n  public:\n    inline void set(int pos, S x) {\n        assert(0 <= pos\
    \ && pos < sz);\n        dat[pos + sz - 1] = x;\n    }\n    inline void build()\
    \ {\n        for (int i = sz - 2; i >= 0; i--) {\n            dat[i] = op(dat[2\
    \ * i + 1], dat[2 * i + 2]);\n        }\n    }\n\n  private:\n    void eval(int\
    \ pos) {\n        if (lz[pos] == id()) return;\n        if (pos < sz - 1) {\n\
    \            lz[2 * pos + 1] = comp(lz[2 * pos + 1], lz[pos]);\n            lz[2\
    \ * pos + 2] = comp(lz[2 * pos + 2], lz[pos]);\n        }\n        dat[pos] =\
    \ mapping(dat[pos], lz[pos]);\n        lz[pos] = id();\n    }\n\n  private:\n\
    \    void internal_apply(int L, int R, int l, int r, const F& x, int k) {\n  \
    \      eval(k);\n        if (L <= l && r <= R) {\n            lz[k] = comp(lz[k],\
    \ x);\n            eval(k);\n        } else if (L < r && l < R) {\n          \
    \  int mid = (l + r) >> 1;\n            internal_apply(L, R, l, mid, x, 2 * k\
    \ + 1);\n            internal_apply(L, R, mid, r, x, 2 * k + 2);\n           \
    \ dat[k] = op(dat[2 * k + 1], dat[2 * k + 2]);\n        }\n    }\n\n  public:\n\
    \    inline void apply(int l, int r, const F& x) {\n        assert(0 <= l && l\
    \ <= r && r <= sz);\n        internal_apply(l, r, 0, sz, x, 0);\n    }\n\n  private:\n\
    \    S internal_prod(int L, int R, int l, int r, int k) {\n        eval(k);\n\
    \        if (r <= L || R <= l) {\n            return e();\n        } else if (L\
    \ <= l && r <= R) {\n            return dat[k];\n        } else {\n          \
    \  int mid = (l + r) >> 1;\n            S vl = internal_prod(L, R, l, mid, 2 *\
    \ k + 1);\n            S vr = internal_prod(L, R, mid, r, 2 * k + 2);\n      \
    \      return op(vl, vr);\n        }\n    }\n\n  public:\n    inline S prod(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= sz);\n        return internal_prod(l,\
    \ r, 0, sz, 0);\n    }\n\n    inline S operator[](int pos) { return prod(pos,\
    \ pos + 1); }\n};\n};  // namespace kyopro\n\n/// @docs docs/data-structure/lazy_segtree.md\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace kyopro {\n\
    /// @brief Segment Tree with Lazy Propagation(\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728)\ntemplate <class S,\n          class F,\n          S\
    \ (*op)(S, S),\n          S (*e)(),\n          F (*comp)(F, F),\n          F (*id)(),\n\
    \          S (*mapping)(S, F)>\nclass lazy_segtree {\n    int sz;\n    std::vector<S>\
    \ dat;\n    std::vector<F> lz;\n\n  public:\n    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\n    lazy_segtree(const std::vector<S>& a)\n        : dat(4 * a.size(),\
    \ e()), lz(4 * a.size(), id()) {\n        int x = 1;\n        while (a.size()\
    \ > x) {\n            x <<= 1;\n        }\n        sz = x;\n        for (int i\
    \ = 0; i < a.size(); i++) {\n            set(i, a[i]);\n        }\n        build();\n\
    \    }\n\n  public:\n    inline void set(int pos, S x) {\n        assert(0 <=\
    \ pos && pos < sz);\n        dat[pos + sz - 1] = x;\n    }\n    inline void build()\
    \ {\n        for (int i = sz - 2; i >= 0; i--) {\n            dat[i] = op(dat[2\
    \ * i + 1], dat[2 * i + 2]);\n        }\n    }\n\n  private:\n    void eval(int\
    \ pos) {\n        if (lz[pos] == id()) return;\n        if (pos < sz - 1) {\n\
    \            lz[2 * pos + 1] = comp(lz[2 * pos + 1], lz[pos]);\n            lz[2\
    \ * pos + 2] = comp(lz[2 * pos + 2], lz[pos]);\n        }\n        dat[pos] =\
    \ mapping(dat[pos], lz[pos]);\n        lz[pos] = id();\n    }\n\n  private:\n\
    \    void internal_apply(int L, int R, int l, int r, const F& x, int k) {\n  \
    \      eval(k);\n        if (L <= l && r <= R) {\n            lz[k] = comp(lz[k],\
    \ x);\n            eval(k);\n        } else if (L < r && l < R) {\n          \
    \  int mid = (l + r) >> 1;\n            internal_apply(L, R, l, mid, x, 2 * k\
    \ + 1);\n            internal_apply(L, R, mid, r, x, 2 * k + 2);\n           \
    \ dat[k] = op(dat[2 * k + 1], dat[2 * k + 2]);\n        }\n    }\n\n  public:\n\
    \    inline void apply(int l, int r, const F& x) {\n        assert(0 <= l && l\
    \ <= r && r <= sz);\n        internal_apply(l, r, 0, sz, x, 0);\n    }\n\n  private:\n\
    \    S internal_prod(int L, int R, int l, int r, int k) {\n        eval(k);\n\
    \        if (r <= L || R <= l) {\n            return e();\n        } else if (L\
    \ <= l && r <= R) {\n            return dat[k];\n        } else {\n          \
    \  int mid = (l + r) >> 1;\n            S vl = internal_prod(L, R, l, mid, 2 *\
    \ k + 1);\n            S vr = internal_prod(L, R, mid, r, 2 * k + 2);\n      \
    \      return op(vl, vr);\n        }\n    }\n\n  public:\n    inline S prod(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= sz);\n        return internal_prod(l,\
    \ r, 0, sz, 0);\n    }\n\n    inline S operator[](int pos) { return prod(pos,\
    \ pos + 1); }\n};\n};  // namespace kyopro\n\n/// @docs docs/data-structure/lazy_segtree.md"
  dependsOn: []
  isVerificationFile: false
  path: src/data-structure/lazy_segtree.hpp
  requiredBy: []
  timestamp: '2023-04-08 13:07:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
  - test/AOJ/DSL/2_E_lazy.test.cpp
  - test/AOJ/DSL/2_D_lazy.test.cpp
documentation_of: src/data-structure/lazy_segtree.hpp
layout: document
redirect_from:
- /library/src/data-structure/lazy_segtree.hpp
- /library/src/data-structure/lazy_segtree.hpp.html
title: "Segment Tree with Lazy Propagation(\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\
  \u30F3\u30C8\u6728)"
---