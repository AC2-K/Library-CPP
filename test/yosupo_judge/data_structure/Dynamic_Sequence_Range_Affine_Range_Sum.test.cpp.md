---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data-structure/bbst/lazy_reversible_bbst.hpp
    title: "\u9045\u5EF6\u8A55\u4FA1\u3064\u304D\u30FB\u53CD\u8EE2\u53EF\u80FD \u5E73\
      \u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':question:'
    path: src/internal/type_traits.hpp
    title: src/internal/type_traits.hpp
  - icon: ':question:'
    path: src/math/gcd.hpp
    title: src/math/gcd.hpp
  - icon: ':question:'
    path: src/math/static_modint.hpp
    title: "\u9759\u7684modint"
  - icon: ':question:'
    path: src/random/xor_shift.hpp
    title: xor shift
  - icon: ':question:'
    path: src/stream.hpp
    title: fastIO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp\"\
    \n#define PROBLEM \\\n    \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n#line 2 \"src/data-structure/bbst/lazy_reversible_bbst.hpp\"\n#include <cassert>\n\
    #include <memory>\n#include <utility>\n#line 2 \"src/random/xor_shift.hpp\"\n\
    #include <chrono>\n#include <cstdint>\n#include <random>\n\nnamespace kyopro {\n\
    struct xor_shift32 {\n    uint32_t rng;\n    constexpr explicit xor_shift32(uint32_t\
    \ seed) : rng(seed) {}\n    explicit xor_shift32()\n        : rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    constexpr uint32_t operator()() {\n        rng ^= rng << 13;\n     \
    \   rng ^= rng >> 17;\n        rng ^= rng << 5;\n        return rng;\n    }\n\
    };\n\nstruct xor_shift {\n    uint64_t rng;\n    constexpr xor_shift(uint64_t\
    \ seed) : rng(seed) {}\n    explicit xor_shift()\n        : rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    constexpr uint64_t operator()() {\n        rng ^= rng << 13;\n     \
    \   rng ^= rng >> 7;\n        rng ^= rng << 17;\n        return rng;\n    }\n\
    };\n\n};  // namespace kyopro\n\n/**\n * @brief xor shift\n */\n#line 6 \"src/data-structure/bbst/lazy_reversible_bbst.hpp\"\
    \n\nnamespace kyopro {\n/**\n * @brief \u9045\u5EF6\u8A55\u4FA1\u3064\u304D\u30FB\
    \u53CD\u8EE2\u53EF\u80FD \u5E73\u8861\u4E8C\u5206\u63A2\u7D22\u6728\n * @tparam\
    \ S \u30E2\u30CE\u30A4\u30C9\n * @tparam F \u4F5C\u7528\u7D20\n * @tparam op S\u306E\
    \u4E8C\u9805\u6F14\u7B97\n * @tparam e S\u306E\u5358\u4F4D\u5143\n * @tparam composition\
    \ F\u306E\u4E8C\u9805\u6F14\u7B97\n * @tparam id F\u306E\u5358\u4F4D\u5143\n *\
    \ @tparam mapping \u4F5C\u7528\n */\ntemplate <class S,\n          class F,\n\
    \          S (*op)(S, S),\n          S (*e)(),\n          F (*composition)(F,\
    \ F),\n          F (*id)(),\n          S (*mapping)(S, F, int)>\nclass lazy_reversible_bbst\
    \ {\n    using u32 = uint32_t;\n    xor_shift32 rng;\n    struct Node {\n    \
    \    std::unique_ptr<Node> l, r;\n        u32 priority;\n        S value, prod;\n\
    \n        F lazy;\n        int size;\n        bool rev;\n\n        Node(const\
    \ S& v, u32 prio)\n            : l(),\n              r(),\n              priority(prio),\n\
    \              value(v),\n              prod(e()),\n              lazy(id()),\n\
    \              size(1),\n              rev(false) {}\n    };\n\n    using ptr\
    \ = std::unique_ptr<Node>;\n    int size(const ptr& p) const { return p ? p->size\
    \ : 0; }\n    S fold(const ptr& p) { return p ? p->prod : e(); }\n\n    void update(const\
    \ ptr& p) {\n        if (!p) return;\n        p->size = size(p->l) + size(p->r)\
    \ + 1;\n        p->prod = op(p->value, op(fold(p->l), fold(p->r)));\n    }\n \
    \   void push(const ptr& p) {\n        if (!p) return;\n        if (p->rev) {\n\
    \            p->rev = false;\n            std::swap(p->l, p->r);\n           \
    \ reverse(p->l), reverse(p->r);\n        }\n\n        if (p->lazy != id()) {\n\
    \            if (p->l) {\n                p->l->lazy = composition(p->l->lazy,\
    \ p->lazy);\n                p->l->prod = mapping(p->l->prod, p->lazy, size(p->l));\n\
    \            }\n            if (p->r) {\n                p->r->lazy = composition(p->r->lazy,\
    \ p->lazy);\n                p->r->prod = mapping(p->r->prod, p->lazy, size(p->r));\n\
    \            }\n\n            p->value = mapping(p->value, p->lazy, 1);\n    \
    \        p->lazy = id();\n        }\n\n        update(p);\n    }\n\n    std::pair<ptr,\
    \ ptr> split(ptr p, int k) {\n        if (!p) return {nullptr, nullptr};\n\n \
    \       push(p);\n        int s = size(p->l);\n        if (s >= k) {\n       \
    \     auto [l, r] = split(std::move(p->l), k);\n            p->l = std::move(r);\n\
    \            update(p);\n\n            return {std::move(l), std::move(p)};\n\
    \        } else {\n            auto [l, r] = split(std::move(p->r), k - s - 1);\n\
    \n            p->r = std::move(l);\n            update(p);\n\n            return\
    \ {std::move(p), std::move(r)};\n        }\n    }\n\n    ptr merge(ptr l, ptr\
    \ r) {\n        if (!l) return r;\n        if (!r) return l;\n        push(l),\
    \ push(r);\n        if (l->priority < r->priority) {\n            r->l = merge(std::move(l),\
    \ std::move(r->l));\n            update(r);\n            return r;\n        }\
    \ else {\n            l->r = merge(std::move(l->r), std::move(r));\n         \
    \   update(l);\n            return l;\n        }\n    }\n\n    void reverse(const\
    \ ptr& p) {\n        if (p) {\n            p->rev ^= 1;\n        }\n    }\n  \
    \  ptr root = nullptr;\n\npublic:\n    constexpr explicit lazy_reversible_bbst()\
    \ : rng(2023) {}\n    void insert(int i, S a) {\n        auto [l, r] = split(std::move(root),\
    \ i);\n        ptr item = std::make_unique<Node>(a, rng());\n        root = merge(std::move(l),\
    \ std::move(item));\n        root = merge(std::move(root), std::move(r));\n  \
    \  }\n\n    void erase(int i) {\n        auto [xy, z] = split(std::move(root),\
    \ i + 1);\n        auto [x, y] = split(std::move(xy), i);\n        root = merge(std::move(x),\
    \ std::move(z));\n    }\n\n    S fold(int l, int r) {\n        auto [xy, z] =\
    \ split(std::move(root), r);\n        auto [x, y] = split(std::move(xy), l);\n\
    \        auto res = fold(y);\n        xy = merge(std::move(x), std::move(y));\n\
    \        root = merge(std::move(xy), std::move(z));\n        return res;\n   \
    \ }\n\n    void apply(int l, int r, const F& f) {\n        auto [xy, z] = split(std::move(root),\
    \ r);\n        auto [x, y] = split(std::move(xy), l);\n\n        y->lazy = composition(y->lazy,\
    \ f);\n        y->prod = mapping(y->prod, f, size(y));\n\n        xy = merge(std::move(x),\
    \ std::move(y));\n        root = merge(std::move(xy), std::move(z));\n    }\n\n\
    \    void reverse(int l, int r) {\n        auto [xy, z] = split(std::move(root),\
    \ r);\n        auto [x, y] = split(std::move(xy), l);\n        reverse(y);\n \
    \       xy = merge(std::move(x), std::move(y));\n        root = merge(std::move(xy),\
    \ std::move(z));\n    }\n};\n};  // namespace kyopro\n\n/**\n * @docs docs/data-structure/bbst/lazy_reversible_bbst.md\n\
    \ * @ref https://xuzijian629.hatenablog.com/entry/2018/12/08/000452\n */\n#line\
    \ 3 \"src/math/static_modint.hpp\"\n#include <iostream>\n#line 3 \"src/internal/type_traits.hpp\"\
    \n#include <limits>\n#include <numeric>\n#include <typeinfo>\nnamespace kyopro\
    \ {\nnamespace internal {\n/*\n * @ref https://qiita.com/kazatsuyu/items/f8c3b304e7f8b35263d8\n\
    \ */\ntemplate <typename... Args> struct first_enabled {};\n\ntemplate <typename\
    \ T, typename... Args>\nstruct first_enabled<std::enable_if<true, T>, Args...>\
    \ {\n    using type = T;\n};\ntemplate <typename T, typename... Args>\nstruct\
    \ first_enabled<std::enable_if<false, T>, Args...>\n    : first_enabled<Args...>\
    \ {};\ntemplate <typename T, typename... Args> struct first_enabled<T, Args...>\
    \ {\n    using type = T;\n};\n\ntemplate <typename... Args>\nusing first_enabled_t\
    \ = typename first_enabled<Args...>::type;\n\ntemplate <int dgt> struct int_least\
    \ {\n    static_assert(dgt <= 128);\n    using type = first_enabled_t<std::enable_if<dgt\
    \ <= 8, __int8_t>,\n                                 std::enable_if<dgt <= 16,\
    \ __int16_t>,\n                                 std::enable_if<dgt <= 32, __int32_t>,\n\
    \                                 std::enable_if<dgt <= 64, __int64_t>,\n    \
    \                             std::enable_if<dgt <= 128, __int128_t> >;\n};\n\
    template <int dgt> struct uint_least {\n    static_assert(dgt <= 128);\n    using\
    \ type = first_enabled_t<std::enable_if<dgt <= 8, __uint8_t>,\n              \
    \                   std::enable_if<dgt <= 16, __uint16_t>,\n                 \
    \                std::enable_if<dgt <= 32, __uint32_t>,\n                    \
    \             std::enable_if<dgt <= 64, __uint64_t>,\n                       \
    \          std::enable_if<dgt <= 128, __uint128_t> >;\n};\n\ntemplate <int dgt>\
    \ using int_least_t = typename int_least<dgt>::type;\ntemplate <int dgt> using\
    \ uint_least_t = typename uint_least<dgt>::type;\n\ntemplate <typename T>\nusing\
    \ double_size_uint_t = uint_least_t<2 * std::numeric_limits<T>::digits>;\n\ntemplate\
    \ <typename T>\nusing double_size_int_t = int_least_t<2 * std::numeric_limits<T>::digits>;\n\
    \nstruct modint_base {};\ntemplate <typename T> using is_modint = std::is_base_of<modint_base,\
    \ T>;\ntemplate <typename T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    \n\n// is_integral\ntemplate <typename T>\nusing is_integral_t =\n    std::enable_if_t<std::is_integral_v<T>\
    \ || std::is_same_v<T, __int128_t> ||\n                   std::is_same_v<T, __uint128_t>>;\n\
    };  // namespace internal\n};  // namespace kyopro\n#line 3 \"src/math/gcd.hpp\"\
    \n#include <tuple>\nnamespace kyopro {\ntemplate <typename T> constexpr T inline\
    \ _gcd(T a, T b) {\n    assert(a >= 0 && b >= 0);\n    if (a == 0 || b == 0) return\
    \ a + b;\n    int d = std::min<T>(__builtin_ctzll(a), __builtin_ctzll(b));\n \
    \   a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n    while (a != b) {\n\
    \        if (!a || !b) {\n            return a + b;\n        }\n        if (a\
    \ >= b) {\n            a -= b;\n            a >>= __builtin_ctzll(a);\n      \
    \  } else {\n            b -= a;\n            b >>= __builtin_ctzll(b);\n    \
    \    }\n    }\n\n    return a << d;\n}\ntemplate <typename T> constexpr T ext_gcd(T\
    \ a, T b, T& x, T& y) {\n    x = 1, y = 0;\n    T nx = 0, ny = 1;\n    while (b)\
    \ {\n        T q = a / b;\n        std::tie(a, b) = std::pair<T, T>{b, a % b};\n\
    \        std::tie(x, nx) = std::pair<T, T>{nx, x - nx * q};\n        std::tie(y,\
    \ ny) = std::pair<T, T>{ny, y - ny * q};\n    }\n    return a;\n}\n};  // namespace\
    \ kyopro\n#line 6 \"src/math/static_modint.hpp\"\nnamespace kyopro {\ntemplate\
    \ <__uint32_t _mod> class modint : internal::modint_base {\nprivate:\n    using\
    \ mint = modint<_mod>;\n    using i32 = __int32_t;\n    using u32 = __uint32_t;\n\
    \    using i64 = __int64_t;\n    using u64 = __uint64_t;\n\n    u32 v;\n    constexpr\
    \ u32 normalize(i64 v_) const {\n        v_ %= _mod;\n        if (v_ < 0) {\n\
    \            v_ += _mod;\n        }\n        return v_;\n    }\n\npublic:\n  \
    \  static constexpr u32 mod() { return _mod; }\n    constexpr modint() : v(0)\
    \ {}\n    constexpr modint(i64 v_) : v(normalize(v_)) {}\n\n    static mint raw(u32\
    \ a) {\n        mint m;\n        m.v = a;\n        return m;\n    }\n    constexpr\
    \ u32 val() const { return v; }\n    constexpr mint& operator+=(const mint& rhs)\
    \ {\n        v += rhs.val();\n        if (v >= _mod) {\n            v -= _mod;\n\
    \        }\n        return (*this);\n    }\n    constexpr mint& operator-=(const\
    \ mint& rhs) {\n        v += _mod - rhs.val();\n        if (v >= _mod) {\n   \
    \         v -= _mod;\n        }\n        return (*this);\n    }\n    constexpr\
    \ mint& operator*=(const mint& rhs) {\n        v = (u64)v * rhs.val() % _mod;\n\
    \        return (*this);\n    }\n\n    constexpr mint operator+(const mint& r)\
    \ const { return mint(*this) += r; }\n    constexpr mint operator-(const mint&\
    \ r) const { return mint(*this) -= r; }\n    constexpr mint operator*(const mint&\
    \ r) const { return mint(*this) *= r; }\n\n    constexpr mint& operator+=(i64\
    \ rhs) {\n        (*this) += mint(rhs);\n        return (*this);\n    }\n    constexpr\
    \ mint& operator-=(i64 rhs) {\n        (*this) -= mint(rhs);\n        return (*this);\n\
    \    }\n    constexpr mint& operator*=(i64 rhs) {\n        (*this) *= mint(rhs);\n\
    \        return (*this);\n    }\n    constexpr friend mint operator+(i64 l, const\
    \ mint& r) {\n        return mint(l) += r;\n    }\n    constexpr friend mint operator-(i64\
    \ l, const mint& r) {\n        return mint(l) -= r;\n    }\n    constexpr friend\
    \ mint operator*(i64 l, const mint& r) {\n        return mint(l) *= r;\n    }\n\
    \n    constexpr mint operator+(i64 r) { return mint(*this) += r; }\n    constexpr\
    \ mint operator-(i64 r) { return mint(*this) -= r; }\n    constexpr mint operator*(i64\
    \ r) { return mint(*this) *= r; }\n\n    constexpr mint& operator=(i64 r) { return\
    \ (*this) = mint(r); }\n\n    constexpr bool operator==(const mint& r) const {\n\
    \        return (*this).val() == r.val();\n    }\n    template <typename T> constexpr\
    \ mint pow(T e) const {\n        mint ans(1), base(*this);\n        while (e)\
    \ {\n            if (e & 1) {\n                ans *= base;\n            }\n \
    \           base *= base;\n            e >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    constexpr mint inv() const {\n        long long x, y;\n        auto\
    \ d = ext_gcd((long long)_mod, (long long)v, x, y);\n        assert(d == 1);\n\
    \        return mint(y);\n    }\n\n    constexpr mint& operator/=(const mint&\
    \ r) { return (*this) *= r.inv(); }\n    constexpr mint operator/(const mint&\
    \ r) const {\n        return mint(*this) *= r.inv();\n    }\n    constexpr friend\
    \ mint operator/(const mint& l, i64 r) {\n        return mint(l) /= mint(r);\n\
    \    }\n    constexpr friend mint operator/(i64 l, const mint& r) {\n        return\
    \ mint(l) /= mint(r);\n    }\n\n    // stream\n    constexpr friend std::ostream&\
    \ operator<<(std::ostream& os,\n                                             \
    \ const mint& mt) {\n        os << mt.val();\n        return os;\n    }\n    constexpr\
    \ friend std::istream& operator>>(std::istream& is, mint& mt) {\n        i64 v_;\n\
    \        is >> v_;\n        mt = v_;\n        return is;\n    }\n};\n};  // namespace\
    \ kyopro\n\n/**\n * @brief \u9759\u7684modint\n * @docs docs/math/static_modint.md\n\
    \ */\n#line 2 \"src/stream.hpp\"\n#include <ctype.h>\n#include <stdio.h>\n#include\
    \ <string>\n#line 6 \"src/stream.hpp\"\n\nnamespace kyopro {\n// read\nvoid single_read(char&\
    \ c) {\n    c = getchar_unlocked();\n    while (isspace(c)) c = getchar_unlocked();\n\
    }\ntemplate <typename T, internal::is_integral_t<T>* = nullptr>\nvoid single_read(T&\
    \ a) {\n    a = 0;\n    bool is_negative = false;\n    char c = getchar_unlocked();\n\
    \    while (isspace(c)) {\n        c = getchar_unlocked();\n    }\n    if constexpr\
    \ (std::is_signed_v<T>) {\n        if (c == '-') is_negative = true, c = getchar_unlocked();\n\
    \    }\n    while (isdigit(c)) {\n        a = 10 * a + (c - '0');\n        c =\
    \ getchar_unlocked();\n    }\n    if constexpr (std::is_signed_v<T>) {\n     \
    \   if (is_negative) a *= -1;\n    }\n}\ntemplate <typename T, internal::is_modint_t<T>*\
    \ = nullptr>\nvoid single_read(T& a) {\n    long long x;\n    single_read(x);\n\
    \    a = T(x);\n}\nvoid single_read(std::string& str) {\n    char c = getchar_unlocked();\n\
    \    while (isspace(c)) c = getchar_unlocked();\n    while (!isspace(c)) {\n \
    \       str += c;\n        c = getchar_unlocked();\n    }\n}\ntemplate <typename\
    \ T> void read(T& x) { single_read(x); }\ntemplate <typename Head, typename...\
    \ Tail>\nvoid read(Head& head, Tail&... tail) {\n    single_read(head), read(tail...);\n\
    }\n\n// write\nvoid single_write(char c) { putchar_unlocked(c); }\ntemplate <typename\
    \ T, internal::is_integral_t<T>* = nullptr>\nvoid single_write(T a) {\n    if\
    \ (!a) {\n        putchar_unlocked('0');\n        return;\n    }\n    if constexpr\
    \ (std::is_signed_v<T>) {\n        if (a < 0) putchar_unlocked('-'), a *= -1;\n\
    \    }\n\n    char s[37];\n    int now = 37;\n    while (a) {\n        s[--now]\
    \ = (char)'0' + a % 10;\n        a /= 10;\n    }\n    while (now < 37) putchar_unlocked(s[now++]);\n\
    }\ntemplate <typename T, internal::is_modint_t<T>* = nullptr>\nvoid single_write(T\
    \ a) {\n    single_write(a.val());\n}\n\nvoid single_write(const std::string&\
    \ str) {\n    for (auto c : str) {\n        putchar_unlocked(c);\n    }\n}\n\n\
    template <typename T> void write(T x) { single_write(x); }\ntemplate <typename\
    \ Head, typename... Tail> void write(Head head, Tail... tail) {\n    single_write(head);\n\
    \    putchar_unlocked(' ');\n    write(tail...);\n}\ntemplate <typename... Args>\
    \ void put(Args... x) {\n    write(x...);\n    putchar_unlocked('\\n');\n}\n};\
    \  // namespace kyopro\n\n/**\n * @brief fastIO\n */\n#line 6 \"test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp\"\
    \nusing mint = kyopro::modint<998244353>;\nusing S = mint;\ninline S op(S a, S\
    \ b) { return a + b; }\ninline S e() { return mint(0); }\nusing Affine = std::pair<mint,\
    \ mint>;\ninline Affine composition(Affine g, Affine f) {\n    // f(g)\n    //\
    \ a(cx+d)+b\n    auto a = f.first, b = f.second;\n    auto c = g.first, d = g.second;\n\
    \    return Affine(a * c, a * d + b);\n}\ninline Affine id() { return Affine(1,\
    \ 0); }\ninline S mapping(S d, Affine f, int length) {\n    auto [a, b] = f;\n\
    \    return a * d + b * length;\n};\nint main() {\n    kyopro::lazy_reversible_bbst<S,\
    \ Affine, op, e, composition, id, mapping>\n        stree;\n    int n, q;\n  \
    \  kyopro::read(n, q);\n    for (int i = 0; i < n; ++i) {\n        mint ai;\n\
    \        kyopro::read(ai);\n        stree.insert(i, ai);\n    }\n    while (q--)\
    \ {\n        int t;\n        kyopro::read(t);\n        if (t == 0) {\n       \
    \     int i, x;\n            kyopro::read(i, x);\n            stree.insert(i,\
    \ mint::raw(x));\n        } else if (t == 1) {\n            int i;\n         \
    \   kyopro::read(i);\n            stree.erase(i);\n        } else if (t == 2)\
    \ {\n            int l, r;\n            kyopro::read(l, r);\n            stree.reverse(l,\
    \ r);\n        } else if (t == 3) {\n            int l, r, a, b;\n           \
    \ kyopro::read(l, r, a, b);\n            stree.apply(l, r, Affine(mint::raw(a),\
    \ mint::raw(b)));\n        } else {\n            int l, r;\n            kyopro::read(l,\
    \ r);\n            kyopro::put(stree.fold(l, r).val());\n        }\n    }\n}\n"
  code: "#define PROBLEM \\\n    \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n#include \"../../../src/data-structure/bbst/lazy_reversible_bbst.hpp\"\n#include\
    \ \"../../../src/math/static_modint.hpp\"\n#include \"../../../src/stream.hpp\"\
    \nusing mint = kyopro::modint<998244353>;\nusing S = mint;\ninline S op(S a, S\
    \ b) { return a + b; }\ninline S e() { return mint(0); }\nusing Affine = std::pair<mint,\
    \ mint>;\ninline Affine composition(Affine g, Affine f) {\n    // f(g)\n    //\
    \ a(cx+d)+b\n    auto a = f.first, b = f.second;\n    auto c = g.first, d = g.second;\n\
    \    return Affine(a * c, a * d + b);\n}\ninline Affine id() { return Affine(1,\
    \ 0); }\ninline S mapping(S d, Affine f, int length) {\n    auto [a, b] = f;\n\
    \    return a * d + b * length;\n};\nint main() {\n    kyopro::lazy_reversible_bbst<S,\
    \ Affine, op, e, composition, id, mapping>\n        stree;\n    int n, q;\n  \
    \  kyopro::read(n, q);\n    for (int i = 0; i < n; ++i) {\n        mint ai;\n\
    \        kyopro::read(ai);\n        stree.insert(i, ai);\n    }\n    while (q--)\
    \ {\n        int t;\n        kyopro::read(t);\n        if (t == 0) {\n       \
    \     int i, x;\n            kyopro::read(i, x);\n            stree.insert(i,\
    \ mint::raw(x));\n        } else if (t == 1) {\n            int i;\n         \
    \   kyopro::read(i);\n            stree.erase(i);\n        } else if (t == 2)\
    \ {\n            int l, r;\n            kyopro::read(l, r);\n            stree.reverse(l,\
    \ r);\n        } else if (t == 3) {\n            int l, r, a, b;\n           \
    \ kyopro::read(l, r, a, b);\n            stree.apply(l, r, Affine(mint::raw(a),\
    \ mint::raw(b)));\n        } else {\n            int l, r;\n            kyopro::read(l,\
    \ r);\n            kyopro::put(stree.fold(l, r).val());\n        }\n    }\n}"
  dependsOn:
  - src/data-structure/bbst/lazy_reversible_bbst.hpp
  - src/random/xor_shift.hpp
  - src/math/static_modint.hpp
  - src/internal/type_traits.hpp
  - src/math/gcd.hpp
  - src/stream.hpp
  isVerificationFile: true
  path: test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp
  requiredBy: []
  timestamp: '2023-08-21 00:27:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp
- /verify/test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp.html
title: test/yosupo_judge/data_structure/Dynamic_Sequence_Range_Affine_Range_Sum.test.cpp
---