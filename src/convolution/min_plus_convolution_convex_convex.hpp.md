---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/internal/type_traits.hpp
    title: src/internal/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
    title: test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Min Plus Convolution(Convex, Convex)
    links: []
  bundledCode: "#line 2 \"src/convolution/min_plus_convolution_convex_convex.hpp\"\
    \n#include <limits>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    #line 2 \"src/internal/type_traits.hpp\"\n#include <iostream>\n#line 5 \"src/internal/type_traits.hpp\"\
    \n#include <typeinfo>\n#include <cstdint>\n\nnamespace kyopro {\nnamespace internal\
    \ {\ntemplate <typename... Args> struct first_enabled {};\n\ntemplate <typename\
    \ T, typename... Args>\nstruct first_enabled<std::enable_if<true, T>, Args...>\
    \ {\n    using type = T;\n};\ntemplate <typename T, typename... Args>\nstruct\
    \ first_enabled<std::enable_if<false, T>, Args...>\n    : first_enabled<Args...>\
    \ {};\ntemplate <typename T, typename... Args> struct first_enabled<T, Args...>\
    \ {\n    using type = T;\n};\n\ntemplate <typename... Args>\nusing first_enabled_t\
    \ = typename first_enabled<Args...>::type;\n\ntemplate <int dgt, std::enable_if_t<dgt\
    \ <= 128>* = nullptr> struct int_least {\n    using type = first_enabled_t<std::enable_if<dgt\
    \ <= 8, std::int8_t>,\n                                 std::enable_if<dgt <=\
    \ 16, std::int16_t>,\n                                 std::enable_if<dgt <= 32,\
    \ std::int32_t>,\n                                 std::enable_if<dgt <= 64, std::int64_t>,\n\
    \                                 std::enable_if<dgt <= 128, __int128_t>>;\n};\n\
    \ntemplate <int dgt, std::enable_if_t<dgt <= 128>* = nullptr> struct uint_least\
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
    };  // namespace internal\n};  // namespace kyopro\n\n/*\n * @ref https://qiita.com/kazatsuyu/items/f8c3b304e7f8b35263d8\n\
    \ */\n#line 7 \"src/convolution/min_plus_convolution_convex_convex.hpp\"\n\nnamespace\
    \ kyopro {\ntemplate <typename T>\nstd::vector<T> min_plus_convolution_convex_convex(const\
    \ std::vector<T>& a,\n                                                  std::vector<T>&\
    \ b) {\n    constexpr T INF = std::numeric_limits<T>::max() / 2;\n    const int\
    \ n = a.size();\n    const int m = b.size();\n    const T A0 = INF;\n    const\
    \ T B0 = INF;\n\n    std::vector<T> da(n);\n    std::vector<T> db(m);\n    for\
    \ (int i = 1; i < n; ++i) da[i] = a[i] - a[i - 1];\n    for (int i = 1; i < m;\
    \ ++i) db[i] = b[i] - b[i - 1];\n    da[0] = a[0] - INF, db[0] = b[0] - INF;\n\
    \n    std::vector<T> ds;\n    ds.reserve(da.size() + db.size());\n    for (int\
    \ ia = 0, ib = 0; ia < n || ib < m;) {\n        if (ia == (int)da.size()) {\n\
    \            ds.emplace_back(db[ib++]);\n        } else if (ib == m) {\n     \
    \       ds.emplace_back(da[ia++]);\n        } else {\n            if (da[ia] >\
    \ db[ib]) {\n                ds.emplace_back(db[ib++]);\n            } else {\n\
    \                ds.emplace_back(da[ia++]);\n            }\n        }\n    }\n\
    \n    std::vector<T> res(n + m - 1);\n    T sum = ds[0];\n    for (int k = 1;\
    \ k < (int)ds.size(); ++k) {\n        sum += ds[k];\n        res[k - 1] = sum\
    \ + A0 + B0;\n    }\n    return res;\n}\n};  // namespace kyopro\n\n/**\n * @brief\
    \ Min Plus Convolution(Convex, Convex)\n */\n"
  code: "#pragma once\n#include <limits>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n#include \"../../src/internal/type_traits.hpp\"\n\nnamespace\
    \ kyopro {\ntemplate <typename T>\nstd::vector<T> min_plus_convolution_convex_convex(const\
    \ std::vector<T>& a,\n                                                  std::vector<T>&\
    \ b) {\n    constexpr T INF = std::numeric_limits<T>::max() / 2;\n    const int\
    \ n = a.size();\n    const int m = b.size();\n    const T A0 = INF;\n    const\
    \ T B0 = INF;\n\n    std::vector<T> da(n);\n    std::vector<T> db(m);\n    for\
    \ (int i = 1; i < n; ++i) da[i] = a[i] - a[i - 1];\n    for (int i = 1; i < m;\
    \ ++i) db[i] = b[i] - b[i - 1];\n    da[0] = a[0] - INF, db[0] = b[0] - INF;\n\
    \n    std::vector<T> ds;\n    ds.reserve(da.size() + db.size());\n    for (int\
    \ ia = 0, ib = 0; ia < n || ib < m;) {\n        if (ia == (int)da.size()) {\n\
    \            ds.emplace_back(db[ib++]);\n        } else if (ib == m) {\n     \
    \       ds.emplace_back(da[ia++]);\n        } else {\n            if (da[ia] >\
    \ db[ib]) {\n                ds.emplace_back(db[ib++]);\n            } else {\n\
    \                ds.emplace_back(da[ia++]);\n            }\n        }\n    }\n\
    \n    std::vector<T> res(n + m - 1);\n    T sum = ds[0];\n    for (int k = 1;\
    \ k < (int)ds.size(); ++k) {\n        sum += ds[k];\n        res[k - 1] = sum\
    \ + A0 + B0;\n    }\n    return res;\n}\n};  // namespace kyopro\n\n/**\n * @brief\
    \ Min Plus Convolution(Convex, Convex)\n */"
  dependsOn:
  - src/internal/type_traits.hpp
  isVerificationFile: false
  path: src/convolution/min_plus_convolution_convex_convex.hpp
  requiredBy: []
  timestamp: '2023-12-09 01:32:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_judge/convolution/Min_Plus_Convolution_Convex_and_Convex.test.cpp
documentation_of: src/convolution/min_plus_convolution_convex_convex.hpp
layout: document
redirect_from:
- /library/src/convolution/min_plus_convolution_convex_convex.hpp
- /library/src/convolution/min_plus_convolution_convex_convex.hpp.html
title: Min Plus Convolution(Convex, Convex)
---