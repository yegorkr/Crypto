// APA.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstddef>
#include <unordered_map>
#include <string>
#include <fstream>
#include <set>
#include <random>
#include <math.h>


using namespace std;
const vector<int> zero = { 0 };
const vector<int> one = { 1 };
const vector<int> two = { 2 };
const vector<int> three = { 3 };
const vector<int> five = { 5 };
const vector<int> four = { 4 };
const vector<int> six = { 6 };
const vector<int> eight = { 8 };

string toString(vector<int> a) {
	string s = "";
	for (int i = 0; i< a.size(); ++i)
		s += to_string(a[i]);
	return s;
}


struct MLH {
	size_t operator()(const vector<int>& t) const {
		return hash<string>()(toString(t));
	}
};

vector<int> mexp(vector<int> a, vector<int> b, vector<int> c);
vector<int> add(vector<int> a, vector<int> b);
vector<int> sub(vector<int> a, vector<int> b);
vector<int> max(vector<int> a, vector<int> b);
vector<int> min(vector<int> a, vector<int> b);
vector<int> mult(vector<int> a, vector<int> b);
vector<int> div(vector<int> a, vector<int> b);
vector<int> mod(vector<int> a, vector<int> b);
vector<int> pow(vector<int> a, vector<int> b);
vector<int> gcd(vector<int> a, vector<int> b);
vector<int> pollard(vector<int> a);
vector<int> euler(vector<int> a);
vector<int> mobius(vector<int> a);
set<vector<int>> factor(vector<int> n);
vector<vector<int>> mfactor(vector<int> n);
int jacobi(vector<int> a, vector<int> b);
int legendre(vector<int> a, vector<int> b);
int solovay(vector<int> a);
vector<int> m(vector<int> a);
vector<int> v(string);
void print(vector<int> a);
string toString(vector<int> a);
string toString(vector<int> a);
int eq(vector<int> a, vector<int> b);

void RSA(vector<int> a, vector<int> b);


vector<int> v(string s) {
	vector<int> r;
	int mFlag = 0;
	while (s.length() > 0) {
		string s1 = s.substr(0, 1);
		if (s1 == "-") {
			mFlag++; s.erase(s.begin()); continue;
		}
		int i;
		if (s1 == "0") i = 0;
		if (s1 == "1") i = 1;
		if (s1 == "2") i = 2;
		if (s1 == "3") i = 3;
		if (s1 == "4") i = 4;
		if (s1 == "5") i = 5;
		if (s1 == "6") i = 6;
		if (s1 == "7") i = 7;
		if (s1 == "8") i = 8;
		if (s1 == "9") i = 9;
		r.push_back(i);
		s.erase(s.begin());
	}
	if (mFlag) r[0] *= -1;
	return r;
}

vector<int> pollard(vector<int> n) {
	vector<int> x = two, y = two, d = one;
	while (eq(d, one)) {
		x = mod(add(one, mult(x, x)), n);
		y = mod(add(one, mult(y, y)), n);
		y = mod(add(one, mult(y, y)), n);
		d = gcd(m(sub(x, y)), n);
	}
	if (eq(d, n)) { 
		return n; 
	}
	n = div(n, d);
	return d;
}

void print(vector<int> a) {
	for(int i = 0; i < a.size(); ++i)
		cout << a[i];
	cout << "\n";
}
vector<int> m(vector<int> a) {
	a[0] = abs(a[0]);
	return a;
}

vector<int> neg(vector<int> a) {
	a[0] = a[0] * (-1);
	return a;
}

vector<int> toNeg(vector<int> a) {
	for (int i = 1; i < a.size(); ++i)
		a[i] *= -1;
	return(a);
}

vector<int> max(vector<int> a, vector<int> b) {
	if (a.size() > 1)
		if (a[0] == 0 && a[1] == 0)
			a = zero;
	if (b.size() > 1)
		if (b[0] == 0 && b[1] == 0)
			b = zero;
	if (a.size() == 0) return b;
	if (b.size() == 0) return a;
	if (a[0] < 0 && b[0] < 0) {
		if (a.size() > b.size()) return b;
		if (a.size() < b.size()) return a;
		for (int i = 0; i < a.size(); ++i)
			if (abs(a[i]) > abs(b[i])) return b;
			else if (abs(b[i]) > abs(a[i])) return a;
	}
	if (a[0] < 0) return b;
	if (b[0] < 0) return a;
	if (a.size() > b.size()) return a;
	if (a.size() < b.size()) return b;
	for (int i = 0; i < a.size(); ++i)
		if (a[i] > b[i]) return a;
		else if (b[i] > a[i]) return b;
	return a;
}

