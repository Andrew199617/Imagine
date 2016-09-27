#pragma once
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qkeyevent>
#pragma warning(pop)

class ObjController
{
public:
	enum TransformationType
	{
		Move,
		Scale,
		Rotate
	};

	ObjController();
	~ObjController();

	TransformationType curType;
	void Update();
};

