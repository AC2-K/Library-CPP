---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data-structure/bbst/reversible_bbst.hpp
    title: "\u53CD\u8EE2\u53EF\u80FD\u5E73\u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':heavy_check_mark:'
    path: src/random/xor_shift.hpp
    title: xor shift
  - icon: ':heavy_check_mark:'
    path: src/stream.hpp
    title: fastIO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_reverse_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_reverse_range_sum
  bundledCode: "#line 1 \"test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    #include <iostream>\n#line 2 \"src/data-structure/bbst/reversible_bbst.hpp\"\n\
    #include <cassert>\n#include <memory>\n#include <utility>\n#line 2 \"src/random/xor_shift.hpp\"\
    \n#include <chrono>\n#include <cstdint>\n#include <random>\n\nnamespace kyopro\
    \ {\nstruct xor_shift32 {\n    uint32_t rng;\n    constexpr explicit xor_shift32(uint32_t\
    \ seed) : rng(seed) {}\n    explicit xor_shift32()\n        : rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    constexpr uint32_t operator()() {\n        rng ^= rng << 13;\n     \
    \   rng ^= rng >> 17;\n        rng ^= rng << 5;\n        return rng;\n    }\n\
    };\n\nstruct xor_shift {\n    uint64_t rng;\n    constexpr xor_shift(uint64_t\
    \ seed) : rng(seed) {}\n    explicit xor_shift()\n        : rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    constexpr uint64_t operator()() {\n        rng ^= rng << 13;\n     \
    \   rng ^= rng >> 7;\n        rng ^= rng << 17;\n        return rng;\n    }\n\
    };\n\n};  // namespace kyopro\n\n/**\n * @brief xor shift\n */\n#line 6 \"src/data-structure/bbst/reversible_bbst.hpp\"\
    \n\nnamespace kyopro {\n/**\n * @brief \u53CD\u8EE2\u53EF\u80FD\u5E73\u8861\u4E8C\
    \u5206\u63A2\u7D22\u6728\n * @tparam S \u30E2\u30CE\u30A4\u30C9\n * @tparam op\
    \ S\u306E\u4E8C\u9805\u6F14\u7B97\n * @tparam e S\u306E\u5358\u4F4D\u5143\n */\n\
    template <class S, S (*op)(S, S), S (*e)()> class reversible_bbst {\n    using\
    \ u32 = uint32_t;\n    xor_shift32 rng;\n    struct Node {\n        std::unique_ptr<Node>\
    \ l, r;\n        u32 priority;\n        S value, prod;\n        int size;\n  \
    \      bool rev;\n\n        Node(S v, u32 prio)\n            : l(),\n        \
    \      r(),\n              priority(prio),\n              value(v),\n        \
    \      prod(v),\n              size(1),\n              rev(false) {}\n    };\n\
    \n    using ptr = std::unique_ptr<Node>;\n    int size(const ptr& p) const { return\
    \ p ? p->size : 0; }\n    S fold(const ptr& p) { return p ? p->prod : e(); }\n\
    \n    void reverse(const ptr& p) {\n        if (p) {\n            p->rev ^= 1;\n\
    \        }\n    }\n\n    void push(const ptr& p) {\n        if (p->rev) {\n  \
    \          p->rev = false;\n            std::swap(p->l, p->r);\n            reverse(p->l),\
    \ reverse(p->r);\n        }\n    }\n\n    void update(const ptr& p) {\n      \
    \  p->size = size(p->l) + size(p->r) + 1;\n        p->prod = op(p->value, op(fold(p->l),\
    \ fold(p->r)));\n    }\n\n    std::pair<ptr, ptr> split(ptr p, int k) {\n    \
    \    if (!p) return {nullptr, nullptr};\n\n        push(p);\n        int s = size(p->l);\n\
    \        if (s >= k) {\n            auto [l, r] = split(std::move(p->l), k);\n\
    \            p->l = std::move(r);\n            update(p);\n\n            return\
    \ {std::move(l), std::move(p)};\n        } else {\n            auto [l, r] = split(std::move(p->r),\
    \ k - s - 1);\n\n            p->r = std::move(l);\n            update(p);\n\n\
    \            return {std::move(p), std::move(r)};\n        }\n    }\n\n    ptr\
    \ merge(ptr l, ptr r) {\n        if (!l) return r;\n        if (!r) return l;\n\
    \n        if (l->priority < r->priority) {\n            push(r);\n           \
    \ r->l = merge(std::move(l), std::move(r->l));\n            update(r);\n     \
    \       return r;\n        } else {\n            push(l);\n            l->r =\
    \ merge(std::move(l->r), std::move(r));\n            update(l);\n\n          \
    \  return l;\n        }\n    }\n\n    ptr root = nullptr;\n\npublic:\n    constexpr\
    \ explicit reversible_bbst() : rng(2023) {}\n    void insert(int i, S a) {\n \
    \       auto [l, r] = split(std::move(root), i);\n        ptr item = std::make_unique<Node>(a,\
    \ rng());\n        root = merge(std::move(l), std::move(item));\n        root\
    \ = merge(std::move(root), std::move(r));\n    }\n    S fold(int l, int r) {\n\
    \        assert(0 <= l && l <= r && r <= size(root));\n        auto [xy, z] =\
    \ split(std::move(root), r);\n        auto [x, y] = split(std::move(xy), l);\n\
    \        auto res = fold(y);\n        xy = merge(std::move(x), std::move(y));\n\
    \        root = merge(std::move(xy), std::move(z));\n        return res;\n   \
    \ }\n    void reverse(int l, int r) {\n        assert(0 <= l && l <= r && r <=\
    \ size(root));\n        auto [xy, z] = split(std::move(root), r);\n        auto\
    \ [x, y] = split(std::move(xy), l);\n        reverse(y);\n        xy = merge(std::move(x),\
    \ std::move(y));\n        root = merge(std::move(xy), std::move(z));\n    }\n\
    };\n};  // namespace kyopro\n\n/**\n * @docs docs/data-structure/bbst/reversible_bbst.md\n\
    \ * @ref\n * https://github.com/yosupo06/library-checker-problems/blob/master/datastructure/range_reverse_range_sum/sol/correct.cpp\n\
    \ */\n#line 2 \"src/stream.hpp\"\n#include <ctype.h>\n#include <stdio.h>\n#include\
    \ <string>\nnamespace kyopro {\n\n/**\n *  \u6574\u6570\u306E\u5165\u51FA\u529B\
    \n */\ntemplate <typename T> constexpr inline void readint(T& a) {\n    a = 0;\n\
    \    bool is_negative = false;\n    char c = getchar_unlocked();\n    while (isspace(c))\
    \ {\n        c = getchar_unlocked();\n    }\n    if (c == '-') is_negative = true,\
    \ c = getchar_unlocked();\n    while (isdigit(c)) {\n        a = 10 * a + (c -\
    \ '0');\n        c = getchar_unlocked();\n    }\n    if (is_negative) a *= -1;\n\
    }\ntemplate <typename Head, typename... Tail>\nconstexpr inline void readint(Head&\
    \ head, Tail&... tail) {\n    readint(head);\n    readint(tail...);\n}\n\ntemplate\
    \ <typename T> void write_int(T a) {\n    if (!a) {\n        putchar_unlocked('0');\n\
    \        putchar_unlocked('\\n');\n        return;\n    }\n    if (a < 0) putchar_unlocked('-'),\
    \ a *= -1;\n    char s[37];\n    int now = 37;\n    while (a) {\n        s[--now]\
    \ = (char)'0' + a % 10;\n        a /= 10;\n    }\n    while (now < 37) putchar_unlocked(s[now++]);\n\
    }\ntemplate <typename T> constexpr inline void putint(T a) {\n    if (!a) {\n\
    \        putchar_unlocked('0');\n        putchar_unlocked('\\n');\n        return;\n\
    \    }\n    if (a < 0) putchar_unlocked('-'), a *= -1;\n    char s[37];\n    int\
    \ now = 37;\n    while (a) {\n        s[--now] = (char)'0' + a % 10;\n       \
    \ a /= 10;\n    }\n    while (now < 37) putchar_unlocked(s[now++]);\n    putchar_unlocked('\\\
    n');\n}\ntemplate <typename Head, typename... Tail>\nconstexpr inline void putint(Head\
    \ head, Tail... tail) {\n    putint(head);\n    putint(tail...);\n}\n\n/**\n *\
    \ \u6587\u5B57\u5217\u306E\u5165\u51FA\u529B\n */\n\nvoid readstr(std::string&\
    \ str) {\n    char c = getchar_unlocked();\n    while (isspace(c)) c = getchar_unlocked();\n\
    \    while (!isspace(c)) {\n        str += c;\n        c = getchar_unlocked();\n\
    \    }\n}\n\nvoid readstr(std::string& str,std::string& tail...) {\n    readstr(str);\n\
    \    readstr(tail);\n}\nvoid putstr(const std::string& str) {\n    for (auto c\
    \ : str) {\n        putchar_unlocked(c);\n    }\n    putchar_unlocked('\\n');\n\
    }\nvoid putstr(const std::string& str, const std::string& tail...) {\n    putstr(str);\n\
    \    putstr(tail);\n}\n};  // namespace kyopro\n\n/**\n * @brief fastIO\n */\n\
    #line 5 \"test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp\"\nusing ll =\
    \ long long;\ninline ll op(ll x, ll y) { return x + y; }\ninline ll e() { return\
    \ 0; }\nint main() {\n    int n, q;\n    kyopro::readint(n, q);\n    kyopro::reversible_bbst<ll,\
    \ op, e> bbst;\n    for (int i = 0; i < n; i++) {\n        int a;\n        kyopro::readint(a);\n\
    \        bbst.insert(i, a);\n    }\n\n    while (q--) {\n        int t, l, r;\n\
    \        kyopro::readint(t, l, r);\n        if (!t) {\n            bbst.reverse(l,\
    \ r);\n        } else {\n            kyopro::putint(bbst.fold(l, r));\n      \
    \  }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n#include <iostream>\n#include \"../../../src/data-structure/bbst/reversible_bbst.hpp\"\
    \n#include \"../../../src/stream.hpp\"\nusing ll = long long;\ninline ll op(ll\
    \ x, ll y) { return x + y; }\ninline ll e() { return 0; }\nint main() {\n    int\
    \ n, q;\n    kyopro::readint(n, q);\n    kyopro::reversible_bbst<ll, op, e> bbst;\n\
    \    for (int i = 0; i < n; i++) {\n        int a;\n        kyopro::readint(a);\n\
    \        bbst.insert(i, a);\n    }\n\n    while (q--) {\n        int t, l, r;\n\
    \        kyopro::readint(t, l, r);\n        if (!t) {\n            bbst.reverse(l,\
    \ r);\n        } else {\n            kyopro::putint(bbst.fold(l, r));\n      \
    \  }\n    }\n}"
  dependsOn:
  - src/data-structure/bbst/reversible_bbst.hpp
  - src/random/xor_shift.hpp
  - src/stream.hpp
  isVerificationFile: true
  path: test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp
  requiredBy: []
  timestamp: '2023-07-05 22:01:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp
- /verify/test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp.html
title: test/yosupo_judge/new/Range_Reverse_Range_Sum.test.cpp
---