vector<int> min(vector<int> a, vector<int> b) {
	if (max(a, b) == a) return b;
	return a;
}
int eq(vector<int> a, vector<int> b) {
	if (max(a, b) == a && min(a, b) == a)
		return 1;
	return 0;
}

vector<int> add(vector<int> a, vector<int> b) {
	if (!(a[0] < 0 && b[0] < 0)) {
		if (a[0] < 0) return sub(m(b), m(a));
		if (b[0] < 0) return sub(m(a), m(b));
	}
	if (a.size() < b.size())
		swap(a, b);
	for (int i = 1; i <= a.size(); ++i) {
		if(b.size() >= i)
			a.at(a.size() - i) += b.at(b.size() - i);
		while (a.at(a.size() - i) > 9)
			if (a.size() - i == 0) {
				a.insert(a.begin(), 1);
				a[1] -= 10;
			}
			else {
				a.at(a.size() - i) -= 10;
				a.at(a.size() - i - 1) += 1;
			}
	}
	return a;
}

vector<int> sub(vector<int> a, vector<int> b) {
	int mFlag = 0;
	if (a[0] < 0 && b[0] < 0)
		return sub(m(b), m(a));
	if (a[0] < 0)
		return sub(zero, add(m(a), m(b)));
	if (b[0] < 0)
		return add(m(a), m(b));
	while (a.size() < b.size())
		a.insert(a.begin(), 0);
	if (max(a, b) == b) {
		swap(a, b);
		mFlag++;
	}
	for (int i = 1; i <= b.size(); ++i) {
		a[a.size() - i] -= b[b.size() - i];
		if (a[a.size() - i] < 0) {
			a[a.size() - i] += 10;
			a[a.size() - i - 1] -= 1;
		}
	}
	while (a[0] == 0 && a.size() > 1)
		a.erase(a.begin());
	if (mFlag) a[0] *= -1;
	return a;
}

vector<int> mult(vector<int> a, vector<int> b) {
	int mFlag = 0;
	if (a.size() < b.size())
		swap(a, b);
	if (a == zero || b == zero)
		return zero;
	if ((a[0] > 0 && b[0] < 0) || (a[0] < 0 && b[0] > 0)) {
		a = m(a);
		b = m(b);
		mFlag++;
	}
	a = m(a); b = m(b);
	vector<int> r = zero;
	for (int i = 1; i <= b.size(); ++i) {
		vector<int> c = zero;
		for (int j = b[b.size() - i]; j > 0; --j)
			c = add(c, a);
		for (int j = 1; j < i; ++j)
			c.push_back(0);
		r = add(r, c);
	}
	if (mFlag) r = neg(r);
	return r;
}

vector<int> div(vector<int> a, vector<int> b) {
	int mFlag = 0;
	if (eq(a, b)) return one;
	if (a == zero || max(a, b) == b) return zero;
	if (b == zero) { cout << "ERROR";  return a; }
	if ((a[0] > 0 && b[0] < 0) || (a[0] < 0 && b[0] > 0)) {
		a = m(a);
		b = m(b);
		mFlag++;
	}
	a = m(a); b = m(b);
	vector<int> r;
	vector<int> c;
	int i = 0; int j = 0;
	while (max(b, c) != c) 
		c.push_back(a[i++]);
	while (max(b, c) == c) {
		c = sub(c, b);
		++j;
	}
	r.push_back(j);
	for (i; i > 0; --i)
		a.erase(a.begin());
	while (a.size() > 0) {
		if (c == zero) c.erase(c.begin());
		j = 0;
		while (max(b, c) != c) {
			if (i == a.size()) {
				r.push_back(0);
				return r;
			}
			c.push_back(a[i++]);
			if (i > 1) r.push_back(0);
		}
		while (max(b, c) == c) {
			c = sub(c, b);
			++j;
		}
		r.push_back(j);
		if (i > a.size()) break;
		for (i; i > 0; --i)
			a.erase(a.begin());
	}
	if (mFlag) r = neg(r);
	return r;
}

vector<int> mod(vector<int> a, vector<int> b) {
	return sub(a, mult(b, div(a, b)));
}

vector<int> pow(vector<int> a, vector<int> b) {
	b = m(b);
	vector<int> c = zero;
	vector<int> r = one;
	while (!eq(c, b)) {
		r = mult(a, r);
		c = add(c, one);
	}
	return r;
}

vector<int> gcd(vector<int> a, vector<int> b) {
	if (a == zero) return b;
	while (b != zero) {
		vector<int> r = mod(a, b);
		a = b;
		b = r;
	}
	return a;
}

