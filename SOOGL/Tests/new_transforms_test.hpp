#pragma once

#include "SOOGL/Render.hpp"
#include "SOOGL/Graphics/Mesh.hpp"
#include "SOOGL/System/User.hpp"
#include "SOOGL/System/Time/Clock.hpp"

#include <iostream>
#include "SOOGL/Tests/debug.hpp"
#include "SOOGL/Other/print_primitives.hpp"

namespace sgl::tests
{
	Transform2D mergeTransforms(const Transform2D& camera, const Transform2D& object)
	{
		Transform2D t;

		t.scale.x = object.scale.x * 2.f / camera.scale.x;
		t.scale.y = object.scale.y * 2.f / camera.scale.y;

		t.position.x = (object.position.x - camera.position.x) * 2.f;
		t.position.y = (object.position.y - camera.position.y) * 2.f;

		t.rotation = object.rotation - camera.rotation;

		return t;
	}

	inline int new_transforms_test()
	{
		using namespace std;

		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return -1;

		Camera2D camera;
		Mesh mesh;
		color3f color(0.5f, 0.5f, 1.f);

		Clock clock;

		mesh.vertexBuffer(&VertexBuffer2f::default_quad_verts());
		mesh.color(&color);
		mesh.scale *= 0.5f;

		camera.position = { 0.5f, 0.5f };

		while (window.isOpen()) 
		{
			float delta = (float)clock.update();

			if (window.shouldClose())
				window.close();

			if (Keyboard::isPressed(Key::E))
				camera.top_down = true;
			else camera.top_down = false;

			if (Keyboard::isPressed(Key::LShift))
			{
				if (Keyboard::isPressed(Key::Left)) camera.scale *= 1.f - 0.5f * delta;
				if (Keyboard::isPressed(Key::Right)) camera.scale *= 1.f + 0.5f * delta;

				if (Keyboard::isPressed(Key::A)) mesh.scale *= 1.f - 0.5f * delta;
				if (Keyboard::isPressed(Key::D)) mesh.scale *= 1.f + 0.5f * delta;
			}
			else
			{
				if (Keyboard::isPressed(Key::Left)) camera.position.x -= 0.5f * delta;
				if (Keyboard::isPressed(Key::Right)) camera.position.x += 0.5f * delta;
				if (Keyboard::isPressed(Key::Down)) camera.position.y -= 0.5f * delta;
				if (Keyboard::isPressed(Key::Up)) camera.position.y += 0.5f * delta;

				if (Keyboard::isPressed(Key::A)) mesh.position.x -= 0.5f * delta;
				if (Keyboard::isPressed(Key::D)) mesh.position.x += 0.5f * delta;
			}

			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			PRINT(mesh.transform());
			PRINT(camera.transform());
			auto merge = mergeTransforms(camera.transform(), mesh.transform());
			PRINT(merge);

			glViewport(-0, -0, 800, 800);

			window.clear(color3f());
			mesh.draw(camera, DrawMode::TriangleFan);
			window.update();
		}

		return 0;
	}
}