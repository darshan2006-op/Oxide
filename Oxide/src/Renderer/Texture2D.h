#pragma once
#include <memory>

#include "Image.h"

namespace Oxide {
	class Texture2D {
	public:
		static std::shared_ptr<Texture2D> create();
		virtual void addData(const std::shared_ptr<Image>& image) = 0;
		virtual void use() = 0;
		virtual void destroy() = 0;
		virtual ~Texture2D() = default;
	protected:
		static uint8_t s_texCount;
		Texture2D() = default;
	};
}