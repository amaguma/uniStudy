#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GLFW/glfw3.h>


#define PI 3.14159265

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

GLfloat rotationX = 0;
GLfloat rotationY = 0;
GLfloat rotationZ = 0;
GLfloat hW = 0;
GLfloat hH = 0;



GLfloat x = 0.5;
GLfloat y = 0.5;
GLfloat z = 0.5;

GLfloat RAD = 180 / PI;
GLfloat edge_C = 0.07;


struct Point {
    GLfloat x, y, z;

    Point(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

};

struct Anti {
    std::vector<Point> top, bottom, edges;
    int n;
    GLfloat r, h;
    bool mode = true;

    Point multiplication(GLfloat k, Point p1) {
        p1.x = k * p1.x;
        p1.y = k * p1.y;
        return p1;
    }

    void buildPoints() {
        top.clear();
        bottom.clear();
        edges.clear();
        for (int i = 0; i < 360; i += 360 / n) {
            Point p1{ r * std::cos(i / RAD), r * std::sin(i / RAD), h / 2 };
            Point p2{ r * std::cos(i / RAD), r * std::sin(i / RAD), -h / 2 };
            top.push_back(p1);
            bottom.push_back(p2);
          
        }
        GLfloat teta = PI / n;
        GLfloat cosT = std::cos(teta);
        GLfloat sinT = std::sin(teta);
        GLfloat matrZ[3][3] = {
            {cosT, sinT, 0 },
            {-sinT, cosT, 0},
            {0, 0, 1}
        };

        GLfloat alpha = PI / 2;
        GLfloat cosA = std::cos(alpha);
        GLfloat sinA = std::sin(alpha);
        GLfloat matrX[3][3] = {
            {1, 0, 0 },
            {0, cosA, sinA},
            {0, -sinA, cosA}
        };

        for (int i = 0; i < top.size(); i++) {
            Point p1 = top[i];
            GLfloat a1 = matrZ[0][0] * p1.x + matrZ[0][1] * p1.y;
            GLfloat a2 = matrZ[1][0] * p1.x + matrZ[1][1] * p1.y;
            top[i].x = a1;
            top[i].y = a2;
        }

        for (int i = 0; i < top.size(); i++) {
            Point p1 = top[i];
            GLfloat a2 = matrX[1][1] * p1.y + matrX[1][2] * p1.z;
            GLfloat a3 = matrX[2][1] * p1.y + matrX[2][2] * p1.z;
            top[i].y = a2;
            top[i].z = a3;
        }

        for (int i = 0; i < bottom.size(); i++) {
            Point p1 = bottom[i];
            GLfloat a2 = matrX[1][1] * p1.y + matrX[1][2] * p1.z;
            GLfloat a3 = matrX[2][1] * p1.y + matrX[2][2] * p1.z;
            bottom[i].y = a2;
            bottom[i].z = a3;
        }

        for (int i = 0; i < top.size(); i++) {
            Point p1 = top[i];
            Point p2 = bottom[i];
            Point p3 = top[(i + 1) % top.size()];
            Point p4 = bottom[(i + 1) % bottom.size()];
            edges.push_back(p1);
            edges.push_back(p2);
            edges.push_back(p3);
            edges.push_back(p4);
        }
    }

    void drow() {


        int isPolygon = mode ? GL_FILL : GL_LINE;

        glPolygonMode(GL_FRONT_AND_BACK, isPolygon);
        glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        for (int i = 0; i < top.size(); i++) {
            glVertex3f(top[i].x, top[i].y, top[i].z);
           
        }
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        for (int i = 0; i < top.size(); i++) {
            glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
        }
        glEnd();

        for (int i = 0; i < edges.size(); i += 2) {
            glColor3f(1.0, 1.0, 0.0);
            glBegin(GL_TRIANGLES);


            glVertex3f(edges[i].x, edges[i].y, edges[i].z);
            glVertex3f(edges[i + 1].x, edges[i + 1].y, edges[i + 1].z);
            glVertex3f(edges[(i + 2) % edges.size()].x, edges[(i + 2) % edges.size()].y, edges[(i + 2) % edges.size()].z);

            glEnd();

            glBegin(GL_TRIANGLES);


            glVertex3f(edges[i + 1].x, edges[i + 1].y, edges[i + 1].z);
            glVertex3f(edges[(i + 2) % edges.size()].x, edges[(i + 2) % edges.size()].y, edges[(i + 2) % edges.size()].z);
            glVertex3f(edges[(i + 3) % edges.size()].x, edges[(i + 3) % edges.size()].y, edges[(i + 3) % edges.size()].z);

            glEnd();


            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_LINE_LOOP);


            glVertex3f(edges[i].x, edges[i].y, edges[i].z);
            glVertex3f(edges[i + 1].x, edges[i + 1].y, edges[i + 1].z);
            glVertex3f(edges[(i + 2) % edges.size()].x, edges[(i + 2) % edges.size()].y, edges[(i + 2) % edges.size()].z);

            glEnd();

            glBegin(GL_LINE_LOOP);


            glVertex3f(edges[i + 1].x, edges[i + 1].y, edges[i + 1].z);
            glVertex3f(edges[(i + 2) % edges.size()].x, edges[(i + 2) % edges.size()].y, edges[(i + 2) % edges.size()].z);
            glVertex3f(edges[(i + 3) % edges.size()].x, edges[(i + 3) % edges.size()].y, edges[(i + 3) % edges.size()].z);

            glEnd();
        }

