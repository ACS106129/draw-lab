#pragma once
#include <cassert>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "draw/Circle.h"
#include "draw/Dot.h"
#include "draw/mode/DrawMode.h"
#include "draw/Line.h"
#include "draw/Polygon.h"

void display();
void keyUp(unsigned char, int, int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
draw::upDraw newDraw(const draw::DrawMode, const int, const int);
void removeDrawing(std::vector<draw::upDraw>& src);
void reshape(int, int);
void storeDraw(std::vector<draw::upDraw>&, std::vector<draw::upDraw>&, const bool);
