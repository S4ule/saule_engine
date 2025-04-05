#ifndef __APP_HPP__
# define __APP_HPP__

# include "engine/rendering/renderer.hpp"
# include "engine/context_api/window.hpp"

class App
{
	public:
		Window		window;
		Renderer	renderer;

	public:
		Scene	*scene;

	public:
		App();
		~App();

	public:
		int setup();
		int open(const std::string name, size_t width, size_t height);
		int draw_loop();
		void close();

	public:
		void use_scene(Scene &user_scene);

	private:
		void match_window_size();
};

#endif /* __APP_HPP__ */