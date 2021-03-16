#pragma once

#include "SOOGL/Graphics/Mesh.hpp"
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/RenderTarget/FrameBuffer.hpp"

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
		color3f color;
		ColorBuffer3f cb;
		IndexBuffer ib;
		Texture t1, t2;

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
		m1.color(&color);
		m1.indexBuffer(&ib);
		m1.position(-0.5f, -0.5f);
		m1.reverse_uv = true;

		m2.vertexBuffer(&vb);
		m2.uvBuffer(&uvb);
		m2.texture(&t2);
		m2.position(-0.25f, -0.25f);
		m2.scope(0.5f, 0.5f);
		//m2.reverse_uv = true;

		Clock clock;

		FrameBuffer fbuf;
		fbuf.create({ 50, 50 });
		m2.texture(&fbuf.texture());

		while (window.isOpen())
		{
			if (window.shouldClose())
				window.close();

			float delta = (float)clock.update();

			if (Keyboard::isPressed(Key::Left))
				m2.move(-0.5f * delta, 0);
			if (Keyboard::isPressed(Key::Right))
				m2.move(0.5f * delta, 0);

			fbuf.activate(); 
			{
				PRINTR(fbuf.isValid());
				fbuf.clear(color3f());
				m1.draw(Camera2D::by_default, DrawMode::Triangles);
				m1.draw(Camera2D::by_default, DrawMode::Triangles);
			}
			fbuf.deactivate(); 

			window.clear(color3f(0.5f, 0.5f, 0.5f));
			m2.draw(Camera2D::by_default, DrawMode::TriangleFan);
			m2.draw(Camera2D::by_default, DrawMode::TriangleFan); 
			window.update();
		}
	}
}