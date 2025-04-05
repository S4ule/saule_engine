#ifndef __MATERIAL_HPP__
# define __MATERIAL_HPP__ 1

# include <vector>

# include "engine/object_info/texture.hpp"
# include "engine_tool/vector_3.hpp"
# include "saule_engine_define.hpp"

class Material
{
	public:
		size_t	id;

	private:
		static size_t	_total_id;

	public:
		Texture		*texture;

	public:
		float		specular_highlights; 	// Ns
		Vector_3	ambient_color;			// Ka
		Vector_3	diffuse_color;			// Kd
		Vector_3	specular_color;			// Ks
		Vector_3	emissive_color;			// Ke
		float		optical_density;		// Ni
		float		dissolve;				// d

	public:
		Material();
		~Material();

	public:
		void set_texture(Texture &user_texture);
};

#endif /* __MATERIAL_HPP__ */