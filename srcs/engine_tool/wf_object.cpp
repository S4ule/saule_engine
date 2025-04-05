
#include "engine_tool/wf_object.hpp"

WF_Object::WF_Object()
{
	return ;
}

WF_Object::~WF_Object()
{
	return ;
}

int
WF_Object::import_file(const std::string &file_path)
{
	File	mesh_file;
	int		err;

	this->clear();
	SAULE_ENGINE_INFO_LOG("import WF_Object file:");
	SAULE_ENGINE_INFO_LOG(file_path.c_str());
	err = mesh_file.open_file(file_path);
	if (err == -1)
	{
		SAULE_ENGINE_ERROR_LOG("can't open WF_Object file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	err = this->_pars_mesh_file(mesh_file);
	mesh_file.close_file();
	return err;
}

std::vector<Blueprint *> 
WF_Object::get_blueprint_vector()
{
	return this->_blueprint_vector;
}

void
WF_Object::clear(void)
{
	this->_wf_mesh.clear();
	this->_wf_material.clear();
	this->_blueprint_vector.clear();
	return ;
}

int
WF_Object::_generate_blueprint_vector()
{
	size_t		index;
	int			err;
	std::string	material_name;

	index = 0;
	material_name = this->_wf_mesh.get_material_name(index, err);
	while (err == 0)
	{
		Blueprint *blueprint;

		blueprint = new Blueprint;
		if (blueprint == NULL)
		{
			return -1;
		}
		blueprint->mesh = this->_wf_mesh.get_mesh(material_name);
		blueprint->material = this->_wf_material.get_material(material_name);
		blueprint->shader = NULL;
		this->_blueprint_vector.push_back(blueprint);
		index++;
		material_name = this->_wf_mesh.get_material_name(index, err);
	}
	return 0;
}

int
WF_Object::_pars_mesh_file(File &file)
{
	std::string	err_line;
	std::string	line;
	std::string	f_name;
	size_t		offset;
	size_t		line_n;
	size_t		find_pos;
	int			err;

	line_n = 0;
	offset = 0;
	while (offset != file.size())
	{
		line_n++;

		file.get_next_line(line, offset);

		// Remove space and comment
		find_pos = 0;
		while (isspace(line[find_pos]) != 0)
		{
			find_pos++;
		}
		line.erase(0, find_pos);
		find_pos = line.find('#');
		if (find_pos != std::string::npos)
		{
			line.erase(find_pos);
		}
		if (line[0] == '\0')
		{
			continue ;
		}
		// std::cout << line << ":" << line_n << std::endl;

		// find the first part of the string to know the element
		find_pos = line.find(' ');
		if (find_pos == std::string::npos)
		{
			err_line = "`" + line + "`";
			SAULE_ENGINE_ERROR_LOG("in WF_Object file:");
			SAULE_ENGINE_ERROR_LOG(file.get_file_path().c_str());
			SAULE_ENGINE_ERROR_LOG(err_line.c_str());
			this->clear();
			return -1;
		}

		
		err_line = line;
		f_name = line.substr(0, find_pos);
		line.erase(0, find_pos + 1);
		if (f_name == "mtllib")
		{
			// Get .mtl file path
			find_pos = file.get_file_path().rfind("/");
			if (find_pos == std::string::npos)
			{
				line = file.get_file_path().substr(0, file.get_file_path().size()) + line;
			}
			else
			{
				line = file.get_file_path().substr(0, find_pos + 1) + line;
			}
			err = this->_open_material_file(line);
			if (err != 0)
			{
				SAULE_ENGINE_ERROR_LOG("import in WF_Object file:");
				SAULE_ENGINE_ERROR_LOG(file.get_file_path().c_str());
				SAULE_ENGINE_ERROR_LOG(err_line.c_str());
				SAULE_ENGINE_WARNING_LOG("catching WF_Material error");
				SAULE_ENGINE_WARNING_LOG("keeping up with default material");
			}
		}
		else if (f_name == "usemtl")
		{
			this->_wf_mesh.set_used_material(line);
		}
		else
		{
			err = this->_wf_mesh.pars_line(f_name, line);
			if (err < 0)
			{
				err_line = "`" + err_line + "`";
				SAULE_ENGINE_ERROR_LOG("in WF_Object file:");
				SAULE_ENGINE_ERROR_LOG(file.get_file_path().c_str());
				SAULE_ENGINE_ERROR_LOG(err_line.c_str());
				this->clear();
				return -1;
			}
		}
	}
	this->_wf_mesh.generate_all_mesh();
	this->_generate_blueprint_vector();
	return 0;
}


int
WF_Object::_open_material_file(const std::string &file_path)
{
	File	material_file;
	int		err;

	SAULE_ENGINE_INFO_LOG("import WF_Material file:");
	SAULE_ENGINE_INFO_LOG(file_path.c_str());
	err = material_file.open_file(file_path);
	if (err == -1)
	{
		SAULE_ENGINE_ERROR_LOG("can't open WF_Material file:");
		SAULE_ENGINE_ERROR_LOG(file_path.c_str());
		return -1;
	}
	err = this->_pars_material_file(material_file);
	material_file.close_file();
	return err;
}

int
WF_Object::_pars_material_file(File &file)
{
	std::string	err_line;
	std::string	line;
	std::string	f_name;
	size_t		offset;
	size_t		line_n;
	size_t		find_pos;
	int			err;

	line_n = 0;
	offset = 0;
	while (offset != file.size())
	{
		line_n++;

		file.get_next_line(line, offset);

		// Remove space and comment
		find_pos = 0;
		while (isspace(line[find_pos]) != 0)
		{
			find_pos++;
		}
		line.erase(0, find_pos);
		find_pos = line.find('#');
		if (find_pos != std::string::npos)
		{
			line.erase(find_pos);
		}
		if (line[0] == '\0')
		{
			continue ;
		}
		// std::cout << line << ":" << line_n << std::endl;

		// find the first part of the string to know the element
		find_pos = line.find(' ');
		if (find_pos == std::string::npos)
		{
			err_line = "`" + line + "`";
			SAULE_ENGINE_ERROR_LOG("in WF_Material file:");
			SAULE_ENGINE_ERROR_LOG(file.get_file_path().c_str());
			SAULE_ENGINE_ERROR_LOG(err_line.c_str());
			this->clear();
			return -1;
		}

		err_line = line;
		f_name = line.substr(0, find_pos);
		line.erase(0, find_pos + 1);

		err = this->_wf_material.pars_line(f_name, line);
		if (err < 0)
		{
			err_line = "`" + err_line + "`";
			SAULE_ENGINE_ERROR_LOG("in WF_Material file:");
			SAULE_ENGINE_ERROR_LOG(file.get_file_path().c_str());
			SAULE_ENGINE_ERROR_LOG(err_line.c_str());
			this->clear();
			return -1;
		}
	}
	return 0;
}