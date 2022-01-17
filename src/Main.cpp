#include "Main.h"

#define LINE_LENGTH 128

using namespace std;

enum class ContextMode {
	Initial,
	Process
};

int currentCommandIndex = 0;
int currentFilenameIndex = 0;
ContextMode currentMode = ContextMode::Initial;
draw::TransformMatrix transMatrix;
vector<string> filenames;
vector<draw::Command> commands;
vector<std::shared_ptr<draw::Shape>> shapes;
vector<std::unique_ptr<draw::View>> views;

int main(int argc, char** argv) {
	system("pause");
	FILE* file;
	char line[LINE_LENGTH];
	// initialize commands from input file(s)
	for (int i = 1; i < argc; ++i) {
		fopen_s(&file, argv[i], "r");
		assertm(file, "File should open successfully");
		if (!file)
			continue;
		filenames.emplace_back(draw::getFilename<string>(argv[i]));
		while (fgets(line, LINE_LENGTH, file)) {
			if (line[0] == '\n' || line[0] == '\0')
				continue;
			line[strlen(line) - 1] = '\0';
			commands.emplace_back(line);
		}
	}
	if (commands.empty())
		exit(1);
	const int monitorWidth = GetSystemMetrics(SM_CXSCREEN), monitorHeight = GetSystemMetrics(SM_CYSCREEN);
	const int iniWidth = 800, iniHeight = 600;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(iniWidth, iniHeight);
	glutInitWindowPosition((monitorWidth - iniWidth) / 2, (monitorHeight - iniHeight) / 2);
	glutCreateWindow("Glutwindow - 110522089");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, iniWidth, 0, iniHeight);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	for (const auto& v : views)
		v->draw();
	glFlush();
}

void idle() {
	if (!isKeyboardHit("Press any key to continue . . ."))
		return;
	if (currentMode == ContextMode::Initial) {
		cout << "Input file: " + filenames[currentFilenameIndex] << endl;
		currentFilenameIndex = (currentFilenameIndex + 1) % filenames.size();
		transMatrix.reset();
		views.clear();
		shapes.clear();
		currentMode = ContextMode::Process;
		display();
		return;
	}
	for (bool isDone = false; !isDone; currentCommandIndex = (currentCommandIndex + 1) % commands.size()) {
		const auto& c = commands[currentCommandIndex];
		switch (c.getType()) {
		case draw::CommandType::CLEAR_DATA:
			assertm(c.getArgs().size() == 0, "Clear data no args");
			shapes.clear();
			break;
		case draw::CommandType::CLEAR_SCREEN:
			assertm(c.getArgs().size() == 0, "Clear screen no args");
			views.clear();
			break;
		case draw::CommandType::COMMENT:
			assertm(c.getArgs().size() == 1, "Comment need exists and only one per line");
			cout << "### " << c.getArgs().front() << " ###" << endl;
			break;
		case draw::CommandType::END:
			assertm(c.getArgs().size() == 0, "End no args");
			currentMode = ContextMode::Initial;
			isDone = true;
			break;
		case draw::CommandType::RESET:
			assertm(c.getArgs().size() == 0, "Reset no args");
			transMatrix.reset();
			break;
		case draw::CommandType::ROTATE:
			assertm(c.getArgs().size() == 1, "Degree is only one arg");
			transMatrix.transform(new draw::Rotate(draw::Angle::degrees(stod(c.getArgs()[0]))));
			cout << "Rotate\n" << transMatrix << endl;
			break;
		case draw::CommandType::SCALE:
			assertm(c.getArgs().size() == 2, "Scale are exactly two args");
			transMatrix.transform(new draw::Scale(stod(c.getArgs()[0]), stod(c.getArgs()[1])));
			cout << "Scale\n" << transMatrix << endl;
			break;
		case draw::CommandType::SQUARE:
			assertm(c.getArgs().size() == 0, "Square no args");
			shapes.emplace_back(new draw::Square);
			shapes.back()->setTransformMatrix(transMatrix);
			cout << draw::stringFormat("You have %d square(s)", std::count_if(shapes.cbegin(), shapes.cend(),
				[](const auto& s) { return dynamic_cast<draw::Square*>(s.get()); })) << endl;
			break;
		case draw::CommandType::TRANSLATE:
			assertm(c.getArgs().size() == 2, "Translate are exactly two args");
			transMatrix.transform(new draw::Translate(stod(c.getArgs()[0]), stod(c.getArgs()[1])));
			cout << "Translate\n" << transMatrix << endl;
			break;
		case draw::CommandType::TRIANGLE:
			assertm(c.getArgs().size() == 0, "Triangle no args");
			shapes.emplace_back(new draw::Triangle);
			shapes.back()->setTransformMatrix(transMatrix);
			cout << draw::stringFormat("You have %d triangle(s)", std::count_if(shapes.cbegin(), shapes.cend(),
				[](const auto& s) { return dynamic_cast<draw::Triangle*>(s.get()); })) << endl;
			break;
		case draw::CommandType::VIEW:
			assertm(c.getArgs().size() == 8, "View need two ports of 8 arguments");
			views.emplace_back(new draw::View(
				draw::ViewPort{ stod(c.getArgs()[0]), stod(c.getArgs()[1]), stod(c.getArgs()[2]), stod(c.getArgs()[3]) },
				draw::ViewPort{ stod(c.getArgs()[4]), stod(c.getArgs()[5]), stod(c.getArgs()[6]), stod(c.getArgs()[7]) }));
			for (const auto& s : shapes)
				views.back()->add(s);
			cout << "View\nWVM\n" << *views.back() << endl;
			// if next command is end will continue
			isDone = commands[(currentCommandIndex + 1) % commands.size()].getType() != draw::CommandType::END;
			break;
		default:
			throw new runtime_error("Command type is not existed!");
		}
	}
	display();
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
	display();
}
