#ifndef __SCENE_HPP__
# define __SCENE_HPP__ 1

# include <list>

# include "engine/context_api/window.hpp"
# include "engine/object_info/object_entity.hpp"
# include "engine/camera.hpp"

class Scene
{
	private:
		std::list<Object_entity *>	_object_entity_list;

	public:
		float	delta_time;
		Camera	camera;

	public:
		Scene();
		virtual ~Scene();

	public:
		int add_object_entity(Object_entity &ref);

	public:
		const std::list<Object_entity *> &get_object_entity() const;

	public:
		void call_start(const Window *window);
		void call_update(const Window *window);
};

#endif /* __SCENE_HPP__ */