---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/barrett.hpp
    title: barrett reduction
  - icon: ':heavy_check_mark:'
    path: math/dynamic_modint.hpp
    title: dynamic_modint(64bit)
  - icon: ':heavy_check_mark:'
    path: math/gcd.hpp
    title: math/gcd.hpp
  - icon: ':heavy_check_mark:'
    path: math/miller.hpp
    title: "MillerRabin\u306E\u7D20\u6570\u5224\u5B9A"
  - icon: ':heavy_check_mark:'
    path: math/montgomery.hpp
    title: MontgomeryReduction
  - icon: ':heavy_check_mark:'
    path: math/primitive_root.hpp
    title: "primitive root(\u539F\u59CB\u6839)"
  - icon: ':heavy_check_mark:'
    path: math/rho.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho\u6CD5)"
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
    PROBLEM: https://judge.yosupo.jp/problem/primitive_root
    links:
    - https://judge.yosupo.jp/problem/primitive_root
  bundledCode: "#line 1 \"test/yosupo_judge/new/Primitive_Root.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n#line 2 \"template.hpp\"\
    \n#include<bits/stdc++.h>\nusing namespace std;\n#define rep(i, N)  for(int i=0;i<(N);i++)\n\
    #define all(x) (x).begin(),(x).end()\n#define popcount(x) __builtin_popcount(x)\n\
    using i128=__int128_t;\nusing ll = long long;\nusing ld = long double;\nusing\
    \ graph = vector<vector<int>>;\nusing P = pair<int, int>;\nconstexpr int inf =\
    \ 1e9;\nconstexpr ll infl = 1e18;\nconstexpr ld eps = 1e-6;\nconst long double\
    \ pi = acos(-1);\nconstexpr uint64_t MOD = 1e9 + 7;\nconstexpr uint64_t MOD2 =\
    \ 998244353;\nconstexpr int dx[] = { 1,0,-1,0 };\nconstexpr int dy[] = { 0,1,0,-1\
    \ };\ntemplate<class T>static constexpr inline void chmax(T&x,T y){if(x<y)x=y;}\n\
    template<class T>static constexpr inline void chmin(T&x,T y){if(x>y)x=y;}\n#line\
    \ 2 \"math/barrett.hpp\"\nnamespace internal {\n\t///@brief barrett reduction\n\
    \tclass barrett {\n\t\tusing u32 = uint32_t;\n\t\tusing u64 = uint64_t;\n\n\t\t\
    u32 m;\n\t\tu64 im;\n\tpublic:\n\t\texplicit barrett() = default;\n\t\texplicit\
    \ barrett(const u32& m_) :m(m_), im((u64)(-1) / m_ + 1) {}\n\n\t\tu32 get_mod()\
    \ const { return m; }\n\t\tu32 mul(u32 a, u32 b) {\n\t\t\tif (a == 0 || b == 0)\
    \ {\n\t\t\t\treturn 0;\n\t\t\t}\n\t\t\tu64 z = a;\n\t\t\tz *= b;\n#ifdef _MSC_VER\n\
    \t\t\tu64 x;\n\n\t\t\t_umul128(z, im, &x);\n#else\n\t\t\tu64 x = (u64)(((__uint128_t)(z)*im)\
    \ >> 64);\n#endif\n\n\t\t\tu32 v = (u32)(z - x * m);\n\n\t\t\tif (v >= m)v +=\
    \ m;\n\t\t\treturn v;\n\t\t}\n\t};\n}\n#line 2 \"math/montgomery.hpp\"\nnamespace\
    \ internal {\n    using u32 = uint32_t;\n    using u64 = uint64_t;\n    using\
    \ i32 = int32_t;\n    using i64 = int64_t;\n    using u128 = __uint128_t;\n  \
    \  using i128 = __int128_t;\n    /// @brief MontgomeryReduction\n    template<typename\
    \ T,typename LargeT>\n    class MontgomeryReduction64 {\n        static constexpr\
    \ int lg = numeric_limits<T>::digits;\n        T mod, r, r2, minv;\n        T\
    \ calc_inv() {\n            T t = 0, res = 0;\n            for (int i = 0; i <\
    \ lg; i++) {\n                if (~t & 1) {\n                    t += mod;\n \
    \                   res += static_cast<T>(1) << i;\n                }\n      \
    \          t >>= 1;\n            }\n            return res;\n        }\n\n\n \
    \   public:\n        MontgomeryReduction64() = default;\n        constexpr T get_mod()\
    \ { return mod; }\n        constexpr int get_lg() { return lg; }\n\n\n       \
    \ void set_mod(const T& m) {\n            assert(m > 0);\n            assert(m\
    \ & 1);\n\n            mod = m;\n\n            r = (-static_cast<T>(mod)) % mod;\n\
    \            r2 = (-static_cast<LargeT>(mod)) % mod;\n            minv = calc_inv();\n\
    \        }\n\n\n        T reduce(LargeT x) const {\n            u64 res = (x +\
    \ static_cast<LargeT>(static_cast<T>(x) * minv) * mod) >> lg;\n\n            if\
    \ (res >= mod)res -= mod;\n            return res;\n        }\n\n        T generate(LargeT\
    \ x) {\n            return reduce(x * r2);\n        }\n\n        T mult(T x, T\
    \ y) {\n            return reduce(static_cast<LargeT>(x) * y);\n        }\n  \
    \  };\n};\n#line 4 \"math/dynamic_modint.hpp\"\nclass dynamic_modint32 {\n\tusing\
    \ u32 = uint32_t;\n\tusing u64 = uint64_t;\n\n\tusing i32 = int32_t;\n\tusing\
    \ i64 = int64_t;\n\tusing br = internal::barrett;\n\n\tstatic br brt;\n\tstatic\
    \ u32 mod;\n\tu32 v;\t//value\npublic:\n\tstatic void set_mod(const u32& mod_)\
    \ {\n\t\tbrt = br(mod_);\n\t\tmod = mod_;\n\t}\nprivate:\n\tu32 normalize(const\
    \ i64& x) const {\n\t\ti32 m = x % mod;\n\t\tif (m < 0) {\n\t\t\tm += mod;\n\t\
    \t}\n\t\treturn m;\n\t}\npublic:\n\tdynamic_modint32() :v(0) { assert(mod); }\t\
    //mod\u304C\u6C7A\u5B9A\u6E08\u307F\u3067\u3042\u308B\u5FC5\u8981\u304C\u3042\u308B\
    \n\tdynamic_modint32(const i64& v_) :v(normalize(v_)) { assert(mod); }\t\n\n\t\
    u32 val() const { return v; }\n    static u32 get_mod() { return mod; }\n    using\
    \ mint = dynamic_modint32;\n\n\t//operators\n\tmint& operator=(const i64& r) {\n\
    \t\tv = normalize(r); \n\t\treturn (*this);\n\t}\n\tmint& operator+=(const mint&\
    \ r) {\n\t\tv += r.v;\n\t\tif (v >= mod) {\n\t\t\tv -= mod;\n\t\t}\n\t\treturn\
    \ (*this);\n\t}\n\tmint& operator-=(const mint&r) {\n\t\tv += mod - r.v;\n\t\t\
    if (v >= mod) {\n\t\t\tv -= mod;\n\t\t}\n\n\t\treturn (*this);\n\t}\n\tmint& operator*=(const\
    \ mint& r) {\n\t\tv = brt.mul(v, r.v);\n\t\treturn (*this);\n\t}\n\n\tmint operator+(const\
    \ mint& r) const { return mint(*this) += r; }\n\tmint operator-(const mint& r)\
    \ const { return mint(*this) -= r; }\n\tmint operator*(const mint& r) const {\
    \ return mint(*this) *= r; }\n\n\n\n\tmint& operator+= (const i64& r) { return\
    \ (*this) += mint(r); }\n\tmint& operator-= (const i64& r) { return (*this) -=\
    \ mint(r); }\n\tmint& operator*= (const i64& r) { return (*this) *= mint(r); }\n\
    \n\tfriend mint operator+(const i64& l, const mint& r) { return mint(l) += r;\
    \ }\n\tfriend mint operator+(const mint& l, const i64& r) { return mint(l) +=\
    \ r; }\n\tfriend mint operator-(const i64& l, const mint& r) { return mint(l)\
    \ -= r; }\n\tfriend mint operator-(const mint& l, const i64& r) { return mint(l)\
    \ -= r; }\n\tfriend mint operator*(const i64& l, const mint& r) { return mint(l)\
    \ *= r; }\n\tfriend mint operator*(const mint& l, const i64& r) { return mint(l)\
    \ += r; }\n\n\n\tfriend ostream& operator<<(ostream& os, const mint& mt) {\n\t\
    \tos << mt.val();\n\t\treturn os;\n\t}\n\tfriend istream& operator>>(istream&\
    \ is, mint& mt) {\n\t\ti64 v_;\n\t\tis >> v_;\n\t\tmt = v_;\n\t\treturn is;\n\t\
    }\n\tmint pow(u64 e) const {\n\t\tmint res(1), base(*this);\n\n\t\twhile (e) {\n\
    \t\t\tif (e & 1) {\n\t\t\t\tres *= base;\n\t\t\t}\n\t\t\te >>= 1;\n\t\t\tbase\
    \ *= base;\n\t\t}\n\t\treturn res;\n\t}\n\tmint inv() const {\n\t\treturn pow(mod\
    \ - 2);\n\t}\n\n\tmint& operator/=(const mint& r) { return (*this) *= r.inv();\
    \ }\n\tmint operator/(const mint& r) const { return mint(*this) *= r.inv(); }\n\
    \tmint& operator/=(const i64& r) { return (*this) /= mint(r); }\n\tfriend mint\
    \ operator/(const mint& l, const i64& r) { return mint(l) /= r; }\n\tfriend mint\
    \ operator/(const i64& l, const mint& r) { return mint(l) /= r; }\n};\ntypename\
    \ dynamic_modint32::u32 dynamic_modint32::mod;\ntypename dynamic_modint32::br\
    \ dynamic_modint32::brt;\n\n\n/// @brief dynamic_modint(64bit)\n/// @tparam T\
    \ \u578B(64bit,32bit\u306A\u3069)\n/// @tparam LargeT \u7A4D\u304C\u53CE\u307E\
    \u3063\u3066\u304F\u308C\u308B\u578B\n/// @note T,LargeT\u306E\u3044\u305A\u308C\
    \u3082unsigned\u3067\u6E21\u3059\ntemplate <typename T = uint32_t, typename LargeT\
    \ = uint64_t>\n class dynamic_modint {\n        static T mod;\n        static\
    \ internal::MontgomeryReduction64<T, LargeT> mr;\n\n      public:\n        static\
    \ void set_mod(const T& mod_) {\n                mr.set_mod(mod_);\n         \
    \       mod = mod_;\n        }\n\n        static T get_mod() { return mod; }\n\
    \n      private:\n        T v;\n      public:\n        dynamic_modint(const T&\
    \ v_ = 0) {\n                assert(mod);\n                v = mr.generate(v_);\n\
    \        }\n        T val() const { return mr.reduce(v); }\n\n        using mint\
    \ = dynamic_modint<T, LargeT>;\n        mint& operator+=(const mint& r) {\n  \
    \              v += r.v;\n                if (v >= mr.get_mod()) {\n         \
    \               v -= mr.get_mod();\n                }\n\n                return\
    \ (*this);\n        }\n\n        mint& operator-=(const mint& r) {\n         \
    \       v += mr.get_mod() - r.v;\n                if (v >= mr.get_mod) {\n   \
    \                     v -= mr.get_mod();\n                }\n\n              \
    \  return (*this);\n        }\n\n        mint& operator*=(const mint& r) {\n \
    \               v = mr.mult(v, r.v);\n                return (*this);\n      \
    \  }\n\n        mint operator+(const mint& r) { return mint(*this) += r; }\n \
    \       mint operator-(const mint& r) { return mint(*this) -= r; }\n        mint\
    \ operator*(const mint& r) { return mint(*this) *= r; }\n\n        mint& operator=(const\
    \ T& v_) {\n                (*this) = mint(v_);\n                return (*this);\n\
    \        }\n\n        friend ostream& operator<<(ostream& os, const mint& mt)\
    \ {\n                os << mt.val();\n                return os;\n        }\n\
    \        friend istream& operator>>(istream& is, mint& mt) {\n               \
    \ T v_;\n                is >> v_;\n                mt = v_;\n               \
    \ return is;\n        }\n        template <typename P> mint pow(P e) const {\n\
    \                assert(e >= 0);\n                mint res(1), base(*this);\n\n\
    \                while (e) {\n                        if (e & 1) {\n         \
    \                       res *= base;\n                        }\n            \
    \            e >>= 1;\n                        base *= base;\n               \
    \ }\n                return res;\n        }\n        mint inv() const { return\
    \ pow(mod - 2); }\n\n        mint& operator/=(const mint& r) { return (*this)\
    \ *= r.inv(); }\n        mint operator/(const mint& r) const { return mint(*this)\
    \ *= r.inv(); }\n        mint& operator/=(const T& r) { return (*this) /= mint(r);\
    \ }\n        friend mint operator/(const mint& l, const T& r) {\n            \
    \    return mint(l) /= r;\n        }\n        friend mint operator/(const T& l,\
    \ const mint& r) {\n                return mint(l) /= r;\n        }\n};\ntemplate<typename\
    \ T, typename LargeT>T dynamic_modint<T, LargeT>::mod;\ntemplate<typename T,typename\
    \ LargeT>internal::MontgomeryReduction64<T,LargeT> dynamic_modint<T,LargeT>::mr;\n\
    \n\n\n///@brief dynamic modint(\u52D5\u7684modint)\n///@docs docs/math/dynamic_modint.md\n\
    #line 3 \"math/miller.hpp\"\nnamespace prime {\n    namespace miller {\n     \
    \   using i128 = __int128_t;\n        using u128 = __uint128_t;\n        using\
    \ u64 = uint64_t;\n        using u32 = uint32_t;\n\n        template<typename\
    \ mint>\n        bool inline miller_rabin(u64 n, const u64 bases[], int length)\
    \ {\n            u64 d = n - 1;\n\n            while (~d & 1) {\n            \
    \    d >>= 1;\n            }\n\n            u64 rev = n - 1;\n            if (mint::get_mod()\
    \ != n) {\n                mint::set_mod(n);\n            }\n            for (int\
    \ i = 0; i < length; i++) {\n                u64 a = bases[i];\n\n           \
    \     if (n <= a) {\n                    return true;\n                }\n   \
    \             u64 t = d;\n                mint y = mint(a).pow(t);\n         \
    \       while (t != n - 1 && y.val() != 1 && y.val() != rev) {\n             \
    \       y *= y;\n                    t <<= 1;\n                }\n\n         \
    \       if (y.val() != rev && (~t & 1))return false;\n            }\n        \
    \    return true;\n        }\n\n\n        constexpr u64 bases_int[3] = { 2, 7,\
    \ 61 };  // int\u3060\u3068\u30012,7,61\u3067\u5341\u5206\n        constexpr u64\
    \ bases_ll[7] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };\n      \
    \  constexpr bool inline is_prime(u64 n) {\n            if (n < 2) {\n       \
    \         return false;\n            }\n            else if (n == 2) {\n     \
    \           return true;\n            }\n            else if (~n & 1) {\n    \
    \            return false;\n            }\n            if (n < (1ul << 31)) {\n\
    \                return miller_rabin<dynamic_modint<u32,u64>>(n, bases_int, 3);\n\
    \            }\n            else {\n                return miller_rabin<dynamic_modint<u64,u128>>(n,\
    \ bases_ll, 7);\n            }\n        }\n    };\n};\n///@brief MillerRabin\u306E\
    \u7D20\u6570\u5224\u5B9A\n#line 2 \"math/gcd.hpp\"\ntemplate<typename T>\nconstexpr\
    \ inline T _gcd(T a, T b) {\n    assert(a >= 0 && b >= 0);\n    if (a == 0 ||\
    \ b == 0) return a + b;\n    int d = min(__builtin_ctzll(a), __builtin_ctzll(b));\n\
    \    a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n    while (a != b) {\n\
    \        if (a == 0 || b == 0) {\n            return a + b;\n        }\n     \
    \   if (a > b) {\n            a -= b;\n            a >>= __builtin_ctzll(a);\n\
    \        }else{\n            b -= a;\n            b >>= __builtin_ctzll(b);\n\
    \        }\n    }\n\n    return a << d;\n}\ntemplate<typename T>\nconstexpr inline\
    \ T ext_gcd(T a, T b, T &x, T &y) {\n    x = 1, y = 0;\n    T nx = 0, ny = 1;\n\
    \    while(b) {\n        T q = a / b;\n        tie(a, b) = make_pair(b, a % b);\n\
    \        tie(x, nx) = make_pair(nx, x - nx*q);\n        tie(y, ny) = make_pair(ny,\
    \ y - ny*q);\n    }\n    return a;\n}\n#line 5 \"math/rho.hpp\"\n///@brief \u9AD8\
    \u901F\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho\u6CD5)\nnamespace prime {\n \
    \   namespace rho {\n        using i128 = __int128_t;\n        using u128 = __uint128_t;\n\
    \        using u64 = uint64_t;\n        using u32 = uint32_t;\n\n        template<typename\
    \ mint>\n        inline u64 find_factor(u64 n) {\n            static u64 v = 20001;\n\
    \n            if (~n & 1uL) {\n                return 2;\n            }\n    \
    \        if (prime::miller::is_prime(n)) {\n                return n;\n      \
    \      }\n\n            if (mint::get_mod() != n) {\n                mint::set_mod(n);\n\
    \            }\n            while (1) {\n                v ^= v << 13, v ^= v\
    \ >> 7, v ^= v << 17;\n                u64 c = v;\n                auto f = [&](mint\
    \ x) -> mint {\n                    return x.pow(2) + c;\n                };\n\
    \                v ^= v << 13, v ^= v >> 7, v ^= v << 17;\n                mint\
    \ x = v;\n                mint y = f(x);\n                u64 d = 1;\n       \
    \         while (d == 1) {\n                    d = _gcd<long long>(abs((long\
    \ long)x.val() - (long long)y.val()), n);\n                    x = f(x);\n   \
    \                 y = f(f(y));\n                }\n                if (1 < d &&\
    \ d < n) {\n                    return d;\n                }\n            }\n\
    \            exit(0);\n        }\n        template<typename mint>\n        inline\
    \ vector<u64> rho_fact(u64 n) {\n            if (n < 2) {\n                return\
    \ {};\n            }\n            if (prime::miller::is_prime(n)) {\n        \
    \        return { n };\n            }\n            vector<u64> v;\n          \
    \  vector<u64> st{ n };\n            while (st.size()) {\n                u64&\
    \ m = st.back();\n                if (prime::miller::is_prime(m)) {\n        \
    \            v.emplace_back(m);\n                    st.pop_back();\n        \
    \        }\n                else {\n                    u64 d = find_factor<mint>(m);\n\
    \                    m /= d;\n                    st.emplace_back(d);\n      \
    \          }\n            }\n            return v;\n        }\n        inline\
    \ vector<u64> factorize(u64 n) {\n            if (n < 2) {\n                return\
    \ {};\n            }\n            auto v = (n < (1uL << 31) ? rho_fact<dynamic_modint<u32,\
    \ u64>>(n) : rho_fact<dynamic_modint<u64, u128>>(n));\n            sort(v.begin(),\
    \ v.end());\n            return v;\n        }\n\n        inline vector<pair<u64,\
    \ int>> exp_factorize(u64 n) {\n            vector<u64> pf = factorize(n);\n \
    \           if (pf.empty()) {\n                return {};\n            }\n   \
    \         vector<pair<u64, int>> res;\n            res.emplace_back(pf.front(),\
    \ 1);\n            for (int i = 1; i < pf.size(); i++) {\n                if (res.back().first\
    \ == pf[i]) {\n                    res.back().second++;\n                }\n \
    \               else {\n                    res.emplace_back(pf[i], 1);\n    \
    \            }\n            }\n\n            return res;\n        }\n    };  //\
    \ namespace pollard\n};  // namespace prime\n#line 4 \"math/primitive_root.hpp\"\
    \ninline uint64_t primitive_root(uint64_t p) {\n    if (p == 2) return 1;\n  \
    \  auto pf = prime::rho::factorize(p - 1);\n    pf.erase(unique(all(pf)), pf.end());\n\
    \    for (auto& q : pf) {\n        q = (p - 1) / q;\n    }\n    using ull = unsigned\
    \ long long;\n    if (dynamic_modint<uint64_t, __uint128_t>::get_mod() != p) {\n\
    \        dynamic_modint<uint64_t, __uint128_t>::set_mod(p);\n    }\n    ull rng\
    \ = rand();\n    while (1) {\n        rng ^= rng << 13; rng ^= rng >> 7; rng ^=\
    \ rng << 17;\n        dynamic_modint<uint64_t, __uint128_t> g(rng);\n        if\
    \ (g.val() == 0) continue;\n        bool is_ok = true;\n        for (const auto&\
    \ q : pf) {\n            if (dynamic_modint<uint64_t, __uint128_t>(g).pow(q).val()\
    \ == 1) {\n                is_ok = false;\n                break;\n          \
    \  }\n        }\n        if (is_ok) {\n            return g.val();\n        }\n\
    \    }\n}\n\n//@brief primitive root(\u539F\u59CB\u6839)\n#line 4 \"test/yosupo_judge/new/Primitive_Root.test.cpp\"\
    \nint main(){\n    int q;\n    scanf(\"%d\", &q);\n    while (q--) {\n       \
    \ ll p;\n        scanf(\"%lld\", &p);\n        ll ans = primitive_root(p);\n \
    \       printf(\"%lld\\n\", ans);\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n#include\"\
    template.hpp\"\n#include\"math/primitive_root.hpp\"\nint main(){\n    int q;\n\
    \    scanf(\"%d\", &q);\n    while (q--) {\n        ll p;\n        scanf(\"%lld\"\
    , &p);\n        ll ans = primitive_root(p);\n        printf(\"%lld\\n\", ans);\n\
    \    }\n}\n"
  dependsOn:
  - template.hpp
  - math/primitive_root.hpp
  - math/dynamic_modint.hpp
  - math/barrett.hpp
  - math/montgomery.hpp
  - math/rho.hpp
  - math/miller.hpp
  - math/gcd.hpp
  isVerificationFile: true
  path: test/yosupo_judge/new/Primitive_Root.test.cpp
  requiredBy: []
  timestamp: '2023-04-02 14:35:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_judge/new/Primitive_Root.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_judge/new/Primitive_Root.test.cpp
- /verify/test/yosupo_judge/new/Primitive_Root.test.cpp.html
title: test/yosupo_judge/new/Primitive_Root.test.cpp
---