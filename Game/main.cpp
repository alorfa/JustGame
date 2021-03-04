#include "SOOGL/System/Time/Time.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Init.hpp"
#include "SOOGL/Math/trig.hpp"
#include "SOOGL/System/Time/Clock.hpp"
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "Game/Object/Color.hpp"
#include "SOOGL/Graphics/Blend.hpp"
#include "SOOGL/Tests/debug.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/System/User/Mouse.hpp"
#include "SOOGL/Other/print_primitives.hpp"
#include "SOOGL/System/Time/FpsManager.hpp"
#include <Windows.h>
#include "GLFW/glfw3.h"
#include <SFML/Graphics.hpp>

using namespace sgl::types;
using namespace sgl::vec;

int main()
{
	sgl::Init Initializer;

	sgl::Blend::activate(sgl::Blend::Default);

	sgl::Window window;
	window.create({ 800, 800 }, "Title");
	glewExperimental = true;
	glewInit();

	//window.sizeLimit({ 400, 300 }, { 0, 0 });

	sgl::VertexBuffer2f vbuf;
	vbuf.changeData() = {
		{0.f, 0.f},
		{1.f, 0.f},
		{1.f, 1.f},
		{0.f, 1.f}
	};

	sgl::Camera2D camera;
	camera.move(0.5f, 0.5f);

	sgl::FpsManager fps;
	fps.limit = 120;

	double d_delta = 0.0;
	float delta = 0.f;

	gd::Color color;
	color.change({0.8f, 0.1f, 0.5f, 1.f});

	while (window.isOpen())
	{
		d_delta = fps.begin();
		delta = float(delta);

		window.clear(color3f{ 0.f, 0.f, 0.f });

		if (window.shouldClose())
			window.close();

		if (window.isFocused())
		{
			if (sgl::Keyboard::justPressed(sgl::Key::Left))
				color.change({ 0.3f, 0.3f, 0.6f, 1.f }, 0.3);
			if (sgl::Keyboard::justReleased(sgl::Key::Left))
				color.change({ 0.5f, 0.3f, 0.3f, 1.f }, 0.3);
		}
		color.update(d_delta);

		const sgl::Shader* shader = sgl::Shader::get(sgl::Vert2b | sgl::Col4u);
		if (not shader)
			continue;

		shader->setUniform(shader->location("transform"), camera.matrix());
		shader->setUniform(shader->location("color"), color.color());
		shader->activate();

		vbuf.activate(0);
		vbuf.drawArrays(sgl::TriangleFan);
		vbuf.deactivate(0);

		window.update();

		fps.end();
	}

	return 0;
}