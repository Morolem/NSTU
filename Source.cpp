#include <stdlib.h>
#include <windows.h>
#include "glut.h"
#include <vector>
#include <locale.h>
using namespace std;
GLint Width = 600, Height = 300;
int number_figure = 0; // текущая позиция
GLint colorR = 255, colorB = 255, colorG = 255;

enum keys { Empty, KeyR, KeyG, KeyB, KeyW, KeyA, 
			KeyS, KeyD, KeyU, KeyI, KeyEnd, KeyHome,
			KeyDel};

struct type_lines
{
	vector<GLfloat> xy;
	vector<GLubyte> Color;
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
	glColor3ub(pVer.Color[0], pVer.Color[1], pVer.Color[2]);
	glDrawArrays(GL_LINE_STRIP, 0, pVer.xy.size() / 2);
	glPointSize((GLfloat)pVer.point_size+5);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < pVer.xy.size(); i += 2)
	{
		glColor3ubv(pVer.Color.data());
		glVertex2f(pVer.xy[i], pVer.xy[i + 1]);
	}
	glEnd();
	glDisableClientState(GL_VERTEX_ARRAY);
}

/* Функция вывода на экран */
void Display(void)
{
	glClearColor(colorR, colorG, colorB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
		

	for (unsigned int i = 0; i < Points.size(); i++)
	{
		if(i != number_figure)		glEnable(GL_POINT_SMOOTH);
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
	if (key == 'r' || key == 'R') Points[number_figure].Color[0] += 15;
	if (key == 'g' || key == 'G') Points[number_figure].Color[1] += 15;
	if (key == 'b' || key == 'B') Points[number_figure].Color[2] += 15;
	if (key == '1') {
		Points[number_figure].Color[0] = 255;
		Points[number_figure].Color[1] = 0;
		Points[number_figure].Color[2] = 0;
	}
	if (key == '2') {
		Points[number_figure].Color[0] = 0;
		Points[number_figure].Color[1] = 255;
		Points[number_figure].Color[2] = 0;
	}
	if (key == '3') {
		Points[number_figure].Color[0] = 0;
		Points[number_figure].Color[1] = 0;
		Points[number_figure].Color[2] = 255;
	}

	if (key == '4') {
		colorR = 255;
		colorG = 255;
		colorB = 255;
	}

	if (key == '5') {
		colorR = 1;
		colorG = 1;
		colorB = 0;
	}

	if (key == '6') {
		colorR = 0;
		colorG = 1;
		colorB = 1;
	}

	if (key == '7') {
		colorR = 1;
		colorG = 0;
		colorB = 1;
	}

	/* Изменение XY-кординат точек */
	if (key == 'w' || key == 'W') for (i = 1; i < n; i += 2) Points[number_figure].xy[i] += 15;
	if (key == 's' || key == 'S') for (i = 1; i < n; i += 2) Points[number_figure].xy[i] -= 15;
	if (key == 'a' || key == 'A') for (i = 0; i < n; i += 2) Points[number_figure].xy[i] -= 15;
	if (key == 'd' || key == 'D') for (i = 0; i < n; i += 2) Points[number_figure].xy[i] += 15;
	
	if (key == VK_ESCAPE)
		if (MessageBoxW(NULL, 
			L"Закрыть программу?",
			L"Выход",
			MB_YESNO |
			MB_ICONQUESTION |
			MB_APPLMODAL) == IDYES)		exit(1); // Esc - end programm
	if (key == VK_SPACE && Points[number_figure].xy.size() ) { /* переходим к следующей группе элементов,
															   если текущая группа не пуста*/
		Points.resize(Points.size() + 1);
		number_figure = Points.size() - 1; // переход с текущей группы на созданную
	}
	glutPostRedisplay();
}

void Func_Keyboard(int key, int x, int y)

{
	if (key == GLUT_KEY_LEFT  && number_figure != 0) number_figure--; // ← предыдущая фигура
	if (key == GLUT_KEY_RIGHT && (unsigned int)number_figure < Points.size() - 1) number_figure++; // → следующая фигура
	if (key == GLUT_KEY_UP) { // увеличиваем размер линий
		Points[number_figure].point_size += 2;
		if (Points[number_figure].point_size > 20) Points[number_figure].point_size = 2;
		/* 20 - максимальный размер отображаемный на экране, поэтому зацикливаем размер сбрасывая его до 2
		при привышении 20 */
	}
	if (key == GLUT_KEY_DOWN) { // уменьшаем размер линий
		Points[number_figure].point_size -= 2;
		if (Points[number_figure].point_size > 20) Points[number_figure].point_size = 20;
	}
	if (key == GLUT_KEY_END) number_figure = Points.size() - 1; // выбор последней группы
	if (key == GLUT_KEY_HOME) number_figure = 0; // выбор первой группы
	if (key == GLUT_KEY_PAGE_DOWN)
		if (MessageBoxW(NULL,
			L"Удалить данную группу и перейти к предыдущей?",
			L"Удаление",
			MB_YESNO |
			MB_ICONQUESTION |
			MB_APPLMODAL) == IDYES && number_figure != 0) { // иначе, если группа пуста и не является первой
			Points.erase(Points.begin() + number_figure); // удаляем данную группу			
			number_figure--;
		} // смещаемся к предыдущей группе
		else if (number_figure == 0) Points[number_figure].xy.clear();
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
	if (button == GLUT_RIGHT_BUTTON) {
		/*если в текущей группе еще есть точки, удаляем*/
		if (Points[number_figure].xy.size()) {
			Points[number_figure].xy.pop_back(); // удаление y
			Points[number_figure].xy.pop_back(); // удаление x
		}

		else  if (number_figure &&
				MessageBoxW(NULL,
				L"Удалить данную группу и перейти к предыдущей?",
				L"Удаление",
				MB_YESNO |
				MB_ICONQUESTION |
				MB_APPLMODAL) == IDYES) { // иначе, если группа пуста и не является первой
			Points.erase(Points.begin() + number_figure); // удаляем данную группу			
			number_figure--; // смещаемся к предыдущей группе
		}
		if (number_figure < 0) number_figure = 0;
	}
	glutPostRedisplay();
}

//void MotionMouse(int x, int y)
//{
//	if(Points[number_figure].xy.size())
//		for (int i = 0; i < Points.size(); i += 2)
//		{
//			Points[number_figure].xy[i] = x;
//			Points[number_figure].xy[i + 1] = Height - y;
//			//glutPostRedisplay();
//		}
//	glutPostRedisplay();
//}

void Menu(int pos)
{
	int key = (keys)pos;

	switch (key)
	{
	case KeyR: Keyboard('1', 0, 0); break;
	case KeyG: Keyboard('2', 0, 0); break;
	case KeyB: Keyboard('3', 0, 0); break;
	case KeyW: Keyboard('w', 0, 0); break;
	case KeyS: Keyboard('s', 0, 0); break;
	case KeyA: Keyboard('a', 0, 0); break;
	case KeyD: Keyboard('d', 0, 0); break;
	case KeyU: Keyboard('+', 0, 0); break;
	case KeyI: Keyboard('-', 0, 0); break;
	case KeyEnd: Func_Keyboard(GLUT_KEY_END, 0, 0); break;
	case KeyHome: Func_Keyboard(GLUT_KEY_HOME, 0, 0); break;
	case KeyDel: Func_Keyboard(GLUT_KEY_F12, 0, 0); break;

	default:
		int menu_color = glutCreateMenu(Menu);
		glutAddMenuEntry("Красный        | R", KeyR);
		glutAddMenuEntry("Зеленый        | G", KeyG);
		glutAddMenuEntry("Голубой        | B", KeyB);

		int menu_move = glutCreateMenu(Menu);
		glutAddMenuEntry("Вверх          | W", KeyW);
		glutAddMenuEntry("Вниз           | S", KeyS);
		glutAddMenuEntry("Bлево          | A", KeyA);
		glutAddMenuEntry("Вправо         | D", KeyD);
		glutAddMenuEntry("В конец        | end", KeyEnd);
		glutAddMenuEntry("В начало       | home", KeyHome);
		glutAddMenuEntry("Удалить группу | F12", KeyDel);

		int menu_size = glutCreateMenu(Menu);
		glutAddMenuEntry("Увеличить      | +", KeyU);
		glutAddMenuEntry("Уменьшить      | -", KeyI);

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
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	Height = glutGet(GLUT_SCREEN_HEIGHT);
	Width = glutGet(GLUT_SCREEN_WIDTH);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Рисуем точки");
	glutFullScreen();
	printf("%s\n", glGetString(GL_VERSION));
	Menu(Empty);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Func_Keyboard);
	glutMouseFunc(Mouse);
	//glutMotionFunc(MotionMouse);
	glutMainLoop();
}
