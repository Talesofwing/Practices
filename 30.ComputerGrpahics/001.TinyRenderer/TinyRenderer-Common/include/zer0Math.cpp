#include "zer0Math.h"

namespace zer0 {

	//
	// vec template
	//
	template<int n>
	vec<n>::vec<n>(double v) {
		for (int i = 0; i < n; ++i)
			data[i] = v;
	}

	template<int n>
	double& vec<n>::operator[](const int i) {
		assert(i >= 0 && i < n);
		return data[i];
	}

	template<int n>
	double vec<n>::operator[](const int i) const {
		assert(i >= 0 && i < n);
		return data[i];
	}

	template<int n>
	vec<n> vec<n>::operator+(const vec<n>& other) const {
		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = data[i] + other[i];

		return result;
	}

	template<int n>
	vec<n> vec<n>::operator-(const vec<n>& other) const {
		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = data[i] - other[i];

		return result;
	}

	template<int n>
	vec<n>& vec<n>::operator+=(const vec<n>& other) {
		for (int i = 0; i < n; ++i)
			data[i] += other[i];

		return *this;
	}

	template<int n>
	vec<n>& vec<n>::operator-=(const vec<n>& other) {
		for (int i = 0; i < n; ++i)
			data[i] -= other[i];

		return *this;
	}

	//
	// vec2
	//

	vec<2>::vec<2>(double x, double y) : x(x), y(y) {}

	vec<2>::vec<2>(double v) : x(v), y(v) {}

	vec<2>::vec<2>(const vec<3>& v) : x(v.x), y(v.y) {}

	vec<2>::vec<2>(const vec<4>& v) : x(v.x), y(v.y) {}

	double vec<2>::operator[] (const int i) const {
		assert(i >= 0 && i < 2);
		return i == 0 ? x : y;
	}

	vec<2> vec<2>::orthogonal() const {
		return {-y, x};
	}

	double& vec<2>::operator[] (const int i) {
		assert(i >= 0 && i < 2);
		return i == 0 ? x : y;
	}

	vec<2> vec<2>::operator+(const vec<2>& other) const {
		vec<2> result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	vec<2> vec<2>::operator-(const vec<2>& other) const {
		vec<2> result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	vec<2>& vec<2>::operator+=(const vec<2>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	vec<2>& vec<2>::operator-=(const vec<2>& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	//
	// vec3
	//

	vec<3>::vec<3>(double x, double y, double z) : x(x), y(y), z(z) {}

	vec<3>::vec<3>(double v) : x(v), y(v), z(v) {}

	vec<3>::vec<3>(const vec<2>& v) : x(v.x), y(v.y), z(0) {}

	vec<3>::vec<3>(const vec<4>& v) : x(v.x), y(v.y), z(v.z) {}

	double vec<3>::operator[] (const int i) const {
		assert(i >= 0 && i < 3);
		return i == 0 ? x :
			i == 1 ? y : z;
	}

	double& vec<3>::operator[] (const int i) {
		assert(i >= 0 && i < 3);
		return i == 0 ? x :
			i == 1 ? y : z;
	}

	vec<3> vec<3>::operator+(const vec<3>& other) const {
		vec<3> result;
		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;
		return result;
	}

	vec<3> vec<3>::operator-(const vec<3>& other) const {
		vec<3> result;
		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		return result;
	}

	vec<3>& vec<3>::operator+=(const vec<3>& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec<3>& vec<3>::operator-=(const vec<3>& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	//
	// vec4
	//

	vec<4>::vec<4>(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

	vec<4>::vec<4>(double v) : x(v), y(v), z(v) {}

	vec<4>::vec<4>(const vec<2>& v) : x(v.x), y(v.y), z(0) {}

	vec<4>::vec<4>(const vec<3>& v) : x(v.x), y(v.y), z(v.z) {}

	double vec<4>::operator[] (const int i) const {
		assert(i >= 0 && i < 4);
		return i == 0 ? x :
			i == 1 ? y :
			i == 2 ? z : w;
	}

	double& vec<4>::operator[] (const int i) {
		assert(i >= 0 && i < 4);
		return i == 0 ? x :
			i == 1 ? y :
			i == 2 ? z : w;
	}

	vec<4> vec<4>::operator+(const vec<4>& other) const {
		vec<4> result;
		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;
		result.w = w + other.w;
		return result;
	}

	vec<4> vec<4>::operator-(const vec<4>& other) const {
		vec<4> result;
		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		result.w = w - other.w;
		return result;
	}

	vec<4>& vec<4>::operator+=(const vec<4>& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec<4>& vec<4>::operator-=(const vec<4>& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	//
	// Other
	//
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
}
