#pragma once

#include "SOOGL/Graphics/Transform/Transformable2D.hpp"
#include "SOOGL/Graphics/Text/Font.hpp"
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/System/string.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/color.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"

namespace sgl
{
	using namespace color;
	using namespace mat;

	class TextLine : public Transformable2D
	{
		const Font* fontptr = nullptr;
		string m_content;
	public:
		TextLine() = default;
		~TextLine() = default;

		const Font& font(const Font& new_font);
		const Font& font();
		const string& content(const string& new_content);
		const string& content();

		void draw(const Camera2D& camera, const Shader& shader, const color3f& col);
	};
}