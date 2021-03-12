#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Transform/Transformable2D.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Math/mat3.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "debug.hpp"

namespace sgl::tests
{
	using namespace mat;

	class Rectangle : public Transformable2D
	{
		static Uniform mat, img;
		static const Shader* shader;

		static VertexBuffer2f* vertexes;
		static UVBuffer* uv;

		const Texture* texture;
	public:
		void setTexture(const Texture& texture)
		{
			this->texture = &texture;
		}
		Rectangle(const Texture& texture)
		{
			setTexture(texture);
		}

		static void init()
		{
			// init buffers
			vertexes = new VertexBuffer2f;
			vertexes->changeData() = {
				{0.f, 0.f},
				{1.f, 0.f},
				{1.f, 1.f},
				{0.f, 1.f}
			};
			uv = new UVBuffer;
			uv->changeData() = {
				{0.f, 0.f},
				{1.f, 0.f},
				{1.f, 1.f},
				{0.f, 1.f}
			};
			vertexes->clearFromMemory();
			uv->clearFromMemory();

			// init shaders
			Rectangle::shader = Shader::get(Vert2b | rUVb);
			mat = shader->location("transform");
			img = shader->location("img");
			PRINT(mat);
			PRINT(img);
		}

		void draw(const Camera2D& camera)
		{
			mat3 to_shader;
			mat3::multiply(camera.matrix(), matrix(), to_shader);

			if (shader)
			{
				shader->setUniform(mat, to_shader);
				shader->setUniform(img, *texture);
				shader->activate();
			}

			vertexes->activate(0);
			uv->activate(2);

			vertexes->drawArrays(DrawMode::TriangleFan);

			uv->deactivate(2);
			vertexes->deactivate(0);
		}
	};
	VertexBuffer2f* Rectangle::vertexes;
	UVBuffer* Rectangle::uv;

	Uniform Rectangle::mat = 0;
	Uniform Rectangle::img = 0;

	const Shader* Rectangle::shader = nullptr;
}