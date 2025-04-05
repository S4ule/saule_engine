#ifndef __RENDERER_HPP__
# define __RENDERER_HPP__ 1

# include "engine/scene.hpp"
# include "engine/rendering/draw_queue.hpp"
# include "engine/context_api/window.hpp"
# include "engine/gpu_api/gpu_draw_context.hpp"

class Renderer
{
	private:
		static Draw_queue	_draw_queue;
		GPU_Draw_context	_draw_context;

	public:
		Renderer();
		virtual ~Renderer();

	public:
		int	setup(const Window &window);
		int draw_scene(const Scene &scene);
		void clean();

	public:
		void enable_blending() const;
		void disable_blending() const;
		void enable_depth_testing() const;
		void disable_depth_testing() const;
		void clear();
		void set_clear_color(float r, float g, float b, float a);
		void set_frame_buffer_size(size_t width, size_t height);
};

#endif /* __RENDERER_HPP__ */
