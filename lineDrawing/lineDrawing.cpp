#include <stdlib.h>
#include <stdio.h>
#include <math.h> // For mathematical functions
#include "GL/glut.h" //OpenGL functions

GLfloat xInit, xEnd, yInit, yEnd, b = 0;

/**
 * GLint x - Coord x of the pixel to color
 * GLint y - Coord y of the pixel to color
 */
void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y); // Paints specified pixel
    glEnd();
    glFlush();
}

/**
 * If the slope of the line is undefined, it draws an horizontal line
 */

void horizontal() {
    if(xInit > xEnd) {
        GLfloat temp;
        temp = xInit;
        xInit = xEnd;
        xEnd = temp;
    }
    for(GLfloat x = xInit; x <= xEnd; ++x) setPixel(x, yInit);
}

/**
 * If the slope of the line is 0, it draws a vertical line
 */
void vertical() {
    if(yInit > yEnd) {
        GLfloat temp;
        temp = yInit;
        yInit = yEnd;
        yEnd = temp;
    }
    for(GLfloat y = yInit; y <= yEnd; ++y) setPixel(xInit,y);
}

/**
 * GLfloat m - Slope of the line to draw
 * 
 * Draws a line using DDA algorithm 
 * It moves x0 and x1 to avoid doing this line over Bresenham algorithm line
 */

void lineDDA(GLfloat m) {
    xInit += 100;
    xEnd += 100;
    glColor3f(0.0, 0.0, 1.0);

    GLint dx = xEnd - xInit;
    GLint dy = yEnd - yInit;
    GLint steps;
    GLfloat xIncrement, yIncrement, x = xInit, y = yInit;

    if(abs(dx) > abs(dy)) steps = abs(dx);
    else steps = abs(dy);

    xIncrement = dx / GLfloat(steps);
    yIncrement = dy / GLfloat(steps);
    //setPixel(x + 0.5, y + 0.5);

    for(int i = 1; i <= steps; ++i)
    {
        setPixel((x + 0.5), (y + 0.5));
        x += xIncrement;
        y += yIncrement;
    }
}

/**
 * Calculates the line path using Bresenham algorithm if the slope is between 0 and 1
 */

void bresenham1() {
    glColor3f(1.0, 0.0, 0.0);
    if(xInit > xEnd) {
        GLfloat temp;
        temp = xInit;
        xInit = xEnd;
        xEnd = temp;
        temp = yInit;
        yInit = yEnd;
        yEnd = temp;
    }

    GLint x = xInit, y = yInit;
    GLint dx = xEnd - xInit;
    GLint dy = yEnd - yInit;
    GLint dT = 2 * (dy - dx);
    GLint dS = 2 * dy;
    GLint d = 2 * dy - dx;

    setPixel(x, y);
    while(x < xEnd) {
        ++x;
        if(d < 0) d += dS;
        else {
            d += dT;
            ++y;
        }
        setPixel(x, y);
    }
    setPixel(xEnd, yEnd);
}


/**
 * Calculates the line path using Bresenham algorithm if the slope is between -1 and 0 
 */

void bresenham2() {
    glColor3f(1.0, 0.0, 0.0);
    if(xInit > xEnd) {
        GLfloat temp;
        temp = xInit;
        xInit = xEnd;
        xEnd = temp;
        temp = yInit;
        yInit = yEnd;
        yEnd = temp;
    }
    GLint x = xInit, y = yInit;
    GLint dx = xEnd - xInit;
    GLint dy = yEnd - yInit;
    GLint dT = 2 * (dy + dx);
    GLint dS = 2 * dy;
    GLint d = -(2 * dx + dy);

    setPixel(x, y);
    while(x < xEnd) {
        ++x;
        if(d < 0) d -= dS;
        else {
            --y;
            d -= dT;
        }
        setPixel(x, y);
    }
    setPixel(xEnd, yEnd);
}


/**
 * Calculates the line path using Bresenham algorithm if the slope is bigger than 1
 */

void bresenham3(){
    glColor3f(1.0, 0.0, 0.0);
    if(yInit > yEnd) {
        GLfloat temp;
        temp = xInit;
        xInit = xEnd;
        xEnd = temp;
        temp = yInit;
        yInit = yEnd;
        yEnd = temp;
    }
    GLint x = xInit, y = yInit;
    GLint dx = xEnd - xInit;
    GLint dy = yEnd - yInit;
    GLint dT = 2 * (dx - dy);
    GLint dS = 2 * dx;
    GLint d = 2 * dx - dy;

    setPixel(x, y);
    while(y < yEnd) {
        ++y;
        if(d < 0) d += dS;
        else {
            ++x;
            d += dT;
        }
        setPixel(x, y);
    }
    setPixel(xEnd, yEnd);
}


/**
 * Calculates the line path using Bresenham algorithm if the slope is smaller than -1 
 */

void bresenham4() {
    glColor3f(1.0, 0.0, 0.0);
    if(yInit > yEnd) {
        GLfloat temp;
        temp = xInit;
        xInit = xEnd;
        xEnd = temp;
        temp = yInit;
        yInit = yEnd;
        yEnd = temp;
    }
    GLint x = xInit, y = yInit;
    GLint dx = xEnd - xInit;
    GLint dy = yEnd - yInit;
    GLint dT = 2 * (dy + dx);
    GLint dS = 2 * dx;
    GLint d = -(2 * dy + dx);

    setPixel(x, y);
    while(y < yEnd) {
        ++y;
        if(d < 0) d -= dS;
        else {
            --x;
            d -= dT;
        }
        setPixel(x, y);
    }
    setPixel(xEnd, yEnd);
}

/**
 * int button - Which button of the mouse is being clicked
 * int state - Returns if the mouse is being clicked
 * int x - Coordinate x of the initial and end points
 * int y - Coordinate y of the initial and end points
 * 
 * Asks is the mouse is being pressed and saves the coordinates where the mouse was pressed
 * to know where is the initial and the ending points. 
 * 
 * Calls Bresenham and DDA algorithms to draw the lines. 
 * 
 * Clears the screen when a new line is going to be created. 
 */
void mouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(b == 0) {
            xInit = x;
            yInit = 480 - y;
            b = 1;
        }
        else if(b == 1) {
            xEnd = x;
            yEnd = 480 - y;
            b = 0;

            if(yInit == yEnd) horizontal();
            else if(xInit == xEnd) vertical();

            GLfloat m = (yEnd - yInit)/(xEnd - xInit);

            if(0 < m && m < 1) bresenham1();
            else if(0 > m && m > -1) bresenham2();
            else if(1 < m) bresenham3();
            else if(-1 > m) bresenham4();

            lineDDA(m);
            glClear(GL_COLOR_BUFFER_BIT);

        }
    }
}

/**
 * Sets the color of screen as white
 * Calls glutMouseFunc to use the drawing-with-mouse method
 * Flushes the buffer
 */

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mouseFunc);
    glFlush();
}

/**
 * Main function - Initializes GLUT and calls the loop that keeps showing the lines
 * Returns 0 on success. 
 */

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow ("Bresenham / DDA");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}