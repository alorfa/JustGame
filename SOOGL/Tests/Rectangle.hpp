#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Transform/Transform2D.hpp"
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

		VertexBuffer2f vertexes;
		ColorBuffer3f colors;
		UVBuffer uv;
		const Texture* texture;
	public:
		Rectangle(const Texture& texture)
		{
			vertexes.changeData() = {
				{-1.f, -1.f},
				{1.f, -1.f},
				{1.f, 1.f},
				{-1.f, 1.f}
			};
			/*
			colors.changeData() = {
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 1.f, 1.f},
				{0.f, 1.f, 1.f}
			};/**/
			colors.changeData() = {
				{1.f, 1.f, 1.f},
				{1.f, 1.f, 1.f},
				{1.f, 1.f, 1.f},
				{1.f, 1.f, 1.f}
			};
			uv.changeData() = {
				{0.f, 0.f},
				{1.f, 0.f},
				{1.f, 1.f},
				{0.f, 1.f}
			};
			this->texture = &texture;
		}

		static void setShader(const Shader& shader)
		{
			Rectangle::shader = &shader;
			mat = shader.location("transform");
			img = shader.location("img");
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

			vertexes.activate(0);
			colors.activate(1);
			uv.activate(2);

			vertexes.drawArrays(PrimitiveType::TriangleFan);

			uv.deactivate(2);
			colors.deactivate(1);
			vertexes.deactivate(0);
		}
	};
	Uniform Rectangle::mat = 0;
	Uniform Rectangle::img = 0;
	const Shader* Rectangle::shader = nullptr;
}