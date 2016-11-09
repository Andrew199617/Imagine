#pragma once
#include "OriginalGameIncludes.h"
#include "RenderEngine\FrameBuffer.h"

class ImgnViewport
{

public:
	ImgnViewport();
	~ImgnViewport();
	void SendDataToOpenGL();
	void InitializeGl();
	bool Initialize();
	void Update(bool focus);
	void ProcessKeys(float dt);
	void ProcessMouseMove(QMouseEvent* e);
	void ProcessMousePress(QMouseEvent* e);
	void Draw(float dt);

	static EntityManager entityManager;
	void SetWidth(int Width);
	inline int GetWidth() { return m_Width; }
	void SetHeight(int Height);
	inline int GetHeight() { return m_Height; }

	bool isPlaying;
	int xOffset;
	int yOffset;
private:
	FrameBuffer* frameBuffer;
	int m_Width;
	int m_Height;
	

#pragma warning(push)
#pragma warning (disable:4512)
};
#pragma warning(pop)

