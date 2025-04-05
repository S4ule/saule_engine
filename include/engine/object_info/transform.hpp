#ifndef __TRANSFORM_HPP__
# define __TRANSFORM_HPP__ 1

# include "engine_tool/vector_3.hpp"
# include "engine_tool/vector_4.hpp"

class Transform
{
	public:
		Vector_3	position;
		Vector_4	rotation;
		Vector_3	scale;

	public:
		Transform();
		Transform(const Transform &ref);
		Transform &operator=(const Transform &ref);
		virtual ~Transform();

	// public:

};

#endif /* __TRANSFORM_HPP__ */