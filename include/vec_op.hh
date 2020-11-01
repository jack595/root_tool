#pragma once
#ifndef VEC_OP_HPP
#define VEC_OP_HPP

#include "type_transform.hh"
#include<TString.h>
#include<sstream>
#include <vector>
#include <complex>
#include <numeric>
#include <algorithm>
#include<iostream>

namespace vec_op {

	template <class T_src, class T_dest>
	std::vector<T_dest> cast(std::vector<T_src> &v) {
		std::vector<T_dest> ans(v.size());
		for (size_t i = 0, size = ans.size(); i < size; ++i)
			ans[i] = (T_dest) v[i];
		return ans;
	}

	template <class T1, class T2>
	void fill(std::vector<T1> &v, const T2 &c) {
		for (T1 &e : v)
			e = (T1) c;
	}

	template <class T>
	std::vector<T> concat(const std::vector<T> &v1, const std::vector<T> &v2) {
		std::vector<T> ans;
		ans.reserve(v1.size() + v2.size());
		ans.insert(ans.end(), v1.begin(), v1.end());
		ans.insert(ans.end(), v2.begin(), v2.end());
		return ans;
	}

	template <class T>
	T dot(const std::vector<T> &v1, const std::vector<T> &v2) {
		T ans(0);
		for (size_t i = 0, size = v1.size(); i < size; ++i)
			ans += v1[i] * v2[i];
		return ans;
	}

	template <class T>
	T sum(const std::vector<T> &v) {
		T ans(0);
		for (const T &e : v)
			ans += e;
		return ans;
	}

	template <class T>
	T prod(const std::vector<T> &v) {
		T ans(1);
		for (const T &e : v)
			ans *= e;
		return ans;
	}

	template <class T>
	T min(const std::vector<T> &v) {
		return *std::min_element(v.begin(), v.end());
	}

	template <class T>
	T max(const std::vector<T> &v) {
		return *std::max_element(v.begin(), v.end());
	}

	template <typename T>
	std::vector<T> sort(const std::vector<T> &v) {
		std::vector<T> ans = v;
		std::sort(ans.begin(), ans.end());
		return ans;
	}

	template <typename T>
	std::vector<size_t> argsort(const std::vector<T> &v) {
		std::vector<size_t> idx(v.size());
		std::iota(idx.begin(), idx.end(), 0);
		std::sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {
			return v[i1] < v[i2];
		});
		return idx;
	}

	std::vector<size_t> randomIndex(size_t n) {
		std::vector<size_t> idx(n);
		std::iota(idx.begin(), idx.end(), 0);
		std::random_shuffle(idx.begin(), idx.end());
		return idx;
	}

	std::vector<size_t> range(size_t n) {
		std::vector<size_t> idx(n);
		std::iota(idx.begin(), idx.end(), 0);
		return idx;
	}

	template<class T>
    std::vector<T> range_new(const T &begin, const T &end, const T &add = 1) {
		std::vector<T> idx;
		idx.reserve((size_t) ((end - begin) / add));
		for (T i = begin; i < end; i += add)
			idx.push_back(i);
		return idx;
	}
}

template <class T>
std::vector<T> operator+(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] += v2[i];
	return ans;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] -= v2[i];
	return ans;
}

template <class T>
std::vector<T> operator*(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] *= v2[i];
	return ans;
}

template <class T>
std::vector<T> operator/(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans = v1;
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] /= v2[i];
	return ans;
}

template <class T>
std::vector<T> operator^(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<T> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (T) std::pow(v1[i], v2[i]);
	return ans;
}

template <class T>
std::vector<T>& operator+=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] += v2[i];
	return v1;
}

template <class T>
std::vector<T>& operator-=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] -= v2[i];
	return v1;
}

template <class T>
std::vector<T>& operator*=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] *= v2[i];
	return v1;
}

template <class T>
std::vector<T>& operator/=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] /= v2[i];
	return v1;
}

template <class T>
std::vector<T>& operator^=(std::vector<T> &v1, const std::vector<T> &v2) {
	for (size_t i = 0, size = v1.size(); i < size; ++i)
		v1[i] = (T) std::pow(v1[i], v2[i]);
	return v1;
}

template <class T>
std::vector<bool> operator==(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] == v2[i]);
	return ans;
}

template <class T>
std::vector<bool> operator!=(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] != v2[i]);
	return ans;
}

template <class T>
std::vector<bool> operator<(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] < v2[i]);
	return ans;
}

template <class T>
std::vector<bool> operator<=(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] <= v2[i]);
	return ans;
}

template <class T>
std::vector<bool> operator>(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] > v2[i]);
	return ans;
}

template <class T>
std::vector<bool> operator>=(const std::vector<T> &v1, const std::vector<T> &v2) {
	std::vector<bool> ans(v1.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (v1[i] >= v2[i]);
	return ans;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v) {
	os << "[ ";
	for (const T &e : v)
		os << e << ", ";
	os << "]";
	return os;
}

template <class T>
std::vector<T> operator+(const std::vector<T> &v, const T &c) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e += c;
	return ans;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &v, const T &c) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e -= c;
	return ans;
}

