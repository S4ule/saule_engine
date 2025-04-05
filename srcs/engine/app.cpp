
#include "engine/app.hpp"

App::App()
{
	this->setup();
	return ;
}

App::~App()
{
	return ;
}

int
App::setup()
{
	return this->window.setup();
}

int
App::open(const std::string name, size_t width, size_t height)
{
	this->window.open(name, width, height);
	this->renderer.setup(this->window);
	this->renderer.set_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
	this->renderer.enable_blending();
	this->renderer.enable_depth_testing();
	return 0;
}


int
App::draw_loop()
{
	if (this->scene == NULL)
	{
		SAULE_ENGINE_ERROR_LOG("app loop have no scene to draw");
		return -1;
	}

	SAULE_ENGINE_INFO_LOG("start app loop");
	this->window.bind();
	this->scene->call_start(&this->window);
	while (this->window.should_close() == false)
	{
		this->renderer.clear();
		this->renderer.draw_scene(*(this->scene));
		this->window.swap_buffers();
		this->window.pool_events();
		this->match_window_size();
		this->scene->call_update(&this->window);
	}
	this->renderer.clean();
	return 0;
}

void
App::close()
{
	this->window.close();
	return ;
}


void
App::use_scene(Scene &user_scene)
{
	this->scene = &user_scene;
	this->renderer.clean();
	return ;
}

void
App::match_window_size()
{
	size_t width;
	size_t height;

	this->window.get_frame_buffer_size(width, height);
	this->renderer.set_frame_buffer_size(width, height);
	return ;
}