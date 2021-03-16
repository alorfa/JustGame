#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Buffer/IndexBuffer.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Transform/Transformable2D.hpp"

namespace sgl
{
	class Mesh : public Transformable2D
	{
		const VertexBuffer2f* vertb = nullptr;
		union {
			const ColorBuffer3f* f3;
			const ColorBuffer4f* f4;
		} colb;
		union {
			const color3f* f3;
			const color4f* f4;
		} colu;
		const UVBuffer* uvb = nullptr;
		const Texture* tex = nullptr;

		const IndexBuffer* indb = nullptr;

		bool is_col3b = false, is_col3u = false;
	private:
		int vertFlag() const;
		int colbufFlag() const;
		int coluniFlag() const;
		int uvFlag() const;
	public:
		Mesh();
		~Mesh();
		Mesh(const Mesh&) = default;
		Mesh& operator=(const Mesh&) = default;
		Mesh(Mesh&&) = default;
		Mesh& operator=(Mesh&&) = default;
	public:
		void vertexBuffer(const VertexBuffer2f* vb);

		void colorBuffer(const ColorBuffer3f* cb);
		void colorBuffer(const ColorBuffer4f* cb);

		void color(const color3f* col);
		void color(const color4f* col);

		void indexBuffer(const IndexBuffer* indb);
		void uvBuffer(const UVBuffer* uvb);

		void texture(const Texture* t);

		bool reverse_uv;
	public:
		void draw(const Camera2D& cumera, DrawMode mode, const Shader* shader = nullptr, 
			const char* transform_mat_unif = "transform", const char* col_unif = "color",
			const char* tex_unif = "img",
			int vert_attr = 0, int col_attr = 1, int uv_attr = 2);
	};
}