#ifndef __GPU_DRAW_CONTEXT__
# define __GPU_DRAW_CONTEXT__

# include <glad/glad.h>
# include <stddef.h>

# include "saule_engine_debug_tool.hpp"

class GPU_Draw_context
{
	public:
		GPU_Draw_context();
		virtual ~GPU_Draw_context();

	public:
		int setup(void *context_proc_address);
		int draw_triangle(size_t count);
		void enable_blending() const;
		void disable_blending() const;
		void enable_depth_testing() const;
		void disable_depth_testing() const;
		void clear();
		void set_clear_color(float r, float g, float b, float a);
		void set_frame_buffer_size(size_t width, size_t height);
};

#endif /* __GPU_DRAW_CONTEXT__ */