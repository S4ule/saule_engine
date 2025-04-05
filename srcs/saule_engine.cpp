
#include "saule_engine_define.hpp"
#include "saule_engine_debug_tool.hpp"

void saule_engine_enable(int value)
{
	if ( (SAULE_ENGINE_DEBUG_LOG & value) == SAULE_ENGINE_DEBUG_LOG)
	{
		saule_engine_set_debug_log_status(true);
	}
	return ;
}

void saule_engine_disable(int value)
{
	if ( (SAULE_ENGINE_DEBUG_LOG & value) == SAULE_ENGINE_DEBUG_LOG)
	{
		saule_engine_set_debug_log_status(false);
	}
	return ;
}
