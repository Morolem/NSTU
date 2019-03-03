//#include "includes.h"
//#include "menu.cpp"
#include <stdlib.h>
#include "gl/freeglut.h"
#include <windows.h>
#include <vector>
using namespace std;
GLint Width = 1366, Height = 768;
int number_figure = 0; // текущая позиция
int max_number_figure = 0; // всего групп

enum keys { Empty, KeyR, KeyG, KeyB, KeyW, KeyA, KeyS, KeyD, KeyU, KeyI };

struct type_lines
{
	vector<GLfloat> xy;
	vector<GLfloat> Color;
	GLubyte point_size; // размер фигуры

	type_lines()
	{
		point_size = 4;
		Color = { 0, 0, 0 }; // черный цвет по умолчанию
	}

};
vector <type_lines> Points(1);

void draw_broken_line(type_lines pVer)
{
	glLineWidth(pVer.point_size);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pVer.xy.data());
	glColor3b(pVer.Color[0], pVer.Color[1], pVer.Color[2]);
	glDrawArrays(GL_LINE_STRIP, 0, pVer.xy.size() / 2);
	glPointSize(pVer.point_size + 5);
	glBegin(GL_POINTS);
	for (int i = 0; i < pVer.xy.size(); i += 2)
	{
		glColor3fv(pVer.Color.data());
		glVertex2f(pVer.xy[i], pVer.xy[i + 1]);
	}
	glEnd();
	glDisableClientState(GL_VERTEX_ARRAY);
}

/* Функция вывода на экран */
void Display(void)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	for (int i = 0; i < max_number_figure + 1; i++)
	{
		if (i != number_figure)		glEnable(GL_POINT_SMOOTH);
		else glDisable(GL_POINT_SMOOTH);
		draw_broken_line(Points[i]);
	}

	glFinish();
}

/* Функция изменения размеров окна */
void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Функция обработки сообщений от клавиатуры */
void Keyboard(unsigned char key, int x, int y)

{
	int i, n = Points[number_figure].xy.size();
	if (key == '+') { // увеличиваем размер линий
		Points[number_figure].point_size += 2;
		if (Points[number_figure].point_size > 20) Points[number_figure].point_size = 2;
		/* 20 - максимальный размер отображаемный на экране, поэтому зацикливаем размер сбрасывая его до 2
		при привышении 20 */
	}
	if (key == '-') { // уменьшаем размер линий
		Points[number_figure].point_size -= 2;
		if (Points[number_figure].point_size > 20) Points[number_figure].point_size = 20;
	}
	/* Изменение RGB-компонент цвета точек */
	if (key == 'r' || key == 'R') Points[number_figure].Color[0] += 5;
	if (key == 'g' || key == 'G') Points[number_figure].Color[1] += 5;
	if (key == 'b' || key == 'B') Points[number_figure].Color[2] += 5;
	/* Изменение XY-кординат точек */
	if (key == 'w' || key == 'W') for (i = 1; i < n; i += 2) Points[number_figure].xy[i] += 15;
	if (key == 's' || key == 'S') for (i = 1; i < n; i += 2) Points[number_figure].xy[i] -= 15;
	if (key == 'a' || key == 'A') for (i = 0; i < n; i += 2) Points[number_figure].xy[i] -= 15;
	if (key == 'd' || key == 'D') for (i = 0; i < n; i += 2) Points[number_figure].xy[i] += 15;
	if (key == '1' && number_figure != 0) number_figure--; // ← предыдущая фигура
	if (key == '2' && number_figure != max_number_figure) number_figure++; // → следующая фигура
	if (key == VK_ESCAPE)
		if (MessageBox(NULL, (LPCTSTR)"Закрыть программу?", (LPCTSTR)"Выход",
			MB_YESNO |
			MB_ICONQUESTION |
			MB_APPLMODAL) == IDYES)		exit(1); // Esc - end programm
	if (key == VK_SPACE) { // переходим к следующей группе элементов
		Points.resize(Points.size() + 1);
		max_number_figure++;
		number_figure = max_number_figure; // переход с текущей группы на созданную
	}
	glutPostRedisplay();
}

/* Функция обработки сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
	/* клавиша была нажата, но не отпущена */
	if (state != GLUT_DOWN) return;
	/* новая точка по левому клику */
	if (button == GLUT_LEFT_BUTTON)
	{
		Points[number_figure].xy.push_back(x);
		Points[number_figure].xy.push_back(Height - y);
	}

	/* удаление последней точки по правому клику */
	if (button == GLUT_RIGHT_BUTTON)
		/*если в текущей группе еще есть точки, удаляем*/
		if (Points[number_figure].xy.size()) {
			Points[number_figure].xy.pop_back(); // удаление y
			Points[number_figure].xy.pop_back(); // удаление x
		}

		else  if (number_figure) { // иначе, если группа пуста и не является первой
			Points.erase(Points.begin() + number_figure); // удаляем данную группу
			max_number_figure--;
			number_figure--; // смещаемся к предыдущей группе
		}


	glutPostRedisplay();
}

void Menu(int pos)
{
	int key = (keys)pos;

	switch (key)
	{
	case KeyR: Keyboard('r', 0, 0); break;
	case KeyG: Keyboard('g', 0, 0); break;
	case KeyB: Keyboard('b', 0, 0); break;
	case KeyW: Keyboard('w', 0, 0); break;
	case KeyS: Keyboard('s', 0, 0); break;
	case KeyA: Keyboard('a', 0, 0); break;
	case KeyD: Keyboard('d', 0, 0); break;
	case KeyU: Keyboard('u', 0, 0); break;
	case KeyI: Keyboard('i', 0, 0); break;

	default:
		int menu_color = glutCreateMenu(Menu);
		glutAddMenuEntry("Компонента R", KeyR);
		glutAddMenuEntry("Компонента G", KeyG);
		glutAddMenuEntry("Компонента B", KeyB);

		int menu_move = glutCreateMenu(Menu);
		glutAddMenuEntry("Вверх", KeyW);
		glutAddMenuEntry("Вниз", KeyS);
		glutAddMenuEntry("Bлево", KeyA);
		glutAddMenuEntry("Вправо", KeyD);

		int menu_size = glutCreateMenu(Menu);
		glutAddMenuEntry("Увеличить", KeyU);
		glutAddMenuEntry("Уменьшить", KeyI);

		int menu = glutCreateMenu(Menu);
		glutAddSubMenu("Смена цвета", menu_color);
		glutAddSubMenu("Перемещение", menu_move);
		glutAddSubMenu("Изменение размера точки", menu_size);

		glutAttachMenu(GLUT_MIDDLE_BUTTON);
		Keyboard(Empty, 0, 0);
	}
}


/* Головная программа */
int main(int argc, char *argv[])

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Рисуем точки");
	//printf("%s\n", glGetString(GL_VERSION));
	Menu(Empty);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
}
