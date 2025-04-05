#ifndef __BLUEPRINT_BUFFER_HPP__
# define __BLUEPRINT_BUFFER_HPP__ 1

# include <string>
# include <map>
# include <stddef.h>

# include "engine/object_info/blueprint.hpp"
# include "engine/object_info/object.hpp"
# include "engine/rendering/mesh_buffer.hpp"
# include "engine/rendering/material_buffer.hpp"
# include "engine/rendering/shader_buffer.hpp"
# include "engine_tool/vector_2.hpp"
# include "engine_tool/vector_3.hpp"
# include "engine_tool/vector_4.hpp"

class Blueprint_buffer
{
	private:
		static std::map<size_t, Mesh_buffer *>		_mesh_buffer;		// size_t = id
		static std::map<size_t, Material_buffer *>	_material_buffer;	// size_t = id
		static std::map<size_t, Shader_buffer *>	_shader_buffer;		// size_t = id

	private:
		size_t	_mesh_id;
		size_t	_material_id;
		size_t	_shader_id;

	public:
		const Object	*ref_object;
		const Blueprint	*ref_blueprint;

	public:
		Blueprint_buffer();
		Blueprint_buffer(const Blueprint &blueprint);
		~Blueprint_buffer();

	public:
		int	setup(const Blueprint &blueprint);

	public:
		int add_uniform_float(const std::string &name, const float &data);
		int add_uniform_float(const std::string &name, const Vector_2 &data);
		int add_uniform_float(const std::string &name, const Vector_3 &data);
		int add_uniform_float(const std::string &name, const Vector_4 &data);
		int add_uniform_int(const std::string &name, const int &data);

	public:
		int		bind() const;
		int		unbind() const;
		size_t	count() const;

	public:
		static void clean();
};

#endif /* __BLUEPRINT_BUFFER_HPP__ */