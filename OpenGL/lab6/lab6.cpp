#include <iostream>
#include <string>    
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <cmath>
#include <math.h>
#include <time.h>
#include <SOIL/SOIL.h>
#include <fstream>

#define PI 3.14159265

struct cube {
    double dx, rx, ry, rz, x, y, z = 0, h = 0.7, R = 0.7, rotate = 60 * PI / 180, r = 0.06;
    double dy = 0.0, sx = 1, fi = PI / 4.0, teta = PI * 35.64 / 180.0;
    int num_p = 40, num_elem = 2;
    float* proj;
    float* polygons;
    float f = PI / 10;
};

static cube C;
static cube sphere_shape;
static cube tor_shape;
static cube animation_shape;
static double X, Y = 1;
static int mod = 0;
static double ang = 0.0;
static double RAD = 180 / PI;
static double a = 1080;
static double b = 1080;
static double V[] = { 700 / a, 200 / a, 200 / a };
static double Const = a / b;
static clock_t global_time = 0;
static int pol = 1;
static int zoomod = 0;
static double zoomv = 0;
static bool modA = false, modL = false, modT = false, modL1 = true, modL2 = true;
static GLuint texture;
static int axis, spir;
static double T = 0;
GLfloat light_ambient1[] = { 1.0, 1, 1.0, 1.0 };
GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position1[] = { -1.0, 1.0, -1.0, 0.0 };
GLfloat light_ambient[] = { 0.3, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, -1.0, 1.0, 0.0 };
static void animation(cube* t1, cube* t2, cube* t3);
static void game_loop();
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void move(double x, double y);
static void init(cube* t);
static void sphere(cube* t);
static void tor(cube* t);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void drow(cube t, int k);
static void check();
static void init_lists();

void set_light() {
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
}

int main(int argc, char const* argv[])
{

    init(&C);
    sphere(&sphere_shape);
    tor(&tor_shape);
    init(&animation_shape);

    if (!glfwInit()) {
        std::cout << "faild\n";
        return 0;
    }

    GLFWwindow* window = glfwCreateWindow(a, b, "lol", NULL, NULL);

    if (!window) {
        std::cout << "faild\n";
        return 0;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.05f, 0.05f, 0.15f, 0.0f);

    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    int width = 512, height = 512;

    texture = SOIL_load_OGL_texture
    (
        "./texture.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (texture == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    set_light();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (modT) {
            glEnable(GL_TEXTURE_2D);
        }
        else {
            glDisable(GL_TEXTURE_2D);
        }

        if (modL1) glEnable(GL_LIGHT0);
        else glDisable(GL_LIGHT0);
        if (modL2) glEnable(GL_LIGHT1);
        else glDisable(GL_LIGHT1);

        if (zoomod) {
            C.sx += zoomv;
        }

        game_loop();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    delete[](C.proj);
    delete[](C.polygons);

    std::cout << "success\n";
    return 0;
}


static void init(cube* t) {
    delete[](t->polygons);
    int size = t->num_elem * t->num_p * 3;

    double endx = t->R; double endy = 0.0; double endz = 0.0;
    double X = endx * cosf(t->rotate) - endz * sinf(t->rotate);
    double Y = endy;
    double Z = endx * sinf(t->rotate) + endz * cosf(t->rotate);
    double len = sqrt(pow(endx - X, 2) + pow(endy - Y, 2) + pow(endz - Z, 2));
    double d_len = len / (t->num_elem - 1);

    t->polygons = new float[t->num_elem * t->num_p * 3];

    for (int i = 0; i < t->num_elem; i++) {
        float rt = t->rotate * float(i) / float(t->num_elem - 1);
        double R = pow(d_len * i, 2) + pow(t->R, 2) - 2 * d_len * i * t->R * len / (t->R * 2);
        float h = t->h * d_len * i / len;

        for (int j = 0; j < t->num_p; j++) {
            float ang = 2.0 * PI * float(j) / float(t->num_p - 1);

            float x = (R)*cosf(ang);
            float y = h;
            float z = (R)*sinf(ang);

            t->polygons[i * t->num_p * 3 + j * 3] = x * cosf(rt) - z * sinf(rt);
            t->polygons[i * t->num_p * 3 + j * 3 + 1] = y;
            t->polygons[i * t->num_p * 3 + j * 3 + 2] = x * sinf(rt) + z * cosf(rt);
        }
    }
}

