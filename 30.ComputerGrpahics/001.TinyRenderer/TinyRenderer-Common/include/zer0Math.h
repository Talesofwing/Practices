#pragma once

#include <cassert>
#include <iostream>

namespace zer0 {

	template<int n>
	struct vec {
		double data[n] = {0};

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<n> operator+(const vec<n>& other) const;
		vec<n> operator-(const vec<n>& other) const;
		vec<n>& operator+=(const vec<n>& other);
		vec<n>& operator-=(const vec<n>& other);
	};

	template<>
	struct vec<2> {
		double x = 0, y = 0;

		vec<2> orthogonal() const;

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<2> operator+(const vec<2>& other) const;
		vec<2> operator-(const vec<2>& other) const;
		vec<2>& operator+=(const vec<2>& other);
		vec<2>& operator-=(const vec<2>& other);
	};

	template<>
	struct vec<3> {
		double x = 0, y = 0, z = 0;

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<3> operator+(const vec<3>& other) const;
		vec<3> operator-(const vec<3>& other) const;
		vec<3>& operator+=(const vec<3>& other);
		vec<3>& operator-=(const vec<3>& other);
	};

	template<>
	struct vec<4> {
		double x = 0, y = 0, z = 0, w = 0;

		double& operator[](const int i);
		double operator[] (const int i) const;

		vec<4> operator+(const vec<4>& other) const;
		vec<4> operator-(const vec<4>& other) const;
		vec<4>& operator+=(const vec<4>& other);
		vec<4>& operator-=(const vec<4>& other);
	};

	typedef vec<2> vec2;
	typedef vec<3> vec3;
	typedef vec<4> vec4;

	template<int n>
	double dot(const vec<n>& v1, const vec<n>& v2) {
		double result = 0;
		for (int i = 0; i < n; ++i)
			result += v1[i] * v2[i];

		return result;
	}

	double cross(const vec<2>& v1, const vec<2>& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}

	vec<3> cross(const vec<3>& v1, const vec<3>& v2) {
		vec<3> result;
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}

	template<int n>
	std::ostream& operator<<(std::ostream& out, const vec<n>& v) {
		for (int i = 0; i < n; ++i)
			out << v[i] << " ";

		return out;
	}

}
