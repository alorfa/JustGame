#pragma once

#include "SOOGL/Graphics/Mesh.hpp"
#include "SOOGL/RenderTarget/Window.hpp"

namespace sgl::tests
{
	inline void mesh_test()
	{
		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return;
		window.frameLinit(60);

		VertexBuffer2f vb;
		UVBuffer uvb;
		Texture texture;

		vb.changeData() = {
			{0.f, 0.f},
			{0.f, 1.f},
			{1.f, 1.f},
			{1.f, 0.f}
		};
		uvb.changeData() = {
			{0.f, 0.f},
			{0.f, 1.f},
			{1.f, 1.f},
			{1.f, 0.f}
		};
		texture.loadFromFile("asd.jpg");

		Mesh mesh;
		mesh.vertexBuffer(&vb);
		mesh.uvBuffer(&uvb);
		mesh.texture(&texture);

		while (window.isOpen())
		{
			if (window.shouldClose())
				window.close();

			mesh.draw(Camera2D::by_default, DrawMode::TriangleFan);
			window.update();
		}
	}
}