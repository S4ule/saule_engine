#ifndef __GPU_TEXTURE_BUFFER_HPP__
# define __GPU_TEXTURE_BUFFER_HPP__ 1

# include <glad/glad.h>
# include <stddef.h>

# include "engine/object_info/material.hpp"
# include "saule_engine_debug_tool.hpp"

class GPU_Texture_buffer
{
	private:
		unsigned int	_id;
		unsigned int	_slot;
		bool			_is_create;

	public:
		GPU_Texture_buffer();
		GPU_Texture_buffer(const Material *material);
		~GPU_Texture_buffer();

	public:
		int		setup(const Material *material);

	public:
		void	set_slot(unsigned int slot);
		void	bind(void) const;
		void	unbind(void) const;
		
	public:
		unsigned int slot(void) const;
};

#endif /* __GPU_TEXTURE_BUFFER_HPP__ */