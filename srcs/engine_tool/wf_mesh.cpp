
#include "engine_tool/wf_mesh.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

WF_Mesh::WF_Mesh()
{
	this->_function["v"] = &WF_Mesh::_pars_geometric_vertices;
	this->_function["vt"] = &WF_Mesh::_pars_texture_vertices;
	this->_function["vn"] = &WF_Mesh::_pars_vertex_normals;
	this->_function["f"] = &WF_Mesh::_pars_face;
	this->_function["o"] = &WF_Mesh::_pars_object_name;
	this->_function["g"] = &WF_Mesh::_pars_group_name;
	this->_function["s"] = &WF_Mesh::_pars_smoothing_group;
	this->_function["bevel"] = &WF_Mesh::_pars_bevel_interpolation;
	this->_function["c_interp"] = &WF_Mesh::_pars_color_interpolation;
	this->_function["d_interp"] = &WF_Mesh::_pars_dissolve_interpolation;
	this->_function["lod"] = &WF_Mesh::_pars_level_of_detail;
	this->_function["usemap"] = &WF_Mesh::_pars_texture_mapping;
	this->_function["shadow_obj"] = &WF_Mesh::_pars_shadow_casting;
	this->_function["trace_obj"] = &WF_Mesh::_pars_ray_tracing;
	return ;
}

WF_Mesh::~WF_Mesh()
{
	return ;
}

const std::vector<float> *
WF_Mesh::get_vertices(const std::string &material_name)
{
	if (this->_vertices.find(material_name) == this->_vertices.end())
	{
		return NULL;
	}
	return &(this->_vertices[material_name]);
}

const std::vector<unsigned int> *
WF_Mesh::get_index(const std::string &material_name)
{
	if (this->_index.find(material_name) == this->_index.end())
	{
		return NULL;
	}
	return &(this->_index[material_name]);
}

const Layout *
WF_Mesh::get_layout(const std::string &material_name)
{
	if (this->_layout.find(material_name) == this->_layout.end())
	{
		return NULL;
	}
	return &(this->_layout[material_name]);
}

const Mesh	*
WF_Mesh::get_mesh(const std::string &material_name)
{
	if (this->_mesh.find(material_name) == this->_mesh.end())
	{
		return NULL;
	}
	return &(this->_mesh[material_name]);
}

const std::string
WF_Mesh::get_material_name(size_t index, int &err)
{
	std::map<std::string, Layout >::iterator it;

	it = this->_layout.begin();
	while (it != this->_layout.end())
	{
		if (index == 0)
		{
			err = 0;
			return it->first;
		}
		index--;
		it++;
	}
	err = -1;
	return "";
}

void
WF_Mesh::clear(void)
{
	this->_vertex.clear();
	this->_normal.clear();
	this->_textures.clear();
	this->_faces.clear();
	this->_vertices.clear();
	this->_index.clear();
	this->_layout.clear();
	this->_mesh.clear();
	this->_name = "";
	return ;
}


int
WF_Mesh::pars_line(const std::string &f_name, std::string &line)
{
	std::map<std::string, int (WF_Mesh::*)(std::string &)>::iterator	it;
	int err;

	it = this->_function.find(f_name);
	if (it == this->_function.end())
	{
		SAULE_ENGINE_WARNING_LOG("unknow/unimplemented element in WF_Mesh is getting ignored:");
		SAULE_ENGINE_WARNING_LOG(f_name.c_str());
		return 1;
	}
	err = (this->*(it->second))(line);
	return err;
}

int
WF_Mesh::set_used_material(const std::string material_name)
{
	this->_used_material_name = material_name;
	return 0;
}

void
WF_Mesh::generate_all_mesh()
{
	std::map<std::string, std::vector<Vector_3> >::iterator it;
	Vector_3	world_position;
	Vector_3	range;
	Vector_3	max;
	Vector_3	min;

	for (size_t i = 0; i < this->_vertex.size(); i++)
	{
		world_position += this->_vertex[i];

		for (size_t j = 0; j < 3; j++)
		{
			if (i == 0 || this->_vertex[i][j] > max[j])
			{
				max[j] = this->_vertex[i][j];
			}
			if (i == 0 || this->_vertex[i][j] < min[j])
			{
				min[j] = this->_vertex[i][j];
			}
		}
	}
	world_position /= Vector_3(this->_vertex.size(), this->_vertex.size(), this->_vertex.size());
	world_position = Vector_3() - world_position;
	// std::cout << world_position << std::endl;

	range = max - min;
	// std::cout << max << std::endl;
	// std::cout << min << std::endl;
	// std::cout << range << std::endl;
	
	for (it = this->_faces.begin(); it != this->_faces.end(); it++)
	{
		this->_generate_mesh(it->first, world_position, max, range);
		this->_mesh[it->first].vertices = &(this->_vertices[it->first]);
		this->_mesh[it->first].index = &(this->_index[it->first]);
		this->_mesh[it->first].layout = &(this->_layout[it->first]);
	}
	this->_vertex.clear();
	this->_normal.clear();
	this->_textures.clear();
	this->_faces.clear();
	return ;
}

