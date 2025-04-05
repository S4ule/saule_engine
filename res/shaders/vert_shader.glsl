#version 330 core

#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 tex_coord;
layout (location = 2) in vec3 normal;

/*
	Move a camera backwards, is the same as moving the entire scene forward.
*/
uniform vec3 f3_position;
uniform vec4 f4_rotation;
uniform vec3 f3_scale;

uniform vec3 f3_camera_position;
uniform vec4 f4_camera_rotation;
uniform float f1_fov;

out vec3 v_model_position;
out vec3 v_view_position;
out vec3 v_clip_position;
out vec3 v_norm;
out vec3 v_text;

vec3 rotate(vec3 position, vec4 v4_rotate)
{
	// cos(θ) + Rx^2 * (1 - cos(θ))			|	Rx * Ry * (1 - cos(θ)) - Rz * sin(θ)	|	Rx * Rz * (1 - cos(θ)) + Ry * sin(θ)
	// Ry * Rx * (1 - cos(θ)) + Rz * sin(θ)	|	cos(θ) + Ry^2 * (1 - cos(θ))			|	Ry * Rz * (1 - cos(θ)) - Rx * sin(θ)
	// Rz * Rx * (1 - cos(θ)) - Ry * sin(θ)	|	Rz * Ry * (1 - cos(θ)) + Rx * sin(θ)	|	cos(θ) + Rz^2 * (1 - cos(θ))

	float	cos_angle;
	float	sin_angle;
	float	one_minus_cos;
	float	rx_time_sin;
	float	ry_time_sin;
	float	rz_time_sin;
	float	rx_time_ry;
	float	rx_time_rz;
	float	ry_time_rz;
	float	x_buf;
	float	y_buf;
	float	z_buf;
	float	angle_in_radians = v4_rotate.w * (M_PI / 180);

	cos_angle = cos(angle_in_radians);
	sin_angle = sin(angle_in_radians);
	one_minus_cos = 1 - cos_angle;
	rx_time_sin = v4_rotate.x * sin_angle;
	ry_time_sin = v4_rotate.y * sin_angle;
	rz_time_sin = v4_rotate.z * sin_angle;
	rx_time_ry = v4_rotate.x * v4_rotate.y;
	rx_time_rz = v4_rotate.x * v4_rotate.z;
	ry_time_rz = v4_rotate.y * v4_rotate.z;

	x_buf = position.x * (cos_angle + v4_rotate.x * v4_rotate.x * one_minus_cos) +	\
			position.y * (rx_time_ry * one_minus_cos - rz_time_sin) +				\
			position.z * (rx_time_rz * one_minus_cos + ry_time_sin);

	y_buf = position.x * (rx_time_ry * one_minus_cos + rz_time_sin) +				\
			position.y * (cos_angle + v4_rotate.y * v4_rotate.y * one_minus_cos) +	\
			position.z * (ry_time_rz * one_minus_cos - rx_time_sin);

	z_buf = position.x * (rx_time_rz * one_minus_cos - ry_time_sin) +				\
			position.y * (ry_time_rz * one_minus_cos + rx_time_sin) +				\
			position.z * (cos_angle + v4_rotate.z * v4_rotate.z * one_minus_cos);

	return vec3(x_buf, y_buf, z_buf);
}

void main()
{
	v_text = tex_coord;

	// Set object vertex
	v_model_position = vec3(vertex.x, vertex.y, vertex.z);

	// Model Position
	// Scale, Rotate, Move
	v_model_position = v_model_position * f3_scale; // scale
	v_model_position = rotate(v_model_position, f4_rotation);
	//v_norm = rotate(normal, f4_rotation);
	v_norm = normal;
	v_model_position = v_model_position + f3_position;

	// View Position
	// Move a camera backwards, is the same as moving the entire scene forward.
	// Rotate the camera right, is the same as rotating the entire scene left.

	/*
		Rx Ry Rz 0
		Ux Uy Uz 0
		Dx Dy Dz 0
		-Px -Py -Pz 1
	*/
	vec3 camera_direction = v_model_position - f3_camera_position; // vector to model
	camera_direction = rotate(camera_direction, f4_camera_rotation); // rotate this vetor
	v_view_position = camera_direction;


	// Clip Position
	// Use FoV to Make Perspective
	/*
		Find near distance :
		1 = `const` for the plane size
		near = 1 / tan(FoV/2)

		Find clip position :
		near / x' = (z + n) / x
		x' = (x * near) / (z + near)
	*/

	float near = 1 / tanh(f1_fov / 2);
	v_clip_position.x = (v_view_position.x * near) / abs((v_view_position.z + near));
	v_clip_position.y = (v_view_position.y * near) / abs((v_view_position.z + near));
	v_clip_position.z = (v_view_position.z * near) / abs((v_view_position.z + near));

	gl_Position = vec4(v_clip_position, 1.0f);
}