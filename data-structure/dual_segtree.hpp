/// @brief Dual Segmenttree(双対セグメント木)
/// @tparam F 要素の型
/// @tparam comp 二項演算
/// @tparam id 単位元
/// @docs docs/data-structure/dual_segtree.md

#pragma once
template<class F, F(*comp)(F, F), F(*id)()>
class dual_segtree {
	int n, sz, lg;

	const int lowest = -1;
	vector<pair<int, F>> dat;

	int cur;
	const F id_val = id();

public:
	dual_segtree(const int& n_) : n(n_), cur(0) {
		sz = 1;
		lg = 0;
		while (sz < n) {
			sz <<= 1;
			lg++;
		}

		dat.assign(sz << 1, make_pair(lowest, id_val));
	}

private:
	void innner_apply(const int& p, const int& l, const int& r, const int& L, const  int& R, const  F& f) {
		if (r <= L || R <= l) {
			return;
		}
		if (L <= l && r <= R) {
			F nf = comp(dat[p].second, f);
			dat[p] = make_pair(cur, nf);
			return;
		}
		int md = (l + r) >> 1;
		innner_apply(2 * p + 1, l, md, L, R, f);
		innner_apply(2 * p + 2, md, r, L, R, f);
	}
public:
	void apply(const int& l, const int& r, const F& x) {
		assert(0 <= l && l <= r && r <= n);
		innner_apply(0, 0, sz, l, r, x);
		cur++;
	}

	F operator[](int p) {
		p = p + sz - 1;	//1-index

		vector<pair<int, F>> path;
		path.emplace_back(dat[p]);
		path.reserve(lg);
		while (p) {
			p = (p - 1) >> 1;
			path.emplace_back(dat[p]);
		};

		sort(path.begin(), path.end());

		F res = id_val;
		for (const auto& q : path) {
			if (q.first == lowest || q.second == id_val) {
				continue;
			}
			res = comp(res, q.second);
		}

		return res;
	}
	//debug
	void print() {
		cout << "[";
		for (int i = 0; i < n; i++) {
			cout << (*this)[i] << ' ';
		}
		cout << "]\n";
	}
};
