#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"

namespace sgl
{
	class Singletone
	{
		static Singletone* inst;

		Singletone()
		{
			vb.changeData() = {
				{0.f, 0.f},
				{0.f, 1.f},
				{1.f, 1.f},
				{1.f, 0.f}
			};
			ub.changeData() = {
				{0.f, 0.f},
				{0.f, 1.f},
				{1.f, 1.f},
				{1.f, 0.f}
			};
		}
	public:
		VertexBuffer2f vb;
		UVBuffer ub;

		static const Singletone& get() {
			if (not inst)
				inst = new Singletone;
			return *inst;
		}
	};
	Singletone* Singletone::inst = nullptr;


	class Sprite : public Transformable2D
	{
		const Texture* r_texture = nullptr;
	public:
		Sprite(const Texture& t)
		{
			r_texture = &t;
		}
		void texture(const Texture& t)
		{
			r_texture = &t;
		}

		void draw(const Camera2D& camera, const Shader& shader)
		{
			auto& ub = Singletone::get().ub;
			auto& vb = Singletone::get().vb;

			mat3 to_shader;
			mat3::multiply(camera.matrix(), this->matrix(), to_shader);
			shader.setUniform(shader.location("transform"), to_shader);
			shader.setUniform(shader.location("img"), *r_texture);
			shader.activate();

			vb.activate(0);
			ub.activate(2);

			vb.drawArrays(DrawMode::TriangleFan);

			ub.deactivate(2);
			vb.deactivate(0);
		}
	};
}