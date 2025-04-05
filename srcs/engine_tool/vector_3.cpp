
#include "engine_tool/vector_3.hpp"

Vector_3::Vector_3()
	:	x(0),
		y(0),
		z(0)
{
	return ;
}

Vector_3::Vector_3(const float x)
	:	x(x),
		y(0),
		z(0)
{
	return ;
}

Vector_3::Vector_3(const float x, const float y)
	:	x(x),
		y(y),
		z(0)
{
	return ;
}

Vector_3::Vector_3(const float x, const float y, const float z)
	:	x(x),
		y(y),
		z(z)
{
	return ;
}

Vector_3::Vector_3(const Vector_3 &ref)
{
	*this = ref;
	return ;
}




float &
Vector_3::operator[](const size_t index)
{
	switch (index)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			return this->x;
	}
	return this->x;
}

float
Vector_3::length() const
{
	// length = sqrt((ax * ax) + (ay * ay) + (az * az))
	// length = sqrt(9 + 1 + 4) = 3.742
	float res;

	res =sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	return res;
}




Vector_3 &
Vector_3::operator=(const Vector_3 &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	return *this;
}

Vector_3::~Vector_3()
{
	return ;
}


Vector_3
Vector_3::operator+(const Vector_3 &ref) const
{
	return Vector_3(this->x + ref.x, this->y + ref.y, this->z + ref.z);
}


Vector_3
Vector_3::operator-(const Vector_3 &ref) const
{
	return Vector_3(this->x - ref.x, this->y - ref.y, this->z - ref.z);
}


Vector_3
Vector_3::operator/(const Vector_3 &ref) const
{
	return Vector_3(this->x / ref.x, this->y / ref.y, this->z / ref.z);
}

Vector_3
Vector_3::operator*(const Vector_3 &ref) const	// use dot_product()
{
	return Vector_3(this->x * ref.x, this->y * ref.y, this->z * ref.z);
}

Vector_3 &
Vector_3::operator+=(const Vector_3 &ref)
{
	this->x = this->x + ref.x;
	this->y = this->y + ref.y;
	this->z = this->z + ref.z;
	return *this;
}

Vector_3 &
Vector_3::operator-=(const Vector_3 &ref)
{
	this->x = this->x - ref.x;
	this->y = this->y - ref.y;
	this->z = this->z - ref.z;
	return *this;
}

Vector_3 &
Vector_3::operator/=(const Vector_3 &ref)
{
	this->x = this->x / ref.x;
	this->y = this->y / ref.y;
	this->z = this->z / ref.z;
	return *this;
}

Vector_3 &
Vector_3::operator*=(const Vector_3 &ref)
{
	this->x = this->x * ref.x;
	this->y = this->y * ref.y;
	this->z = this->z * ref.z;
	return *this;
}



Vector_3
Vector_3::operator+(const float &ref) const
{
	return Vector_3(this->x + ref, this->y + ref, this->z + ref);
}

Vector_3
Vector_3::operator-(const float &ref) const
{
	return Vector_3(this->x - ref, this->y - ref, this->z - ref);
}

Vector_3
Vector_3::operator/(const float &ref) const
{
	return Vector_3(this->x / ref, this->y / ref, this->z / ref);
}

Vector_3
Vector_3::operator*(const float &ref) const
{
	// use dot_product()
	return Vector_3(this->x * ref, this->y * ref, this->z * ref);
}

Vector_3 &
Vector_3::operator+=(const float &ref)
{
	this->x = this->x + ref;
	this->y = this->y + ref;
	this->z = this->z + ref;
	return *this;
}

Vector_3 &
Vector_3::operator-=(const float &ref)
{
	this->x = this->x - ref;
	this->y = this->y - ref;
	this->z = this->z - ref;
	return *this;
}

Vector_3 &
Vector_3::operator/=(const float &ref)
{
	this->x = this->x / ref;
	this->y = this->y / ref;
	this->z = this->z / ref;
	return *this;
}

Vector_3 &
Vector_3::operator*=(const float &ref)
{
	this->x = this->x * ref;
	this->y = this->y * ref;
	this->z = this->z * ref;
	return *this;
}



Vector_3
Vector_3::dot(const Vector_3 &v3, const Vector_3 &ref)
{
	return Vector_3(v3.x * ref.x, v3.y * ref.y, v3.z * ref.z);
}

