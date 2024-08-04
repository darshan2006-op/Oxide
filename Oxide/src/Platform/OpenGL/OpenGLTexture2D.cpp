#include "OpenGLTexture2D.h"
#include "glad/glad.h"

namespace Oxide {
    static uint32_t getTextSlot(uint8_t slot) {
        return GL_TEXTURE0 + slot;
    }

    OpenGLTexture2D::OpenGLTexture2D(): m_id(0), m_slot(s_texCount)
    {
        glGenTextures(1, &m_id);
    }
    void OpenGLTexture2D::addData(const std::shared_ptr<Image>& image)
    {
        use();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData().data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    void OpenGLTexture2D::use()
    {
        glActiveTexture(getTextSlot(m_slot));
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
    void OpenGLTexture2D::destroy()
    {
        glDeleteTextures(1, &m_id);
    }
    OpenGLTexture2D::~OpenGLTexture2D()
    {
        if (m_id != 0) destroy();
    }
}