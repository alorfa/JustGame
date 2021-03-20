#pragma once

#include "SOOGL/Graphics/Mesh.hpp"
#include "SOOGL/Render/Window.hpp"
#include "SOOGL/Render/FrameBuffer.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/Graphics/Shader.hpp"
#include "SOOGL/Other/exceptions.hpp"
#include "SOOGL/System/Time/Clock.hpp"
#include "SOOGL/Tests/debug.hpp"

namespace sgl::tests
{
	inline void mesh_test()
	{
		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return;
		window.frameLimit(60);

		VertexBuffer2f vb;
		UVBuffer uvb;
		color3f color;
		ColorBuffer3f cb;
		IndexBuffer ib;
		Texture t1, t2;

		Shader post_proc;
		try
		{
			ShaderCompiler compiler;
			auto vertex_data = ShaderCreater::createVertex(Vert2b | UVb);
			compiler.loadFromMemory(vertex_data.c_str(), Shader::Vertex);
			compiler.loadFromFile("shaders/8bit.fsh", Shader::Fragment);
			post_proc = compiler.link();
		}
		catch (shader_error& e)
		{
			PRINT(e.message());
			return;
		}
		catch (...)
		{
			return;
		}

		vb = VertexBuffer2f::default_quad_verts();
		uvb = UVBuffer::default_quad_UV();
		cb.changeData() = {
			{1.f, 1.f, 1.f},
			{0.5f, 0.5f, 0.5f},
			{0.f, 0.2f, 0.8f},
			{10.f, 0.f, 0.f}
		};
		ib.changeData() = {0, 1, 2, 0, 2, 3};
		color = color3f(0.5f, 0.5f, 2.f);

		t1.loadFromFile("asd.jpg");
		t2.loadFromFile("blya.jpg");

		Mesh m1, m2;
		m1.vertexBuffer(&vb);
		m1.uvBuffer(&uvb);
		m1.texture(&t1);
		//m1.color(&color);
		m1.indexBuffer(&ib);
		m1.position = fvec2(-0.5f, -0.5f);
		m1.reverse_uv = true;

		m2.vertexBuffer(&vb);
		m2.uvBuffer(&uvb);
		m2.texture(&t2);
		m2.position = {-0.4f, -0.4f};
		m2.scale = {0.8f, 0.8f};
		//m2.position(-0.5f, -0.5f);

		Clock clock;

		FrameBuffer fbuf;
		fbuf.create({ 800, 800 });
		m2.texture(&fbuf.texture());

		while (window.isOpen())
		{
			if (window.shouldClose())
				window.close();

			float delta = (float)clock.update();

			if (Keyboard::isPressed(Key::Left))
				m2.position.x -= 0.5f * delta;
			if (Keyboard::isPressed(Key::Right))
				m2.position.x += 0.5f * delta;

			fbuf.activate(); 
			{
				fbuf.clear(color3f());
				m1.draw(Camera2D::by_default, DrawMode::Triangles);
			}
			fbuf.deactivate();

			window.clear(color3f());

			m2.draw(Camera2D::by_default, DrawMode::TriangleFan, &post_proc);

			window.update();
		}
	}
}