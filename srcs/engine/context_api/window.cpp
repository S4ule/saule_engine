
#include "engine/context_api/window.hpp"

Window::Window()
	:	_window(NULL)
{
	return ;
}

Window::~Window()
{
	return ;
}

int
Window::setup()
{
	int err;

	err = glfwInit();
	if (err == 0)
	{
		return -1;
	}
	return 0;
}

int
Window::open(const std::string name, size_t width, size_t height)
{
	this->_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (this->_window == NULL)
	{
		return -1;
	}
	return 0;
}

void
Window::close()
{
	if (this->_window != NULL)
	{
		glfwDestroyWindow(this->_window);
	}
	glfwTerminate();
	return ;
}

void
Window::swap_buffers()
{
	glfwSwapBuffers(this->_window);
	return ;
}

void
Window::pool_events()
{
	glfwPollEvents();
	return ;
}

bool
Window::key_is_release(unsigned int key_code) const
{
	int state;

	state = glfwGetKey(this->_window, key_code);
	if (state == GLFW_RELEASE)
	{
		return true;
	}
	return false;
}

bool
Window::key_is_press(unsigned int key_code) const
{
	int state;

	state = glfwGetKey(this->_window, key_code);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

bool
Window::should_close() const
{
	return glfwWindowShouldClose(this->_window);
}

void
Window::set_should_close(bool value) const
{
	glfwSetWindowShouldClose(this->_window, value);
	return ;	
}

void
Window::get_frame_buffer_size(size_t &width, size_t &height)
{
	glfwGetFramebufferSize(this->_window, (int *)&width, (int *)&height);
	return ;
}

void *
Window::get_context_proc_address() const
{
	return (void *)glfwGetProcAddress;
}

void
Window::bind(void) const
{
	glfwMakeContextCurrent(this->_window);
	return ;
}