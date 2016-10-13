#pragma once
#include "OriginalGameIncludes.h"
#include "RenderEngine\FrameBuffer.h"

class OriginalGame
{

public:
	OriginalGame();
	~OriginalGame();
	void SendDataToOpenGL();
	void InitializeGl();
	bool Initialize();
	void Update(bool focus);
	void ProcessKeys(float dt);
	void ProcessMouseMove(QMouseEvent* e);
	void ProcessMousePress(QMouseEvent* e);
	void Draw(float dt);
	MeModel* getModel()
	{
		return &theModel;
	}

	static EntityManager entityManager;
	inline void SetWidth(int width) { m_Width = width; delete frameBuffer; frameBuffer = new FrameBuffer; frameBuffer->GenerateFBO(m_Width, m_Height); }
	inline int GetWidth() { return m_Width; }
	inline void SetHeight(int height) { m_Height = height; delete frameBuffer; frameBuffer = new FrameBuffer; frameBuffer->GenerateFBO(m_Width, m_Height);}
	inline int GetHeight() { return m_Height; }

	bool isPlaying;
	int xOffset;
	int yOffset;
private:
	FrameBuffer* frameBuffer;
	int m_Width;
	int m_Height;
	
	MeModel theModel;


#pragma warning(push)
#pragma warning (disable:4512)
};
#pragma warning(pop)

