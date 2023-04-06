---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: internal/barrett.hpp
    title: barrett reduction
  - icon: ':question:'
    path: internal/montgomery.hpp
    title: MontgomeryReduction
  - icon: ':question:'
    path: math/dynamic_modint.hpp
    title: "dynamic modint(\u52D5\u7684modint)"
  - icon: ':question:'
    path: math/gcd.hpp
    title: math/gcd.hpp
  - icon: ':question:'
    path: math/miller.hpp
    title: "MillerRabin\u306E\u7D20\u6570\u5224\u5B9A"
  - icon: ':x:'
    path: math/primitive_root.hpp
    title: "primitive root(\u539F\u59CB\u6839)"
  - icon: ':question:'
    path: math/rho.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho\u6CD5)"
  - icon: ':question:'
    path: template.hpp
    title: template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/primitive_root
    links:
    - https://judge.yosupo.jp/problem/primitive_root
  bundledCode: "#line 1 \"test/yosupo_judge/math/Primitive_Root.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n#line 2 \"template.hpp\"\
    \n#include<bits/stdc++.h>\n#define rep(i, N)  for(int i=0;i<(N);i++)\n#define\
    \ all(x) (x).begin(),(x).end()\n#define popcount(x) __builtin_popcount(x)\nusing\
    \ i128=__int128_t;\nusing ll = long long;\nusing ld = long double;\nusing graph\
    \ = std::vector<std::vector<int>>;\nusing P = std::pair<int, int>;\nconstexpr\
    \ int inf = 1e9;\nconstexpr ll infl = 1e18;\nconstexpr ld eps = 1e-6;\nconst long\
    \ double pi = acos(-1);\nconstexpr uint64_t MOD = 1e9 + 7;\nconstexpr uint64_t\
    \ MOD2 = 998244353;\nconstexpr int dx[] = { 1,0,-1,0 };\nconstexpr int dy[] =\
    \ { 0,1,0,-1 };\ntemplate<class T>static constexpr inline void chmax(T&x,T y){if(x<y)x=y;}\n\
    template<class T>static constexpr inline void chmin(T&x,T y){if(x>y)x=y;}\n#line\
    \ 3 \"internal/barrett.hpp\"\nnamespace library {\nnamespace internal {\n/// @brief\
    \ barrett reduction\nclass barrett {\n    using u32 = uint32_t;\n    using u64\
    \ = uint64_t;\n\n    u64 m;\n    u64 im;\n\n  public:\n    explicit barrett()\
    \ = default;\n    constexpr explicit barrett(u64 m_)\n        : m(m_), im((u64)(long\
    \ double)static_cast<u64>(-1) / m_ + 1) {}\n\n    inline u64 get_mod() const {\
    \ return m; }\n    inline u64 reduce(int64_t a) const {\n        if (a < 0) return\
    \ m - reduce(-a);\n        u64 q = ((__uint128_t)a * im) >> 64;\n        a -=\
    \ m * q;\n        if (a >= m) a -= m;\n        return a;\n    }\n    inline u64\
    \ mul(u64 a, u64 b) {\n        if (a == 0 || b == 0) {\n            return 0;\n\
    \        }\n        u64 z = a;\n        z *= b;\n        u64 x = (u64)(((__uint128_t)(z)*im)\
    \ >> 64);\n\n        u32 v = (u32)(z - x * m);\n\n        if (v >= m) v += m;\n\
    \        return v;\n    }\n};\n};  // namespace internal\n};  // namespace library\n\
    #line 3 \"internal/montgomery.hpp\"\nnamespace library {\nnamespace internal {\n\
    using u32 = uint32_t;\nusing u64 = uint64_t;\nusing i32 = int32_t;\nusing i64\
    \ = int64_t;\nusing u128 = __uint128_t;\nusing i128 = __int128_t;\n/// @brief\
    \ MontgomeryReduction\ntemplate <typename T, typename LargeT>\nclass MontgomeryReduction\
    \ {\n    static constexpr int lg = std::numeric_limits<T>::digits;\n    T mod,\
    \ r, r2, minv;\n    T calc_inv() {\n        T t = 0, res = 0;\n        for (int\
    \ i = 0; i < lg; i++) {\n            if (~t & 1) {\n                t += mod;\n\
    \                res += static_cast<T>(1) << i;\n            }\n            t\
    \ >>= 1;\n        }\n        return res;\n    }\n\n  public:\n    MontgomeryReduction()\
    \ = default;\n    constexpr T get_mod() { return mod; }\n    constexpr int get_lg()\
    \ { return lg; }\n\n    void set_mod(const T& m) {\n\n        assert(m > 0);\n\
    \        assert(m & 1);\n\n        mod = m;\n\n        r = (-static_cast<T>(mod))\
    \ % mod;\n        r2 = (-static_cast<LargeT>(mod)) % mod;\n        minv = calc_inv();\n\
    \    }\n\n    T reduce(LargeT x) const {\n        u64 res =\n            (x +\
    \ static_cast<LargeT>(static_cast<T>(x) * minv) * mod) >> lg;\n\n        if (res\
    \ >= mod) res -= mod;\n        return res;\n    }\n\n    T generate(LargeT x)\
    \ { return reduce(x * r2); }\n\n    T mult(T x, T y) { return reduce(static_cast<LargeT>(x)\
    \ * y); }\n};\n};  // namespace internal\n};  // namespace library\n#line 4 \"\
    math/dynamic_modint.hpp\"\n\nnamespace library{\ntemplate<int id=-1>\nclass barrett_modint\
    \ {\n\tusing u32 = uint32_t;\n\tusing u64 = uint64_t;\n\n\tusing i32 = int32_t;\n\
    \tusing i64 = int64_t;\n\tusing br = internal::barrett;\n\n\tstatic br brt;\n\t\
    static u32 mod;\n\tu32 v;\t//value\npublic:\n\tstatic void set_mod(u32 mod_) {\n\
    \t\tbrt = br(mod_);\n\t\tmod = mod_;\n\t}\npublic:\n\texplicit constexpr barrett_modint()\
    \ :v(0) { assert(mod); }\t//mod\u304C\u6C7A\u5B9A\u6E08\u307F\u3067\u3042\u308B\
    \u5FC5\u8981\u304C\u3042\u308B\n\texplicit constexpr barrett_modint(i64 v_) :v(brt.reduce(v_))\
    \ { assert(mod); }\t\n\n\tu32 val() const { return v; }\n    static u32 get_mod()\
    \ { return mod; }\n    using mint = barrett_modint<id>;\n\n\t//operators\n\tconstexpr\
    \ mint& operator=(i64 r) {\n\t\tv = brt.reduce(r); \n\t\treturn (*this);\n\t}\n\
    \tconstexpr mint& operator+=(const mint& r) {\n\t\tv += r.v;\n\t\tif (v >= mod)\
    \ {\n\t\t\tv -= mod;\n\t\t}\n\t\treturn (*this);\n\t}\n\tconstexpr mint& operator-=(const\
    \ mint&r) {\n\t\tv += mod - r.v;\n\t\tif (v >= mod) {\n\t\t\tv -= mod;\n\t\t}\n\
    \n\t\treturn (*this);\n\t}\n\tconstexpr mint& operator*=(const mint& r) {\n\t\t\
    v = brt.mul(v, r.v);\n\t\treturn (*this);\n\t}\n\n\tconstexpr mint operator+(const\
    \ mint& r) const { return mint(*this) += r; }\n\tconstexpr mint operator-(const\
    \ mint& r) const { return mint(*this) -= r; }\n\tconstexpr mint operator*(const\
    \ mint& r) const { return mint(*this) *= r; }\n\n\n\n\tconstexpr mint& operator+=\
    \ (i64 r) { return (*this) += mint(r); }\n\tconstexpr mint& operator-= (i64 r)\
    \ { return (*this) -= mint(r); }\n\tconstexpr mint& operator*= (i64 r) { return\
    \ (*this) *= mint(r); }\n\n\tfriend mint operator+(i64 l, const mint& r) { return\
    \ mint(l) += r; }\n\tfriend mint operator+(const mint& l, i64 r) { return mint(l)\
    \ += r; }\n\tfriend mint operator-(i64 l, const mint& r) { return mint(l) -= r;\
    \ }\n\tfriend mint operator-(const mint& l, i64 r) { return mint(l) -= r; }\n\t\
    friend mint operator*(i64 l, const mint& r) { return mint(l) *= r; }\n\tfriend\
    \ mint operator*(const mint& l, i64 r) { return mint(l) += r; }\n\n\n\tfriend\
    \ std::ostream& operator<<(std::ostream& os, const mint& mt) {\n\t\tos << mt.val();\n\
    \t\treturn os;\n\t}\n\tfriend std::istream& operator>>(std::istream& is, mint&\
    \ mt) {\n\t\ti64 v_;\n\t\tis >> v_;\n\t\tmt = v_;\n\t\treturn is;\n\t}\n\tconstexpr\
    \ mint pow(u64 e) const {\n\t\tmint res(1), base(*this);\n\n\t\twhile (e) {\n\t\
    \t\tif (e & 1) {\n\t\t\t\tres *= base;\n\t\t\t}\n\t\t\te >>= 1;\n\t\t\tbase *=\
    \ base;\n\t\t}\n\t\treturn res;\n\t}\n\tconstexpr mint inv() const {\n\t\treturn\
    \ pow(mod - 2);\n\t}\n\n\tmint& operator/=(const mint& r) { return (*this) *=\
    \ r.inv(); }\n\tmint operator/(const mint& r) const { return mint(*this) *= r.inv();\
    \ }\n\tmint& operator/=(i64 r) { return (*this) /= mint(r); }\n\tfriend mint operator/(const\
    \ mint& l, i64 r) { return mint(l) /= r; }\n\tfriend mint operator/(i64 l, const\
    \ mint& r) { return mint(l) /= r; }\n};\n};  // namespace library\ntemplate <int\
    \ id> typename library::barrett_modint<id>::u32 library::barrett_modint<id>::mod;\n\
    template<int id>typename library::barrett_modint<id>::br library::barrett_modint<id>::brt;\n\
    \nnamespace library{\n\ntemplate <typename T = uint32_t, typename LargeT = uint64_t,\
    \ int id = -1>\nclass dynamic_modint {\n        static T mod;\n        static\
    \ internal::MontgomeryReduction<T, LargeT> mr;\n\n      public:\n        static\
    \ void set_mod(T mod_) {\n            mr.set_mod(mod_);\n            mod = mod_;\n\
    \        }\n\n        static T get_mod() { return mod; }\n\n      private:\n \
    \       T v;\n      public:\n        dynamic_modint(T v_ = 0) {\n            \
    \    assert(mod);\n                v = mr.generate(v_);\n        }\n        T\
    \ val() const { return mr.reduce(v); }\n\n        using mint = dynamic_modint<T,\
    \ LargeT,id>;\n        mint& operator+=(const mint& r) {\n                v +=\
    \ r.v;\n                if (v >= mr.get_mod()) {\n                        v -=\
    \ mr.get_mod();\n                }\n\n                return (*this);\n      \
    \  }\n\n        mint& operator-=(const mint& r) {\n                v += mr.get_mod()\
    \ - r.v;\n                if (v >= mr.get_mod) {\n                        v -=\
    \ mr.get_mod();\n                }\n\n                return (*this);\n      \
    \  }\n\n        mint& operator*=(const mint& r) {\n                v = mr.mult(v,\
    \ r.v);\n                return (*this);\n        }\n\n        mint operator+(const\
    \ mint& r) { return mint(*this) += r; }\n        mint operator-(const mint& r)\
    \ { return mint(*this) -= r; }\n        mint operator*(const mint& r) { return\
    \ mint(*this) *= r; }\n\n        mint& operator=(const T& v_) {\n            \
    \    (*this) = mint(v_);\n                return (*this);\n        }\n\n     \
    \   friend std::ostream& operator<<(std::ostream& os, const mint& mt) {\n    \
    \            os << mt.val();\n                return os;\n        }\n        friend\
    \ std::istream& operator>>(std::istream& is, mint& mt) {\n                T v_;\n\
    \                is >> v_;\n                mt = v_;\n                return is;\n\
    \        }\n        template <typename P> mint pow(P e) const {\n            \
    \    assert(e >= 0);\n                mint res(1), base(*this);\n\n          \
    \      while (e) {\n                        if (e & 1) {\n                   \
    \             res *= base;\n                        }\n                      \
    \  e >>= 1;\n                        base *= base;\n                }\n      \
    \          return res;\n        }\n        mint inv() const { return pow(mod -\
    \ 2); }\n\n        mint& operator/=(const mint& r) { return (*this) *= r.inv();\
    \ }\n        mint operator/(const mint& r) const { return mint(*this) *= r.inv();\
    \ }\n        mint& operator/=(T r) { return (*this) /= mint(r); }\n        friend\
    \ mint operator/(const mint& l, T r) {\n                return mint(l) /= r;\n\
    \        }\n        friend mint operator/(T l, const mint& r) {\n            \
    \    return mint(l) /= r;\n        }\n};\n\n};  // namespace library\n\ntemplate\
    \ <typename T, typename LargeT, int id>\nT library::dynamic_modint<T, LargeT,\
    \ id>::mod;\ntemplate <typename T, typename LargeT, int id>\nlibrary::internal::MontgomeryReduction<T,\
    \ LargeT>\n    library::dynamic_modint<T, LargeT, id>::mr;\n\n///@brief dynamic\
    \ modint(\u52D5\u7684modint)\n///@docs docs/math/dynamic_modint.md\n#line 3 \"\
    math/miller.hpp\"\nnamespace library {\n    namespace miller {\n        using\
    \ i128 = __int128_t;\n        using u128 = __uint128_t;\n        using u64 = uint64_t;\n\
    \        using u32 = uint32_t;\n\n        template<typename mint>\n        bool\
    \ miller_rabin(u64 n, const u64 bases[], int length) {\n            u64 d = n\
    \ - 1;\n\n            while (~d & 1) {\n                d >>= 1;\n           \
    \ }\n\n            u64 rev = n - 1;\n            if (mint::get_mod() != n) {\n\
    \                mint::set_mod(n);\n            }\n            for (int i = 0;\
    \ i < length; i++) {\n                u64 a = bases[i];\n\n                if\
    \ (n <= a) {\n                    return true;\n                }\n          \
    \      u64 t = d;\n                mint y = mint(a).pow(t);\n                while\
    \ (t != n - 1 && y.val() != 1 && y.val() != rev) {\n                    y *= y;\n\
    \                    t <<= 1;\n                }\n\n                if (y.val()\
    \ != rev && (~t & 1))return false;\n            }\n            return true;\n\
    \        }\n\n\n        constexpr u64 bases_int[3] = { 2, 7, 61 };  // int\u3060\
    \u3068\u30012,7,61\u3067\u5341\u5206\n        constexpr u64 bases_ll[7] = { 2,\
    \ 325, 9375, 28178, 450775, 9780504, 1795265022 };\n        bool is_prime(u64\
    \ n) {\n            if (n < 2) {\n                return false;\n            }\n\
    \            else if (n == 2) {\n                return true;\n            }\n\
    \            else if (~n & 1) {\n                return false;\n            }\n\
    \            if (n < (1ul << 31)) {\n                return miller_rabin<barrett_modint<-1>>(n,\
    \ bases_int, 3);\n            }\n            else {\n                return miller_rabin<dynamic_modint<u64,u128,-1>>(n,\
    \ bases_ll, 7);\n            }\n        }\n    };\n};\n///@brief MillerRabin\u306E\
    \u7D20\u6570\u5224\u5B9A\n#line 2 \"math/gcd.hpp\"\nnamespace library {\ntemplate\
    \ <typename T> constexpr inline T _gcd(T a, T b) {\n    assert(a >= 0 && b >=\
    \ 0);\n    if (a == 0 || b == 0) return a + b;\n    int d = std::min(__builtin_ctzll(a),\
    \ __builtin_ctzll(b));\n    a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n\
    \    while (a != b) {\n        if (a == 0 || b == 0) {\n            return a +\
    \ b;\n        }\n        if (a > b) {\n            a -= b;\n            a >>=\
    \ __builtin_ctzll(a);\n        }else{\n            b -= a;\n            b >>=\
    \ __builtin_ctzll(b);\n        }\n    }\n\n    return a << d;\n}\ntemplate<typename\
    \ T>\nconstexpr inline T ext_gcd(T a, T b, T &x, T &y) {\n    x = 1, y = 0;\n\
    \    T nx = 0, ny = 1;\n    while(b) {\n        T q = a / b;\n        std::tie(a,\
    \ b) = std::make_pair(b, a % b);\n        std::tie(x, nx) = std::make_pair(nx,\
    \ x - nx * q);\n        std::tie(y, ny) = std::make_pair(ny, y - ny * q);\n  \
    \  }\n    return a;\n}\n\n};  // namespace library\n#line 6 \"math/rho.hpp\"\n\
    ///@brief \u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho\u6CD5)\nnamespace\
    \ library {\nnamespace rho {\nusing i128 = __int128_t;\nusing u128 = __uint128_t;\n\
    using u64 = uint64_t;\nusing u32 = uint32_t;\n\ntemplate <typename mint> \nu64\
    \ find_factor(u64 n) {\n    static u64 v = 20001;   //rng\n    \n    if (~n &\
    \ 1uL) {\n        return 2;\n    }\n    if (library::miller::is_prime(n)) {\n\
    \        return n;\n    }\n\n    if (mint::get_mod() != n) {\n        mint::set_mod(n);\n\
    \    }\n    while (1) {\n        v ^= v << 13, v ^= v >> 7, v ^= v << 17;\n  \
    \      mint c(v);\n        auto f = [&](mint x) -> mint { return x.pow(2) + c;\
    \ };\n        v ^= v << 13, v ^= v >> 7, v ^= v << 17;\n        mint x = v;\n\
    \        mint y = f(x);\n        u64 d = 1;\n        while (d == 1) {\n      \
    \      d = _gcd<long long>(abs((long long)x.val() - (long long)y.val()),\n   \
    \                             n);\n            x = f(x);\n            y = f(f(y));\n\
    \        }\n        if (1 < d && d < n) {\n            return d;\n        }\n\
    \    }\n    return -1;  \n}\ntemplate<typename mint>\nstd::vector<u64> rho_fact(u64\
    \ n) {\n    if (n < 2) {\n        return {};\n    }\n    if (library::miller::is_prime(n))\
    \ {\n        return { n };\n    }\n    std::vector<u64> v;\n    std::vector<u64>\
    \ st{n};\n    while (st.size()) {\n        u64& m = st.back();\n        if (library::miller::is_prime(m))\
    \ {\n            v.emplace_back(m);\n            st.pop_back();\n        }else\
    \ {\n            u64 d = find_factor<mint>(m);\n            m /= d;\n        \
    \    st.emplace_back(d);\n        }\n    }\n    return v;\n}\nstd::vector<u64>\
    \ factorize(u64 n) {\n    if (n < 2) {\n        return {};\n    }\n    auto v\
    \ = (n < (1uL << 31) ? rho_fact<dynamic_modint<u32, u64, 10>>(n)\n           \
    \                   : rho_fact<dynamic_modint<u64, u128, 10>>(n));\n    std::sort(v.begin(),\
    \ v.end());\n    return v;\n}\nstd::vector<std::pair<u64, int>> exp_factorize(u64\
    \ n) {\n    std::vector<u64> pf = factorize(n);\n    if (pf.empty()) {\n     \
    \   return {};\n    }\n    std::vector<std::pair<u64, int>> res;\n    res.emplace_back(pf.front(),\
    \ 1);\n    for (int i = 1; i < pf.size(); i++) {\n        if (res.back().first\
    \ == pf[i]) {\n            res.back().second++;\n        } else {\n          \
    \  res.emplace_back(pf[i], 1);\n        }\n    }\n    return res;\n}\n\n};  //\
    \ namespace rho\n};  // namespace library\n#line 5 \"math/primitive_root.hpp\"\
    \n\nnamespace library {\n    \n//@brief primitive root(\u539F\u59CB\u6839)\ninline\
    \ uint64_t primitive_root(uint64_t p) {\n    if (p == 2) return 1;\n    auto pf\
    \ = library::rho::factorize(p - 1);\n    pf.erase(std::unique(pf.begin(),pf.end()),\
    \ pf.end());\n    for (auto& q : pf) {\n        q = (p - 1) / q;\n    }\n    using\
    \ ull = unsigned long long;\n    using mint = dynamic_modint<uint64_t, __uint128_t,\
    \ 10>;\n    if (mint::get_mod() != p) {\n        mint::set_mod(p);\n    }\n  \
    \  static ull rng = 2008;\n    while (1) {\n        rng ^= rng << 13; rng ^= rng\
    \ >> 7; rng ^= rng << 17;\n        mint g(rng);\n        if (g.val() == 0) continue;\n\
    \        bool is_ok = true;\n        for (const auto& q : pf) {\n            if\
    \ (mint(g).pow(q).val() == 1) {\n                is_ok = false;\n            \
    \    break;\n            }\n        }\n        if (is_ok) {\n            return\
    \ g.val();\n        }\n    }\n}\n\n};  // namespace library\n#line 4 \"test/yosupo_judge/math/Primitive_Root.test.cpp\"\
    \nusing namespace std;\nusing namespace library;\nint main() {\n    int q;\n \
    \   scanf(\"%d\", &q);\n    while (q--) {\n        ll p;\n        scanf(\"%lld\"\
    , &p);\n        printf(\"%lld\\n\", primitive_root(p));\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n#include\"\
    template.hpp\"\n#include\"math/primitive_root.hpp\"\nusing namespace std;\nusing\
    \ namespace library;\nint main() {\n    int q;\n    scanf(\"%d\", &q);\n    while\
    \ (q--) {\n        ll p;\n        scanf(\"%lld\", &p);\n        printf(\"%lld\\\
    n\", primitive_root(p));\n    }\n}\n"
  dependsOn:
  - template.hpp
  - math/primitive_root.hpp
  - math/dynamic_modint.hpp
  - internal/barrett.hpp
  - internal/montgomery.hpp
  - math/rho.hpp
  - math/miller.hpp
  - math/gcd.hpp
  isVerificationFile: true
  path: test/yosupo_judge/math/Primitive_Root.test.cpp
  requiredBy: []
  timestamp: '2023-04-06 21:43:06+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_judge/math/Primitive_Root.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/math/Primitive_Root.test.cpp
- /verify/test/yosupo_judge/math/Primitive_Root.test.cpp.html
title: test/yosupo_judge/math/Primitive_Root.test.cpp
---