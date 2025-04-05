#ifndef __VECTOR_3_HPP__
# define __VECTOR_3_HPP__

#include <ostream>
#include <cmath>

#include "engine_tool/vector_4.hpp"
#include "saule_engine_define.hpp"

class Vector_3
{
	public:
		float x;
		float y;
		float z;

	public:
		Vector_3();
		Vector_3(const float x);
		Vector_3(const float x, const float y);
		Vector_3(const float x, const float y, const float z);
		Vector_3(const Vector_3 &ref);
		Vector_3 &operator=(const Vector_3 &ref);
		~Vector_3();

	public:
		float &operator[](const size_t index);
		float length() const;

	public:
		Vector_3 operator+(const Vector_3 &ref) const;
		Vector_3 operator-(const Vector_3 &ref) const;
		Vector_3 operator/(const Vector_3 &ref) const;
		Vector_3 operator*(const Vector_3 &ref) const;	// use dot() for product
		Vector_3 &operator+=(const Vector_3 &ref);
		Vector_3 &operator-=(const Vector_3 &ref);
		Vector_3 &operator/=(const Vector_3 &ref);
		Vector_3 &operator*=(const Vector_3 &ref);

	public:
		Vector_3 operator+(const float &ref) const;
		Vector_3 operator-(const float &ref) const;
		Vector_3 operator/(const float &ref) const;
		Vector_3 operator*(const float &ref) const;	// use dot_product()
		Vector_3 &operator+=(const float &ref);
		Vector_3 &operator-=(const float &ref);
		Vector_3 &operator/=(const float &ref);
		Vector_3 &operator*=(const float &ref);

	public:
		static Vector_3 dot(const Vector_3 &v3, const Vector_3 &ref);
		static Vector_3 cross(const Vector_3 &v3, const Vector_3 &ref);
		static Vector_3 rotate(const Vector_3 &v3, const Vector_4 v4_rotate);
		static Vector_3 normalize(const Vector_3 &v3);
	
	public:
		Vector_3 &dot(const Vector_3 &ref);
		Vector_3 &cross(const Vector_3 &ref);
		Vector_3 &rotate(Vector_4 v4_rotate);
		Vector_3 &normalize();

	public:
		bool	operator==(const Vector_3 &ref) const;
		bool	operator!=(const Vector_3 &ref) const;
};

std::ostream &operator<<(std::ostream& os, const Vector_3 &vector_3);

#endif /* __VECTOR_3_HPP__ */