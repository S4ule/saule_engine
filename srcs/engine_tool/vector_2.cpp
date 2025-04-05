
#include "engine_tool/vector_2.hpp"

Vector_2::Vector_2()
	:	x(0),
		y(0)
{
	return ;
}

Vector_2::Vector_2(const float x)
	:	x(x),
		y(0)
{
	return ;
}

Vector_2::Vector_2(const float x, const float y)
	:	x(x),
		y(y)
{
	return ;
}

Vector_2::Vector_2(const Vector_2 &ref)
{
	*this = ref;
	return ;
}

float &
Vector_2::operator[](const size_t index)
{
	switch (index)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			return this->x;
	}
	return this->x;
}

Vector_2 &
Vector_2::operator=(const Vector_2 &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->x = ref.x;
	this->y = ref.y;
	return *this;
}

Vector_2::~Vector_2()
{
	return ;
}

Vector_2
Vector_2::operator+(const Vector_2 &ref) const
{
	return Vector_2(this->x + ref.x, this->y + ref.y);
}

Vector_2
Vector_2::operator-(const Vector_2 &ref) const
{
	return Vector_2(this->x - ref.x, this->y - ref.y);
}

Vector_2
Vector_2::operator/(const Vector_2 &ref) const
{
	return Vector_2(this->x / ref.x, this->y / ref.y);
}

Vector_2
Vector_2::operator*(const Vector_2 &ref) const
{
	return Vector_2(this->x * ref.x, this->y * ref.y);
}

Vector_2 &
Vector_2::operator+=(const Vector_2 &ref)
{
	this->x = this->x + ref.x;
	this->y = this->y + ref.y;
	return *this;
}

Vector_2 &
Vector_2::operator-=(const Vector_2 &ref)
{
	this->x = this->x - ref.x;
	this->y = this->y - ref.y;
	return *this;
}

Vector_2 &
Vector_2::operator/=(const Vector_2 &ref)
{
	this->x = this->x / ref.x;
	this->y = this->y / ref.y;
	return *this;
}

Vector_2 &
Vector_2::operator*=(const Vector_2 &ref)
{
	this->x = this->x * ref.x;
	this->y = this->y * ref.y;
	return *this;
}

Vector_2
Vector_2::dot_product(const Vector_2 &ref) const
{
	return Vector_2(this->x * ref.x, this->y * ref.y);
}

bool
Vector_2::operator==(const Vector_2 &ref) const
{
	if (this->x == ref.x && this->y == ref.y) {
		return true;
	}
	return false;
}

bool
Vector_2::operator!=(const Vector_2 &ref) const
{
	if (this->x != ref.x && this->y != ref.y) {
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream& os, const Vector_2 &vector_2)
{
	os << vector_2.x << ", " << vector_2.y;
	return os;
}