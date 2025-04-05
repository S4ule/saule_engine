
#include "engine/rendering/renderer.hpp"

Draw_queue Renderer::_draw_queue;

Renderer::Renderer()
{
	return ;
}

Renderer::~Renderer()
{
	return ;
}

int
Renderer::setup(const Window &window)
{
	int err;

	window.bind();
	err = this->_draw_context.setup(window.get_context_proc_address());
	if (err != 0)
	{
		return -1;
	}
	return 0;
}

int
Renderer::draw_scene(const Scene &scene)
{
	// geting the list of all object to render
	const std::list<Object_entity *> &object_entity_list = scene.get_object_entity();

	for (std::list<Object_entity *>::const_iterator it = object_entity_list.begin(); it != object_entity_list.end(); it++)
	{
		// add object to draw queue
		this->_draw_queue.add(&(*it)->object);
	}
	this->_draw_queue.draw_all(this->_draw_context, &scene.camera);
	return 0;
}

void
Renderer::clean()
{
	this->_draw_queue.clean();
	return ;
}


void
Renderer::enable_blending() const
{
	this->_draw_context.enable_blending();
	return ;
}

void
Renderer::disable_blending() const
{
	this->_draw_context.disable_blending();
	return ;
}

void
Renderer::enable_depth_testing() const
{
	this->_draw_context.enable_depth_testing();
	return ;
}

void
Renderer::disable_depth_testing() const
{
	this->_draw_context.disable_depth_testing();
	return ;
}

void
Renderer::clear()
{
	this->_draw_context.clear();
	return ;
}

void
Renderer::set_clear_color(float r, float g, float b, float a)
{
	this->_draw_context.set_clear_color(r, g, b, a);
	return ;
}

void
Renderer::set_frame_buffer_size(size_t width, size_t height)
{
	this->_draw_context.set_frame_buffer_size(width, height);
	return ;
}