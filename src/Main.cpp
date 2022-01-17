#include "Main.h"

using namespace std;

enum class ContextMode {
	Initial,
	Process
};

constexpr auto title = "Glutwindow - 110522089";
int width = 0, height = 0, offsetX = 0, offsetY = 0;
ContextMode currentMode = ContextMode::Initial;
unique_ptr<draw::Reader> reader = nullptr;
draw::Scene scene;
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
	scene.draw();
	glFlush();
}

void idle() {
	if (!isKeyboardHit("Press any key to continue . . ."))
		return;
	if (currentMode == ContextMode::Initial) {
		const auto& cmdFilename = reader->nextCommandFilename();
		cout << "Input file: " + cmdFilename << endl;
		glutSetWindowTitle(draw::stringFormat("%s (%s)", title, cmdFilename.c_str()).c_str());
		scene.clearObjects();
		scene.shade->reset();
		transMatrix.reset();
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
		case CMD::AMBIENT:
			cout << type << endl;
			scene.shade->setAmbient(draw::Color(stod(args[0]), stod(args[1]), stod(args[2])));
			break;
		case CMD::BACKGROUND:
			cout << type << endl;
			scene.shade->setBackground(draw::Color(stod(args[0]), stod(args[1]), stod(args[2])));
			break;
		case CMD::COMMENT:
			cout << "### " << args[0] << " ###" << endl;
			break;
		case CMD::DISPLAY:
			cout << type << endl;
			scene.update(width, height);
			isDone = reader->peekCommand().getType() != CMD::END;
			display();
			break;
		case CMD::END:
			currentMode = ContextMode::Initial;
			isDone = true;
			break;
		case CMD::LIGHT:
			cout << type << endl;
			scene.shade->addLight(static_cast<size_t>(stoi(args[0]) - 1), draw::Light(draw::Color(stod(args[1]), stod(args[2]), stod(args[3])),
				draw::Point(stod(args[4]), stod(args[5]), stod(args[6]))));
			break;
		case CMD::OBJECT:
			cout << type << ": " << args[0] << endl;
			scene.addObject(make_unique<draw::Object>(draw::Light(draw::Color(stod(args[1]), stod(args[2]), stod(args[3])),
				draw::Point(stod(args[4]), stod(args[5]), stod(args[6]))), reader->getBlueprint(args[0]).buildPolygons(transMatrix)));
			break;
		case CMD::OBSERVER:
			cout << type << endl;
			scene.observer->setEye(draw::EyeMatrix(draw::Point(stod(args[0]), stod(args[1]), stod(args[2])),
				draw::Point(stoi(args[3]), stoi(args[4]), stoi(args[5])), draw::Angle::degrees(stod(args[6]))));
			scene.observer->setProjection(draw::ProjectionMatrix(stod(args[7]), stod(args[8]), draw::Angle::degrees(stod(args[9]))));
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
			cout << type << endl;
			transMatrix.transform(make_shared<const draw::Rotate>(draw::Angle::degrees(stod(args[0])),
				draw::Angle::degrees(stod(args[1])), draw::Angle::degrees(stod(args[2]))));
			break;
		case CMD::SCALE:
			cout << type << endl;
			transMatrix.transform(make_shared<const draw::Scale>(stod(args[0]), stod(args[1]), stod(args[2])));
			break;
		case CMD::TRANSLATE:
			cout << type << endl;
			transMatrix.transform(make_shared<const draw::Translate>(stod(args[0]), stod(args[1]), stod(args[2])));
			break;
		case CMD::VIEWPORT:
			cout << type << endl;
			scene.observer->setViewPort(draw::ViewPort(stod(args[0]), stod(args[1]), stod(args[2]), stod(args[3])));
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
