#ifndef __OBJECT_ENTITY_HPP__
# define __OBJECT_ENTITY_HPP__ 1

# include "engine/object_info/object.hpp"
# include "engine/scene.hpp"
# include "engine/context_api/window.hpp"

class Scene;

class Object_entity
{
	public:
		Object object;

	public:
		Object_entity() { return ; };
		virtual ~Object_entity() { return ; };

	public:
		// virtual int awake(const Window &window, const Scene &scene) { (void)window; (void)scene; return ; }

		virtual void start(const Window *window, Scene &scene)
		{ (void)window; (void)scene; return ; }
		virtual void update(const Window *window, Scene &scene)
		{ (void)window; (void)scene; return ; }
};

#endif /* __OBJECT_ENTITY_HPP__ */