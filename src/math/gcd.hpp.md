---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
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
  - icon: ':heavy_check_mark:'
    path: src/math/static_modint.hpp
    title: "static modint(\u9759\u7684modint)"
  - icon: ':warning:'
    path: src/string/rolling_hash.hpp
    title: "Rollinghash(\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/NTL/1_D.test.cpp
    title: test/AOJ/NTL/1_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/AOJ/NTL/1_E.test.cpp
    title: test/AOJ/NTL/1_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Point_Set_Range_Composite.test.cpp
    title: test/yosupo_judge/data_structure/Point_Set_Range_Composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Range_Affine_Point_Get.test.cpp
    title: test/yosupo_judge/data_structure/Range_Affine_Point_Get.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
    title: test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
    title: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Factorize.test.cpp
    title: test/yosupo_judge/math/Factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Primitive_Root.test.cpp
    title: test/yosupo_judge/math/Primitive_Root.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/matrix/Matrix Product.test.cpp
    title: test/yosupo_judge/matrix/Matrix Product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/math/gcd.hpp\"\n#include <cassert>\n#include <tuple>\n\
    namespace kyopro {\ntemplate <typename T> constexpr T _gcd(T a, T b) {\n    assert(a\
    \ >= 0 && b >= 0);\n    if (a == 0 || b == 0) return a + b;\n    int d = std::min<T>(__builtin_ctzll(a),\
    \ __builtin_ctzll(b));\n    a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n\
    \    while (a != b) {\n        if (a == 0 || b == 0) {\n            return a +\
    \ b;\n        }\n        if (a > b) {\n            a -= b;\n            a >>=\
    \ __builtin_ctzll(a);\n        } else {\n            b -= a;\n            b >>=\
    \ __builtin_ctzll(b);\n        }\n    }\n\n    return a << d;\n}\ntemplate <typename\
    \ T> constexpr T ext_gcd(T a, T b, T& x, T& y) {\n    x = 1, y = 0;\n    T nx\
    \ = 0, ny = 1;\n    while (b) {\n        T q = a / b;\n        std::tie(a, b)\
    \ = std::pair<T, T>{b, a % b};\n        std::tie(x, nx) = std::pair<T, T>{nx,\
    \ x - nx * q};\n        std::tie(y, ny) = std::pair<T, T>{ny, y - ny * q};\n \
    \   }\n    return a;\n}\n};  // namespace kyopro\n"
  code: "#pragma once\n#include <cassert>\n#include <tuple>\nnamespace kyopro {\n\
    template <typename T> constexpr T _gcd(T a, T b) {\n    assert(a >= 0 && b >=\
    \ 0);\n    if (a == 0 || b == 0) return a + b;\n    int d = std::min<T>(__builtin_ctzll(a),\
    \ __builtin_ctzll(b));\n    a >>= __builtin_ctzll(a), b >>= __builtin_ctzll(b);\n\
    \    while (a != b) {\n        if (a == 0 || b == 0) {\n            return a +\
    \ b;\n        }\n        if (a > b) {\n            a -= b;\n            a >>=\
    \ __builtin_ctzll(a);\n        } else {\n            b -= a;\n            b >>=\
    \ __builtin_ctzll(b);\n        }\n    }\n\n    return a << d;\n}\ntemplate <typename\
    \ T> constexpr T ext_gcd(T a, T b, T& x, T& y) {\n    x = 1, y = 0;\n    T nx\
    \ = 0, ny = 1;\n    while (b) {\n        T q = a / b;\n        std::tie(a, b)\
    \ = std::pair<T, T>{b, a % b};\n        std::tie(x, nx) = std::pair<T, T>{nx,\
    \ x - nx * q};\n        std::tie(y, ny) = std::pair<T, T>{ny, y - ny * q};\n \
    \   }\n    return a;\n}\n};  // namespace kyopro"
  dependsOn: []
  isVerificationFile: false
  path: src/math/gcd.hpp
  requiredBy:
  - src/string/rolling_hash.hpp
  - src/math/primitive_root.hpp
  - src/math/rho.hpp
  - src/math/mod_log.hpp
  - src/math/static_modint.hpp
  - src/math/phi_function.hpp
  timestamp: '2023-04-08 13:07:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/NTL/1_D.test.cpp
  - test/AOJ/NTL/1_E.test.cpp
  - test/yosupo_judge/data_structure/Range_Affine_Range_Sum.test.cpp
  - test/yosupo_judge/data_structure/Range_Affine_Point_Get.test.cpp
  - test/yosupo_judge/data_structure/Point_Set_Range_Composite.test.cpp
  - test/yosupo_judge/matrix/Matrix Product.test.cpp
  - test/yosupo_judge/math/Factorize.test.cpp
  - test/yosupo_judge/math/Primitive_Root.test.cpp
  - test/yosupo_judge/math/Discrete_Logarithm.test.cpp
documentation_of: src/math/gcd.hpp
layout: document
redirect_from:
- /library/src/math/gcd.hpp
- /library/src/math/gcd.hpp.html
title: src/math/gcd.hpp
---