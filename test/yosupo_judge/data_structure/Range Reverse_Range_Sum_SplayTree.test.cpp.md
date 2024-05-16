---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data-structure/bbst/SplayTree.hpp
    title: Splay Tree
  - icon: ':heavy_check_mark:'
    path: src/debug.hpp
    title: Debugger
  - icon: ':heavy_check_mark:'
    path: src/internal/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: src/stream.hpp
    title: "Fast IO(\u9AD8\u901F\u5165\u51FA\u529B)"
  - icon: ':heavy_check_mark:'
    path: src/template.hpp
    title: Template
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
  bundledCode: "#line 1 \"test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    \n#line 2 \"src/data-structure/bbst/SplayTree.hpp\"\n#include <memory>\n#include\
    \ <vector>\n\nnamespace kyopro {\ntemplate <typename S, auto op, auto e> struct\
    \ SplayTree {\n    using usize = std::size_t;\n\n    struct Node {\n        Node\
    \ *lch, *rch, *par;\n        usize sz;\n        S value, agg;\n        bool rev;\n\
    \n        Node()\n            : lch(nullptr),\n              rch(nullptr),\n \
    \             par(nullptr),\n              sz(1),\n              value(e()),\n\
    \              agg(e()),\n              rev(false) {}\n        Node(const S& v)\n\
    \            : lch(nullptr),\n              rch(nullptr),\n              par(nullptr),\n\
    \              sz(1),\n              value(v),\n              agg(v),\n      \
    \        rev(false) {}\n\n        static usize size(Node* x) { return x ? x->sz\
    \ : 0; }\n        static S fold(Node* x) { return x ? x->agg : e(); }\n      \
    \  static void reverse(Node*& x) {\n            if (x) {\n                x->rev\
    \ ^= 1;\n            }\n        }\n\n        void push() {\n            if (this->rev)\
    \ {\n                std::swap(this->lch, this->rch);\n                this->rev\
    \ = false;\n                Node::reverse(this->lch);\n                Node::reverse(this->rch);\n\
    \            }\n        }\n\n        void update() {\n            this->sz = 1\
    \ + size(this->lch) + size(this->rch);\n            this->agg = op(op(fold(this->lch),\
    \ this->value), fold(this->rch));\n        }\n\n        void rotate() {\n    \
    \        Node *pp, *p, *c;\n            p = this->par;\n            pp = p->par;\n\
    \n            if (p->lch == this) {\n                c = this->rch;\n        \
    \        this->rch = p;\n                p->lch = c;\n            } else {\n \
    \               c = this->lch;\n                this->lch = p;\n             \
    \   p->rch = c;\n            }\n\n            if (pp != nullptr) {\n         \
    \       (pp->lch == p ? pp->lch : pp->rch) = this;\n            }\n\n        \
    \    this->par = pp;\n            p->par = this;\n\n            if (c != nullptr)\
    \ {\n                c->par = p;\n            }\n\n            p->update();\n\
    \            this->update();\n        }\n\n        int state() {\n           \
    \ if (!this->par) {\n                return 0;\n            } else if (this->par->lch\
    \ == this) {\n                return -1;\n            } else if (this->par->rch\
    \ == this) {\n                return 1;\n            }\n            return 0;\n\
    \        }\n\n        void splay() {\n            this->push();\n            while\
    \ (this->state()) {\n                Node* p = this->par;\n                Node*\
    \ pp = p->par;\n\n                if (pp) pp->push();\n                if (p)\
    \ p->push();\n                this->push();\n\n                if (p->state()\
    \ == 0) {\n                    this->rotate();\n                } else if (this->state()\
    \ == p->state()) {\n                    p->rotate();\n                    this->rotate();\n\
    \                } else {\n                    this->rotate();\n             \
    \       this->rotate();\n                }\n\n                if (pp) pp->update();\n\
    \                if (p) p->update();\n                this->update();\n      \
    \      }\n        }\n    };\n\n    Node* access(usize k, Node* t) {\n        Node*\
    \ now = t;\n        while (1) {\n            now->push();\n            usize lsize\
    \ = Node::size(now->lch);\n            if (k < lsize) {\n                now =\
    \ now->lch;\n            } else if (k == lsize) {\n                now->splay();\n\
    \                return now;\n            } else {\n                now = now->rch;\n\
    \                k = k - lsize - 1;\n            }\n        }\n    }\n\n    Node*\
    \ merge(Node* l, Node* r) {\n        if (!l) return r;\n        if (!r) return\
    \ l;\n        l->push();\n        r->push();\n        l = access(Node::size(l)\
    \ - 1, l);\n        l->rch = r;\n        r->par = l;\n        l->update();\n\n\
    \        return l;\n    }\n\n    std::pair<Node*, Node*> split(usize k, Node*\
    \ t) {\n        if (!t) return {nullptr, nullptr};\n        if (k == 0) return\
    \ {nullptr, t};\n        if (k == t->sz) return {t, nullptr};\n        t->push();\n\
    \        t = access(k, t);\n        Node *l, *r;\n        l = t->lch;\n      \
    \  r = t;\n        r->lch = nullptr;\n        l->par = nullptr;\n        r->update();\n\
    \        return {l, r};\n    }\n\npublic:\n    Node* root;\n    SplayTree(int\
    \ n = 0) : SplayTree(std::vector<S>(n)) {}\n    SplayTree(const std::vector<S>&\
    \ a) : root(nullptr) {\n        if (a.size() == 0) return;\n\n        auto nodes\
    \ = new Node*[a.size()];\n        for (int i = 0; i < (int)a.size(); ++i) nodes[i]\
    \ = new Node(a[i]);\n        for (int i = 0; i < (int)a.size() - 1; ++i) {\n \
    \           nodes[i + 1]->lch = nodes[i];\n            nodes[i]->par = nodes[i\
    \ + 1];\n            nodes[i + 1]->update();\n        }\n\n        root = nodes[a.size()\
    \ - 1];\n    }\n\n    S access(usize k) {\n        root = access(k, root);\n \
    \       return root->value;\n    }\n\n    void update(int i, const S& v) {\n \
    \       root = access(i, root);\n        root->value = v;\n        root->update();\n\
    \    }\n\n    void insert(int i, const S& v) {\n        auto [l, r] = split(i,\
    \ root);\n        Node* tmp = new Node(v);\n        root = merge(merge(l, tmp),\
    \ r);\n    }\n\n    void erase(int i) {\n        root = access(i, root);\n   \
    \     Node *l = root->lch, *r = root->rch;\n        if (l) l->par = nullptr;\n\
    \        if (r) r->par = nullptr;\n        root->lch = nullptr, root->rch = nullptr;\n\
    \        root = merge(l, r);\n        root->update();\n    }\n\n    S fold(int\
    \ l, int r) {\n        auto [xy, z] = split(r, root);\n        auto [x, y] = split(l,\
    \ xy);\n        S ans = Node::fold(y);\n        root = merge(merge(x, y), z);\n\
    \        return ans;\n    }\n\n    void reverse(int l, int r) {\n        auto\
    \ [xy, z] = split(r, root);\n        auto [x, y] = split(l, xy);\n        Node::reverse(y);\n\
    \        root = merge(merge(x, y), z);\n    }\n};\n};  // namespace kyopro\n\n\
    /**\n * @brief Splay Tree\n */\n#line 1 \"src/debug.hpp\"\n#ifdef ONLINE_JUDGE\n\
    #define debug(x) void(0)\n#else\n#define _GLIBCXX_DEBUG\n#define debug(x) std::cerr\
    \ << __LINE__ << \" : \" << #x << \" = \" << (x) << std::endl\n#endif\n\n/**\n\
    \ * @brief Debugger\n*/\n#line 2 \"src/stream.hpp\"\n#include <ctype.h>\n#include\
    \ <stdio.h>\n#include <string>\n#line 2 \"src/internal/type_traits.hpp\"\n#include\
    \ <iostream>\n#include <limits>\n#include <numeric>\n#include <typeinfo>\n#include\
    \ <cstdint>\n\nnamespace kyopro {\nnamespace internal {\ntemplate <typename...\
    \ Args> struct first_enabled {};\n\ntemplate <typename T, typename... Args>\n\
    struct first_enabled<std::enable_if<true, T>, Args...> {\n    using type = T;\n\
    };\ntemplate <typename T, typename... Args>\nstruct first_enabled<std::enable_if<false,\
    \ T>, Args...>\n    : first_enabled<Args...> {};\ntemplate <typename T, typename...\
    \ Args> struct first_enabled<T, Args...> {\n    using type = T;\n};\n\ntemplate\
    \ <typename... Args>\nusing first_enabled_t = typename first_enabled<Args...>::type;\n\
    \ntemplate <int dgt, std::enable_if_t<dgt <= 128>* = nullptr> struct int_least\
    \ {\n    using type = first_enabled_t<std::enable_if<dgt <= 8, std::int8_t>,\n\
    \                                 std::enable_if<dgt <= 16, std::int16_t>,\n \
    \                                std::enable_if<dgt <= 32, std::int32_t>,\n  \
    \                               std::enable_if<dgt <= 64, std::int64_t>,\n   \
    \                              std::enable_if<dgt <= 128, __int128_t>>;\n};\n\n\
    template <int dgt, std::enable_if_t<dgt <= 128>* = nullptr> struct uint_least\
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
    };  // namespace internal\n};  // namespace kyopro\n\n/**\n * @brief Type Traits\n\
    \ * @see https://qiita.com/kazatsuyu/items/f8c3b304e7f8b35263d8\n */\n#line 6\
    \ \"src/stream.hpp\"\n\nnamespace kyopro {\n\ninline void single_read(char& c)\
    \ {\n    c = getchar_unlocked();\n    while (isspace(c)) c = getchar_unlocked();\n\
    }\ntemplate <typename T, internal::is_integral_t<T>* = nullptr>\ninline void single_read(T&\
    \ a) {\n    a = 0;\n    bool is_negative = false;\n    char c = getchar_unlocked();\n\
    \    while (isspace(c)) {\n        c = getchar_unlocked();\n    }\n    if (c ==\
    \ '-') is_negative = true, c = getchar_unlocked();\n    while (isdigit(c)) {\n\
    \        a = 10 * a + (c - '0');\n        c = getchar_unlocked();\n    }\n   \
    \ if (is_negative) a *= -1;\n}\ntemplate <typename T, internal::is_modint_t<T>*\
    \ = nullptr>\ninline void single_read(T& a) {\n    long long x;\n    single_read(x);\n\
    \    a = T(x);\n}\ninline void single_read(std::string& str) noexcept {\n    char\
    \ c = getchar_unlocked();\n    while (isspace(c)) c = getchar_unlocked();\n  \
    \  while (!isspace(c)) {\n        str += c;\n        c = getchar_unlocked();\n\
    \    }\n}\ntemplate<typename T>\ninline void read(T& x) noexcept {single_read(x);}\n\
    template <typename Head, typename... Tail>\ninline void read(Head& head, Tail&...\
    \ tail) noexcept {\n    single_read(head), read(tail...);\n}\n\ninline void single_write(char\
    \ c) noexcept { putchar_unlocked(c); }\ntemplate <typename T, internal::is_integral_t<T>*\
    \ = nullptr>\ninline void single_write(T a) noexcept {\n    if (!a) {\n      \
    \  putchar_unlocked('0');\n        return;\n    }\n    if constexpr (std::is_signed_v<T>)\
    \ {\n        if (a < 0) putchar_unlocked('-'), a *= -1;\n    }\n    constexpr\
    \ int d = std::numeric_limits<T>::digits10;\n    char s[d + 1];\n    int now =\
    \ d + 1;\n    while (a) {\n        s[--now] = (char)'0' + a % 10;\n        a /=\
    \ 10;\n    }\n    while (now <= d) putchar_unlocked(s[now++]);\n}\ntemplate <typename\
    \ T, internal::is_modint_t<T>* = nullptr>\ninline void single_write(T a) noexcept\
    \ {\n    single_write(a.val());\n}\ninline void single_write(const std::string&\
    \ str) noexcept {\n    for (auto c : str) {\n        putchar_unlocked(c);\n  \
    \  }\n}\ntemplate <typename T> inline void write(T x) noexcept { single_write(x);\
    \ }\ntemplate <typename Head, typename... Tail>\ninline void write(Head head,\
    \ Tail... tail) noexcept {\n    single_write(head);\n    putchar_unlocked(' ');\n\
    \    write(tail...);\n}\ntemplate <typename... Args> inline void put(Args... x)\
    \ noexcept {\n    write(x...);\n    putchar_unlocked('\\n');\n}\n};  // namespace\
    \ kyopro\n\n/**\n * @brief Fast IO(\u9AD8\u901F\u5165\u51FA\u529B)\n */\n#line\
    \ 2 \"src/template.hpp\"\n#include <bits/stdc++.h>\n#define rep(i, n) for (int\
    \ i = 0; i < (n); i++)\n#define all(x) std::begin(x), std::end(x)\n#define popcount(x)\
    \ __builtin_popcountll(x)\nusing i128 = __int128_t;\nusing ll = long long;\nusing\
    \ ld = long double;\nusing graph = std::vector<std::vector<int>>;\nusing P = std::pair<int,\
    \ int>;\nconstexpr int inf = std::numeric_limits<int>::max() / 2;\nconstexpr ll\
    \ infl = std::numeric_limits<ll>::max() / 2;\nconst long double pi = acosl(-1);\n\
    constexpr int dx[] = {1, 0, -1, 0, 1, -1, -1, 1, 0};\nconstexpr int dy[] = {0,\
    \ 1, 0, -1, 1, 1, -1, -1, 0};\ntemplate <typename T1, typename T2> constexpr inline\
    \ bool chmax(T1& a, T2 b) {\n    return a < b && (a = b, true);\n}\ntemplate <typename\
    \ T1, typename T2> constexpr inline bool chmin(T1& a, T2 b) {\n    return a >\
    \ b && (a = b, true);\n}\n\n/**\n * @brief Template\n*/\n#line 7 \"test/yosupo_judge/data_structure/Range\
    \ Reverse_Range_Sum_SplayTree.test.cpp\"\n\nusing namespace std;\nusing namespace\
    \ kyopro;\n\nusing ll = long long;\n\nconstexpr inline ll op(ll x, ll y) noexcept\
    \ { return x + y; }\nconstexpr inline ll e() noexcept { return 0; }\n\nint main()\
    \ {\n    int n, q;\n    read(n, q);\n    vector<ll> a(n);\n    rep(i, n) read(a[i]);\n\
    \n    SplayTree<ll, op, e> sg(a);\n\n    while (q--) {\n        int t, l, r;\n\
    \        read(t, l, r);\n        if (!t) {\n            sg.reverse(l, r);\n  \
    \      } else {\n            put(sg.fold(l, r));\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n\n#include \"../../../src/data-structure/bbst/SplayTree.hpp\"\n#include \"../../../src/debug.hpp\"\
    \n#include \"../../../src/stream.hpp\"\n#include \"../../../src/template.hpp\"\
    \n\nusing namespace std;\nusing namespace kyopro;\n\nusing ll = long long;\n\n\
    constexpr inline ll op(ll x, ll y) noexcept { return x + y; }\nconstexpr inline\
    \ ll e() noexcept { return 0; }\n\nint main() {\n    int n, q;\n    read(n, q);\n\
    \    vector<ll> a(n);\n    rep(i, n) read(a[i]);\n\n    SplayTree<ll, op, e> sg(a);\n\
    \n    while (q--) {\n        int t, l, r;\n        read(t, l, r);\n        if\
    \ (!t) {\n            sg.reverse(l, r);\n        } else {\n            put(sg.fold(l,\
    \ r));\n        }\n    }\n}\n"
  dependsOn:
  - src/data-structure/bbst/SplayTree.hpp
  - src/debug.hpp
  - src/stream.hpp
  - src/internal/type_traits.hpp
  - src/template.hpp
  isVerificationFile: true
  path: test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp
  requiredBy: []
  timestamp: '2024-05-16 17:50:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp
- /verify/test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp.html
title: test/yosupo_judge/data_structure/Range Reverse_Range_Sum_SplayTree.test.cpp
---