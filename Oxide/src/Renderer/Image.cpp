#include "Image.h"
#include "Logging/logger.h"
#include "stb_image.h"

namespace Oxide {
    std::shared_ptr<Image> Image::fromFile(const char* filepath)
    {
        int width, height;
        uint8_t* data = stbi_load(filepath, &width, &height, nullptr, 4);
        if (!data) OX_CORE_ERROR("Failed to load the Image {}", filepath);
        return fromBuffer(data, width, height);
    }
    std::shared_ptr<Image> Image::fromBuffer(void* data, int32_t width, int32_t height)
    {
        std::shared_ptr<Image> i = std::make_shared<Image>();
        i->m_width = width;
        i->m_height = height;
        i->m_data.resize(width * height * 4);
        memmove(i->m_data.data(), data, width * height * 4);
        return i;
    }
    std::vector<uint8_t>& Image::getData()
    {
        return m_data;
    }
    void Image::destroy()
    {
        stbi_image_free(m_data.data());
        m_data.clear();
    }
    Image::~Image()
    {
        destroy();
    }
}