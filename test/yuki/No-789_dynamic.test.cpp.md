---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data-structure/dynamic_segtree.hpp
    title: "Dynamic Segment Tree(\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
  - icon: ':question:'
    path: template.hpp
    title: template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/789
    links:
    - https://yukicoder.me/problems/no/789
  bundledCode: "#line 1 \"test/yuki/No-789_dynamic.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/789\"\n\n#line 2 \"template.hpp\"\n#include<bits/stdc++.h>\n\
    using namespace std;\n#define rep(i, N)  for(int i=0;i<(N);i++)\n#define all(x)\
    \ (x).begin(),(x).end()\n#define popcount(x) __builtin_popcount(x)\nusing i128=__int128_t;\n\
    using ll = long long;\nusing ld = long double;\nusing graph = vector<vector<int>>;\n\
    using P = pair<int, int>;\nconstexpr int inf = 1e9;\nconstexpr ll infl = 1e18;\n\
    constexpr ld eps = 1e-6;\nconst long double pi = acos(-1);\nconstexpr uint64_t\
    \ MOD = 1e9 + 7;\nconstexpr uint64_t MOD2 = 998244353;\nconstexpr int dx[] = {\
    \ 1,0,-1,0 };\nconstexpr int dy[] = { 0,1,0,-1 };\ntemplate<class T>static constexpr\
    \ inline void chmax(T&x,T y){if(x<y)x=y;}\ntemplate<class T>static constexpr inline\
    \ void chmin(T&x,T y){if(x>y)x=y;}\n#line 1 \"data-structure/dynamic_segtree.hpp\"\
    \n/// @brief Dynamic Segment Tree(\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    )\n/// @tparam S \u8981\u7D20\u306E\u578B\n/// @tparam op \u4E8C\u9805\u6F14\u7B97\
    \n/// @tparam e \u5358\u4F4D\u5143\n/// @docs docs/data-structure/dynamic_segtree.md\n\
    template<class S,S(*op)(S,S),S(*e)()>\nclass dynamic_segtree {\npublic:\n\tdynamic_segtree(const\
    \ size_t& n) :n(n), root(nullptr) {}\nprivate:\n\tstruct node {\n\t\tS val;\n\t\
    \tnode* left;\n\t\tnode* right;\n\n\t\tnode(const S& v) :val(v), left(nullptr),\
    \ right(nullptr) {}\n\t};\n\tnode* root;\n\tsize_t n;\npublic:\n\tvoid update(const\
    \ size_t& p, const S& x) { \n\t\tassert(0 <= p && p < n);\n\t\tinternal_update(root,\
    \ 0, n, p, x); \n\t}\n\tvoid add(const size_t& p, const S& x) { \n\t\tassert(0\
    \ <= p && p < n);\n\t\tinternal_add(root, 0, n, p, x); \n\t}\n\tS operator[](const\
    \ size_t& p) { \n\t\tassert(0 <= p && p < n);\n\t\treturn internal_access(root,\
    \ 0, n, p); \n\t}\n\tS prod(const size_t& l, const size_t& r) {\n\t\tassert(0\
    \ <= l && l <= r && r <= n);\n\t\tif (l == r) {\n\t\t\treturn e();\n\t\t}\n\n\t\
    \treturn internal_prod(root, 0, n, l, r);\n\t}\n\nprivate:\n\tvoid internal_update(node*&\
    \ p, const size_t& l, const size_t& r, const  size_t& idx, const S& new_val) {\n\
    \t\tif (p == nullptr) {\n\t\t\tp = new node(e());\n\t\t}\n\n\t\tif (r - l == 1)\
    \ {\n\t\t\tp->val = new_val;\n\t\t\treturn;\n\t\t}\n\n\t\tsize_t mid = (l + r)\
    \ >> 1;\n\t\tif (idx < mid) internal_update(p->left, l, mid, idx, new_val);\n\t\
    \telse internal_update(p->right, mid, r, idx, new_val);\n\t\tp->val = e();\n\t\
    \tif (p->left!=nullptr) p->val = op(p->left->val, p->val);\n\t\tif (p->right!=nullptr)\
    \ p->val = op(p->val, p->right->val);\n\t}\n\tvoid internal_add(node*& p, const\
    \ size_t& l, const size_t& r, const  size_t& idx, const S& new_val) {\n\t\tif\
    \ (p == nullptr) {\n\t\t\tp = new node(e());\n\t\t}\n\n\t\tif (r - l == 1) {\n\
    \t\t\tp->val = op(p->val, new_val);;\n\t\t\treturn;\n\t\t}\n\n\t\tsize_t mid =\
    \ (l + r) >> 1;\n\t\tif (idx < mid) internal_add(p->left, l, mid, idx, new_val);\n\
    \t\telse internal_add(p->right, mid, r, idx, new_val);\n\t\tp->val = e();\n\t\t\
    if (p->left!=nullptr) p->val = op(p->left->val, p->val);\n\t\tif (p->right!=nullptr)\
    \ p->val = op(p->val, p->right->val);\n\t}\n\n\n\tS internal_access(node*& p,\
    \ const size_t& l, const size_t& r, const  size_t& idx) {\n\t\tif (p == nullptr)\
    \ {\n\t\t\treturn e();\n\t\t}\n\t\tif (r - l == 1) {\n\t\t\treturn p->val;\n\t\
    \t}\n\n\t\tsize_t mid = (l + r) >> 1;\n\t\tif (idx < mid) return internal_access(p->left,\
    \ l, mid, idx);\n\t\telse return internal_access(p->right, mid, r, idx);\n\t}\n\
    \n\tS internal_prod(node*& p, const size_t& l, const size_t& r, const size_t&\
    \ L, const size_t& R) {\n\t\tif (p == nullptr || r <= L || R <= l) {\n\t\t\treturn\
    \ e();\n\t\t}\n\t\tif (L <= l && r <= R) {\n\t\t\treturn p->val;\n\t\t}\n\n\t\t\
    size_t mid = (l + r) >> 1;\n\t\treturn op(internal_prod(p->left, l, mid, L, R),\
    \ internal_prod(p->right, mid, r, L, R));\n\t}\n};\n#line 5 \"test/yuki/No-789_dynamic.test.cpp\"\
    \nint op(int x, int y) { return x + y; }\nint e() { return 0; }\nint main() {\n\
    \    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\tconst size_t n = 1000000001;\n\
    \tdynamic_segtree<int, op, e> seg(n);\n\n\tint q;\n\tcin >> q;\n\tlong long ans\
    \ = 0;\n\twhile (q--) {\n\t\tint type;\n\t\tcin >> type;\n\t\tif (type == 0) {\n\
    \t\t\tsize_t x;\n\t\t\tlong long y;\n\t\t\tcin >> x >> y;\n\t\t\tseg.add(x, y);\n\
    \t\t}\n\t\telse {\n\t\t\tsize_t l, r;\n\t\t\tcin >> l >> r;\n\t\t\tans += seg.prod(l,\
    \ r + 1);\n\t\t}\n\t}\n\tcout << ans << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/789\"\n\n#include\"template.hpp\"\
    \n#include\"data-structure/dynamic_segtree.hpp\"\nint op(int x, int y) { return\
    \ x + y; }\nint e() { return 0; }\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n\tconst size_t n = 1000000001;\n\tdynamic_segtree<int,\
    \ op, e> seg(n);\n\n\tint q;\n\tcin >> q;\n\tlong long ans = 0;\n\twhile (q--)\
    \ {\n\t\tint type;\n\t\tcin >> type;\n\t\tif (type == 0) {\n\t\t\tsize_t x;\n\t\
    \t\tlong long y;\n\t\t\tcin >> x >> y;\n\t\t\tseg.add(x, y);\n\t\t}\n\t\telse\
    \ {\n\t\t\tsize_t l, r;\n\t\t\tcin >> l >> r;\n\t\t\tans += seg.prod(l, r + 1);\n\
    \t\t}\n\t}\n\tcout << ans << '\\n';\n}"
  dependsOn:
  - template.hpp
  - data-structure/dynamic_segtree.hpp
  isVerificationFile: true
  path: test/yuki/No-789_dynamic.test.cpp
  requiredBy: []
  timestamp: '2023-03-28 10:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yuki/No-789_dynamic.test.cpp
layout: document
redirect_from:
- /verify/test/yuki/No-789_dynamic.test.cpp
- /verify/test/yuki/No-789_dynamic.test.cpp.html
title: test/yuki/No-789_dynamic.test.cpp
---