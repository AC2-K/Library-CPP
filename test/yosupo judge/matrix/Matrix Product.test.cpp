#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include"template.hpp"
#include"math/dynamic_modint.hpp"
#include"math/matrix.hpp"
int main() {
    mint::set_mod(MOD2);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    using mat = Matrix<mint>;
    mat a(n, m), b(m, k);
    rep(i, n) rep(j, m) { cin >> a[i][j]; }
    rep(i, m) rep(j, k) { cin >> b[i][j]; }
    auto res = a * b;
    rep(i, n) {
        rep(j, k) { cout << res[i][j] << ' '; }
        cout << '\n';
    }
}
