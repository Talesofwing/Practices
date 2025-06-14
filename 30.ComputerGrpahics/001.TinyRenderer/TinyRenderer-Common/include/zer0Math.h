#pragma once

#include <cassert>
#include <iostream>

namespace zer0 {

	template<int n>
	struct vec {
		vec<n>() = default;
		vec<n>(int v);
		vec<n>(double v);

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<n> operator+(const vec<n>& other) const;
		vec<n> operator-(const vec<n>& other) const;
		vec<n>& operator+=(const vec<n>& other);
		vec<n>& operator-=(const vec<n>& other);

		double data[n] = {0};
	};

	template<>
	struct vec<2> {
		vec<2>() = default;
		vec<2>(double x, double y);
		vec<2>(double v);
		vec<2>(const vec<3>& v);
		vec<2>(const vec<4>& v);

		vec<2> orthogonal() const;

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<2> operator+(const vec<2>& other) const;
		vec<2> operator-(const vec<2>& other) const;
		vec<2>& operator+=(const vec<2>& other);
		vec<2>& operator-=(const vec<2>& other);

		double x = 0, y = 0;
	};

	template<>
	struct vec<3> {
		vec<3>() = default;
		vec<3>(double x, double y, double z);
		vec<3>(double v);
		vec<3>(const vec<2>& v);
		vec<3>(const vec<4>& v);

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<3> operator+(const vec<3>& other) const;
		vec<3> operator-(const vec<3>& other) const;
		vec<3>& operator+=(const vec<3>& other);
		vec<3>& operator-=(const vec<3>& other);

		double x = 0, y = 0, z = 0;
	};

	template<>
	struct vec<4> {
		vec<4>() = default;
		vec<4>(double x, double y, double z, double w);
		vec<4>(double v);
		vec<4>(const vec<2>& v);
		vec<4>(const vec<3>& v);

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<4> operator+(const vec<4>& other) const;
		vec<4> operator-(const vec<4>& other) const;
		vec<4>& operator+=(const vec<4>& other);
		vec<4>& operator-=(const vec<4>& other);

		double x = 0, y = 0, z = 0, w = 0;
	};

	typedef vec<2> vec2;
	typedef vec<3> vec3;
	typedef vec<4> vec4;

	template<int n>
	double dot(const vec<n>& v1, const vec<n>& v2);

	double cross(const vec<2>& v1, const vec<2>& v2);

	vec<3> cross(const vec<3>& v1, const vec<3>& v2);

	template<int n>
	std::ostream& operator<<(std::ostream& out, const vec<n>& v) {
		for (int i = 0; i < n; ++i)
			out << v[i] << " ";

		return out;
	}

}
