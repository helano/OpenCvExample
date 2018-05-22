#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

int win_width = 500;
int win_height = 500;
int view_mode = 0; //0-Ambs,1-Viewport,2-Ortho

void display(void) {
	
	glMatrixMode(GL_MODELVIEW); //Informa que as opera��es seguintes ser�o executadas na matrix modelview
	glLoadIdentity(); //Carrega a matriz identidade

	glClear(GL_COLOR_BUFFER_BIT);//Inicializa o buffer de cores antes de ele ser alterado
	glLineWidth(3); //Espessura das linhas a serem desenhadas

	glColor3f(0.0f, 0.0f, 0.0f); //Define a cor do desenho em formato RGB
	glBegin(GL_LINES); //Indica que ser�o tra�adas linhas com os pontos a seguir
	glVertex2i(-500 / 2.0f, 0); //Especifica pontos no espa�o bidimensional (pixels)
	glVertex2i(500 / 2.0f, 0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(0, -500 / 2.0f);
	glVertex2i(0, 500 / 2.0f);
	glEnd();//Encerra a cria��o de linhas

	glPushMatrix(); //Empilha a atual matriz de transforma��o (nova inst�ncia para aplicar transforma��es)
	{
		glTranslatef(100.0f, 100.0f, 0.0f); //Aplica transla��o no formato XYZ
		glRotatef(90.0f, 0, 0, 1); //Aplica rota��o (graus em determinados eixos)
		glTranslatef(-100.0f, -100.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLES); //Indica que ser�o gerados tri�ngulo usando os pr�ximos pontos
		glVertex2i(50, 50);
		glVertex2i(150, 50);
		glVertex2i(100, 150);
		glEnd();//Encerra a cria��o de tri�ngulos
	}
	glPopMatrix(); //Empilha a atual matriz de transforma��o (nova inst�ncia para aplicar transforma��es)

	glFlush(); //Informa que as opera��es devem ser processadas imediatamente e exibidas na tela
}

void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Define a cor de fundo da cena (cor usada para limpar o buffer de cor)
}

/*Recebe um o comprimento (width) e altura (height) da janela em pixels.*/
void resize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glMatrixMode(GL_PROJECTION);//Carrega a matriz de proje��o (visualiza��o)
	glLoadIdentity();

	switch (view_mode) {
	case 0:
		gluOrtho2D(-(w / 2.0f), (w / 2.0f), -(h / 2.0f), (h / 2.0f)); //Define o tamanho do cubo de visualiza��o em rela��o ao cen�rio
		glViewport(0, 0, w, h); //Define o tamanho do viewport
		break;
	case 1:
		gluOrtho2D(-(win_width / 2.0f), (win_width / 2.0f),
				-(win_height / 2.0f), (win_height / 2.0f));
		glViewport(0, 0, w, h);
		break;
	case 2:
		gluOrtho2D(-(w / 2.0f), (w / 2.0f), -(h / 2.0f), (h / 2.0f));
		glViewport(0, 0, win_width, win_height);
		break;
	default:
		break;
	}

}

/*Recebe um c�digo para cada tecla (ASCII) e as coordenadas do mouse.*/
void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 27:
		exit(0);
		break;
	case 32:
		++view_mode;
		view_mode = (view_mode) % 3;
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv); //Inicializa a OpenGL
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Configura os modos de exibi��o (mais detalhes no futuro)
	glutInitWindowSize(win_width, win_height); //Define o tamanho da janela em pixels
	glutInitWindowPosition(0, 0); //Define a posi��o inicial da janela
	glutCreateWindow("Pratica01"); //Cria a janela especificando seu t�tulo
	glutDisplayFunc(display); //Especifica a fun��o de rendering (exibe a cena no loop)
	glutReshapeFunc(resize); //Especifica fun��o a ser executada quando a janela � redimensionada
	glutKeyboardFunc(keyboard); //Especifica fun��o a ser executada quando uma tecla � pressionada
	init();
	glutMainLoop(); //Executa o loop de renderiza��o
	return 0;
}
