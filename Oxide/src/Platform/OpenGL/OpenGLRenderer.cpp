#include "OpenGLRenderer.h"
#include "glad/glad.h"

namespace Oxide {
	void OpenGLRenderer::setClearColour(float r, float g, float b, float a)
	{
		glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
	void OpenGLRenderer::setClearColour(uint32_t color)
	{
		float r = float((0xff000000 & color) >> 24);
		float g = float((0x00ff0000 & color) >> 16);
		float b = float((0x0000ff00 & color) >> 8 );
		float a = float((0x000000ff & color) >> 0 );

		setClearColour(r, g, b, a);
	}
	void OpenGLRenderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}