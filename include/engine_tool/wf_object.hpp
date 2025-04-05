#ifndef __WF_OBJECT_HPP__
# define __WF_OBJECT_HPP__ 1

# include <string>

# include "engine/object_info/blueprint.hpp"
# include "engine_tool/file.hpp"
# include "engine_tool/wf_mesh.hpp"
# include "engine_tool/wf_material.hpp"
# include "saule_engine_debug_tool.hpp"

class WF_Object
{
	private:
		WF_Mesh		_wf_mesh;
		WF_Material	_wf_material;

	private:
		std::vector<Blueprint *> _blueprint_vector;

	public:
		WF_Object();
		~WF_Object();

	public:
		int	import_file(const std::string &file_path);
		std::vector<Blueprint *> get_blueprint_vector();
		void clear(void);

	private:
		int _generate_blueprint_vector();

	private:
		int	_pars_mesh_file(File &file);
		int	_pars_material_file(File &file);
		int	_open_material_file(const std::string &file_path);
};

#endif /* __WF_OBJECT_HPP__ */