static void sphere(cube* t) {
    delete[](t->polygons);

    t->polygons = new float[t->num_elem * t->num_p * 3];

    for (int i = 0; i < t->num_elem; i++) {
        float ang = 2.0 * PI * float(i) / float(t->num_elem - 1);

        for (int j = 0; j < t->num_p; j++) {
            float ang1 = 1.0 * PI * float(j) / float(t->num_p - 1);

            float x = (t->R) * cosf(ang) * sinf(ang1);
            float y = (t->R) * sinf(ang1) * sinf(ang);
            float z = (t->R) * cosf(ang1);

            t->polygons[i * t->num_p * 3 + j * 3] = x;
            t->polygons[i * t->num_p * 3 + j * 3 + 1] = y;
            t->polygons[i * t->num_p * 3 + j * 3 + 2] = z;
        }
    }
}
static void tor(cube* t) {
    delete[](t->polygons);

    t->polygons = new float[t->num_elem * t->num_p * 3];

    for (int i = 0; i < t->num_elem; i++) {
        float A = 2.0 * PI * float(i) / float(t->num_elem - 1);
        float d = t->h * i / t->num_elem;
        for (int j = 0; j < t->num_p; j++) {
            float ang = 2.0 * PI * float(j) / float(t->num_p);
            float x = t->R + (t->r) * cosf(ang);
            float y = 0;
            float z = (t->r) * sinf(ang);
            float x2 = x * cos(A) - y * sin(A);
            float y2 = y * cos(A) + x * sin(A);
            t->polygons[i * t->num_p * 3 + j * 3] = x2;
            t->polygons[i * t->num_p * 3 + j * 3 + 1] = y2;
            t->polygons[i * t->num_p * 3 + j * 3 + 2] = z;
        }
    }
}



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    mod++;
    mod %= 2;
    return;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    xpos = (-1 + xpos / (a / 2.0));
    ypos = (1 - ypos / (b / 2.0));

    if (mod == 1) {
        C.rx += (xpos - X) * 70;
        C.ry += (ypos - Y) * 70;
    }
    X = xpos;
    Y = ypos;
    return;
}

static void move(double x, double y) {

    C.dx += 0.05 * x;
    C.dy += 0.05 * y;

    return;
}

static int animation_phase = 1;
static void animation(cube* t1, cube* t2, cube* t3) {
    clock_t local_time = clock();
    double time = ((double)local_time) / CLOCKS_PER_SEC - ((double)global_time) / CLOCKS_PER_SEC;
    global_time = local_time;
    std::cout << time << '\n';

    if (T > 1) animation_phase = -1;
    if (T < 0) animation_phase = 1;

    T = T + animation_phase * 0.5 * time;

    for (int i = 0; i < t1->num_elem * t1->num_p * 3; ++i) {
        animation_shape.polygons[i] = (1 - T) * (1 - T) * t1->polygons[i] + 2 * T * (1 - T) * t2->polygons[i] + T * T * t3->polygons[i];
    }

    return;
}



