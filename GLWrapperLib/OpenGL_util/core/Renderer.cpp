#include "Renderer.h"
#include <iostream>

void GL::core::GLContext::Init()
{
	GLCall(glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &FramebufferOriginId));
}

void GL::core::GLContext::BindOrigFramebuffer()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferOriginId));
}

void GL::core::GLContext::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::core::GLContext::ClearDepthBufferOnly()
{
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
}

void GL::core::GLContext::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int mode, int count)
{
	size_t c = count == -1 ? ib.GetCount() : (size_t)count;
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(mode, (int)c, GL_UNSIGNED_INT, nullptr));
}

void GL::core::GLContext::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, size_t count)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, (int)count, GL_UNSIGNED_INT, nullptr));
}

void GL::core::GLContext::DrawArray(const VertexArray& va, const Shader& shader, size_t first, size_t count)
{
	shader.Bind();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, (int)first, (int)count);
}

void GL::core::GLContext::DrawInstancedLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, size_t count, size_t instances)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElementsInstanced(GL_LINES, (int)count, GL_UNSIGNED_INT, nullptr, (int)instances));
}