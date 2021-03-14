#pragma once

#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Shader/ShaderCreater.hpp"
#include "SOOGL/Tests/debug.hpp"

namespace sgl::tests
{
	inline void shader_creater_test()
	{
		using namespace std;
		/*
		cout << "Vert2b | Col3b:\n" <<
			ShaderCreater::createVertex(sgl::Vert2b | sgl::Col3b) << endl <<
			ShaderCreater::createFragment(sgl::Vert2b | sgl::Col3b) << endl << endl;
		cout << "Vert2b | Vert3b:\n" <<
			ShaderCreater::createVertex(sgl::Vert2b | sgl::Vert3b) << endl <<
			ShaderCreater::createFragment(sgl::Vert2b | sgl::Vert3b) << endl << endl;
		cout << "Vert3b | rUVb:\n" <<
			ShaderCreater::createVertex(sgl::Vert3b | sgl::rUVb) << endl <<
			ShaderCreater::createFragment(sgl::Vert3b | sgl::rUVb) << endl << endl;
		cout << "Vert3b | Col3b | UVb:\n" <<
			ShaderCreater::createVertex(sgl::Vert3b | sgl::Col3b | sgl::UVb) << endl <<
			ShaderCreater::createFragment(sgl::Vert3b | sgl::Col3b | sgl::UVb) << endl << endl;
		cout << "Vert2b | Col3u:\n" <<
			ShaderCreater::createVertex(sgl::Vert2b | sgl::Col3u) << endl <<
			ShaderCreater::createFragment(sgl::Vert2b | sgl::Col3u) << endl << endl;
		cout << "Vert2b | UVb:\n" <<
			ShaderCreater::createVertex(Vert2b | UVb) << endl;
		cout << "Vert2b | rUVb:\n" <<
			ShaderCreater::createVertex(Vert2b | rUVb) << endl;/**/

		cout << "Vert2b | Col3b | Col4u:\n" <<
			ShaderCreater::createFragment(Vert2b | Col3b | Col4u) << endl << endl;

	}
}