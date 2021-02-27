#include "ShaderCreater.hpp"
#include "Shader.hpp"
#include "SOOGL/Tests/debug.hpp"

constexpr int anyUV = sgl::UVb | sgl::rUVb;
constexpr int anyColb = sgl::Col3b | sgl::Col4b;
constexpr int anyColu = sgl::Col3u | sgl::Col4u;
constexpr int anyCol = anyColb | anyColu;

namespace sgl
{
	bool bothFlags(int flags, sgl::Inbuilt f1, sgl::Inbuilt f2)
	{
		return ((flags & f1) && (flags & f2));
	}

	std::string ShaderCreater::createVertex(int shader)
	{
		std::string output = "#version 330\n\n";

		if (bothFlags(shader, sgl::Vert2b, sgl::Vert3b) ||		// only one type of vertex
			bothFlags(shader, sgl::Col3b, sgl::Col4b) ||		// and type of color
			bothFlags(shader, sgl::UVb, sgl::rUVb))				// ...and other
			return std::string();

		// vertex buffer
		if (shader & sgl::Vert2b)
			output += "layout (location = 0) in vec2 in_vertex;\n";
		else if (shader & sgl::Vert3b)
			output += "layout (location = 0) in vec3 in_vertex;\n";
		else return std::string(); // Vertex buffer is required, at least one must be used

		const std::string color_type = [&]() -> std::string {
			if (shader & sgl::Col3b)
				return "vec3";
			return "vec4";
		}();

		// color buffer
		if (shader & anyColb)
			output += "layout (location = 1) in " + color_type + " in_color;\n";

		// uv buffer
		if (shader & anyUV)
			output += "layout (location = 2) in vec2 in_UV;\n";

		output += '\n';

		// out variables
		if (shader & (anyUV | anyColb))
		{
			if (shader & anyColb) output += "out " + color_type + " frag_color;\n";
			if (shader & anyUV) output += "out vec2 frag_UV;\n";
			
			output += "\n";
		}

		// transform
		if (shader & sgl::Vert2b)
			output += "uniform mat3 transform";
		else output += "uniform mat4 transform";
		output += ";\n\n";

		// void main()
		output += "void main()\n"
			"{\n";
		// vertex
		if (shader & sgl::Vert2b) {
			output += "\tvec3 out_pos = transform * vec3(in_vertex, 1.0);\n"
				"\tgl_Position = vec4(out_pos.xy, 0, 1);\n";
		} else {
			output += "\tgl_Position = transform * vec4(in_vertex, 1);\n";
		}
		// color
		if (shader & anyColb)
			output += "\tfrag_color = in_color;\n";
		// UV
		if (shader & sgl::UVb)
			output += "\tfrag_UV = in_UV;\n";
		if (shader & sgl::rUVb)
			output += "\tfrag_UV = vec2(in_UV.x, 1 - in_UV.y);\n";

		output += "}";

		//PRINT(output);

		return output;
	}
	std::string ShaderCreater::createFragment(int shader)
	{
		std::string output = "#version 330\n\n";

		if (bothFlags(shader, sgl::Col3b, sgl::Col4b) ||
			bothFlags(shader, sgl::Col3u, sgl::Col4u) ||
			bothFlags(shader, (sgl::Inbuilt)anyColb, (sgl::Inbuilt)anyColu)) // there must be either a buffer or a uniform 
			return std::string();

		if (not (shader & (anyUV | anyCol)))
			return std::string();

		const std::string color_type = [&]() -> std::string {
			if (shader & (sgl::Col3b | sgl::Col3u))
				return "vec3";
			return "vec4";
		}();

		// in variables
		if (shader & anyColb) output += "in " + color_type + " frag_color;\n";
		if (shader & anyUV) output += "in vec2 frag_UV;\n";
		if (shader & (anyColb | anyUV))
			output += "\n";

		// out color
		output += "out vec4 out_color;\n\n";

		// uniforms
		if (shader & anyColu) output += "uniform " + color_type + " color;\n";
		if (shader & anyUV) output += "uniform sampler2D img;\n";
		if (shader & (anyColu | anyUV)) output += "\n";

		// void main()
		output += "void main()\n"
			"{\n";

		auto additionalColor = [&]() -> std::string 
		{
			std::string outp;
			if (shader & sgl::Col3b) outp += "vec4(frag_color, 1)";
			if (shader & sgl::Col4b) outp += "frag_color";
			if (shader & sgl::Col3u) outp += "vec4(color, 1)";
			if (shader & sgl::Col4u) outp += "color";
			return outp;
		};

		output += "\tout_color = ";
		/**/
		std::vector<std::string> out_col_comps;
		if (shader & anyUV)
			out_col_comps.push_back("texture(img, frag_UV)");
		if (shader & anyCol)
			out_col_comps.push_back(additionalColor());
		size_t i = 0;
		for (; i < out_col_comps.size() - 1; i++)
			output += out_col_comps[i] + " * ";
		output += out_col_comps[i] + ";\n";/**/
		/*
		if (shader & anyUV)
		{
			output += "texture(img, frag_UV)";
			if (shader & anyCol)
				output += " * " + additionalColor() + ";\n";
		}
		else
		{
			output += additionalColor() + ";\n";
		}/**/

		output += "}";

		//PRINT(output);

		return output;
	}
}