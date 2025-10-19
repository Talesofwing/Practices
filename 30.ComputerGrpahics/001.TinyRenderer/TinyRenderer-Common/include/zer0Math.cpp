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
	double vec<n>::length() const {
		double l = 0;
		for (int i = 0; i < n; ++i)
			l += (data[i] * data[i]);

		return std::sqrt(l);
	}

	template<int n>
	vec<n> vec<n>::normalize() const {
		double l = length();
		assert(l != 0);
		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = data[i] / l;

		return result;
	}

	template<int n>
	void vec<n>::normalized() {
		double l = length();
		assert(l != 0);
		for (int i = 0; i < n; ++i)
			data[i] /= l;
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
	vec<n> vec<n>::operator-() const {
		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = -data[i];

		return result;
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
	vec<n> vec<n>::operator*(const double value) const {
		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = data[i] * value;

		return result;
	}

	template<int n>
	vec<n> vec<n>::operator/(const double value) const {
		assert(value != 0);

		vec<n> result;
		for (int i = 0; i < n; ++i)
			result.data[i] = data[i] / value;

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

	template<int n>
	vec<n>& vec<n>::operator*=(const double value) {
		for (int i = 0; i < n; ++i)
			data[i] *= value;

		return *this;
	}

	template<int n>
	vec<n>& vec<n>::operator/=(const double value) {
		assert(value != 0);

		for (int i = 0; i < n; ++i)
			data[i] /= value;

		return *this;
	}

	//
	// vec2
	//

	vec<2>::vec<2>(double x, double y) : x(x), y(y) {}

	vec<2>::vec<2>(double v) : x(v), y(v) {}

	vec<2>::vec<2>(const vec<2>& v) : x(v.x), y(v.y) {}

	vec<2>::vec<2>(const vec<3>& v) : x(v.x), y(v.y) {}

	vec<2>::vec<2>(const vec<4>& v) : x(v.x), y(v.y) {}

	vec<2> vec<2>::orthogonal() const {
		return {-y, x};
	}

	double vec<2>::length() const {
		return std::sqrt(x * x + y * y);
	}

	vec<2> vec<2>::normalize() const {
		double l = length();
		assert(l != 0);
		vec<2> result;
		result.x = x / l;
		result.y = y / l;

		return result;
	}

	void vec<2>::normalized() {
		double l = length();
		assert(l != 0);
		x /= l;
		y /= l;
	}

	double vec<2>::operator[] (const int i) const {
		assert(i >= 0 && i < 2);
		return i == 0 ? x : y;
	}

	double& vec<2>::operator[] (const int i) {
		assert(i >= 0 && i < 2);
		return i == 0 ? x : y;
	}

	vec<2> vec<2>::operator-() const {
		return vec<2>(-x, -y);
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

	vec<2> vec<2>::operator*(const double value) const {
		vec<2> result;
		result.x = x * value;
		result.y = y * value;
		return result;
	}

	vec<2> vec<2>::operator/(const double value) const {
		assert(value != 0);

		vec<2> result;
		result.x = x / value;
		result.y = y / value;
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

	vec<2>& vec<2>::operator*=(const double value) {
		x *= value;
		y *= value;

		return *this;
	}

	vec<2>& vec<2>::operator/=(const double value) {
		assert(value != 0);

		x /= value;
		y /= value;

		return *this;
	}

	//
	// vec3
	//

	vec<3>::vec<3>(double x, double y, double z) : x(x), y(y), z(z) {}

	vec<3>::vec<3>(double v) : x(v), y(v), z(v) {}

	vec<3>::vec<3>(const vec<2>& v) : x(v.x), y(v.y), z(1) {}

	vec<3>::vec<3>(const vec<3>& v) : x(v.x), y(v.y), z(v.z) {}

	vec<3>::vec<3>(const vec<4>& v) : x(v.x), y(v.y), z(v.z) {}

	double vec<3>::length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	vec<3> vec<3>::normalize() const {
		double l = length();
		assert(l != 0);
		vec<3> result;
		result.x = x / l;
		result.y = y / l;
		result.z = z / l;

		return result;
	}

	void vec<3>::normalized() {
		double l = length();
		assert(l != 0);
		x /= l;
		y /= l;
		z /= l;
	}

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

	vec<3> vec<3>::operator-() const {
		return vec<3>(-x, -y, -z);
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

	vec<3> vec<3>::operator*(const double value) const {
		vec<3> result;
		result.x = x * value;
		result.y = y * value;
		result.z = z * value;
		return result;
	}

	vec<3> vec<3>::operator/(const double value) const {
		assert(value != 0);

		vec<3> result;
		result.x = x / value;
		result.y = y / value;
		result.z = z / value;
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

	vec<3>& vec<3>::operator*=(const double value) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	vec<3>& vec<3>::operator/=(const double value) {
		assert(value != 0);

		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	//
	// vec4
	//

	vec<4>::vec<4>(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

	vec<4>::vec<4>(double v) : x(v), y(v), z(v) {}

	vec<4>::vec<4>(const vec<2>& v) : x(v.x), y(v.y), z(1) {}

	vec<4>::vec<4>(const vec<3>& v) : x(v.x), y(v.y), z(v.z), w(1) {}

	vec<4>::vec<4>(const vec<4>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	double vec<4>::length() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	vec<4> vec<4>::normalize() const {
		double l = length();
		assert(l != 0);
		vec<4> result;
		result.x = x / l;
		result.y = y / l;
		result.z = z / l;
		result.w = w / l;

		return result;
	}

	void vec<4>::normalized() {
		double l = length();
		assert(l != 0);
		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

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

	vec<4> vec<4>::operator-() const {
		return vec<4>(-x, -y, -z, -w);
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

	vec<4> vec<4>::operator*(const double value) const {
		vec<4> result;
		result.x = x * value;
		result.y = y * value;
		result.z = z * value;
		result.w = w * value;
		return result;
	}

	vec<4> vec<4>::operator/(const double value) const {
		assert(value != 0);

		vec<4> result;
		result.x = x / value;
		result.y = y / value;
		result.z = z / value;
		result.w = w / value;
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

	vec<4>& vec<4>::operator*=(const double value) {
		x *= value;
		y *= value;
		z *= value;
		w *= value;

		return *this;
	}

	vec<4>& vec<4>::operator/=(const double value) {
		assert(value != 0);

		x /= value;
		y /= value;
		z /= value;
		w /= value;

		return *this;
	}

	//
	// Other
	// 
	//
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

	vec<3> operator*(const mat3x3& m, const vec<3>& v) {
		vec<3> result;
		result.x = m.a * v.x + m.b * v.y + m.c * v.z;
		result.y = m.d * v.x + m.e * v.y + m.f * v.z;
		result.z = m.g * v.x + m.h * v.y + m.i * v.z;
		return result;
	}

	vec<3> operator*(const vec<3>& v, const mat3x3& m) {
		vec<3> result;
		result.x = m.a * v.x + m.d * v.y + m.g * v.z;
		result.y = m.b * v.x + m.e * v.y + m.h * v.z;
		result.z = m.c * v.x + m.f * v.y + m.i * v.z;
		return result;
	}

	std::ostream& operator<<(std::ostream& out, const mat3x3& m) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				out << m.mat[y][x] << " ";
			}
			out << "\n";
		}

		return out;
	}

	vec<4> operator*(const mat4x4& m, const vec<4>& v) {
		vec<4> result;
		result.x = m.a * v.x + m.b * v.y + m.c * v.z + m.d * v.w;
		result.y = m.e * v.x + m.f * v.y + m.g * v.z + m.h * v.w;
		result.z = m.i * v.x + m.j * v.y + m.k * v.z + m.l * v.w;
		result.w = m.m * v.x + m.n * v.y + m.o * v.z + m.p * v.w;
		return result;
	}

	vec<4> operator*(const vec<4>& v, const mat4x4& m) {
		vec<4> result;
		result.x = m.a * v.x + m.e * v.y + m.i * v.z + m.m * v.w;
		result.y = m.b * v.x + m.f * v.y + m.j * v.z + m.n * v.w;
		result.z = m.c * v.x + m.g * v.y + m.k * v.z + m.o * v.w;
		result.w = m.d * v.x + m.h * v.y + m.l * v.z + m.p * v.w;
		return result;
	}

	mat4x4 operator*(const mat4x4& m1, const mat4x4& m2) {
		return mat4x4 {
			m1.a * m2.a + m1.b * m2.e + m1.c * m2.i + m1.d * m2.m, m1.a * m2.b + m1.b * m2.f + m1.c * m2.j + m1.d * m2.n, m1.a * m2.c + m1.b * m2.g + m1.c * m2.k + m1.d * m2.o, m1.a * m2.d + m1.b * m2.h + m1.c * m2.l + m1.d * m2.p,
			m1.e * m2.a + m1.f * m2.e + m1.g * m2.i + m1.h * m2.m, m1.e * m2.b + m1.f * m2.f + m1.g * m2.j + m1.h * m2.n, m1.e * m2.c + m1.f * m2.g + m1.g * m2.k + m1.h * m2.o, m1.e * m2.d + m1.f * m2.h + m1.g * m2.l + m1.h * m2.p,
			m1.i * m2.a + m1.j * m2.e + m1.k * m2.i + m1.l * m2.m, m1.i * m2.b + m1.j * m2.f + m1.k * m2.j + m1.l * m2.n, m1.i * m2.c + m1.j * m2.g + m1.k * m2.k + m1.l * m2.o, m1.i * m2.d + m1.j * m2.h + m1.k * m2.l + m1.l * m2.p,
			m1.m * m2.a + m1.n * m2.e + m1.o * m2.i + m1.p * m2.m, m1.m * m2.b + m1.n * m2.f + m1.o * m2.j + m1.p * m2.n, m1.m * m2.c + m1.n * m2.g + m1.o * m2.k + m1.p * m2.o, m1.m * m2.d + m1.n * m2.h + m1.o * m2.l + m1.p * m2.p
		};
	}

	std::ostream& operator<<(std::ostream& out, const mat4x4& m) {
		for (int y = 0; y < 4; ++y) {
			for (int x = 0; x < 4; ++x) {
				out << m.mat[y][x] << " ";
			}
			out << "\n";
		}

		return out;
	}

	// >> Chapter 6 
	//	Transformation Matrics

	mat4x4 view(const vec3& eye, const vec3& up, const vec3& lookAt) {
		vec3 z = (eye - lookAt).normalize();
		vec3 x = cross(up, z).normalize();
		vec3 y = cross(z, x).normalize();
		return {
			x.x, x.y, x.z, -dot(x, eye),
			y.x, y.y, y.z, -dot(y, eye),
			z.x, z.y, z.z, -dot(z, eye),
			0, 0, 0, 1
		};
	}

	mat4x4 proj(const double coeff) {
		return {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, -1 / coeff, 1
		};
	}

	mat4x4 viewport(const int width, const int height) {
		return {
			width * 0.5, 0, 0, width * 0.5,
			0, height * 0.5, 0, height * 0.5,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	vec4 transform(
		vec4 v,
		const vec3& eye, const vec3& up, const vec3& lookAt,
		const int width, const int height)
	{
		mat4x4 vm = view(eye, up, lookAt);
		mat4x4 pm = proj((eye - lookAt).length());
		mat4x4 vpm = viewport(width, height);

		v = pm * (vm * v);
		v /= v.w;		// ndc
		v = vpm * v;

		return v;
	}
}