int legendre(vector<int> a, vector<int> b) {
	if (solovay(b) == 0) return -2;
	return(jacobi(a, b));
}

vector<int> lcm(vector<int> a, vector<int> b) {
	return div(mult(a, b), gcd(a, b));
}

int jacobi(vector<int> a, vector<int> b) {
	if(max(b, zero) == zero || mod(b, two) == zero)
		return 0;
	int j = 1;
	if (max(a, zero) == zero) {
		a[0] *= -1;
		if(eq(mod(b, four), three)) j = -j;
	}
	while(!eq(a, zero)) {
		 while(eq(mod(a, two), zero)) {
			 a = div(a, two);
			if(eq(mod(b, eight), three) || eq(mod(b, eight), five)) j = -j;
		}
		swap(a, b);
		if(eq(mod(a, four), three) && eq(mod(b, four), three)) j = -j;
		a = mod(a, b);
	}
	if (eq(b, one))
		return j;
	else return 0;
}

set<vector<int>> factor(vector<int> a) {
	std::set<vector<int>> st, st1, st2;
	while (!eq(a, zero) && !eq(a, one)) {
		vector<int> b = pollard(a);
		st.insert(b);
		a = div(a, b);
	}
	st1 = st;
	while (st1 != st2) {
		for each (vector<int> vec in st1)
		{
			st2 = st1;
			vector<int> b = pollard(vec);
			if (!eq(b, vec)) {
				st1.erase(vec);
				st1.insert(div(vec, b));
				st1.insert(b);
			}
		}
	}
	st = st1;
	st2.clear();
	for each (vector<int> vect in st)
	{
		vector<int> vec = vect;
		if (eq(mod(vect, two), zero)) vec = two;
		if (eq(mod(vect, three), zero)) vec = three;
		if (eq(mod(vect, five), zero)) vec = five;
		if (eq(mod(vect, v("7")), zero)) vec = v("7");
		if (eq(mod(vect, v("11")), zero)) vec = v("11");
		if (eq(mod(vect, v("13")), zero)) vec = v("13");
		if (eq(mod(vect, v("17")), zero)) vec = v("17");
		st2.insert(vec);
	}
	return st2;
}


vector<int> euler(vector<int> a) {
	set<vector<int>> st = factor(a);
	vector<int> r = a;
	for each (vector<int> vect in st)
		r = div(mult(r, sub(vect, one)), vect);
	return r;
}

vector<vector<int>> mfactor(vector<int> n) {
	vector<vector<int>> r;
	while (eq(mod(n, two), zero))
	{
		r.push_back(two);
		n = div(n, two);
	}

	for (vector<int> i = three;; i = add(i, two))
	{
		while (eq(mod(n, i), zero))
		{
			r.push_back(i);
			n = div(n, i);
		}
		if (max(mult(i, i), n) != n) break;
	}

	if (max(n, two) != n)
		r.push_back(n);
	return r;
}

vector<int> mobius(vector<int> a) {
	vector<int> r = a;
	vector<vector<int>> temp = mfactor(r);
	if (r == one) return one;
	if (temp.size() == 1) return neg(one);
	if (temp.size() == 2 && temp[0] == temp[1]) return zero;
	if (temp.size() == 2) return one;
	int cnt = 1;
	for (int i = 1; i < temp.size(); ++i) {
		if (temp[i - 1] == temp[i])
			++cnt;
		else
			if (cnt == 2) return zero;
			else cnt = 1;
	}
	if (cnt == 2) return zero;
	set<vector<int>> st;
	for each (vector<int> vect in temp)
		st.insert(vect);
	int c = st.size();
	if (c % 2 == 0) return one;
	return zero;
}  

vector<int> mexp(vector<int> a, vector<int> b, vector<int> c) {
	if (eq(c, one)) return zero;
	vector<int> d = one;
	for (vector<int> i = zero; !eq(i, b); i = add(i, one))
		d = mod(mult(d, a), c);
	return d;
}

int solovay(vector<int> a) {
	if (!eq(mod(a, two), one)) return 0;
	for (int k = 0; k < 5; ++k) {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, 264738);
		vector<int> r = one;
		vector<int> r1 = v(to_string(dist(rng)));
		vector<int> r2 = v(to_string(dist(rng)));
		vector<int> r3 = v(to_string(dist(rng)));
		for (int i = 0; i < 3; ++i)
			r = mod(add(mult(r1, r), mult(r2, add(r3, r1))), a);
		int x = jacobi(r, a);
		vector<int> vt = mexp(r, div(sub(a, one), two), a);
		if (x == 0) return 0;
		if (x == -1 && !eq(vt, sub(a, one))) return 0;
		if (x == 1 && !eq(vt, one)) return 0;
	}
	return 1;
}