static void pars() {
    std::ifstream file("./position.txt");
    std::string s, t = "";
    getline(file, s);
    //std::cout<< s << std::endl;
    file.close();
    int i = 0;
    double v_t[3] = { 0,0,0 };

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    T = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    animation_phase = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    modA = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    pol = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    modT = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ')'; t += s[i++]);
    C.rotate = std::stod(t);
    t = "";

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ' '; t += s[i++]);

    int num = std::stod(t);
    t = "";
    C.num_p = num;
    sphere_shape.num_p = num;
    tor_shape.num_p = num;
    animation_shape.num_p = num;

    for (; s[i] != ')'; t += s[i++]);
    num = std::stod(t);
    t = "";
    C.num_elem = num;
    sphere_shape.num_elem = num;
    tor_shape.num_elem = num;
    animation_shape.num_elem = num;

    for (; s[i] != '('; i++);
    i++;
    for (; s[i] != ' '; t += s[i++]);
    C.dx = std::stod(t);
    t = "";
    i++;
    for (; s[i] != ' '; t += s[i++]);
    C.dy = std::stod(t);
    t = "";
    i++;
    for (; s[i] != ' '; t += s[i++]);
    C.rx = std::stod(t);
    t = "";
    i++;
    for (; s[i] != ' '; t += s[i++]);
    C.ry = std::stod(t);
    t = "";
    i++;
    for (; s[i] != ' '; t += s[i++]);
    C.rz = std::stod(t);
    t = "";
    i++;
    for (; s[i] != ')'; t += s[i++]);
    C.sx = std::stod(t);
    t = "";

    init(&C);
    sphere(&sphere_shape);
    tor(&tor_shape);
    init(&animation_shape);


    return;
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    int t = 0; //флаг для переотрисовки объекта при изменении количества полигонов
    std::ofstream ttt;
    std::cout << key << " ";
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
                glfwSetWindowShouldClose(window, true);
            }
            break;
        case 90: //z
            ttt.open("./position.txt");
            if (ttt.is_open()) {
                ttt << "animation_shase = (" << T << ") animation_sign = (" << animation_phase << ") animation_mode = (" << modA << ") poligon_mode = (" << pol << ") textur_mode = (" << modT << ") rotation = (" << C.rotate << ") nodes = (" << C.num_p << " " << C.num_elem << ") position = (" << C.dx << " " << C.dy << " " << C.rx << " " << C.ry << " " << C.rz << " " << C.sx << ")" << std::endl;
            }
            break;
        case 88: //x
            pars();
            break;
        case 84: //T
            modT ^= true;
            break;
        case 76:
            modL ^= true;
            break;
        case 61:
            t++;
            C.rotate += 0.01;
            break;
        case 45:
            t++;
            C.rotate -= 0.01;
            break;
        case 46:
            if (C.num_p > 1) {
                t++;
                C.num_p -= 1;
                animation_shape.num_p -= 1;
                tor_shape.num_p -= 1;
                sphere_shape.num_p -= 1;
            }
            break;
        case 44:
            t++;
            C.num_p += 1;
            animation_shape.num_p += 1;
            tor_shape.num_p += 1;
            sphere_shape.num_p += 1;
            break;
        case 57:
            t++;
            C.num_elem += 1;
            animation_shape.num_elem += 1;
            tor_shape.num_elem += 1;
            sphere_shape.num_elem += 1;
            break;
        case 48:
            if (C.num_elem > 2) {
                t++;
                C.num_elem -= 1;
                animation_shape.num_elem -= 1;
                tor_shape.num_elem -= 1;
                sphere_shape.num_elem -= 1;
                break;
            }
            break;
        case 65:
            move(-1.0, 0.0);
            break;
        case 68:
            move(1.0, 0.0);
            break;
        case 87:
            move(0.0, 1.0);
            break;
        case 83:
            move(0.0, -1.0);
            break;
        case 265:
            C.sx += 0.03;
            break;
        case 264:
            C.sx += -0.03;
            break;
        case 263:
            C.rz += 4;
            break;
        case 262:
            C.rz -= 4;
            break;
        case GLFW_KEY_R:
            pol++;
            pol %= 2;
            break;
        case GLFW_KEY_2:
            modL1 ^= true;
            break;
        case GLFW_KEY_1:
            modL2 ^= true;
            break;

        case 32:
            modA ^= true;
            global_time = clock();
            break;
        default:
            std::cout << key << std::endl;
            break;
        }
    }
    if (t) {
        init(&C);
        sphere(&sphere_shape);
        tor(&tor_shape);
        init(&animation_shape);

    }
}

