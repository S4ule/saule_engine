
#include "engine/camera.hpp"

Camera::Camera()
	:	front(1.0f, 0.0f, 0.0f),
		right(0.0f, 0.0f, 1.0f),
		up(0.0f, 1.0f, 0.0f),
		position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f, 0.0f),
		fov(90.0f)
{
	return ;
}

Camera::~Camera()
{
	return ;
}

#include <iostream>
#include <ostream>

int
Camera::update_direction_vector()
{
	/*
		--TODO--
		Y angle is not taken in consideration, and this is prorbaly quacked-up 🦆 somewhere
	*/
	Vector_3 angle_in_radians;
	Vector_3 direction;

	angle_in_radians.x = this->rotation.y * this->rotation.w;
	angle_in_radians.z = this->rotation.x * this->rotation.w;
	angle_in_radians *= (SAULE_ENGINE_PI / 180);

/*
	v3.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	v3.y = sin(glm::radians(pitch));
	v3.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	pitch = rotation.y;
	yaw = rotation.x;
	roll = rotation.z;
*/

	direction.x = cos(angle_in_radians.x) * cos(angle_in_radians.z);
	direction.z = sin(angle_in_radians.x) * cos(angle_in_radians.z);
	direction.normalize();


	this->right = direction;
	this->front = Vector_3::cross(this->right, this->up);
	this->up = Vector_3::cross(this->front, this->right);

//	std::cout << "Front: " << this->front << std::endl;
//	std::cout << "Right: " << this->right << std::endl;
//	std::cout << "Up   : " << this->up << std::endl;
	return 0;
}