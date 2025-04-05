#ifndef __DRAW_QUEUE_HPP__
# define __DRAW_QUEUE_HPP__ 1

# include <queue>

# include "engine/object_info/object.hpp"
# include "engine/camera.hpp"
# include "engine/object_info/material.hpp"
# include "engine/rendering/blueprint_buffer.hpp"
# include "engine/gpu_api/gpu_draw_context.hpp"

class Draw_queue
{
	private:
		std::queue<Blueprint_buffer *>	_draw_queue;

	public:
		Draw_queue();
		~Draw_queue();

	public:
		int add(const Object *object);

	public:
		int draw(GPU_Draw_context &draw_context, const Camera *camera);
		int draw_all(GPU_Draw_context &draw_context, const Camera *camera);

	public:
		void clean();

	private:
		void _setup_bueprint_buffer_uniform(Blueprint_buffer *blueprint_buffer, const Camera *camera);
};

#endif /* __DRAW_QUEUE_HPP__ */