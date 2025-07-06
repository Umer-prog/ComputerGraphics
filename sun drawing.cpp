#include <cmath>
#include "glut.h"
#include <Windows.h>
//
//
const int numTriangles = 12; // Number of triangles around the circle
const float triangleGap = 0.05f; // Space between triangles
#define M_PI 3.14159265358979323846
//
void drawSunWithTriangles() {
    float circleRadius = 0.3f;
    float triangleRadius = 0.5f; // Distance from center to the triangle tip
    float angleIncrement = 2.0f * M_PI / numTriangles;

    // Draw the center circle
    glColor3f(1.0, 1.0, 0.0); // Yellow color for the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the circle
    for (int i = 0; i <= 100; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(100);
        float x = circleRadius * cosf(theta);
        float y = circleRadius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw isosceles triangles around the circumference
    glColor3f(1.0, 0.6, 0.0); // Orange color for the triangles
    for (int i = 0; i < numTriangles; ++i) {
        float angle = i * angleIncrement;

        // Vertex at the tip of the triangle
        float x1 = triangleRadius * cosf(angle);
        float y1 = triangleRadius * sinf(angle);

        // Base points of the triangle with added gap
        float x2 = (circleRadius + triangleGap) * cosf(angle + angleIncrement / 2);
        float y2 = (circleRadius + triangleGap) * sinf(angle + angleIncrement / 2);

        float x3 = (circleRadius + triangleGap) * cosf(angle - angleIncrement / 2);
        float y3 = (circleRadius + triangleGap) * sinf(angle - angleIncrement / 2);

        glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }

    glFlush();
}

 void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSunWithTriangles();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sun Design with Isosceles Triangles");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
