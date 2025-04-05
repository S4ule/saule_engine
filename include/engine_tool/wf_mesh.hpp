#ifndef __WF_MESH_HPP__
# define __WF_MESH_HPP__ 1

# include <vector>
# include <string>
# include <map>
# include <stddef.h>

# include "engine/object_info/layout.hpp"
# include "engine/object_info/mesh.hpp"
# include "engine_tool/file.hpp"
# include "engine_tool/vector_2.hpp"
# include "engine_tool/vector_3.hpp"
# include "engine_tool/vector_4.hpp"
# include "saule_engine_debug_tool.hpp"
# include "saule_engine_define.hpp"

class Mesh;

class WF_Mesh
{
	private:
		std::map<std::string, int (WF_Mesh::*)(std::string &)>	_function;

	private:
		std::string		_name;
		std::string		_used_material_name;

	private:
		std::vector<Vector_3>		_vertex;
		std::vector<Vector_3>		_normal;
		std::vector<Vector_3>		_textures;
		std::map<std::string, std::vector<Vector_3> >	_faces;

	private:
		std::map<std::string, std::vector<float> >			_vertices;
		std::map<std::string, std::vector<unsigned int> >	_index;
		std::map<std::string, Layout>						_layout;

	private:
		std::map<std::string, Mesh>	_mesh;

	public:
		WF_Mesh();
		virtual ~WF_Mesh();

	public:
		const std::vector<float> *get_vertices(const std::string &material_name);
		const std::vector<unsigned int> *get_index(const std::string &material_name);
		const Layout *get_layout(const std::string &material_name);
		const Mesh	*get_mesh(const std::string &material_name);
		const std::string get_material_name(size_t index, int &err);

	public:
		int		pars_line(const std::string &f_name, std::string &line);
		int		set_used_material(const std::string material_name);
		void	generate_all_mesh();
		void	clear(void);

	private:
		void _generate_mesh(const std::string &material_name, Vector_3 world_position, Vector_3 max, Vector_3 range);

	private:
		/*
			Vertex data
		*/
		int _pars_geometric_vertices(std::string &line);
		int _pars_texture_vertices(std::string &line);
		int _pars_vertex_normals(std::string &line);

	private:
		/*
			Elements
		*/
		int _pars_face(std::string &line);
		int _get_face_info(std::string &line, Vector_3 &index);

	private:
		/*
			Grouping
		*/
		int	_pars_object_name(std::string &line);
		int	_pars_group_name(std::string &line);
		int	_pars_smoothing_group(std::string &line);

	private:
		/*
			Display/render attributes
		*/
		int	_pars_bevel_interpolation(std::string &line);
		int	_pars_color_interpolation(std::string &line);
		int	_pars_dissolve_interpolation(std::string &line);
		int	_pars_level_of_detail(std::string &line);
		int	_pars_texture_mapping(std::string &line);
		int	_pars_shadow_casting(std::string &line);
		int	_pars_ray_tracing(std::string &line);
};

#endif /* __WAVEFRONT_OBJECT_HPP__ */