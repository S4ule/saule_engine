
#include "engine_tool/wf_material.hpp"

WF_Material::WF_Material()
{
	this->_function["newmtl"] = &WF_Material::_pars_new_material;
	this->_function["map_Kd"] = &WF_Material::_pars_texture;
	this->_function["Ns"] = &WF_Material::_pars_specular_highlights;
	this->_function["Ka"] = &WF_Material::_pars_ambient_color;
	this->_function["Kd"] = &WF_Material::_pars_diffuse_color;
	this->_function["Ks"] = &WF_Material::_pars_specular_color;
	this->_function["Ke"] = &WF_Material::_pars_emissive_color;
	this->_function["Ni"] = &WF_Material::_pars_optical_density;
	this->_function["d"] = &WF_Material::_pars_dissolve;
	this->_function["illum"] = &WF_Material::_pars_illumination_model;
	return ;
}

WF_Material::~WF_Material()
{
	return ;
}

Material *
WF_Material::get_material(std::string &name)
{
	// Use default material if it don't exist
	return &this->_material[name];
}

Texture *
WF_Material::get_texture(std::string &name)
{
	if (this->_textures.find(name) == this->_textures.end())
	{
		return NULL;
	}
	return &(this->_textures[name]);
}

void
WF_Material::clear(void)
{
	this->_used_material_name = "";
	this->_material.clear();
	this->_textures.clear();
	return ;
}

int
WF_Material::pars_line(const std::string &f_name, std::string &line)
{
	std::map<std::string, int (WF_Material::*)(std::string &)>::iterator	it;
	int err;

	it = this->_function.find(f_name);
	if (it == this->_function.end())
	{
		SAULE_ENGINE_WARNING_LOG("unknow/unimplemented element in WF_Material is getting ignored:");
		SAULE_ENGINE_WARNING_LOG(f_name.c_str());
		return 1;
	}
	err = (this->*(it->second))(line);
	return err;
}

int
WF_Material::_pars_new_material(std::string &line)
{
	this->_used_material_name = line;
	return 0;
}

int
WF_Material::_pars_texture(std::string &line)
{
	int err;

	err = this->_textures[this->_used_material_name].import_file(line);
	if (err != 0)
	{
		return err;
	}
	this->_material[this->_used_material_name].texture = &(this->_textures[this->_used_material_name]);
	return 0;
}

int
WF_Material::_pars_specular_highlights(std::string &line)
{
	int	err;

	this->_material[this->_used_material_name].specular_highlights = this->_get_float_in_string(line, err);
	return err;
}

int
WF_Material::_pars_ambient_color(std::string &line)
{
	int err;

	this->_material[this->_used_material_name].ambient_color = this->_get_vector_3_in_string(line, err);
	return err;
}

int
WF_Material::_pars_diffuse_color(std::string &line)
{
	int err;

	this->_material[this->_used_material_name].diffuse_color = this->_get_vector_3_in_string(line, err);
	return err;
}

int
WF_Material::_pars_specular_color(std::string &line)
{
	int err;

	this->_material[this->_used_material_name].specular_color = this->_get_vector_3_in_string(line, err);
	return err;
}

int
WF_Material::_pars_emissive_color(std::string &line)
{
	int err;

	this->_material[this->_used_material_name].emissive_color = this->_get_vector_3_in_string(line, err);
	return err;
}

int
WF_Material::_pars_optical_density(std::string &line)
{
	int	err;

	this->_material[this->_used_material_name].specular_highlights = this->_get_float_in_string(line, err);
	return err;
}

int
WF_Material::_pars_dissolve(std::string &line)
{
	int	err;

	this->_material[this->_used_material_name].specular_highlights = this->_get_float_in_string(line, err);
	return err;
}

int
WF_Material::_pars_illumination_model(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("illumination model is not implemented in WF_Material");
		SAULE_ENGINE_WARNING_LOG("ignoring `illum` lines");
		warning_done = true;
	}
	return 0;
}

float
WF_Material::_get_float_in_string(const std::string &str, int &err)
{
	char	*ptr;
	float	res;

	res = strtof(str.c_str(), &ptr);
	if (ptr == str.c_str())
	{
		err = -1;
		return 0.0f;
	}
	err = 0;
	return res;
}

Vector_3
WF_Material::_get_vector_3_in_string(const std::string &str, int &err)
{
	std::string	line;
	char		*ptr;
	Vector_3	res;

	line = str;
	for (int i = 0; i < 3; ++i)
	{
		res[i] = strtof(line.c_str(), &ptr);
		if (ptr == line.c_str())
		{
			err = -1;
			return res;
		}
		line.erase(0, ptr - line.c_str());
	}
	err = 0;
	return res;
}