template <class T>
std::vector<T> operator*(const std::vector<T> &v, const T &c) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e *= c;
	return ans;
}

template <class T>
std::vector<T> operator/(const std::vector<T> &v, const T &c) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e /= c;
	return ans;
}

template <class T>
std::vector<T>& operator+=(std::vector<T> &v, const T &c) {
	for (T &e : v)
		e += c;
	return v;
}

template <class T>
std::vector<T>& operator-=(std::vector<T> &v, const T &c) {
	for (T &e : v)
		e -= c;
	return v;
}

template <class T>
std::vector<T>& operator*=(std::vector<T> &v, const T &c) {
	for (T &e : v)
		e *= c;
	return v;
}

template <class T>
std::vector<T>& operator/=(std::vector<T> &v, const T &c) {
	for (T &e : v)
		e /= c;
	return v;
}

template <class T>
std::vector<T> operator+(const T &c, const std::vector<T> &v) {
	std::vector<T> ans(v.size(), c);
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] += v[i];
	return ans;
}

template <class T>
std::vector<T> operator-(const T &c, const std::vector<T> &v) {
	std::vector<T> ans(v.size(), c);
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] -= v[i];
	return ans;
}

template <class T>
std::vector<T> operator*(const T &c, const std::vector<T> &v) {
	std::vector<T> ans(v.size(), c);
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] *= v[i];
	return ans;
}

template <class T>
std::vector<T> operator/(const T &c, const std::vector<T> &v) {
	std::vector<T> ans(v.size(), c);
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] /= v[i];
	return ans;
}

template<class T1, class T2>
std::vector<T1> operator^(const std::vector<T1> &v, const T2 &i) {
	std::vector<T1> ans = v;
	for (T1 &e : ans)
		e = (T1) std::pow(e, i);
	return ans;
}

template<class T1, class T2>
std::vector<T1> operator^(const T1 &b, const std::vector<T2> &v) {
	std::vector<T1> ans(v.size());
	for (size_t i = 0, size = ans.size(); i < size; ++i)
		ans[i] = (T1) std::pow(b, v[i]);
	return ans;
}

template<class T1, class T2>
std::vector<T1>& operator^=(std::vector<T1> &v, const T2 &i) {
	for (T1 &e : v)
		e = (T1) std::pow(e, i);
	return v;
}

template <class T>
std::vector<T> operator+(const std::vector<T> &v) {
	return v;
}

template <class T>
std::vector<T> operator-(const std::vector<T> &v) {
	std::vector<T> ans = v;
	for (T &e : ans)
		e = -e;
	return ans;
}

template <class T>
std::vector<std::string> ve_ntoa(std::vector<T> v_num)
{
    using namespace std;
    std::vector<std::string> v_str;
    v_str.reserve(v_num.size());
    for(int i=0;i<v_num.size();i++)
    {
        v_str.push_back((n2str(v_num[i])));
    }
    return v_str;
}

using namespace std;
template <class T>
T mean(vector<T> v)
{
    T v_sum=accumulate(v.begin(),v.end(),0.0);
    return v_sum/v.size();

}

int mean_int(vector<int> v)
{
    int v_sum=accumulate(v.begin(),v.end(),0.0);
    return round(v_sum/v.size());

}




template <class T>
vector<T> find_max(vector<T> v)
{
    int maxPos=0;
    for(int i=0;i<v.size();i++)
    {
        if (v[i] > v[maxPos]) // Found a bigger max
        maxPos = i;

    }
    vector<T> v_max={(T)maxPos,v[maxPos]};
    return v_max;
}
template <class T>
vector<T> find_min(vector<T> v)
{
    int minPos=0;
    for(int i=0;i<v.size();i++)
    {
        if (v[i] < v[minPos]) // Found a minner min
        minPos = i;

    }
    vector<T> v_min={(T)minPos,v[minPos]};
    return v_min;
}
template <class T>
void vector2array_2d(vector<vector<T>> v_2d,T array_return[][3])
{
    //this function is to convert the 2d vector to 2d array ,but unfortunately,we have to
    //assign the array's size whenever we use it.this may be optimize in the furture.
    for (int i=0;i<v_2d.size();i++)
    {
        for(int j=0;j<v_2d[0].size();j++)
        {
            array_return[i][j]=v_2d[i][j];
        }
    }
}

template <class T>
void print_vector(vector<T> v_to_print)
{
using namespace std;
    for(int i=0;i<v_to_print.size();i++)
    {
        cout<<i<<"	"<<v_to_print[i]<<endl;
    }
}

template <class T>
void print_2Dvector(vector<vector<T>> v2d_to_print)
{
using namespace std;
    for(int i=0;i<v2d_to_print.size();i++)
    {
        cout<<i<<": length("<<v2d_to_print[i].size()<<")	";
    for(int j=0;j<v2d_to_print[i].size();j++)
    {
        cout<<v2d_to_print[i][j]<<" ";
    }
        cout<<endl;
    }
}

#endif /* VEC_OP_HPP */



























