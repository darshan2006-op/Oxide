#pragma once
#include <vector>
#include <memory>

namespace Oxide {
	class Image {
	public:
		Image() = default;

		static std::shared_ptr<Image> fromFile(const char* filepath);
		static std::shared_ptr<Image> fromBuffer(void* data, int32_t width, int32_t height);

		int32_t getWidth() { return m_width; }
		int32_t getHeight() { return m_height; }
		std::vector<uint8_t>& getData();
		void destroy();
		~Image();
	private:
		int32_t m_width = 0, m_height = 0;
		std::vector<uint8_t> m_data;
	};
}