void
WF_Mesh::_generate_mesh(const std::string &material_name, Vector_3 world_position, Vector_3 max, Vector_3 range)
{
	for (size_t i = 0; i < this->_faces[material_name].size(); i++)
	{
		Vector_3	position;
		Vector_3	texture_position;
		Vector_3	normal;

		if (this->_faces[material_name][i][0] != 0)
		{
			position = this->_vertex[this->_faces[material_name][i][0] - 1];			
		}
		if (this->_faces[material_name][i][1] != 0)
		{
			texture_position = this->_textures[this->_faces[material_name][i][1] - 1];
		}
		else
		{
			// Create default texture position
			for (size_t j = 0; j < 3; j++)
			{
				if (range[j] != 0)
				{
					texture_position[j] = (max[j] - position[j]) / range[j];
				}
				else
				{
					texture_position[j] = 0;
				}
			}
			// Transform 3d texture position to 2d
			texture_position.x = (texture_position.x + texture_position.z) / 2;
			// texture_position.y = (texture_position.y + texture_position.z) / 2; // probably unwanted effect
			texture_position.z = 0;
		}
		if (this->_faces[material_name][i][2] != 0)
		{
			normal = this->_normal[this->_faces[material_name][i][2] - 1];
		}
		else
		{
			// --TODO--
			// Calculate Default Normal
			// Normal = A cross B

			// normal = ;
		}

		// std::cout << "veterx : " << position << std::endl;
		// std::cout << "texture: " << texture_position << std::endl;
		// std::cout << "normal : " << normal << std::endl;
		position += world_position;
		this->_vertices[material_name].push_back(position.x);
		this->_vertices[material_name].push_back(position.y);
		this->_vertices[material_name].push_back(position.z);
		this->_vertices[material_name].push_back(texture_position.x);
		this->_vertices[material_name].push_back(texture_position.y);
		this->_vertices[material_name].push_back(texture_position.z);
		this->_vertices[material_name].push_back(normal.x);
		this->_vertices[material_name].push_back(normal.y);
		this->_vertices[material_name].push_back(normal.z);
	}
	this->_layout[material_name].clear();
	this->_layout[material_name].add_layout(3, SAULE_ENGINE_FLOAT, sizeof(float), false);
	this->_layout[material_name].add_layout(3, SAULE_ENGINE_FLOAT, sizeof(float), false);
	this->_layout[material_name].add_layout(3, SAULE_ENGINE_FLOAT, sizeof(float), false);
	return ;
}



int
WF_Mesh::_pars_geometric_vertices(std::string &line)
{
	char		*ptr;
	Vector_3	vertex;

	for (int i = 0; i < 3; ++i)
	{
		vertex[i] = strtof(line.c_str(), &ptr);
		if (ptr == line.c_str())
		{
			return -1;
		}
		line.erase(0, ptr - line.c_str());		
	}
	// std::cout << "v " << vertex << std::endl;
	this->_vertex.push_back(vertex);
	return 0;
}

int
WF_Mesh::_pars_texture_vertices(std::string &line)
{
	char		*ptr;
	Vector_3	vertex;

	for (int i = 0; i < 3; ++i)
	{
		vertex[i] = strtof(line.c_str(), &ptr);
		if (ptr == line.c_str() && i != 2)
		{
			// not checking z, can be at default 0
			return -1;
		}
		line.erase(0, ptr - line.c_str());
	}
	// std::cout << "vt " << vertex << std::endl;
	this->_textures.push_back(vertex);
	return 0;
}

int
WF_Mesh::_pars_vertex_normals(std::string &line)
{
	char		*ptr;
	Vector_3	vertex;

	for (int i = 0; i < 3; ++i)
	{
		vertex[i] = strtof(line.c_str(), &ptr);
		if (ptr == line.c_str())
		{
			return -1;
		}
		line.erase(0, ptr - line.c_str());		
	}
	// std::cout << "vn " << vertex << std::endl;
	this->_normal.push_back(vertex);
	return 0;
}


