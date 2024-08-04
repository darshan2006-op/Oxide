#pragma once
#include "Renderer/Texture2D.h"

namespace Oxide {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D();
		virtual void addData(const std::shared_ptr<Image>& image) override;
		virtual void use() override;
		virtual void destroy() override;
		virtual ~OpenGLTexture2D();
	private:
		uint32_t m_id;
		uint8_t m_slot;
	};
}
