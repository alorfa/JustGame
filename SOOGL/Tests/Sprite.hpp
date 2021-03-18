#pragma once

#include "SOOGL/Graphics/Buffer.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "SOOGL/Graphics/Transform/Camera2DBase.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"

namespace sgl
{
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
			auto& ub = UVBuffer::default_quad_UV();
			auto& vb = VertexBuffer2f::default_quad_verts();

			mat3 to_shader;
			mat3::multiply(camera.matrix(), matrix(), to_shader);

			shader.activate();
			shader.setUniform(shader.location("transform"), to_shader);
			shader.setUniform(shader.location("img"), *r_texture);

			Activator vbuf(vb, 0);
			Activator ubuf(ub, 2);

			vb.drawArrays(DrawMode::TriangleFan);
		}
	};
}