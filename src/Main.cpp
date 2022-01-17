#include "Main.h"

using namespace std;

static draw::DrawMode mode = draw::DrawMode::NONE;
static vector<draw::upDraw> drawables = {};
static vector<draw::upDraw> stagedDrawables = {};

int main(int argc, char** argv) {
	const int monitorWidth = GetSystemMetrics(SM_CXSCREEN), monitorHeight = GetSystemMetrics(SM_CYSCREEN);
	const int iniWidth = 800, iniHeight = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(iniWidth, iniHeight);
	glutInitWindowPosition((monitorWidth - iniWidth) / 2, (monitorHeight - iniHeight) / 2);
	glutCreateWindow("Glutwindow(110522089)");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, iniWidth, 0, iniHeight);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMotion);
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	for (auto& d : drawables)
		d->draw();
	glFlush();
}

void keyUp(unsigned char key, int x, int y) {
	draw::DrawMode temp = mode;
	switch (key)
	{
	case 'c' | 'C':
		storeDraw(drawables, stagedDrawables, true);
		cout << "Cleared" << endl;
		break;
	case 'd' | 'D':
		temp = draw::DrawMode::DOT;
		break;
	case 'l' | 'L':
		temp = draw::DrawMode::LINE;
		break;
	case 'o' | 'O':
		temp = draw::DrawMode::CIRCLE;
		break;
	case 'p' | 'P':
		temp = draw::DrawMode::POLYGON;
		break;
	case 'q' | 'Q':
		exit(0);
	case 'r' | 'R':
		storeDraw(stagedDrawables, drawables, false);
		cout << "Redrawed" << endl;
		break;
	default:
		break;
	}
	if (mode == temp)
		return;
	mode = temp;
	cout << "Switch to " << mode << " mode" << endl;
	removeDrawing(drawables);
	display();
}

void mouse(int bin, int state, int x, int y) {
	if (state != GLUT_DOWN)
		return;
	if (bin == GLUT_RIGHT_BUTTON && !drawables.empty()) {
		if (!dynamic_cast<draw::Appendable*>(drawables.back().get()))
			return;
		auto a = dynamic_cast<draw::Appendable*>(drawables.back().get());
		if (!a->isDone())
			a->done();
		else
			return;
		if (a->isDone())
			if (auto p = dynamic_cast<draw::Printable*>(a))
				cout << *p << endl;
		return;
	}
	if (bin != GLUT_LEFT_BUTTON || mode == draw::DrawMode::NONE)
		return;
	if (drawables.empty())
		drawables.emplace_back(newDraw(mode, x, y));
	else if (auto c = dynamic_cast<draw::ICompletable*>(drawables.back().get())) {
		if (c->isDone())
			drawables.emplace_back(newDraw(mode, x, y));
		else if (auto p = dynamic_cast<draw::Appendable*>(c))
			p->append();
	}
	if (auto p = dynamic_cast<draw::Printable*>(drawables.back().get()))
		cout << *p << endl;
}

void mouseMotion(int x, int y) {
	if (drawables.empty())
		return;
	if (auto a = dynamic_cast<draw::Appendable*>(drawables.back().get())) {
		a->buffering(x, y);
		display();
	}
}

draw::upDraw newDraw(const draw::DrawMode mode, const int x, const int y) {
	assert(mode != draw::DrawMode::NONE);
	switch (mode)
	{
	case draw::DrawMode::CIRCLE:
		return make_unique<draw::Circle>(draw::Dot(x, y));
	case draw::DrawMode::DOT:
		return make_unique<draw::Dot>(x, y);
	case draw::DrawMode::LINE:
		return make_unique<draw::Line>(draw::Dot(x, y));
	case draw::DrawMode::POLYGON:
		return make_unique<draw::Polygon>(draw::Dot(x, y));
	default:
		throw new invalid_argument("Error: Unknown argument in DrawMode");
	}
}

void removeDrawing(vector<draw::upDraw>& src) {
	if (src.empty())
		return;
	if (auto p = dynamic_cast<draw::Appendable*>(src.back().get()))
		if (!p->isDone())
			src.pop_back();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	display();
}

void storeDraw(vector<draw::upDraw>& src, vector<draw::upDraw>& dest, const bool isBackInsert) {
	removeDrawing(src);
	dest.insert(isBackInsert ? dest.end() : dest.begin(), make_move_iterator(src.begin()), make_move_iterator(src.end()));
	src.clear();
	assert(src.empty());
	display();
}
