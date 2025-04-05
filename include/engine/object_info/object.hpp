#ifndef __OBJECT_HPP__
# define __OBJECT_HPP__ 1

# include <vector>

# include "engine/object_info/blueprint.hpp"
# include "engine/object_info/transform.hpp"
# include "engine_tool/wf_object.hpp"

class Object
{
	public:
		std::vector<Blueprint *>	blueprint_vector;
		Transform					transform;

	public:
		Object();
		Object(const Object &ref);
		Object &operator=(const Object &ref);
		virtual ~Object();

	public:
		void add_blueprint(Blueprint &user_blueprint);

	public:
		void set_with_WF_object(WF_Object &wf_object);
		void set_object_shader(const Shader &user_shader);
};

#endif /* __OBJECT_HPP__ */