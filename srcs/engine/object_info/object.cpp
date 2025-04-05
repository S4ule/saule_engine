
#include "engine/object_info/object.hpp"

Object::Object()
{
	return ;
}

Object::Object(const Object &ref)
{
	*this = ref;
	return ;
}

Object &
Object::operator=(const Object &ref)
{
	if (this == &ref) {
		return *this;
	}
	this->blueprint_vector = ref.blueprint_vector;
	this->transform = ref.transform;
	return *this;
}

Object::~Object()
{
	return ;
}

void
Object::add_blueprint(Blueprint &user_blueprint)
{
	this->blueprint_vector.push_back(&user_blueprint);
}

void
Object::set_with_WF_object(WF_Object &wf_object)
{
	this->blueprint_vector.clear();
	this->blueprint_vector = wf_object.get_blueprint_vector();
	return ;
}

void
Object::set_object_shader(const Shader &user_shader)
{
	for (size_t i = 0; i < this->blueprint_vector.size(); i++)
	{
		if (this->blueprint_vector[i] != NULL)
		{
			this->blueprint_vector[i]->set_shader(user_shader);
		}
	}
	return ;
}