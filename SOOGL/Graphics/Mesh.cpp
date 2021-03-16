#include "Mesh.hpp"

namespace sgl
{
	Mesh::Mesh()
		: Transformable2D()
	{
		colb.f3 = nullptr;
		colu.f3 = nullptr;
	}
	Mesh::~Mesh() { }

	int Mesh::vertFlag() const
	{
		if (vertb)
			return Vert2b;
		return 0;
	}
	int Mesh::colbufFlag() const
	{
		if (colb.f3) {
			if (is_col3b)
				return Col3b;
			return Col4b;
		}
		return 0;
	}
	int Mesh::coluniFlag() const
	{
		if (colu.f3) {
			if (is_col3u)
				return Col3u;
			return Col4u;
		}
		return 0;
	}
	int Mesh::uvFlag() const
	{
		if (uvb && tex) {
			if (reverse_uv)
				return rUVb;
			return UVb;
		}
		return 0;
	}

	void Mesh::vertexBuffer(const VertexBuffer2f * vb)
	{
		vertb = vb;
	}

	void Mesh::colorBuffer(const ColorBuffer3f * cb)
	{
		is_col3b = true;
		colb.f3 = cb;
	}
	void Mesh::colorBuffer(const ColorBuffer4f * cb)
	{
		is_col3b = false;
		colb.f4 = cb;
	}

	void Mesh::color(const color3f * color)
	{
		is_col3u = true;
		colu.f3 = color;
	}
	void Mesh::color(const color4f * color)
	{
		is_col3u = false;
		colu.f4 = color;
	}

	void Mesh::indexBuffer(const IndexBuffer * ind)
	{
		indb = ind;
	}
	void Mesh::uvBuffer(const UVBuffer * uvbuf)
	{
		uvb = uvbuf;
	}
	void Mesh::texture(const Texture * t)
	{
		tex = t;
	}
	void Mesh::draw(const Camera2D & cumera, DrawMode mode, const Shader* shader,
		const char* tr_mat_unif, const char* col_unif,
		const char* tex_unif,
		int vert_attr, int col_attr, int uv_attr)
	{

		if (vertFlag() == 0)	// if vertex buffer does not exists
			return;				// drawing is impossible

		if (not shader) // use default shader if no shader is specified
		{
			int flag = vertFlag();
			flag |= colbufFlag();
			flag |= coluniFlag();
			flag |= uvFlag();

			shader = Shader::get(flag);
		}

		// compute matrix
		mat3 out;
		mat3::multiply(cumera.matrix(), matrix(), out);

		// set uniforms
		shader->setUniform(shader->location(tr_mat_unif), out);
		if (coluniFlag()) {	// if there is a color uniform

			if (is_col3u) shader->setUniform(shader->location(col_unif), *colu.f3);
			else shader->setUniform(shader->location(col_unif), *colu.f4);
		}
		if (uvFlag())
		{
			shader->setUniform(shader->location(tex_unif), *tex);
		}
		shader->activate();

		// activate attributes and drawing
		vertb->activate(vert_attr);
		if (colb.f3)
		{
			if (is_col3b) colb.f3->activate(col_attr);
			else colb.f4->activate(col_attr);
		}
		if (uvb)
			uvb->activate(uv_attr);
		// end of activation
		
		if (indb)
			indb->drawIndexes(mode);
		else
			vertb->drawArrays(mode);

		// begin of deactivation
		if (uvb)
			uvb->deactivate(uv_attr);
		if (colb.f3)
		{
			if (is_col3b) colb.f3->deactivate(col_attr); 
			else colb.f4->deactivate(col_attr); 
		}
		vertb->deactivate(vert_attr);
	}
}