int
WF_Mesh::_get_face_info(std::string &line, Vector_3 &index)
{
	char	*ptr;

	index = Vector_3();
	for (int i = 0; i < 3; ++i)
	{
		index[i] = strtol(line.c_str(), &ptr, 10);
		if (ptr == line.c_str())
		{
			if (i == 0)
			{
				return -1;
			}
			return 0;
		}
		line.erase(0, ptr - line.c_str());
		if (line[0] == '/' && line[1] == '/')
		{
			line.erase(0, 2);
			i++;
			continue ;
		}
		if (line[0] != '/')
		{
			break ;
		}
		line.erase(0, 1);
	}
	return 0;
}

int
WF_Mesh::_pars_face(std::string &line)
{
	Vector_3	face;
	size_t		faces_count;
	size_t		faces_position;
	int			err;

	// Save size for later use
	faces_position = this->_faces[this->_used_material_name].size();

	// Can pars [3, +inf[ values
	while (1)
	{
		face = Vector_3();
		err = this->_get_face_info(line, face);
		if (err != 0)
		{
			break ;
		}
		this->_faces[this->_used_material_name].push_back(face);
	}
	faces_count = this->_faces[this->_used_material_name].size() - faces_position;
	if (faces_count < 3)
	{
		SAULE_ENGINE_ERROR_LOG("WF_Mesh can only create face with at least 3 points");
		return -1;
	}

	for (size_t i = 0; i < faces_count; i++)
	{
		for (size_t param = 0; param < 3; param++)
		{
			int	id;

			id = this->_faces[this->_used_material_name][faces_position + i][param];
			if (id == 0)
			{
				if (param == 0)
				{
					SAULE_ENGINE_ERROR_LOG("WF_Mesh face with no vector");
					return -1;
				}
				// SAULE_ENGINE_WARNING_LOG("WF_Mesh face with no id");
				continue ;
			}

			switch (param)
			{
				case 0: // Possition
				{
					if (id < 0)
					{
						id = this->_vertex.size() + id;
						if (id < 0)
						{
							return -1;
						}
					}
					if ((size_t)id > this->_vertex.size())
					{
						return -1;
					}
					break ;
				}
				case 1: // Texture
				{
					if (id < 0)
					{
						id = this->_textures.size() + id;
						if (id < 0)
						{
							return -1;
						}
					}
					if ((size_t)id > this->_textures.size())
					{
						return -1;
					}
					break ;
				}
				case 2: // Normal
				{
					if (id < 0)
					{
						id = this->_normal.size() + id;
						if (id < 0)
						{
							return -1;
						}
					}
					if ((size_t)id > this->_normal.size())
					{
						return -1;
					}
					break ;
				}
			}
			this->_faces[this->_used_material_name][faces_position + i][param] = id;
		}
		// std::cout << "f " << this->_faces[this->_used_material_name][faces_position + i] << std::endl;
	}

	// face can be define with [3, +inf[ points
	// p0 is a commom point for all faces, every point that follow (p1, p2... pN)
	// Define a face like faces = { [p0, p1, p2], [p0, p2, p3], [p0, p3, p4]... [p0, pN-1, pN] }
	for (size_t i = 1; (i + 1) < faces_count; i++)
	{
		this->_index[this->_used_material_name].push_back(faces_position);
		this->_index[this->_used_material_name].push_back(faces_position + i);
		this->_index[this->_used_material_name].push_back(faces_position + i + 1);
	}
	return 0;
}

int
WF_Mesh::_pars_object_name(std::string &line)
{
	this->_name = line;
	return 0;
}

int
WF_Mesh::_pars_group_name(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("group name is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `g` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_smoothing_group(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("smoothing group is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `s` lines");
		warning_done = true;
	}
	return 0;
}


int
WF_Mesh::_pars_bevel_interpolation(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("bevel interpolation is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `bevel` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_color_interpolation(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("color interpolation is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `c_interp` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_dissolve_interpolation(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("dissolve interpolation is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `d_interp` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_level_of_detail(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("level of detail is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `lod` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_texture_mapping(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("texture mapping is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `usemap` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_shadow_casting(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("shadow casting is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `shadow_obj` lines");
		warning_done = true;
	}
	return 0;
}

int
WF_Mesh::_pars_ray_tracing(std::string &line)
{
	static bool warning_done = false;
	
	(void)line;
	if (warning_done != true)
	{
		SAULE_ENGINE_WARNING_LOG("ray tracing is not implemented in WF_Mesh");
		SAULE_ENGINE_WARNING_LOG("ignoring `trace_obj` lines");
		warning_done = true;
	}
	return 0;
}
