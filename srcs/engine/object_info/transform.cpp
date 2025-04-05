
#include "engine/object_info/transform.hpp"

Transform::Transform()
	:	position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1.0f, 1.0f, 1.0f)
{
	return ;
}

Transform::Transform(const Transform &ref)
{
	*this = ref;
	return ;
}

Transform &
Transform::operator=(const Transform &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->position = ref.position;
	this->rotation = ref.rotation;
	this->scale = ref.scale;
	return *this;
}

Transform::~Transform()
{
	return ;
}
