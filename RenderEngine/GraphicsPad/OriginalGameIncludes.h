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
#include "VertexFormats.h"
#include "EntityManager.h"
#include "PlayerEntity.h"
#include "KeyboardComponent.h"
#include "MouseComponent.h"
#include "SpatialComponent.h"

using namespace std;

