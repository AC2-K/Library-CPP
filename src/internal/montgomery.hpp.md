---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/math/dynamic_modint.hpp
    title: "dynamic modint(\u52D5\u7684modint)"
  - icon: ':heavy_check_mark:'
    path: src/math/miller.hpp
    title: "MillerRabin\u306E\u7D20\u6570\u5224\u5B9A"
  - icon: ':heavy_check_mark:'
    path: src/math/mod_log.hpp
    title: "Discrete Logarithm(\u96E2\u6563\u5BFE\u6570)"
  - icon: ':heavy_check_mark:'
    path: src/math/phi_function.hpp
    title: "phi function($\\phi$ \u95A2\u6570)"
  - icon: ':heavy_check_mark:'
    path: src/math/primitive_root.hpp
    title: "primitive root(\u539F\u59CB\u6839)"
  - icon: ':heavy_check_mark:'
    path: src/math/rho.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho\u6CD5)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/NTL/1_D.test.cpp
    title: test/AOJ/NTL/1_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
    title: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Factorize.test.cpp
    title: test/yosupo_judge/math/Factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Primitive_Root.test.cpp
    title: test/yosupo_judge/math/Primitive_Root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: MontgomeryReduction
    links: []
  bundledCode: "#line 2 \"src/internal/montgomery.hpp\"\n#include <cassert>\n#include\
    \ <limits>\n#include <numeric>\nnamespace kyopro {\nnamespace internal {\nusing\
    \ u32 = uint32_t;\nusing u64 = uint64_t;\nusing i32 = int32_t;\nusing i64 = int64_t;\n\
    using u128 = __uint128_t;\nusing i128 = __int128_t;\n/// @brief MontgomeryReduction\n\
    template <typename T, typename LargeT> class Montgomery {\n    static constexpr\
    \ int lg = std::numeric_limits<T>::digits;\n    T mod, r, r2, minv;\n    T calc_inv()\
    \ {\n        T t = 0, res = 0;\n        for (int i = 0; i < lg; i++) {\n     \
    \       if (~t & 1) {\n                t += mod;\n                res += static_cast<T>(1)\
    \ << i;\n            }\n            t >>= 1;\n        }\n        return res;\n\
    \    }\n\n  public:\n    Montgomery() = default;\n    constexpr inline T get_mod()\
    \ { return mod; }\n    constexpr inline int get_lg() { return lg; }\n\n    void\
    \ set_mod(const T& m) {\n        assert(m > 0);\n        assert(m & 1);\n\n  \
    \      mod = m;\n\n        r = (-static_cast<T>(mod)) % mod;\n        r2 = (-static_cast<LargeT>(mod))\
    \ % mod;\n        minv = calc_inv();\n    }\n\n    T reduce(LargeT x) const {\n\
    \        u64 res =\n            (x + static_cast<LargeT>(static_cast<T>(x) * minv)\
    \ * mod) >> lg;\n\n        if (res >= mod) res -= mod;\n        return res;\n\
    \    }\n\n    inline T generate(LargeT x) { return reduce(x * r2); }\n\n    inline\
    \ T mult(T x, T y) { return reduce((LargeT)x * y); }\n};\n};  // namespace internal\n\
    };  // namespace kyopro\n"
  code: "#pragma once\n#include <cassert>\n#include <limits>\n#include <numeric>\n\
    namespace kyopro {\nnamespace internal {\nusing u32 = uint32_t;\nusing u64 = uint64_t;\n\
    using i32 = int32_t;\nusing i64 = int64_t;\nusing u128 = __uint128_t;\nusing i128\
    \ = __int128_t;\n/// @brief MontgomeryReduction\ntemplate <typename T, typename\
    \ LargeT> class Montgomery {\n    static constexpr int lg = std::numeric_limits<T>::digits;\n\
    \    T mod, r, r2, minv;\n    T calc_inv() {\n        T t = 0, res = 0;\n    \
    \    for (int i = 0; i < lg; i++) {\n            if (~t & 1) {\n             \
    \   t += mod;\n                res += static_cast<T>(1) << i;\n            }\n\
    \            t >>= 1;\n        }\n        return res;\n    }\n\n  public:\n  \
    \  Montgomery() = default;\n    constexpr inline T get_mod() { return mod; }\n\
    \    constexpr inline int get_lg() { return lg; }\n\n    void set_mod(const T&\
    \ m) {\n        assert(m > 0);\n        assert(m & 1);\n\n        mod = m;\n\n\
    \        r = (-static_cast<T>(mod)) % mod;\n        r2 = (-static_cast<LargeT>(mod))\
    \ % mod;\n        minv = calc_inv();\n    }\n\n    T reduce(LargeT x) const {\n\
    \        u64 res =\n            (x + static_cast<LargeT>(static_cast<T>(x) * minv)\
    \ * mod) >> lg;\n\n        if (res >= mod) res -= mod;\n        return res;\n\
    \    }\n\n    inline T generate(LargeT x) { return reduce(x * r2); }\n\n    inline\
    \ T mult(T x, T y) { return reduce((LargeT)x * y); }\n};\n};  // namespace internal\n\
    };  // namespace kyopro"
  dependsOn: []
  isVerificationFile: false
  path: src/internal/montgomery.hpp
  requiredBy:
  - src/math/dynamic_modint.hpp
  - src/math/miller.hpp
  - src/math/phi_function.hpp
  - src/math/mod_log.hpp
  - src/math/primitive_root.hpp
  - src/math/rho.hpp
  timestamp: '2023-04-08 13:07:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_judge/math/Factorize.test.cpp
  - test/yosupo_judge/math/Primitive_Root.test.cpp
  - test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  - test/AOJ/NTL/1_D.test.cpp
documentation_of: src/internal/montgomery.hpp
layout: document
redirect_from:
- /library/src/internal/montgomery.hpp
- /library/src/internal/montgomery.hpp.html
title: MontgomeryReduction
---