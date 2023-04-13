#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

using namespace std;

vector<pair<int, int>> points; // vetor para armazenar os pontos
int numPoints = 0; // número de pontos adicionados

void addPoint(int x, int y) {
    points.push_back(make_pair(x, y)); // adiciona as coordenadas do ponto ao final do vetor
    numPoints++; // incrementa o número de pontos
}

void removePoint(int x, int y) {
    int index = -1;
    double minDist = 1e9;
    for (int i = 0; i < numPoints; i++) {
        double dist = sqrt(pow(points[i].first - x, 2) + pow(points[i].second - y, 2)); // calcula a distância do ponto clicado aos pontos armazenados
        if (dist < minDist) {
            index = i; // armazena o índice do ponto mais próximo
            minDist = dist; // armazena a distância mínima encontrada
        }
    }
    if (index != -1) {
        points.erase(points.begin() + index); // remove o ponto do vetor
        numPoints--; // decrementa o número de pontos
    }
}

void drawLines() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numPoints - 1; i++) {
        glVertex2i(points[i].first, points[i].second);
        glVertex2i(points[i+1].first, points[i+1].second);
    }
    glEnd();
    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        addPoint(x, glutGet(GLUT_WINDOW_HEIGHT) - y); // adiciona o ponto na posição (x, y) invertendo a coordenada y
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        removePoint(x, glutGet(GLUT_WINDOW_HEIGHT) - y); // remove o ponto mais próximo ao clique com o botão direito do mouse
    }
    glutPostRedisplay(); // redesenha a janela após o clique do mouse
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Desenhar linhas");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    
    glutDisplayFunc(drawLines);
    glutMouseFunc(mouseClick);
    
    glutMainLoop();
    
    return 0;
}