#include "TextLine.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "SOOGL/Tests/debug.hpp"

std::ostream& operator<<(std::ostream& out, const sgl::mat::mat3& mat);
std::ostream& operator<<(std::ostream& out, const sgl::color::color3f& col)
{
	out << "[" << col.r << ", " << col.g << ", " << col.b << "]";
	return out;
}

namespace sgl
{
	const Font& TextLine::font(const Font& new_font)
	{
		fontptr = &new_font;
		return *fontptr;
	}
	const Font& TextLine::font()
	{
		return *fontptr;
	}
	const string& TextLine::content(const string& new_content)
	{
		m_content = new_content;
		return m_content;
	}
	const string& TextLine::content()
	{
		return m_content;
	}
	void TextLine::draw(const Camera2D& camera, const Shader& shader, const color3f& col)
	{
		constexpr float scale = 1.f;

		if (!fontptr)
			return;

		mat3 out_matrix;
		mat3::multiply(camera.matrix(), this->matrix(), out_matrix);
		shader.activate();
		shader.setUniform(shader.location("transform"), out_matrix);
		shader.setUniform(shader.location("textColor"), col.asVec3());

		const Font::GlyphMap& glyph_map = fontptr->glyphMap();

		float x = position().x;
		float y = position().y;

		VertexBuffer2f vert_buf;
		UVBuffer uvs;
		uvs.changeData() = {
			{0.f, 0.f},
			{0.f, 1.f},
			{1.f, 1.f},
			{1.f, 0.f},
		};

		for (auto ch : m_content)
		{
			const Font::CharTexture& symbol_data = glyph_map.at(ch);
			const Texture& texture = symbol_data.texture;

			shader.setUniform(shader.location("text"), texture); 
			
			float xpos = x + symbol_data.bearing.x * scale;
			float ypos = y - (texture.size().y - symbol_data.bearing.y) * scale;

			float w = texture.size().x * scale;
			float h = texture.size().y * scale;

			// update VBO for each character
			vert_buf.changeData() = {
				{ xpos,     ypos + h },
				{ xpos,     ypos },
				{ xpos + w, ypos },
				{ xpos + w, ypos + h }
			};
			vert_buf.activate(0, LoadMode::Dynamic);
			uvs.activate(1, LoadMode::Dynamic);
			vert_buf.drawArrays(DrawMode::TriangleFan);
			uvs.deactivate(1);
			vert_buf.deactivate(0);

			x += (symbol_data.advance >> 6) * scale;
		}
		/**/
	}
}