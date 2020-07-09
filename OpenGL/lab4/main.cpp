
#include <iostream>

#include <unordered_map>

#include <GLFW/glfw3.h>
#include <vector>
#include <deque>
#include <algorithm>


int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;


int step = 1;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);


GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;


struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    Point() {}
};

struct Edge {
    Point source;
    Point target;

    Edge(Point source, Point target) : source(source), target(target) {}
};

void draw();

std::vector<Point> points;

void resize(GLFWwindow *window, int width, int height) {
    halfScreenHeight = height / 2;
    halfScreenWidth = width / 2;
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    glViewport(0.0f, 0.0f, width, height);

    step = 1;
    points.clear();
}


void mouseCallback(GLFWwindow *w, int button, int action, int mods) {
    if (step != 1) {
        return;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x;
        double y;
        glfwGetCursorPos(w, &x, &y);
        int xi = -SCREEN_WIDTH / 2 + x;
        int yi = SCREEN_HEIGHT / 2 - y;

        points.push_back({xi, yi});
    }
}

int main(void) {
    GLFWwindow *window;

    if (!glfwInit()) {
        return -1;
    }
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR | GLFW_STICKY_KEYS, GLFW_CURSOR_NORMAL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0.0f, screenWidth, screenHeight);

    glfwSetWindowSizeCallback(window, resize);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        // Очищаю буфер

        if (step == 1) {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < points.size(); i++) {
                glVertex2f(2. * points[i].x / SCREEN_WIDTH, 2. * points[i].y / SCREEN_HEIGHT);
            }
            glEnd();
            glFlush();
        } else {
            draw();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}

