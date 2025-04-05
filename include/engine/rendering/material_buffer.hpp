#ifndef __MATERIAL_BUFFER_HPP__
# define __MATERIAL_BUFFER_HPP__ 1

# include <vector>

# include "engine/object_info/material.hpp"
# include "engine/gpu_api/gpu_texture_buffer.hpp"

class Material_buffer
{
	private:
		GPU_Texture_buffer	_texture_buffer;

	public:
		Material_buffer();
		Material_buffer(const Material *material);
		virtual ~Material_buffer();

	public:
		int setup(const Material *material);

	public:
		int bind() const;
		int unbind() const;
};

#endif /* __MATERIAL_BUFFER_HPP__ */