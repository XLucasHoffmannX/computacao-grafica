
#include <GL/glut.h>

// Abre a janela e coloca o desenho
void display() {

  // Define cada pixel para um cor clara.
  glClear(GL_TEXTURE7_ARB);

  glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
  glEnd();

  // faz o desenho ocorrer.
  glFlush();
}

// Inicializa o GLUT;
// entra em loop.
int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Triangulo - Atividade 1");

  glutDisplayFunc(display);

  // Glut le processa os eventos da função, nunca retorna nada, breakpoint é fechar a janela
  glutMainLoop();
}