vector<int> pollardlg(vector<int> alpha, vector<int> beta, vector<int> n) {
	vector<int> x = one, a = zero, b = zero, N = add(n, one);
	vector<int> X = x, A = a, B = b;
	for (vector<int> i = one; !eq(i, n); i = add(i, one)) {
		if (eq(mod(x, three), zero)) { x = mod(mult(x, x), N);  a = mod(mult(a, two), n);  b = mod(mult(b, two), n); } else
		if (eq(mod(x, three), one)) { x = mod(mult(x, alpha), N);  a = mod(add(a, one), n); } else
		if (eq(mod(x, three), two)) { x = mod(mult(x, beta), N); b = mod(add(b, one), n); }
		if (eq(mod(X, three), zero)) { X = mod(mult(X, X), N);  A = mod(mult(A, two), n);  B = mod(mult(B, two), n); } else
		if (eq(mod(X, three), one)) { X = mod(mult(X, alpha), N);  A = mod(add(A, one), n); } else
		if (eq(mod(X, three), two)) { X = mod(mult(X, beta), N); B = mod(add(B, one), n); }
		if (eq(mod(X, three), zero)) { X = mod(mult(X, X), N);  A = mod(mult(A, two), n);  B = mod(mult(B, two), n); }
		else
			if (eq(mod(X, three), one)) { X = mod(mult(X, alpha), N);  A = mod(add(A, one), n); }
			else
				if (eq(mod(X, three), two)) { X = mod(mult(X, beta), N); B = mod(add(B, one), n); }
		print(x); print(a); print(b); print(X); print(A); print(B);
		if (x == X) break;
	}
	return mod(m(div(sub(a, A), sub(B, b))), n);;
}

void RSA(vector<int> a, vector<int> b) {
	vector<int> n = mult(a, b);
	vector<int> t = mult(sub(a, one), sub(b, one));
	vector<int> e = v("200");
	while (!eq(e, t)) {
		if (eq(gcd(e, t), one)) break;
		else e = add(e, one);
	}
	vector<int> d;
	vector<int> k = two;
	vector<int> tmp = add(one, mult(k, t));
	while (!eq(mod(tmp, e), zero)) {
		k = add(k, one);
		tmp = add(one, mult(k, t));
	}
	d = div(tmp, e);
	vector<int> m = v("322");
	vector<int> c = one;
	for (vector<int> i = one; !eq(i, add(e, one)); i = add(i, one))
		c = mod(mult(c, m), n);
	print(c);
	vector<int> md = one;
	for (vector<int> i = one; !eq(i, add(d, one)); i = add(i, one))
		md = mod(mult(md, c), n);
	print(md);
}


int main()
{
	string s1, s2, s3;
	//cout << "Pollard\n";
	//vector<int> a = pollard(mult(v("34981"),v("35759")));
	//print(a);
	//vector<int> z = mult(v("11657"),v("35759"));
	//z = mult(v("13"), (v("65")));
	//cout << solovay(v("113")) << "\n" << solovay(z);
	//print(pollard(z));
	//cout << "RSA\n";
	//RSA(v("113"), v("277"));
	//cout << "Pollard log\n";
	//print(pollardlg(two, five, v("1018")));

/*	vector<int> a = pollard(z);
	while (!eq(a, zero) && !eq(a, one)) {
		z = div(z, a);
		a =1111111111321231 pollard(z);
	} */
	/*cout << "\n\nLegendre\n";
	cout << legendre(v("17"), v("113")) << "\n";
	//set<vector<int>> st = factor(z);
	cout << "Solovay\n";
	cout << solovay(v("113")) << "\n" << solovay(z) << "\n";
	cout << "Euler\n";
	print(euler(v("113")));
	print(euler(z));
	cout << "Mobius\n";
	print(mobius(v("49")));
	print(mobius(z)); */
	while (true) {
		cin >> s1 >> s2 >> s3;
		//cout << s1 << "\n" << s2 << "\n" << s3 << "\n";
		vector<int> a = v(s1);
		vector<int> b = v(s3);
		vector<int> c;
		if (s2 == "+") c = add(a, b);
		if (s2 == "-") c = sub(a, b);
		if (s2 == "*") c = mult(a, b);
		if (s2 == "/") c = div(a, b);
		if (s2 == "%") c = mod(a, b);
		if (s2 == "^") c = pow(a, b);
		if (s2 == "gcd") c = gcd(a, b);
		if (s2 == "lcm") c = lcm(a, b);
		//print(a); print(b);
		print(c);
	} 
    return 0;
}