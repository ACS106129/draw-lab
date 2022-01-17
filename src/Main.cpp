#include "Main.h"

using namespace std;

enum class ContextMode {
	Initial,
	Process
};

constexpr auto title = "Glutwindow - 110522089";
bool isNoBackfaces = false;
int width = 0, height = 0, offsetX = 0, offsetY = 0;
ContextMode currentMode = ContextMode::Initial;
unique_ptr<draw::Reader> reader = nullptr;
draw::Object object;
draw::Observer observer;
draw::TransformMatrix transMatrix;

int main(int argc, char** argv) {
	system("pause");
	vector<string> filenames;
	for (int i = 1; i < argc; ++i)
		filenames.push_back(argv[i]);
	reader = make_unique<draw::Reader>(128, filenames);
	constexpr int iniWidth = 400, iniHeight = 200;
	const int initPosX = (GetSystemMetrics(SM_CXSCREEN) - iniWidth) / 2, initPosY = (GetSystemMetrics(SM_CYSCREEN) - iniHeight) / 2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(iniWidth, iniHeight);
	glutInitWindowPosition(initPosX, initPosY);
	glutCreateWindow(draw::stringFormat("%s (Initial)", title).c_str());
	offsetX = initPosX - glutGet(GLUT_WINDOW_X), offsetY = initPosY - glutGet(GLUT_WINDOW_Y);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	object.draw();
	glFlush();
}

void idle() {
	if (!isKeyboardHit("Press any key to continue . . ."))
		return;
	if (currentMode == ContextMode::Initial) {
		const auto& cmdFilename = reader->nextCommandFilename();
		cout << "Input file: " + cmdFilename << endl;
		glutSetWindowTitle(draw::stringFormat("%s (%s)", title, cmdFilename.c_str()).c_str());
		object.reset();
		transMatrix.reset();
		isNoBackfaces = false;
		currentMode = ContextMode::Process;
		display();
		return;
	}
	using CMD = draw::CommandType;
	for (bool isDone = false; !isDone;) {
		const auto& c = reader->nextCommand();
		const auto& type = c.getType();
		const auto& args = c.getArgs();
		switch (type) {
		case CMD::COMMENT:
			cout << "### " << args[0] << " ###" << endl;
			break;
		case CMD::DISPLAY:
			cout << type << endl;
			object.setView(width, height, observer, isNoBackfaces);
			isDone = reader->peekCommand().getType() != CMD::END;
			display();
			break;
		case CMD::END:
			currentMode = ContextMode::Initial;
			isDone = true;
			break;
		case CMD::NOBACKFACES:
			cout << type << endl;
			isNoBackfaces = true;
			break;
		case CMD::OBJECT:
			cout << type << ": " << args[0] << "\nTM\n" << transMatrix << endl;
			object.addPolygons(reader->getBlueprint(args[0]).buildPolygons(transMatrix));
			break;
		case CMD::OBSERVER:
			observer.setEye(draw::EyeMatrix(draw::Point(stod(args[0]), stod(args[1]), stod(args[2])),
				draw::Point(stoi(args[3]), stoi(args[4]), stoi(args[5])), draw::Angle::degrees(stod(args[6]))));
			observer.setProjection(draw::ProjectionMatrix(stod(args[7]), stod(args[8]), draw::Angle::degrees(stod(args[9]))));
			cout << type << "\nEM\n" << observer.getEyeMatrix() << endl;
			break;
		case CMD::RESET:
			transMatrix.reset();
			break;
		case CMD::RESHAPE:
			glutReshapeWindow(width = stoi(args[0]), height = stoi(args[1]));
			glutPositionWindow(glutGet(GLUT_WINDOW_X) + offsetX - ((width - glutGet(GLUT_WINDOW_WIDTH)) >> 1),
				glutGet(GLUT_WINDOW_Y) + offsetY - ((height - glutGet(GLUT_WINDOW_HEIGHT)) >> 1));
			glutPostRedisplay();
			break;
		case CMD::ROTATE:
			transMatrix.transform(make_shared<const draw::Rotate>(draw::Angle::degrees(stod(args[0])),
				draw::Angle::degrees(stod(args[1])), draw::Angle::degrees(stod(args[2]))));
			cout << type << "\n" << transMatrix << endl;
			break;
		case CMD::SCALE:
			transMatrix.transform(make_shared<const draw::Scale>(stod(args[0]), stod(args[1]), stod(args[2])));
			cout << type << "\n" << transMatrix << endl;
			break;
		case CMD::TRANSLATE:
			transMatrix.transform(make_shared<const draw::Translate>(stod(args[0]), stod(args[1]), stod(args[2])));
			cout << type << "\n" << transMatrix << endl;
			break;
		case CMD::VIEWPORT:
			observer.setViewPort(draw::ViewPort(stod(args[0]), stod(args[1]), stod(args[2]), stod(args[3])));
			cout << type << "\nPM\n" << observer.getProjectionMatrix() << endl;
			break;
		default:
			throw new runtime_error("Command type is not existed!");
		}
	}
}

// only available on windows
bool isKeyboardHit(const char* prompt) {
	static bool isPrompted = false;
	if (!isPrompted) {
		cout << prompt << endl;
		isPrompted = true;
	}
	if (!_kbhit())
		return false;
	isPrompted = false;
	(void)_getch();
	return true;
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display();
}
