#ifndef __VECTOR_4_HPP__
# define __VECTOR_4_HPP__

#include <ostream>
#include <cmath>

class Vector_4
{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vector_4();
		Vector_4(const float x);
		Vector_4(const float x, const float y);
		Vector_4(const float x, const float y, const float z);
		Vector_4(const float x, const float y, const float z, const float w);
		Vector_4(const Vector_4 &ref);
		Vector_4 &operator=(const Vector_4 &ref);
		~Vector_4();

	public:
		float &operator[](const size_t index);
		float length() const;

	public:
		Vector_4 operator+(const Vector_4 &ref) const;
		Vector_4 operator-(const Vector_4 &ref) const;
		Vector_4 operator/(const Vector_4 &ref) const;
		Vector_4 operator*(const Vector_4 &ref) const;
		Vector_4 &operator+=(const Vector_4 &ref);
		Vector_4 &operator-=(const Vector_4 &ref);
		Vector_4 &operator/=(const Vector_4 &ref);
		Vector_4 &operator*=(const Vector_4 &ref);

	public:
		Vector_4 operator+(const float &ref) const;
		Vector_4 operator-(const float &ref) const;
		Vector_4 operator/(const float &ref) const;
		Vector_4 operator*(const float &ref) const;
		Vector_4 &operator+=(const float &ref);
		Vector_4 &operator-=(const float &ref);
		Vector_4 &operator/=(const float &ref);
		Vector_4 &operator*=(const float &ref);

	public:
		static Vector_4 dot_product(const Vector_4 &v4, const Vector_4 &ref);
		static Vector_4 normalize(const Vector_4 &v4);

	public:
		Vector_4 &dot(const Vector_4 &ref);
		Vector_4 &normalize();

	public:
		bool	operator==(const Vector_4 &ref) const;
		bool	operator!=(const Vector_4 &ref) const;
};

std::ostream &operator<<(std::ostream& os, const Vector_4 &vector_4);

#endif /* __VECTOR_4_HPP__ */