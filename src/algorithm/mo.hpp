#pragma once
#include <algorithm>
#include <numeric>
#include <vector>
#include <utility>
namespace kyopro {
/// @brief mo's algorithm
class Mo {
    int n;
    std::vector<std::pair<int, int>> lr;
    const int logn;
    const long long maxn;
    std::vector<int> ord;

  public:
    explicit Mo(int n) : n(n), logn(20), maxn(1ll << logn) { lr.reserve(n); }
    inline void add(int l, int r) { lr.emplace_back(l, r); }
    long long hilbertorder(int x, int y) {
        long long d = 0;
        for (int s = 1 << (logn - 1); s; s >>= 1) {
            bool rx = x & s, ry = y & s;
            d = d << 2 | rx * 3 ^ static_cast<int>(ry);
            if (!ry) {
                if (rx) {
                    x = maxn - x;
                    y = maxn - y;
                }
                std::swap(x, y);
            }
        }
        return d;
    }

  private:
    inline void line_up() {
        int q = lr.size();
        ord.resize(q);
        std::iota(std::begin(ord), std::end(ord), 0);
        std::vector<long long> tmp(q);
        for (int i = 0; i < q; i++) {
            tmp[i] = hilbertorder(lr[i].first, lr[i].second);
        }
        std::sort(std::begin(ord), std::end(ord),
                  [&](int a, int b) { return tmp[a] < tmp[b]; });

    }

  public:
    template <typename AL, typename AR, typename EL, typename ER, typename O>
    void build(const AL& add_left,
               const AR& add_right,
               const EL& erase_left,
               const ER& erase_right,
               const O& out) {
        line_up();
        int l = 0, r = 0;
        for (const auto& idx : ord) {
            while (l > lr[idx].first) add_left(--l);
            while (r < lr[idx].second) add_right(r++);
            while (l < lr[idx].first) erase_left(l++);
            while (r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    template <typename A, typename E, typename O>
    void build(const A& add, const E& erase, const O& out) {
        build(add, add, erase, erase, out);
    }
};
};  // namespace kyopro

/// @docs docs/other/mo.md