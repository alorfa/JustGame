#include "SOOGL/System/Time.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Init.hpp"
#include "SOOGL/Math/trig.hpp"
#include "SOOGL/System/Clock.hpp"
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "Game/Object/Color.hpp"
#include "SOOGL/Graphics/Blend.hpp"

using namespace sgl::types;

int main()
{
	sgl::Init Initializer;

	sgl::Blend::activate(sgl::Blend::Default);

	sgl::Window window;
	window.create({ 800, 800 });

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

	while (window.isOpen())
	{
		d_delta = fps.begin();
		delta = float(delta);

		if (window.shouldClose())
			window.close();

		const sgl::Shader* shader = sgl::Shader::get(sgl::Vert2b | sgl::Col4u);
		if (not shader)
			continue;

		shader->setUniform(shader->location("transform"), camera.matrix());
		shader->setUniform(shader->location("color"), sgl::fvec4(0.5f, 0.3f, 0.3f, 1.f));
		shader->activate();

		vbuf.activate(0);
		vbuf.drawArrays(sgl::TriangleFan);
		vbuf.deactivate(0);

		window.update();

		fps.end();
	}

	return 0;
}