#pragma once

namespace sgl
{
	class Blend
	{
	public:
		enum Mode
		{
			SrcAlpha, 
			OneMinusSrcAlpha,
			Default = OneMinusSrcAlpha
		};

		static void activate(Mode sfactor, Mode dfactor);
		static void activate(Mode dfactor);
	};
}