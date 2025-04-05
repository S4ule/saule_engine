
#include "engine/gpu_api/gpu_draw_context.hpp"

GPU_Draw_context::GPU_Draw_context()
{
	return ;
}

GPU_Draw_context::~GPU_Draw_context()
{
	return ;
}

int
GPU_Draw_context::setup(void *context_proc_address)
{
	int err;

	SAULE_ENGINE_INFO_LOG("load context...");
	err = gladLoadGLLoader((GLADloadproc)context_proc_address);
	if (err == 0)
	{
		return -1;
	}
	SAULE_ENGINE_INFO_LOG("context loaded");
	SAULE_ENGINE_INFO_LOG("used openGL version:");
	SAULE_ENGINE_INFO_LOG((const char *)glGetString(GL_VERSION));
	return 0;
}

int
GPU_Draw_context::draw_triangle(size_t count)
{
	// SAULE_ENGINE_INFO_LOG("draw_triangle call");
	GL_CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	return 0;
}

void
GPU_Draw_context::enable_blending() const
{
	SAULE_ENGINE_INFO_LOG("blending enable (1-A)");
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	return ;
}

void
GPU_Draw_context::disable_blending() const
{
	SAULE_ENGINE_INFO_LOG("blending disable");
	GL_CALL(glDisable(GL_BLEND));
	return ;
}

void
GPU_Draw_context::enable_depth_testing() const
{
	SAULE_ENGINE_INFO_LOG("depth testing enable");
	GL_CALL(glEnable(GL_DEPTH_TEST));
	return ;
}

void
GPU_Draw_context::disable_depth_testing() const
{
	SAULE_ENGINE_INFO_LOG("depth testing disable");
	GL_CALL(glDisable(GL_DEPTH_TEST));
	return ;
}

void
GPU_Draw_context::clear()
{
	//SAULE_ENGINE_INFO_LOG("buffer clear");
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	return ;
}

void
GPU_Draw_context::set_clear_color(float r, float g, float b, float a)
{
	SAULE_ENGINE_INFO_LOG("set clear color");
	GL_CALL(glClearColor(r, g, b, a));
	return ;
}

void
GPU_Draw_context::set_frame_buffer_size(size_t width, size_t height)
{
	// SAULE_ENGINE_INFO_LOG("set frame buffer size");
	GL_CALL(glViewport(0, 0, width, height));
	return ;
}