void drow(cube t) {


    for (int k = 0; k < C.num_elem - 1; k++) {
        int j = 0;

        glBindTexture(GL_TEXTURE_2D, texture);


        if (k == 0) {
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < t.num_p + 1; i++) {
                glColor3f(abs((float(k) / t.num_elem - 1) * 1000) / 1000.0, abs((float(j) / (t.num_p * 2) - 0.5) * 1000) / 1000.0, 0.666); j++;
                glVertex3f(t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3)], t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 1], t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 2]);
                glNormal3f(0, 0, -1);
            }
            glEnd();
        }
        if (k == t.num_elem - 2) {
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < t.num_p + 1; i++) {
                glColor3f(abs((float(k) / t.num_elem - 1) * 1000) / 1000.0, abs((float(j) / (t.num_p * 2) - 0.5) * 1000) / 1000.0, 0.666); j++;
                glVertex3f(t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3)], t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 1], t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 2]);
                glNormal3f(0, 0, 1);
            }
            glEnd();
        }
        j = 0;
        double txt_crd = 0;
        double txt_d = 1 / C.num_elem;

        for (int i = 0; i < t.num_p + 1; i++) {

            double x0 = t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3)], x2 = t.polygons[k * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3)], x1 = t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3)];
            double y0 = t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 1], y2 = t.polygons[k * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3) + 1], y1 = t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 1];
            double z0 = t.polygons[k * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 2], z2 = t.polygons[k * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3) + 2], z1 = t.polygons[(k + 1) * t.num_p * 3 + (i * 3) % (t.num_p * 3) + 2];

            double x3 = t.polygons[(k + 1) * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3)], y3 = t.polygons[(k + 1) * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3) + 1], z3 = t.polygons[(k + 1) * t.num_p * 3 + ((i + 1) * 3) % (t.num_p * 3) + 2];

            glBindTexture(GL_TEXTURE_2D, texture);
            glBegin(GL_TRIANGLES);

            glNormal3f((y1 - y0) * (z2 - z1) - (z1 - z0) * (y2 - y1),
                (x1 - x0) * (z2 - z1) - (z1 - z0) * (x2 - x1),
                (x1 - x0) * (y2 - y1) - (y1 - y0) * (x2 - x1));

            glTexCoord2f(0, 0.0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(1, 0.0);
            glVertex3f(x1, y1, z1);
            glTexCoord2f(1, 1);
            glVertex3f(x2, y2, z2);

            glNormal3f((y1 - y3) * (z2 - z1) - (z1 - z3) * (y2 - y1),
                (x1 - x3) * (z2 - z1) - (z1 - z3) * (x2 - x1),
                (x1 - x3) * (y2 - y1) - (y1 - y3) * (x2 - x1));

            glTexCoord2f(0, 0);
            glVertex3f(x3, y3, z3);
            glTexCoord2f(1, 0.0f);
            glVertex3f(x1, y1, z1);
            glTexCoord2f(1, 1);
            glVertex3f(x2, y2, z2);

            txt_crd += txt_d;
            glEnd();

        }
    }
}

void game_loop() {

    if (modA)
        animation(&C, &tor_shape, &sphere_shape);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(C.dx, C.dy, 0.0);
    glRotated(C.ry, 1.0, 0.0, 0.0);
    glRotated(C.rx, 0.0, 1.0, 0.0);
    glRotated(C.rz, 0.0, 0.0, 1.0);
    glScaled(C.sx, C.sx, C.sx);

    if (pol) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (modA) drow(animation_shape);
    else drow(C);

}