#include "VertexBuffer.h"

GL::core::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	:m_DataPtr(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	m_BufferSize = (size_t)size;
}

GL::core::VertexBuffer::VertexBuffer(unsigned int count, size_t elementSize)
	:m_DataPtr(0)
{
	//void* mem = std::malloc(count * elementSize);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, (size_t)count * elementSize, nullptr, GL_DYNAMIC_DRAW));
	//free(mem);

	m_BufferSize = (size_t)count * elementSize;
}

void GL::core::VertexBuffer::AddVertexData(const void* data, int size, int offset) {
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void GL::core::VertexBuffer::AddVertexData(const void* data, int size) {
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, m_DataPtr, size, data));
	m_DataPtr += size;
}

void GL::core::VertexBuffer::Empty()
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_BufferSize, nullptr));
	m_DataPtr = 0;
}

GL::core::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void GL::core::VertexBuffer::addPoly(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2, glm::vec4 color, VertexBuffer& vb)
{
	GL::primitive::vertex::TriangleLight t = GL::primitive::vertex::TriangleLight();

	t.v1.LightColor = color;
	t.v1.Position = pos0;

	t.v2.LightColor = color;
	t.v2.Position = pos1;

	t.v3.LightColor = color;
	t.v3.Position = pos2;

	vb.AddVertexData(&t, sizeof(GL::primitive::vertex::TriangleLight));
}

void GL::core::VertexBuffer::addPoly(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2, glm::vec2 texPos0, glm::vec2 texPos1, glm::vec2 texPos2, glm::vec4 color, float texId, VertexBuffer& vb)
{
	GL::primitive::vertex::Triangle t = GL::primitive::vertex::Triangle();

	t.v1.Color = color;
	t.v1.Position = pos0;
	t.v1.TexCoords = texPos0;
	t.v1.TexID = texId;

	t.v2.Color = color;
	t.v2.Position = pos1;
	t.v2.TexCoords = texPos1;
	t.v2.TexID = texId;

	t.v3.Color = color;
	t.v3.Position = pos2;
	t.v3.TexCoords = texPos2;
	t.v3.TexID = texId;

	vb.AddVertexData(&t, sizeof(GL::primitive::vertex::Triangle));
}

void GL::core::VertexBuffer::addPolyN(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2, glm::vec2 texPos0, glm::vec2 texPos1, glm::vec2 texPos2, glm::vec4 color, float texId, VertexBuffer& vb)
{
	GL::primitive::vertex::TriangleN t = GL::primitive::vertex::TriangleN();
	// Calculate Normal
	glm::vec3 normal = glm::normalize(glm::triangleNormal(pos0, pos1, pos2));

	t.v1.Color = color;
	t.v1.Position = pos0;
	t.v1.TexCoords = texPos0;
	t.v1.TexID = texId;
	t.v1.Normal = normal;

	t.v2.Color = color;
	t.v2.Position = pos1;
	t.v2.TexCoords = texPos1;
	t.v2.TexID = texId;
	t.v2.Normal = normal;

	t.v3.Color = color;
	t.v3.Position = pos2;
	t.v3.TexCoords = texPos2;
	t.v3.TexID = texId;
	t.v3.Normal = normal;

	vb.AddVertexData(&t, sizeof(GL::primitive::vertex::TriangleN));
}

void GL::core::VertexBuffer::addLightSource(glm::vec3 position, float sideLength, glm::vec4 color, VertexBuffer& vb)
{
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), color, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), color, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), color, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), color, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), color, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), color, vb);

	addPoly(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), color, vb);
	addPoly(glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), color, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), color, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), color, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), color, vb);
	addPoly(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), color, vb);
}

void GL::core::VertexBuffer::addCube(glm::vec3 position, float sideLength, glm::vec4 color, float texId, VertexBuffer& vb)
{
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(0.f, 1.f), color, texId, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f), color, texId, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), color, texId, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), color, texId, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f), color, texId, vb);

	addPoly(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPoly(glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), color, texId, vb);

	addPoly(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(0.f, 1.f), color, texId, vb);
	addPoly(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), color, texId, vb);
}

void GL::core::VertexBuffer::addCubeN(glm::vec3 position, float sideLength, glm::vec4 color, float texId, VertexBuffer& vb)
{
	// Front
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	// Bottom
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec2(0.f, 0.f), color, texId, vb);
	// Right
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f), color, texId, vb);
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f), color, texId, vb);
	// Left
	addPolyN(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(0.f, 1.f), color, texId, vb);
	addPolyN(glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f), color, texId, vb);
	// Top
	addPolyN(glm::vec3(position.x + sideLength, position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(1.f, 1.f), glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), color, texId, vb);
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z - (sideLength / 2.f)), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), color, texId, vb);
	// Back
	addPolyN(glm::vec3(position.x - (sideLength / 2.f), position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(0.f, 1.f), color, texId, vb);
	addPolyN(glm::vec3(position.x + sideLength, position.y - (sideLength / 2.f), position.z + sideLength), glm::vec3(position.x + sideLength, position.y + sideLength, position.z + sideLength), glm::vec3(position.x - (sideLength / 2.f), position.y + sideLength, position.z + sideLength), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec2(0.f, 1.f), color, texId, vb);
}

void GL::core::VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void GL::core::VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}