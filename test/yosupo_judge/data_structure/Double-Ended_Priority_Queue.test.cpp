#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "../../../src/BST/Treap.hpp"
#include "../../../src/stream.hpp"
using namespace std;
int main() {
    kyopro::Treap<int> st;
    int n, q;
    kyopro::readint(n, q);
    for (int i = 0; i < n; ++i) {
        int a;
        kyopro::readint(a);
        st.insert(a);
    }
    while (q--) {
        int t;
        kyopro::readint(t);
        if (!t) {
            int x;
            kyopro::readint(x);
            st.insert(x);
        } else if (t == 1) {
            int mn = st.min_element();
            kyopro::putint(mn);
            st.erase(mn);
        } else {
            int mx = st.max_element();
            kyopro::putint(mx);
            st.erase(mx);
        }
    }
}