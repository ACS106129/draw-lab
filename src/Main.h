#pragma once
#include <cassert>
#include <conio.h>
#include <GL/glut.h>
#include <iostream>
#include "draw/command/Command.h"
#include "draw/shape/Square.h"
#include "draw/shape/Triangle.h"
#include "draw/transform/Rotate.h"
#include "draw/transform/Scale.h"
#include "draw/transform/Translate.h"
#include "draw/util/Util.h"
#include "draw/view/View.h"

#define assertm(exp, msg) assert(((void)msg, exp))

void display();
void idle();
bool isKeyboardHit(const char*);
void reshape(int, int);
