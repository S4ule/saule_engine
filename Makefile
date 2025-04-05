
SRCS	=	glad/glad.cpp\
			stbi/stb_image.cpp\
			engine/app.cpp\
			engine/scene.cpp\
			engine/camera.cpp\
			engine/rendering/renderer.cpp\
			engine/rendering/draw_queue.cpp\
			engine/rendering/blueprint_buffer.cpp\
			engine/rendering/mesh_buffer.cpp\
			engine/rendering/material_buffer.cpp\
			engine/rendering/shader_buffer.cpp\
			engine/gpu_api/gpu_draw_context.cpp\
			engine/gpu_api/gpu_vertex_buffer.cpp\
			engine/gpu_api/gpu_vertex_index_buffer.cpp\
			engine/gpu_api/gpu_program_buffer.cpp\
			engine/gpu_api/gpu_shader_buffer.cpp\
			engine/gpu_api/gpu_texture_buffer.cpp\
			engine/context_api/window.cpp\
			engine/object_info/object.cpp\
			engine/object_info/blueprint.cpp\
			engine/object_info/mesh.cpp\
			engine/object_info/layout.cpp\
			engine/object_info/transform.cpp\
			engine/object_info/material.cpp\
			engine/object_info/shader.cpp\
			engine/object_info/texture.cpp\
			engine_tool/vector_2.cpp\
			engine_tool/vector_3.cpp\
			engine_tool/vector_4.cpp\
			engine_tool/wf_object.cpp\
			engine_tool/wf_mesh.cpp\
			engine_tool/wf_material.cpp\
			engine_tool/file.cpp\
			saule_engine.cpp\
			saule_engine_debug_tool.cpp\
			main.cpp

#---------------------------
CC		=	c++
NAME	=	scop
#NAME	=	saule_engine.a
LIBS    =   -lglfw3 -lGL -lX11 -lXrandr -lXi
INCLUDE =	-I ./include
CFLAGS	=	-std=c++98 -g3 -Wall -Wextra -Werror -D SAULE_ENGINE_USE_OPENGL
#---------------------------
SRC_DIR	=	./srcs
OBJ_DIR	=	./.objs
OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
#---------------------------

default:
	make all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir "$(OBJ_DIR)/glad"
	mkdir "$(OBJ_DIR)/stbi"
	mkdir "$(OBJ_DIR)/engine"
	mkdir "$(OBJ_DIR)/engine/gpu_api"
	mkdir "$(OBJ_DIR)/engine/context_api"
	mkdir "$(OBJ_DIR)/engine_tool"
	mkdir "$(OBJ_DIR)/engine/rendering"
	mkdir "$(OBJ_DIR)/engine/object_info"

$(NAME): $(OBJ_DIR) $(OBJS)
#	ar rc $(NAME) $(OBJS)
#	ranlib $(NAME)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(INCLUDE) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJS)
	rm -Rf $(OBJ_DIR)

fclean:		clean
	rm -f $(NAME)

re:
	make fclean
	make all

#test:
#	gcc $(CFLAGS) ./srcs/main.cpp $(LIBS) $(INCLUDE) -o test

.PHONY:	default all clean fclean re
