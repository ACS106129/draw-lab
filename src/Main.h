#pragma once
#include <cassert>
#include <conio.h>
#include <GL/glut.h>
#include <iostream>
#include "draw/Point.h"
#include "draw/command/Command.h"
#include "draw/reader/Reader.h"
#include "draw/transform/Rotate.h"
#include "draw/transform/Scale.h"
#include "draw/transform/Translate.h"
#include "draw/matrix/eye/EyeMatrix.h"
#include "draw/matrix/eye/GeneralRotationMatrix.h"
#include "draw/matrix/eye/MirrorMatrix.h"
#include "draw/matrix/eye/TiltMatrix.h"
#include "draw/matrix/projection/ProjectionMatrix.h"
#include "draw/matrix/transform/TransformMatrix.h"
#include "draw/object/Blueprint.h"
#include "draw/object/Object.h"
#include "draw/util/Util.h"
#include "draw/view/Observer.h"
#include "draw/view/ViewPort.h"

void display();
void idle();
bool isKeyboardHit(const char*);
void reshape(int, int);
