#include "zer0Math.h"

namespace zer0 {

//
// vec template
//

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

}
