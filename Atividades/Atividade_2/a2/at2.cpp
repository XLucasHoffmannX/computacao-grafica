#include <iostream>
#include <vector>
#include <math.h>
#include <GL/glut.h>

using namespace std;

// variáveis globais
int windowHeight = 500;
int windowWidth = 500;
vector<pair<double, double>> points; // armazena as coordenadas dos pontos
int selectedPoint = -1;              // armazena o índice do ponto selecionado para mover (-1 se nenhum ponto estiver selecionado)
double currentX = 0.0;               // armazena a coordenada x do ponto atual (selecionado para mover)
double currentY = 0.0;               // armazena a coordenada y do ponto atual (selecionado para mover)

// função para desenhar os pontos
void drawPoints()
{
    for (int i = 0; i < points.size(); i++)
    {
        double x = points[i].first;
        double y = points[i].second;
        glColor3f(1.0, 0.0, 0.0); // cor vermelha
        glBegin(GL_POLYGON);      // desenha um quadrado em volta do ponto selecionado (se houver)
        if (i == selectedPoint)
        {
            glVertex2f(x - 5, y - 5);
            glVertex2f(x - 5, y + 5);
            glVertex2f(x + 5, y + 5);
            glVertex2f(x + 5, y - 5);
        }
        glEnd();
        glColor3f(0.0, 0.0, 1.0); // cor azul
        glBegin(GL_POINTS);       // desenha o ponto
        glVertex2f(x, y);
        glEnd();
    }
}

// função para desenhar na tela
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoints();
    glutSwapBuffers();
}

// função para redimensionar a janela
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

// função para tratar o clique do mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // adiciona um novo ponto com as coordenadas do clique
        points.push_back(make_pair((double)x, (double)(windowHeight - y)));
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // seleciona o ponto mais próximo do clique
        double minDistance = INFINITY;
        for (int i = 0; i < points.size(); i++)
        {
            double distance = sqrt(pow((double)x - points[i].first, 2.0) + pow((double)(windowHeight - y) - points[i].second, 2.0));
            if (distance < minDistance)
            {
                minDistance = distance;
                selectedPoint = i;
                currentX = points[i].first;
                currentY = points[i].second;
            }
        }
    }
    glutPostRedisplay(); // redesenha a cena
}

// função para tratar o movimento das setas do teclado
void arrowKeys(int key, int x, int y)
{
    if (selectedPoint != -1)
    { // se houver um ponto selecionado para mover
        switch (key)
        {
        case GLUT_KEY_UP:
            currentY += 5.0; // move o ponto para cima
            break;
        case GLUT_KEY_DOWN:
            currentY -= 5.0; // move o ponto para baixo
            break;
        case GLUT_KEY_LEFT:
            currentX -= 5.0; // move o ponto para a esquerda
            break;
        case GLUT_KEY_RIGHT:
            currentX += 5.0; // move o ponto para a direita
            break;
        }
        // atualiza as coordenadas do ponto selecionado
        points[selectedPoint].first = currentX;
        points[selectedPoint].second = currentY;
        glutPostRedisplay(); // redesenha a cena
    }
}

// função principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Moving Points");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(arrowKeys); // registra a função para tratar as setas do teclado
    glutMainLoop();
    return 0;
}