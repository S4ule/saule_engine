#ifndef __VECTOR_2_HPP__
# define __VECTOR_2_HPP__

#include <ostream>

class Vector_2
{
	public:
		float x;
		float y;

	public:
		Vector_2();
		Vector_2(const float x);
		Vector_2(const float x, const float y);
		Vector_2(const Vector_2 &ref);
		Vector_2 &operator=(const Vector_2 &ref);
		~Vector_2();

	public:
		float &operator[](const size_t index);

	public:
		Vector_2 operator+(const Vector_2 &ref) const;
		Vector_2 operator-(const Vector_2 &ref) const;
		Vector_2 operator/(const Vector_2 &ref) const;
		Vector_2 operator*(const Vector_2 &ref) const;
		Vector_2 &operator+=(const Vector_2 &ref);
		Vector_2 &operator-=(const Vector_2 &ref);
		Vector_2 &operator/=(const Vector_2 &ref);
		Vector_2 &operator*=(const Vector_2 &ref);
		Vector_2 dot_product(const Vector_2 &ref) const;

	public:
		bool	operator==(const Vector_2 &ref) const;
		bool	operator!=(const Vector_2 &ref) const;
};

std::ostream &operator<<(std::ostream& os, const Vector_2 &vector_2);

#endif /* __VECTOR_2_HPP__ */