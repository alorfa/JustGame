#include "ShaderCreater.hpp"
#include "Shader.hpp"
#include "SOOGL/Tests/debug.hpp"

using namespace sgl;

constexpr int anyUV = UVb | rUVb;
constexpr int anyColb = Col3b | Col4b;
constexpr int anyColu = Col3u | Col4u;
constexpr int anyCol = anyColb | anyColu;

namespace sgl
{
	bool bothFlags(int flags, Inbuilt f1, Inbuilt f2)
	{
		return ((flags & f1) && (flags & f2));
	}

	std::string ShaderCreater::createVertex(int shader)
	{
		std::string output = "#version 330\n\n";

		if (bothFlags(shader, Vert2b, Vert3b) ||	// must be only one type of vertex
			bothFlags(shader, Col3b, Col4b) ||		// and type of color
			bothFlags(shader, UVb, rUVb))			// ...and other
			return std::string();

		// vertex buffer
		if (shader & Vert2b)
			output += "layout (location = 0) in vec2 in_vertex;\n";
		else if (shader & Vert3b)
			output += "layout (location = 0) in vec3 in_vertex;\n";
		else return std::string(); // Vertex buffer is required, at least one must be used

		const std::string color_type = [&]() -> std::string {
			if (shader & Col3b)
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
		if (shader & Vert2b)
			output += "uniform mat3 transform";
		else output += "uniform mat4 transform";
		output += ";\n\n";

		// void main()
		output += "void main()\n"
			"{\n";
		// vertex
		if (shader & Vert2b) {
			output += "\tvec3 out_pos = transform * vec3(in_vertex, 1.0);\n"
				"\tgl_Position = vec4(out_pos.xy, 0, 1);\n";
		} else {
			output += "\tgl_Position = transform * vec4(in_vertex, 1);\n";
		}
		// color
		if (shader & anyColb)
			output += "\tfrag_color = in_color;\n";
		// UV
		if (shader & UVb)
			output += "\tfrag_UV = in_UV;\n";
		if (shader & rUVb)
			output += "\tfrag_UV = vec2(in_UV.x, 1 - in_UV.y);\n";

		output += "}";

		//PRINT(output);

		return output;
	}
	std::string ShaderCreater::createFragment(int shader)
	{
		std::string output = "#version 330\n\n";

		if (bothFlags(shader, Col3b, Col4b) ||
			bothFlags(shader, Col3u, Col4u))
			return std::string();

		const std::string color_buf_type = [&]() {
			if (shader & Col3b)
				return "vec3";
			return "vec4";
		}();
		const std::string color_uni_type = [&]() {
			if (shader & Col3u)
				return "vec3";
			return "vec4";
		}();

		// in variables
		if (shader & anyColb) output += "in " + color_buf_type + " frag_color;\n";
		if (shader & anyUV) output += "in vec2 frag_UV;\n";
		if (shader & (anyColb | anyUV)) output += "\n";

		// out color
		output += "out vec4 out_color;\n\n";

		// uniforms
		if (shader & anyColu) output += "uniform " + color_uni_type + " color;\n";
		if (shader & anyUV) output += "uniform sampler2D img;\n";
		if (shader & (anyColu | anyUV)) output += "\n";

		// void main() {
		output += "void main()\n"
			"{\n";

		if (not (shader & (anyUV | anyCol))) // not texture and not color == just white
		{
			output += "\tout_color = vec4(1, 1, 1, 1);\n"
				"}";
			return output;
		}

		auto additionalColorBuf = [&]() -> std::string 
		{
			if (shader & Col3b) return "vec4(frag_color, 1)";
			if (shader & Col4b) return "frag_color";
			return std::string();
		};
		auto additionalColorUnif = [&]() -> std::string
		{
			if (shader & Col3u) return "vec4(color, 1)";
			if (shader & Col4u) return "color";
			return std::string();
		};

		output += "\tout_color = ";

		std::vector<std::string> out_col_comps;
		if (shader & anyUV)
			out_col_comps.push_back("texture(img, frag_UV)");
		if (shader & anyColb)
			out_col_comps.push_back(additionalColorBuf());
		if (shader & anyColu)
			out_col_comps.push_back(additionalColorUnif());

		size_t i = 0;
		for (; i < out_col_comps.size() - 1; i++)
			output += out_col_comps[i] + " * ";
		output += out_col_comps[i] + ";\n";

		output += "}";

		return output;
	}
}