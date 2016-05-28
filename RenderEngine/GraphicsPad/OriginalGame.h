#pragma once
#include "OriginalGameIncludes.h"

class OriginalGame
{

public:
	OriginalGame();
	~OriginalGame();
	void SendDataToOpenGL();
	bool Initialize(MeGlWindow* meGlWindow);
	bool Shutdown();
	void Update();
	void ProcessKeys(float dt);
	void ProcessMouse(QMouseEvent* e);
	void Draw();
	MeModel* getModel()
	{
		return &theModel;
	}
private:

	MeModel theModel;
	bool pause;
	int timebeforeunpause;


#pragma warning(push)
#pragma warning (disable:4512)
};
#pragma warning(pop)

