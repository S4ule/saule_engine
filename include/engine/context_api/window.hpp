#ifndef __WINDOW_HPP__
# define __WINDOW_HPP__

# include <string>

# include <glad/glad.h>
# include <GLFW/glfw3.h>

class Window
{
	private:
		GLFWwindow	*_window;
	
	public:
		Window();
		virtual ~Window();

	public:
		int setup();
		int open(const std::string name, size_t width, size_t height);
		void close();
		void swap_buffers();
		bool key_is_release(unsigned int key_code) const;
		bool key_is_press(unsigned int key_code) const;
		void pool_events();
		bool should_close() const;
		void set_should_close(bool value) const;

	public:
		void get_frame_buffer_size(size_t &width, size_t &height);

	public:
		void *get_context_proc_address() const;

	public:
		void bind(void) const;
};

#endif /* __WINDOW_HPP__ */