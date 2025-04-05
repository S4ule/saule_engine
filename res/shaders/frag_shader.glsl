#version 330 core

layout (location = 0) out vec4 color;

uniform vec3 f3_ambient_color;
uniform vec3 f3_diffuse_color;
uniform vec3 f3_specular_color;
uniform float f1_specular_highlights;

uniform sampler2D texture_2d;
uniform float f1_used_texture;

uniform vec3 f3_light_color;
uniform vec3 f3_light_pos;

in vec3 v_model_position;
in vec3 v_view_position;
in vec3 v_clip_position;
in vec3 v_norm;
in vec3 v_text;

void main()
{
	// ambient
	// vec3 ambient = f3_light_color * f3_ambient_color;
	
	// diffuse
	// vec3 norm = normalize(v_norm);
	// vec3 lightDir = normalize(f3_light_pos - v_model_position);
	// float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = f3_light_color * (diff * f3_diffuse_color);
	
	// specular
	// vec3 viewDir = normalize(v_view_position - v_model_position);
	// vec3 reflectDir = reflect(-lightDir, norm);
	// float spec = pow(max(dot(viewDir, reflectDir), 0.0), f1_specular_highlights);
	// vec3 specular = f3_light_color * (spec * f3_specular_color); 

	vec3 result;
	// result = (ambient + diffuse + specular) * texture(texture_2d, vec2(v_text.x, v_text.y)).rgb * f1_used_texture;
	// result += (ambient + diffuse + specular) * (1.0f - f1_used_texture);


	result = texture(texture_2d, vec2(v_text.x, v_text.y)).rgb * f1_used_texture;
	result += f3_diffuse_color * (1.0f - f1_used_texture);
	color = vec4(result, 1.0f);
}