void printMatrix(float a[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void draw() {
    std::deque<Edge> edges;

    // СОЗДАЮ РЕБРА

    for (int i = 0; i < points.size(); i++) {
        if (points[i].y < points[(i + 1) % points.size()].y) {
            edges.push_back({points[i], points[(i + 1) % points.size()]});
        } else {
            edges.push_back({points[(i + 1) % points.size()], points[i]});
        }
    }


    int minx = std::min_element(points.begin(), points.end(), [](const Point &one, const Point &two) {
        return one.x < two.x;
    })->x;
    int maxx = std::min_element(points.begin(), points.end(), [](const Point &one, const Point &two) {
        return one.x > two.x;
    })->x;

    int ymin = std::min_element(points.begin(), points.end(), [](const Point &one, const Point &two) {
        return one.y < two.y;
    })->y;
    int ymax = std::min_element(points.begin(), points.end(), [](const Point &one, const Point &two) {
        return one.y > two.y;
    })->y;

    int index = 0;
    int H = ymax - ymin;
    int W = maxx - minx;
    int centerx = minx + W / 2;
    int centery = ymin + H / 2;
    // БУФЕР

    float data[H][W][3];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            data[i][j][0] = 0;
            data[i][j][1] = 0;
            data[i][j][2] = 0;
        }
    }

    // НАЧАЛО ПРОБЕГА ПО СТРОКАМ
    std::unordered_map<int, std::vector<int>> map;
    for (int ycurrent = ymin; ycurrent < ymax; ycurrent++) {
        std::vector<int> xs;
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].source.y <= ycurrent && ycurrent < edges[i].target.y) {
                int xi = (int) (ycurrent - edges[i].source.y +
                                (edges[i].target.y - edges[i].source.y) * edges[i].source.x /
                                (edges[i].target.x - edges[i].source.x)) *
                         (edges[i].target.x - edges[i].source.x) / (edges[i].target.y - edges[i].source.y);
                xs.push_back(xi);
            }

        }
        std::sort(xs.begin(), xs.end());
        map[ycurrent] = xs;
        for (int i = 0; i < xs.size(); i += 2) {
            int x1 = xs[i];
            int x2 = xs[i + 1];
            for (int j = x1; j < x2; j++) {
                data[ycurrent - ymin][j - minx][0] = 1;
                data[ycurrent - ymin][j - minx][1] = 1;
                data[ycurrent - ymin][j - minx][2] = 1;
            }
        }
    }

    if (step == 2) {
        float ***data2 = new float **[H];
        for (int i = 0; i < H; i++) {
            data2[i] = new float *[W];
            for (int j = 0; j < W; j++) {
                data2[i][j] = new float[3];
                data2[i][j][0] = 0;
                data2[i][j][1] = 0;
                data2[i][j][2] = 0;
            }
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                // ОПРЕДЕЛЯЮ СОСЕДЕЙ ПИКСЕЛЯ
                Point matrix[3][3];
                bool mask[3][3];
                for (int t = 0; t < 3; t++) {
                    for (int u = 0; u < 3; u++) {
                        mask[t][u] = 0;
                    }
                }
                matrix[1][1] = {i, j};
                mask[1][1] = 1;
                if (i < H - 1) {
                    matrix[1][2] = {i + 1, j};
                    mask[1][2] = 1;
                }
                if (j < W - 1) {
                    matrix[2][1] = {i, j + 1};
                    mask[2][1] = 1;
                }
                if (i > 0) {
                    matrix[1][0] = {i - 1, j};
                    mask[1][0] = 1;
                }
                if (j > 0) {
                    matrix[0][1] = {i, j - 1};
                    mask[0][1] = 1;
                }

                if (i < H - 1 && j < W - 1) {
                    matrix[2][2] = {i + 1, j + 1};
                    mask[2][2] = 1;
                }
                if (i < H - 1 && j > 0) {
                    matrix[0][2] = {i + 1, j - 1};
                    mask[0][2] = 1;
                }
                if (i > 0 && j < W - 1) {
                    matrix[2][0] = {i - 1, j + 1};
                    mask[2][0] = 1;
                }
                if (i > 0 && j > 0) {
                    matrix[0][0] = {i - 1, j - 1};
                    mask[0][0] = 1;
                }

                float red[3][3];
                float green[3][3];
                float blue[3][3];

                for (int t = 0; t < 3; t++) {
                    for (int u = 0; u < 3; u++) {
                        if (mask[t][u]) {
                            red[t][u] = data[matrix[t][u].x][matrix[t][u].y][0];
                            green[t][u] = data[matrix[t][u].x][matrix[t][u].y][1];
                            blue[t][u] = data[matrix[t][u].x][matrix[t][u].y][2];
                        } else {
                            red[t][u] = data[matrix[1][1].x][matrix[1][1].y][0];
                            green[t][u] = data[matrix[1][1].x][matrix[1][1].y][1];
                            blue[t][u] = data[matrix[1][1].x][matrix[1][1].y][2];
                        }
                    }
                }
                float matrixR, matrixG, matrixB;
                matrixR = red[0][0] / 16 + red[0][1] / 8 + red[0][2] / 16 + red[1][0] / 8 + red[1][1] / 4 + red[1][2] / 8 + red[2][0] / 16 + red[2][1] / 8 + red[2][2] / 16;
                matrixG = green[0][0] / 16 + green[0][1] / 8 + green[0][2] / 16 + green[1][0] / 8 + green[1][1] / 4 + green[1][2] / 8 + green[2][0] / 16 + green[2][1] / 8 + green[2][2] / 16;
                matrixB = blue[0][0] / 16 + blue[0][1] / 8 + blue[0][2] / 16 + blue[1][0] / 8 + blue[1][1] / 4 + blue[1][2] / 8 + blue[2][0] / 16 + blue[2][1] / 8 + blue[2][2] / 16;
                data2[i][j][0] = matrixR;
                data2[i][j][1] = matrixG;
                data2[i][j][2] = matrixB;
            }
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                data[i][j][0] = data2[i][j][0];
                data[i][j][1] = data2[i][j][1];
                data[i][j][2] = data2[i][j][2];
            }
        }
    }


            // ЗАГРУЖАЮ БУФЕР
    GLfloat white[3] = {1.0, 1.0, 1.0};
    glColor3fv(white);
    glRasterPos2f(2. * minx / SCREEN_WIDTH, 2. * ymin / SCREEN_HEIGHT);
    glDrawPixels(W, H, GL_RGB, GL_FLOAT, data);
    glFlush();
}


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action != GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_A:
                step = 1;
                if (step == 1) {
                    points.clear();
                }

                break;
            case GLFW_KEY_S:
                step = 2;
                break;
            case GLFW_KEY_D:
                step = 3;
                break;
        }

    }

    std::cout << step << std::endl;
}


