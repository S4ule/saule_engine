
#include "saule_engine_debug_tool.hpp"

#include <stdio.h>
#include <iostream>
#include <ostream>

#ifdef SAULE_ENGINE_USE_OPENGL

void
GL_clear_error(void)
{
	while (glGetError() != GL_NO_ERROR)
		continue ;
	return ;
}

int
GL_log_call(const char *fonction, const char *file, int line)
{
	int err;

	err = 0;
	while (GLenum error = glGetError())
	{
		std::cout << "[openGL] error (" << error << "): " << fonction << " " << file << ":" << line << std::endl;
		err = 1;
	}
	return err;
}
#endif /* SAULE_ENGINE_USE_OPENGL */


/*
	Debug Log
*/
static bool global_debug_log_status = false;

void
saule_engine_set_debug_log_status(bool value)
{
	global_debug_log_status = value;
}

void
saule_engine_debug_log_call(const char *msg, int type)
{
	if (global_debug_log_status == false || msg == NULL)
	{
		return ;
	}

	if (type == 0)
	{
		// Info
		printf("[engine] info: %s\n", msg);
	}
	else if (type > 0)
	{
		// Warning
		printf("[engine] warning: %s\n", msg);
	}
	else
	{
		// Error
		printf("[engine] error: %s\n", msg);
	}
	return ;
}