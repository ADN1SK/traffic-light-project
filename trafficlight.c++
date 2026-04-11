// Click R,G,Y to change state
// Compile: g++ traffic_light.cpp -o traffic_light -lGL -lGLU -lglut
//run: ./traffic_light  
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// Light states
enum Light { RED, YELLOW, GREEN };
const float PI = 3.1415926535f;

Light currentLight = RED;
bool paused = false;

// Timing
int redTime = 3000;
int yellowTime = 1000;
int greenTime = 3000;
int lastChangeTime = 0;

// Light positions
struct Circle {
    float x, y, radius;
};
Circle redLight   = {0.0f, 0.4f, 0.15f};
Circle yellowLight= {0.0f, 0.0f, 0.15f};
Circle greenLight = {0.0f, -0.4f, 0.15f};

// Draw a circle
void drawCircle(float x, float y, float radius, bool active, float r, float g, float b) {
    glColor3f(active ? r : r * 0.3f, active ? g : g * 0.3f, active ? b : b * 0.3f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i=0;i<=100;i++){
        float angle = 2.0f * PI * i / 100;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Draw the traffic light
void drawTrafficLight() {
    // Pole / Background
    glColor3f(0.2f,0.2f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f,-0.6f);
        glVertex2f(0.2f,-0.6f);
        glVertex2f(0.2f,0.6f);
        glVertex2f(-0.2f,0.6f);
    glEnd();

    // Lights
    drawCircle(redLight.x, redLight.y, redLight.radius, currentLight==RED, 1,0,0);
    drawCircle(yellowLight.x, yellowLight.y, yellowLight.radius, currentLight==YELLOW, 1,1,0);
    drawCircle(greenLight.x, greenLight.y, greenLight.radius, currentLight==GREEN, 0,1,0);
}

// Update automatic cycling
void updateLight() {
    if(paused) return;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = currentTime - lastChangeTime;

    switch(currentLight){
        case RED: if(elapsed>=redTime){ currentLight=GREEN; lastChangeTime=currentTime;} break;
        case GREEN: if(elapsed>=greenTime){ currentLight=YELLOW; lastChangeTime=currentTime;} break;
        case YELLOW: if(elapsed>=yellowTime){ currentLight=RED; lastChangeTime=currentTime;} break;
    }
}

// Keyboard control
void keyboard(unsigned char key, int x, int y) {
    switch(key){
        case 'r': case 'R': currentLight=RED; lastChangeTime=glutGet(GLUT_ELAPSED_TIME); break;
        case 'y': case 'Y': currentLight=YELLOW; lastChangeTime=glutGet(GLUT_ELAPSED_TIME); break;
        case 'g': case 'G': currentLight=GREEN; lastChangeTime=glutGet(GLUT_ELAPSED_TIME); break;
        case 's': case 'S': paused=!paused; break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

// Check if click is inside a circle
bool insideCircle(float mx, float my, Circle c){
    float dx = mx - c.x;
    float dy = my - c.y;
    return (dx*dx + dy*dy) <= (c.radius*c.radius);
}

// Mouse click handler
void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        // Convert window coordinates to OpenGL (-1 to 1)
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        float mx = (float)x / w * 2 - 1;
        float my = 1 - (float)y / h * 2; // flip y

        if(insideCircle(mx,my,redLight)) currentLight=RED;
        else if(insideCircle(mx,my,yellowLight)) currentLight=YELLOW;
        else if(insideCircle(mx,my,greenLight)) currentLight=GREEN;

        lastChangeTime = glutGet(GLUT_ELAPSED_TIME);
        glutPostRedisplay();
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTrafficLight();
    glutSwapBuffers();
}

// Idle callback
void idle(){
    updateLight();
    glutPostRedisplay();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,600);
    glutCreateWindow("Interactive Clickable Traffic Light");

    glClearColor(0.5f,0.7f,1.0f,1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    lastChangeTime = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
    return 0;
}
