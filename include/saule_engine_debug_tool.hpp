#ifndef __SAULE_ENGINE_DEBUG_TOOL_HPP__
# define __SAULE_ENGINE_DEBUG_TOOL_HPP__ 1

// Set default debug log status 
// #define SAULE_ENGINE_DEBUG_LOG

/*
	Debug Log
*/
# define SAULE_ENGINE_INFO_LOG(x) saule_engine_debug_log_call(x, 0)

# define SAULE_ENGINE_WARNING_LOG(x) saule_engine_debug_log_call(x, 1)

# define SAULE_ENGINE_ERROR_LOG(x) saule_engine_debug_log_call(x, -1)

void saule_engine_set_debug_log_status(bool value);
void saule_engine_debug_log_call(const char *msg, int type);

/*
Assert
*/
# include <stdlib.h> // exit()

# define ASSERT(x) if (x) exit(-1);

/*
	OpenGL GL_CALL()
*/
# ifdef SAULE_ENGINE_USE_OPENGL

# include <glad/glad.h>

#  define GL_CALL(x)							\
	GL_clear_error();							\
	x;											\
	ASSERT(GL_log_call(#x, __FILE__, __LINE__))

void GL_clear_error(void);

int GL_log_call(const char *fonction, const char *file, int line);
# endif /* SAULE_ENGINE_USE_OPENGL */

#endif /* __SAULE_ENGINE_DEBUG_TOOL_HPP__ */