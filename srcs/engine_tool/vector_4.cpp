
#include "engine_tool/vector_4.hpp"

Vector_4::Vector_4()
	:	x(0),
		y(0),
		z(0),
		w(0)
{
	return ;
}

Vector_4::Vector_4(const float x)
	:	x(x),
		y(0),
		z(0),
		w(0)
{
	return ;
}

Vector_4::Vector_4(const float x, const float y)
	:	x(x),
		y(y),
		z(0),
		w(0)
{
	return ;
}

Vector_4::Vector_4(const float x, const float y, const float z)
	:	x(x),
		y(y),
		z(z),
		w(0)
{
	return ;
}

Vector_4::Vector_4(const float x, const float y, const float z, const float w)
	:	x(x),
		y(y),
		z(z),
		w(w)
{
	return ;
}

Vector_4::Vector_4(const Vector_4 &ref)
{
	*this = ref;
	return ;
}

float &
Vector_4::operator[](const size_t index)
{
	switch (index)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			return this->x;
	}
	return this->x;
}

float
Vector_4::length() const
{
	float len;

	len = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
	return len;
}




Vector_4 &
Vector_4::operator=(const Vector_4 &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
	return *this;
}

Vector_4::~Vector_4()
{
	return ;
}

Vector_4
Vector_4::operator+(const Vector_4 &ref) const
{
	return Vector_4(this->x + ref.x, this->y + ref.y, this->z + ref.z, this->w + ref.w);
}

Vector_4
Vector_4::operator-(const Vector_4 &ref) const
{
	return Vector_4(this->x - ref.x, this->y - ref.y, this->z - ref.z, this->w - ref.w);
}

Vector_4
Vector_4::operator/(const Vector_4 &ref) const
{
	return Vector_4(this->x / ref.x, this->y / ref.y, this->z / ref.z, this->w / ref.w);
}

Vector_4
Vector_4::operator*(const Vector_4 &ref) const
{
	return Vector_4(this->x * ref.x, this->y * ref.y, this->z * ref.z, this->w * ref.w);
}

Vector_4 &
Vector_4::operator+=(const Vector_4 &ref)
{
	this->x = this->x + ref.x;
	this->y = this->y + ref.y;
	this->z = this->z + ref.z;
	this->w = this->w + ref.w;
	return *this;
}

Vector_4 &
Vector_4::operator-=(const Vector_4 &ref)
{
	this->x = this->x - ref.x;
	this->y = this->y - ref.y;
	this->z = this->z - ref.z;
	this->w = this->w - ref.w;
	return *this;
}

Vector_4 &
Vector_4::operator/=(const Vector_4 &ref)
{
	this->x = this->x / ref.x;
	this->y = this->y / ref.y;
	this->z = this->z / ref.z;
	this->w = this->w / ref.w;
	return *this;
}

Vector_4 &
Vector_4::operator*=(const Vector_4 &ref)
{
	this->x = this->x * ref.x;
	this->y = this->y * ref.y;
	this->z = this->z * ref.z;
	this->w = this->w * ref.w;
	return *this;
}



Vector_4
Vector_4::operator+(const float &ref) const
{
	return Vector_4(this->x + ref, this->y + ref, this->z + ref, this->w + ref);
}

Vector_4
Vector_4::operator-(const float &ref) const
{
	return Vector_4(this->x - ref, this->y - ref, this->z - ref, this->w - ref);
}

Vector_4
Vector_4::operator/(const float &ref) const
{
	return Vector_4(this->x / ref, this->y / ref, this->z / ref, this->w / ref);
}

Vector_4
Vector_4::operator*(const float &ref) const
{
	return Vector_4(this->x * ref, this->y * ref, this->z * ref, this->w * ref);
}

Vector_4 &
Vector_4::operator+=(const float &ref)
{
	this->x = this->x + ref;
	this->y = this->y + ref;
	this->z = this->z + ref;
	this->w = this->w + ref;
	return *this;
}

Vector_4 &
Vector_4::operator-=(const float &ref)
{
	this->x = this->x - ref;
	this->y = this->y - ref;
	this->z = this->z - ref;
	this->w = this->w - ref;
	return *this;
}

Vector_4 &
Vector_4::operator/=(const float &ref)
{
	this->x = this->x / ref;
	this->y = this->y / ref;
	this->z = this->z / ref;
	this->w = this->w / ref;
	return *this;
}

Vector_4 &
Vector_4::operator*=(const float &ref)
{
	this->x = this->x * ref;
	this->y = this->y * ref;
	this->z = this->z * ref;
	this->w = this->w * ref;
	return *this;
}




Vector_4
Vector_4::dot_product(const Vector_4 &v4, const Vector_4 &ref)
{
	return Vector_4(v4.x * ref.x, v4.y * ref.y, v4.z * ref.z, v4.w * ref.w);
}

Vector_4
Vector_4::normalize(const Vector_4 &v4)
{
	Vector_4	norm;
	float		len;

	len = v4.length();
	if (len == 0)
	{
		return norm;
	}
	norm = v4 / len;
	return norm;
}




Vector_4 &
Vector_4::dot(const Vector_4 &ref)
{
	*this *= ref;
	return *this;
}

Vector_4 &
Vector_4::normalize()
{
	float		len;

	len = this->length();
	if (len == 0)
	{
		*this = Vector_4();
		return *this;
	}
	*this /= len;
	return *this;
}




bool
Vector_4::operator==(const Vector_4 &ref) const
{
	if (this->x == ref.x && this->y == ref.y && this->z == ref.z && this->w == ref.w) {
		return true;
	}
	return false;
}

bool
Vector_4::operator!=(const Vector_4 &ref) const
{
	if (this->x != ref.x && this->y != ref.y && this->z != ref.z && this->w != ref.w) {
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream& os, const Vector_4 &vector_4)
{
	os << vector_4.x << ", " << vector_4.y << ", " << vector_4.z << ", " << vector_4.w;
	return os;
}