Vector_3
Vector_3::cross(const Vector_3 &v3, const Vector_3 &ref)
{
	/*
		// Nx = Ay * Bz - Az * By
		// Ny = Az * Bx - Ax * Bz
		// Nz = Ax * By - Ay * Bx
	*/
	Vector_3	res;

	res.x = v3.y * ref.z - v3.z * ref.y;
	res.y = v3.z * ref.x - v3.x * ref.z;
	res.z = v3.x * ref.y - v3.y * ref.x;
	return res;
}

Vector_3
Vector_3::rotate(const Vector_3 &v3, Vector_4 v4_rotate)
{
	// cos(θ) + Rx^2 * (1 - cos(θ))			|	Rx * Ry * (1 - cos(θ)) - Rz * sin(θ)	|	Rx * Rz * (1 - cos(θ)) + Ry * sin(θ)
	// Ry * Rx * (1 - cos(θ)) + Rz * sin(θ)	|	cos(θ) + Ry^2 * (1 - cos(θ))			|	Ry * Rz * (1 - cos(θ)) - Rx * sin(θ)
	// Rz * Rx * (1 - cos(θ)) - Ry * sin(θ)	|	Rz * Ry * (1 - cos(θ)) + Rx * sin(θ)	|	cos(θ) + Rz^2 * (1 - cos(θ))

	float	cos_angle;
	float	sin_angle;
	float	one_minus_cos;
	float	rx_time_sin;
	float	ry_time_sin;
	float	rz_time_sin;
	float	rx_time_ry;
	float	rx_time_rz;
	float	ry_time_rz;
	float	x_buf;
	float	y_buf;
	float	z_buf;
	float	angle_in_radians = v4_rotate.w * (SAULE_ENGINE_PI / 180);

	cos_angle = cos(angle_in_radians);
	sin_angle = sin(angle_in_radians);
	one_minus_cos = 1 - cos_angle;
	rx_time_sin = v4_rotate.x * sin_angle;
	ry_time_sin = v4_rotate.y * sin_angle;
	rz_time_sin = v4_rotate.z * sin_angle;
	rx_time_ry = v4_rotate.x * v4_rotate.y;
	rx_time_rz = v4_rotate.x * v4_rotate.z;
	ry_time_rz = v4_rotate.y * v4_rotate.z;

	x_buf = v3.x * (cos_angle + v4_rotate.x * v4_rotate.x * one_minus_cos) +	\
			v3.y * (rx_time_ry * one_minus_cos - rz_time_sin) +					\
			v3.z * (rx_time_rz * one_minus_cos + ry_time_sin);

	y_buf = v3.x * (rx_time_ry * one_minus_cos + rz_time_sin) +					\
			v3.y * (cos_angle + v4_rotate.y * v4_rotate.y * one_minus_cos) +	\
			v3.z * (ry_time_rz * one_minus_cos - rx_time_sin);

	z_buf = v3.x * (rx_time_rz * one_minus_cos - ry_time_sin) +				\
			v3.y * (ry_time_rz * one_minus_cos + rx_time_sin) +				\
			v3.z * (cos_angle + v4_rotate.z * v4_rotate.z * one_minus_cos);

	return Vector_3(x_buf, y_buf, z_buf);
}

Vector_3
Vector_3::normalize(const Vector_3 &v3)
{
	// Given vector a its xyz components are calculated as follows
	// x = Ax / |length|
	// y = Ay / |length|
	// z = Az / |length|

	Vector_3	norm;
	float		len;

	len = v3.length();
	if (len == 0)
	{
		return norm;
	}
	norm = v3 / len;
	return norm;
}



Vector_3 &
Vector_3::dot(const Vector_3 &ref)
{
	(*this) *= ref;
	return *this;
}

Vector_3 &
Vector_3::cross(const Vector_3 &ref)
{
	*this = this->cross(*this, ref);
	return *this;
}

Vector_3 &
Vector_3::rotate(Vector_4 v4_rotate)
{
	*this = this->rotate(*this, v4_rotate);
	return *this;
}

Vector_3 &
Vector_3::normalize()
{
	float		len;

	len = this->length();
	if (len == 0)
	{
		*this = Vector_3();
		return *this;
	}
	*this /= len;
	return *this;
}



bool
Vector_3::operator==(const Vector_3 &ref) const
{
	if (this->x == ref.x && this->y == ref.y && this->z == ref.z) {
		return true;
	}
	return false;
}

bool
Vector_3::operator!=(const Vector_3 &ref) const
{
	if (this->x != ref.x && this->y != ref.y && this->z != ref.z) {
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream& os, const Vector_3 &vector_3)
{
	os << vector_3.x << ", " << vector_3.y << ", " << vector_3.z;
	return os;
}