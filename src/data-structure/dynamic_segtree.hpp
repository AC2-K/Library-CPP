#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>
namespace kyopro {
/// @brief 動的セグメント木
template <class S, S (*op)(S, S), S (*e)()>
class dynamic_segtree {
public:
    constexpr explicit dynamic_segtree(std::size_t n = 0)
        : n(n), root(nullptr) {
        root = new Node();
    }
    ~dynamic_segtree() { delete root; }

private:
    struct Node {
        S val;
        Node *l, *r, *parent;

        constexpr explicit Node(const S& v = e(), Node* pt = nullptr)
            : val(v), l(nullptr), r(nullptr), parent(pt) {}
        ~Node() { delete l, delete r; }
    };
    using ptr = Node*;

    Node* root;
    const std::size_t n;

private:
    Node* find(const std::size_t i) {
        assert(0 <= i && i < n);

        std::size_t l = 0, r = n;

        Node* p = root;

        while (r - l > 1) {
            std::size_t md = (r + l) >> 1;
            if (i < md) {
                if (!p->l) {
                    p->l = new Node(e(), p);
                }
                p = p->l;
                r = md;
            } else {
                if (!p->r) {
                    p->r = new Node(e(), p);
                }
                p = p->r;
                l = md;
            }
        }
        return p;
    }
    void push(Node* p) {
        while (p = p->parent) {
            p->val = op((p->l ? p->l->val : e()), (p->r ? p->r->val : e()));
        }
    }

public:
    void apply(std::size_t i, const S& x) {
        assert(0 <= i && i < n);
        auto p = find(i);
        p->val = op(p->val, x);
        push(p);
    }
    void update(std::size_t i, const S& x) {
        assert(0 <= i && i < n);
        auto p = find(i);
        p->val = x;
        push(p);
    }
    S at(std::size_t i) {
        assert(0 <= i && i < n);
        return find(i)->val;
    }
    S prod(std::size_t l, std::size_t r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return e();
        }
        return internal_prod(root, 0, n, l, r);
    }

private:
    /// TODO:非再帰にする
    S internal_prod(const Node* p,
                    std::size_t l,
                    std::size_t r,
                    std::size_t L,
                    std::size_t R) const {
        if (!p || r <= L || R <= l) {
            return e();
        }
        if (L <= l && r <= R) {
            return p->val;
        }

        std::size_t mid = (l + r) >> 1;
        return op(internal_prod(p->l, l, mid, L, R),
                  internal_prod(p->r, mid, r, L, R));
    }
};
};  // namespace kyopro

/// @docs docs/data-structure/dynamic_segtree.md