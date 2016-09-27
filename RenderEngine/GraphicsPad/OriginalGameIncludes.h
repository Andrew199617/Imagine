#pragma once
#include <gl\glew.h>
#pragma warning(push)
#pragma warning (disable:4127)
#pragma warning (disable:4800)
#pragma warning (disable:4251)
#include <QtOpenGL\qglwidget>
#pragma warning(pop)
#include <Qt\qtimer.h>
#include <Qt\qapplication.h>
#include "Slider.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#pragma warning(push)
#pragma warning (disable:4201)
#include "ShapeGenerator.h"
#pragma warning(pop)
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include <QtGui\qmouseevent>
#pragma warning(pop)
#include <QtGui\qkeyevent>
#include "CameraComponent.h"
#include "GameTime.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "MeModel.h"
#include "Vertex.h"
#include "RenderEngine\RenderInfo.h"
#include "RenderEngine\RenderEngine.h"
#include "RenderEngine\TransformInfo.h"
#include "RenderEngine\VertexShaderInfo.h"
#include "RenderEngine\FragmentShaderInfo.h"
#include "RenderEngine\TextureInfo.h"
#include "VertexFormats.h"
#include "EntityManager.h"
#include "PlayerEntity.h"
#include "KeyboardComponent.h"
#include "MouseComponent.h"
#include "SpatialComponent.h"
#include "ObjController.h"

class MeGlWindow;

using namespace glm;
using namespace std;

const GLuint VERTEX_BYTE_SIZE = sizeof(float) * 9;
const int A = 65;
const int W = 87;
const int S = 83;
const int D = 68;
const int X = 88;
