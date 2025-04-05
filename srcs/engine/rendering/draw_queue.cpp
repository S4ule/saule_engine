
#include "engine/rendering/draw_queue.hpp"

Draw_queue::Draw_queue()
{
	return ;
}

Draw_queue::~Draw_queue()
{
	return ;
}



int
Draw_queue::add(const Object *object)
{
	if (object == NULL)
	{
		// Nothing to render
		return 0;
	}
	int err;

	for (size_t i = 0; i < object->blueprint_vector.size(); i++)
	{
		// Mb set default material
		// if (object->blueprint_vector[i]->material == NULL)
		
		Blueprint_buffer *blueprint_buffer;

		blueprint_buffer = new Blueprint_buffer;
		if (blueprint_buffer == NULL)
		{
			SAULE_ENGINE_ERROR_LOG("Fail to create Blueprint_buffer");
			return -1;
		}

		err = blueprint_buffer->setup(*((object->blueprint_vector)[i]));
		if (err != 0)
		{
			SAULE_ENGINE_ERROR_LOG("Fail to create Blueprint_buffer");
			delete blueprint_buffer;
			continue ;
		}
		blueprint_buffer->ref_object = object;
		blueprint_buffer->ref_blueprint = (object->blueprint_vector)[i];

		this->_draw_queue.push(blueprint_buffer);
	}
	return 0;
}

/*

*/

int
Draw_queue::draw(GPU_Draw_context &draw_context, const Camera *camera)
{
	if (camera == NULL)
	{
		// Nothing to render
		return 0;
	}

	Blueprint_buffer *blueprint_buffer = this->_draw_queue.front();

	if (blueprint_buffer == NULL)
	{
		return -1;
	}
	blueprint_buffer->bind();
	this->_setup_bueprint_buffer_uniform(blueprint_buffer, camera);
	draw_context.draw_triangle(blueprint_buffer->count());
	blueprint_buffer->unbind();

	delete blueprint_buffer;
	this->_draw_queue.pop();
	return 0;
}

int
Draw_queue::draw_all(GPU_Draw_context &draw_context, const Camera *camera)
{
	if (camera == NULL)
	{
		// Nothing to render
		return 0;
	}

	Blueprint_buffer *blueprint_buffer;

	while (this->_draw_queue.empty() == false)
	{
		blueprint_buffer = this->_draw_queue.front();

		blueprint_buffer->bind();
		this->_setup_bueprint_buffer_uniform(blueprint_buffer, camera);
		draw_context.draw_triangle(blueprint_buffer->count());
		blueprint_buffer->unbind();

		delete blueprint_buffer;
		this->_draw_queue.pop();
	}
	return 0;
}

void
Draw_queue::clean()
{
	Blueprint_buffer::clean();
	return ;
}

void
Draw_queue::_setup_bueprint_buffer_uniform(Blueprint_buffer *blueprint_buffer, const Camera *camera)
{
	// Transformation info
	blueprint_buffer->add_uniform_float("f3_position", blueprint_buffer->ref_object->transform.position);
	blueprint_buffer->add_uniform_float("f4_rotation", blueprint_buffer->ref_object->transform.rotation);
	blueprint_buffer->add_uniform_float("f3_scale", blueprint_buffer->ref_object->transform.scale);
	blueprint_buffer->add_uniform_float("f3_camera_position", camera->position);
	blueprint_buffer->add_uniform_float("f4_camera_rotation", camera->rotation);
	blueprint_buffer->add_uniform_float("f1_fov", camera->fov);

	// Color/Texture info
	blueprint_buffer->add_uniform_int("texture_2d", 0);
	blueprint_buffer->add_uniform_float("f3_ambient_color", blueprint_buffer->ref_blueprint->material->ambient_color);
	blueprint_buffer->add_uniform_float("f3_diffuse_color", blueprint_buffer->ref_blueprint->material->diffuse_color);
	blueprint_buffer->add_uniform_float("f3_specular_color", blueprint_buffer->ref_blueprint->material->specular_color);
	blueprint_buffer->add_uniform_float("f1_specular_highlights", blueprint_buffer->ref_blueprint->material->specular_highlights);
	if (blueprint_buffer->ref_blueprint->material->texture != NULL)
	{
		blueprint_buffer->add_uniform_float("f1_used_texture", 1.0f);
	}
	else
	{
		blueprint_buffer->add_uniform_float("f1_use_texture", 0.0f);
	}
	

	// Light info
	// blueprint_buffer->add_uniform_float("f3_light_pos", Vector_3(5.0f, 5.0f, 5.0f));
	// blueprint_buffer->add_uniform_float("f3_light_color", Vector_3(1.0f, 1.0f, 1.0f));
	return ;
}