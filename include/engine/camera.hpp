#ifndef __CAMERA_HPP__
# define __CAMERA_HPP__ 1

# include "engine_tool/vector_3.hpp"
# include "engine_tool/vector_4.hpp"

class Camera
{
	public:
		Vector_3	front;
		Vector_3	right;
		Vector_3	up;

		Vector_3	position;
		Vector_4	rotation;
		float		fov;

	public:
		Camera();
		~Camera();

	public:
		int update_direction_vector();
};

#endif /* __CAMERA_HPP__ */