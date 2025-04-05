
#include "engine/scene.hpp"

Scene::Scene()
{
	return ;
}

Scene::~Scene()
{
	return ;
}

int
Scene::add_object_entity(Object_entity &ref)
{
	this->_object_entity_list.push_front(&ref);
	return 0;
}

const std::list<Object_entity *> &
Scene::get_object_entity() const
{
	return this->_object_entity_list;
}

void
Scene::call_start(const Window *window)
{
	std::list<Object_entity *>::const_iterator it;

	it = this->_object_entity_list.begin();
	while (it != this->_object_entity_list.end())
	{
		(*it)->start(window, *this);
		it++;
	}
	return ;
}

void
Scene::call_update(const Window *window)
{
	std::list<Object_entity *>::const_iterator it;

	it = this->_object_entity_list.begin();
	while (it != this->_object_entity_list.end())
	{
		(*it)->update(window, *this);
		it++;
	}

	// --TODO--
	// remove glfwGetTime() from there
	// change the delta_time calcultation
	static float last_frame_time = 0.0f;
	float currentFrame = glfwGetTime();
	
	this->delta_time = currentFrame - last_frame_time;
	last_frame_time = currentFrame;
	return ;
}