#pragma once

#include "SOOGL/Render.hpp"
#include "SOOGL/Graphics/Transform.hpp"
#include "SOOGL/Graphics/Mesh.hpp"
#include "SOOGL/System/User.hpp"
#include "SOOGL/System/Time/Clock.hpp"
#include "SOOGL/Other/print_primitives.hpp"

namespace sgl::tests
{
	inline void createMatrix(const Transform2D& camera, const Transform2D& object, mat3& output)
	{
		Transform2D t;
		PRINTR(object);
		t.position.x = object.position.x - camera.position.x;
		t.position.y = object.position.y - camera.position.y;
		t.rotation = object.rotation - camera.rotation;
		t.scale.x = (object.scale.x * 2.f) / camera.scale.x;
		t.scale.y = (object.scale.y * 2.f) / camera.scale.y;

		mat3::createTransformMatrix(t, output);

		//PRINTR(t);
	}

	using namespace std;

	inline int speed_test_transform()
	{
		constexpr size_t ITERATIONS = 1'000'000;

		Transformable2D tr;
		Camera2D cum;

		mat3 matrix, m1, m2;

		cout << "Constructors:" << endl;
		Clock clock;
		for (size_t i = 0; i < ITERATIONS; i++)
			mat3 m;
		cout << "   matrix3x3: " << clock.update() << endl;
		for (size_t i = 0; i < ITERATIONS; i++)
			Transform2D t;
		cout << "   transforms: " << clock.update() << endl;

		for (size_t i = 0; i < ITERATIONS; i++)
			mat3::createTransformMatrix(tr.transform(), matrix);
		cout << "creating matrix: " << clock.update() << endl;

		for (size_t i = 0; i < ITERATIONS; i++)
			mat3::multiply(m1, m2, matrix);
		cout << "multiply matrix: " << clock.update() << endl << endl;

		/*
		cout << "move:" << endl;
		for (size_t i = 0; i < ITERATIONS; i++)
		{
			tr.move(0.000001f, 0.f);
			cum.move(0.f, 0.1f);
			mat3 out;
			mat3::multiply(cum.matrix(), tr.matrix(), out);
		}
		cout << "   matrix: " << clock.update() << endl;
		for (size_t i = 0; i < ITERATIONS; i++)
		{
			tr.move(0.000001f, 0.f);
			cum.move(0.f, 0.1f);
			mat3 out;
			mat3::createMatrix(cum.transform(), tr.transform(), out);
		}
		cout << "   transform: " << clock.update() << endl;

		cout << "not move:" << endl;
		for (size_t i = 0; i < ITERATIONS; i++)
		{
			mat3 out;
			mat3::multiply(cum.matrix(), tr.matrix(), out);
		}
		cout << "   matrix: " << clock.update() << endl;
		for (size_t i = 0; i < ITERATIONS; i++)
		{
			mat3 out;
			mat3::createMatrix(cum.transform(), tr.transform(), out);
		}
		cout << "   transform: " << clock.update() << endl;
		/**/
		return 0;
	}

	inline int transform_matrix_optimization()
	{
		return speed_test_transform();

		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return -1;

		Camera2D camera;

		VertexBuffer2f vb = VertexBuffer2f::default_quad_verts();
		Transformable2D t2;

		Clock clock;

		/*
		camera.move(0.5f, 0.5f);
		camera.zoom(2.f);

		while (window.isOpen())
		{
			double d_delta = clock.update();
			float delta = float(d_delta);

			if (window.shouldClose())
				window.close();

			window.clear(color3f());

			if (Keyboard::isPressed(Key::R))
			{
				if (Keyboard::isPressed(Key::A)) t2.rotate(-0.5f * delta);
				if (Keyboard::isPressed(Key::D)) t2.rotate(0.5f * delta);
			}
			else if (Keyboard::isPressed(Key::LShift))
			{
				if (Keyboard::isPressed(Key::A)) t2.zoom(1.f - 0.5f * delta);
				if (Keyboard::isPressed(Key::D)) t2.zoom(1.f + 0.5f * delta);
			}
			else
			{
				if (Keyboard::isPressed(Key::A)) t2.move(-0.5f * delta, 0);
				if (Keyboard::isPressed(Key::D)) t2.move(0.5f * delta, 0);
			}

			if (Keyboard::isPressed(Key::R))
			{
				if (Keyboard::isPressed(Key::Left)) camera.rotate(-0.5f * delta);
				if (Keyboard::isPressed(Key::Right)) camera.rotate(0.5f * delta);
			}
			else if (Keyboard::isPressed(Key::LShift))
			{
				if (Keyboard::isPressed(Key::Left)) camera.zoom(1.f - 0.5f * delta);
				if (Keyboard::isPressed(Key::Right)) camera.zoom(1.f + 0.5f * delta);
			}
			else
			{
				if (Keyboard::isPressed(Key::Left)) camera.move(-0.5f * delta, 0);
				if (Keyboard::isPressed(Key::Right)) camera.move(0.5f * delta, 0);
			}
			const Shader* shader = Shader::get(Vert2b | Col3u);
			if (not shader) {
				window.update();
				continue;
			}

			mat3 out;
			//mat3::multiply(camera.matrix(), t2.matrix(), out);
			createMatrix(camera.transform(), t2.transform(), out);

			shader->activate();
			shader->setUniform(shader->location("transform"), out);
			shader->setUniform(shader->location("color"), fvec3(0.5f, 0.5f, 1.f));

			Activator a(vb, 0);

			vb.drawArrays(DrawMode::TriangleFan);

			window.update(); 
		}
		/**/

		return 0;
	}
}