        if (isPolygon == GL_LINE) {
            for (int i = 0; i < top.size(); i++) {
                glBegin(GL_LINE_LOOP);
                glVertex3f(top[i].x, top[i].y, top[i].z);
                glVertex3f(0, h / 2, 0);
                glEnd();                          
            }
            for (int i = 0; i < top.size(); i++) {
                glBegin(GL_LINE_LOOP);
                glVertex3f(bottom[i].x, bottom[i].y, bottom[i].z);
                glVertex3f(0, -h / 2, 0);
                glEnd();
            }
        }

    }

};

void cube() {


    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-edge_C, -edge_C, -edge_C);
    glVertex3f(-edge_C, edge_C, -edge_C);
    glVertex3f(edge_C, edge_C, -edge_C);
    glVertex3f(edge_C, -edge_C, -edge_C);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-edge_C, -edge_C, edge_C);
    glVertex3f(-edge_C, edge_C, edge_C);
    glVertex3f(edge_C, edge_C, edge_C);
    glVertex3f(edge_C, -edge_C, edge_C);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-edge_C, edge_C, -edge_C);
    glVertex3f(edge_C, edge_C, -edge_C);
    glVertex3f(edge_C, edge_C, edge_C);
    glVertex3f(-edge_C, edge_C, edge_C);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-edge_C, -edge_C, -edge_C);
    glVertex3f(edge_C, -edge_C, -edge_C);
    glVertex3f(edge_C, -edge_C, edge_C);
    glVertex3f(-edge_C, -edge_C, edge_C);

    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-edge_C, -edge_C, -edge_C);
    glVertex3f(-edge_C, edge_C, -edge_C);
    glVertex3f(-edge_C, edge_C, edge_C);
    glVertex3f(-edge_C, -edge_C, edge_C);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(edge_C, -edge_C, -edge_C);
    glVertex3f(edge_C, edge_C, -edge_C);
    glVertex3f(edge_C, edge_C, edge_C);
    glVertex3f(edge_C, -edge_C, edge_C);
    glEnd();
}

Anti Prisma;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            rotationX -= 10;
            break;
        case GLFW_KEY_DOWN:
            rotationX += 10;
            break;
        case GLFW_KEY_RIGHT:
            rotationY += 10;
            break;
        case GLFW_KEY_LEFT:
            rotationY -= 10;
            break;
        case 61 :
            rotationZ += 10;
            break;
        case 45:
            rotationZ -= 10;
            break;
        case GLFW_KEY_D:
            hW += 0.1;
            break;
        case GLFW_KEY_A:
            hW -= 0.1;
            break;
        case GLFW_KEY_W:
            hH += 0.1;
            break;
        case GLFW_KEY_S:
            hH -= 0.1;
            break;
        case GLFW_KEY_Y:
            y += 0.01;
            x += 0.01;
            z += 0.01;

            break;
        case GLFW_KEY_X:
            x -= 0.01;
            y -= 0.01;
            z -= 0.01;
            break;
        case GLFW_KEY_Q:
            Prisma.n++;
            break;
        case GLFW_KEY_Z:
            if (Prisma.n > 3) {
                Prisma.n--;
            }
            break;
        case GLFW_KEY_SPACE:
            Prisma.mode = !Prisma.mode;
            break;
        }
    }
    Prisma.buildPoints();
}

void rotateCords() {
    GLfloat matrix[16] = {
         1, 0, 0, 0,
        0, 1, 0, 0,
        -std::cosf(PI / 4), -std::sinf(PI / 4), -1, 0,
        0, 0, 0, 1
    };
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main() {
    Prisma.n = 5;
    Prisma.r = 0.5;
    Prisma.h = 0.5;
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My ANTIPRISMA", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);


    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEFT);
    rotateCords();

    Prisma.buildPoints();
    while (!glfwWindowShouldClose(window)) {
      
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(hW, hH, 0);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glRotatef(rotationZ, 0, 0, 1);
        glScaled(x, y, z);
        Prisma.drow();
        glPopMatrix();

        glPushMatrix();
        glLoadIdentity();
        glTranslatef(-0.7, -0.7, 0);
        cube();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}