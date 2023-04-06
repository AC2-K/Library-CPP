---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/mod_log.hpp
    title: "Discrete Logarithm(\u96E2\u6563\u5BFE\u6570)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/data_structure/Associative_Array_hashmap.test.cpp
    title: test/yosupo_judge/data_structure/Associative_Array_hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
    title: test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  - icon: ':x:'
    path: test/yuki/No-430.test.cpp
    title: test/yuki/No-430.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: HashMap
    links: []
  bundledCode: "#line 1 \"data-structure/hash_map.hpp\"\n#include<iostream>\n#include<chrono>\n\
    namespace library{\n\n/// @brief HashMap\n/// @tparam Key Key\u306E\u578B\n///\
    \ @tparam Val Value\u306E\u578B\ntemplate <typename Key,\n          typename Val,\n\
    \          uint32_t n = 1 << 20,\n          Val default_val = Val()\n        \
    \  >\nclass hash_map {\n    using u32 = uint32_t;\n    using u64 = uint64_t;\n\
    \n    u64* flag = new u64[n];\n    Key* keys = new Key[n];\n    Val* vals = new\
    \ Val[n];\n\n    static constexpr u32 shift = 64 - std::__lg(n);\n\n    u64 r;\n\
    \    inline u32 get_hash(const Key& k) const {\n        return ((u64)k * r) >>\
    \ shift;\n    }\n\n    static constexpr uint8_t mod_msk = (1 << 6) - 1;\n\n  public:\
    \   \n    explicit constexpr hash_map(){\n        r = std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        r ^= r >> 16;\n        r ^= r << 32;\n    }\n    Val& operator[](const\
    \ Key& k) {\n        u32 hash = get_hash(k);\n\n        while (1) {\n        \
    \    if (!(flag[hash >> 6] &\n                  (static_cast<u64>(1) << (hash\
    \ & mod_msk)))) {\n                keys[hash] = k;\n                flag[hash\
    \ >> 6] |= static_cast<u64>(1)\n                                   << (hash &\
    \ mod_msk);\n                return vals[hash] = default_val;\n            }\n\
    \n            if (keys[hash] == k)return vals[hash];\n            hash = (hash\
    \ + 1) & (n - 1);\n        }\n    }\n\n    const Val* find(const Key&k)const{\n\
    \        u32 hash = get_hash(k);\n        while (1) {\n            if (!(flag[hash\
    \ >> 6] &\n                  (static_cast<u64>(1) << (hash & mod_msk))))\n   \
    \             return nullptr;\n            if (keys[hash] == k) return &(vals[hash]);\n\
    \            hash = (hash + 1) & (n - 1);\n        }\n    }\n};\n\n\n};  // namespace\
    \ library\n"
  code: "#include<iostream>\n#include<chrono>\nnamespace library{\n\n/// @brief HashMap\n\
    /// @tparam Key Key\u306E\u578B\n/// @tparam Val Value\u306E\u578B\ntemplate <typename\
    \ Key,\n          typename Val,\n          uint32_t n = 1 << 20,\n          Val\
    \ default_val = Val()\n          >\nclass hash_map {\n    using u32 = uint32_t;\n\
    \    using u64 = uint64_t;\n\n    u64* flag = new u64[n];\n    Key* keys = new\
    \ Key[n];\n    Val* vals = new Val[n];\n\n    static constexpr u32 shift = 64\
    \ - std::__lg(n);\n\n    u64 r;\n    inline u32 get_hash(const Key& k) const {\n\
    \        return ((u64)k * r) >> shift;\n    }\n\n    static constexpr uint8_t\
    \ mod_msk = (1 << 6) - 1;\n\n  public:   \n    explicit constexpr hash_map(){\n\
    \        r = std::chrono::steady_clock::now().time_since_epoch().count();\n  \
    \      r ^= r >> 16;\n        r ^= r << 32;\n    }\n    Val& operator[](const\
    \ Key& k) {\n        u32 hash = get_hash(k);\n\n        while (1) {\n        \
    \    if (!(flag[hash >> 6] &\n                  (static_cast<u64>(1) << (hash\
    \ & mod_msk)))) {\n                keys[hash] = k;\n                flag[hash\
    \ >> 6] |= static_cast<u64>(1)\n                                   << (hash &\
    \ mod_msk);\n                return vals[hash] = default_val;\n            }\n\
    \n            if (keys[hash] == k)return vals[hash];\n            hash = (hash\
    \ + 1) & (n - 1);\n        }\n    }\n\n    const Val* find(const Key&k)const{\n\
    \        u32 hash = get_hash(k);\n        while (1) {\n            if (!(flag[hash\
    \ >> 6] &\n                  (static_cast<u64>(1) << (hash & mod_msk))))\n   \
    \             return nullptr;\n            if (keys[hash] == k) return &(vals[hash]);\n\
    \            hash = (hash + 1) & (n - 1);\n        }\n    }\n};\n\n\n};  // namespace\
    \ library"
  dependsOn: []
  isVerificationFile: false
  path: data-structure/hash_map.hpp
  requiredBy:
  - math/mod_log.hpp
  timestamp: '2023-04-06 18:29:27+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_judge/data_structure/Associative_Array_hashmap.test.cpp
  - test/yosupo_judge/math/Discrete_Logarithm.test.cpp
  - test/yuki/No-430.test.cpp
documentation_of: data-structure/hash_map.hpp
layout: document
redirect_from:
- /library/data-structure/hash_map.hpp
- /library/data-structure/hash_map.hpp.html
title: HashMap
---