
#include "saule_engine.hpp"
#include "saule_engine_tool.hpp"
#include <iostream>
#include <ostream>

class Test_object : public Object_entity
{
public:
	Test_object() : Object_entity() { }

	~Test_object() { }

public:
	void
	start(const Window *window, Scene &scene)
	{
		(void)window;
		scene.camera.position = Vector_3(-5.0f, 0.0f, 0.0f);
		scene.camera.rotation = Vector_4(0.0f, 1.0f, 0.0f, 270.0f);
		this->object.transform.rotation = Vector_4(0.0f, 1.0f, 0.0f, 0.0f);
		return ;
	}

	void
	update(const Window *window, Scene &scene)
	{
		if (window == NULL)
		{
			return ;
		}
		
		if (window->key_is_press(SAULE_ENGINE_KEY_ESCAPE) == true)
		{
			window->set_should_close(true);
			return ;
		}

		Vector_3	movement;
		Vector_4	rotation;
		
		scene.camera.update_direction_vector();
		if (window->key_is_press(SAULE_ENGINE_KEY_W) == true)
		{
			movement += scene.camera.front * 5.0f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_S) == true)
		{
			movement -= scene.camera.front * 5.0f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_D) == true)
		{
			movement += scene.camera.right * 5.0f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_A) == true)
		{
			movement -= scene.camera.right * 5.0f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_SPACE) == true)
		{
			movement += scene.camera.up * 5.0f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_LEFT_SHIFT) == true)
		{
			movement -= scene.camera.up * 5.0f * scene.delta_time;
		}

		if (window->key_is_press(SAULE_ENGINE_KEY_Q) == true)
		{
			rotation += Vector_4(0.0f, 0.0f, 0.0f, 1.0f) * 50.5f * scene.delta_time;
		}
		if (window->key_is_press(SAULE_ENGINE_KEY_E) == true)
		{
			rotation += Vector_4(0.0f, 0.0f, 0.0f, -1.0f) * 50.5f * scene.delta_time;
		}
		scene.camera.position += movement;
		scene.camera.rotation += rotation;

		this->object.transform.rotation += Vector_4(0.0f, 0.0f, 0.0f, 1.0f) * 50.5f * scene.delta_time;
		return ;
	}
};

int
main(void)
{
	int err;

	/*
		Ativate Debug Log
	*/
	saule_engine_enable(SAULE_ENGINE_DEBUG_LOG);

	/*
		Seting up the engine
	*/
	App	app;

	app.setup();
	app.open("test", 1200, 800);

	/*
		Import Shader
	*/
	Shader	shader;

	shader.import_file("./res/shaders/vert_shader.glsl", SAULE_ENGINE_VERTEX_SHADER);
	shader.import_file("./res/shaders/frag_shader.glsl", SAULE_ENGINE_FRAGMENT_SHADER);

	/*
		Import Object
	*/
	Test_object	o_entity;
	WF_Object	wf_object;

	err = wf_object.import_file("./res/objects/42.obj");
	if (err != 0)
	{
		app.close();
		return -1;
	}
	o_entity.object.set_with_WF_object(wf_object);
	o_entity.object.set_object_shader(shader);

	// o_entity.object.transform.scale = Vector_3(0.1f, 0.1f, 0.1f);
	// o_entity.object.transform.position = Vector_3(10.0f, 10.0f, 10.0f);

	/*
		Add Entity to the Scene
	*/
	Scene	scene;

	scene.add_object_entity(o_entity);
	scene.camera.fov = 90.0f;
	
	/*
		Rendering Loop
	*/
	app.use_scene(scene);
	// app.renderer.disable_depth_testing();
	app.draw_loop();
	app.close();
	return 0;
}