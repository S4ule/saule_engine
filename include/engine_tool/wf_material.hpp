#ifndef __WF_MATERIAL_HPP__
# define __WF_MATERIAL_HPP__ 1

# include <map>
# include <string>

# include "engine/object_info/texture.hpp"
# include "engine/object_info/material.hpp"
# include "engine_tool/vector_3.hpp"
# include "saule_engine_define.hpp"

class WF_Material
{
	private:
		std::map<std::string, int (WF_Material::*)(std::string &)>	_function;

	private:
		std::string		_used_material_name;
		std::map<std::string, Material>	_material;
		std::map<std::string, Texture>	_textures;

	public:
		WF_Material();
		~WF_Material();

	public:
		Material *get_material(std::string &name);
		Texture *get_texture(std::string &name);
		void clear(void);

	public:
		int	pars_line(const std::string &f_name, std::string &line);

	public:
		int _pars_new_material(std::string &line);
		int	_pars_texture(std::string &line);
		int	_pars_specular_highlights(std::string &line);
		int	_pars_ambient_color(std::string &line);
		int	_pars_diffuse_color(std::string &line);
		int	_pars_specular_color(std::string &line);
		int	_pars_emissive_color(std::string &line);
		int	_pars_optical_density(std::string &line);
		int	_pars_dissolve(std::string &line);
		int _pars_illumination_model(std::string &line);

	public:
		float		_get_float_in_string(const std::string &str, int &err);
		Vector_3	_get_vector_3_in_string(const std::string &str, int &err);
};

#endif /* __WF_MATERIAL_HPP__ */