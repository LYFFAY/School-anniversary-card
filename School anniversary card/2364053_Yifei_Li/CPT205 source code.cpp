#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "windows.h"
#include <stdlib.h>
#include <vector>
#include <algorithm> 
#define MAX_CHAR 128

// Cloud-related variables
struct Cloud {
    float x;         // X coordinate
    float y;         // Y coordinate
    float size;      // Size
    float speed;     // Movement speed
    int segments;    // Number of cloud segments (controls cloud shape generation)
};
std::vector<Cloud> clouds;
#define CLOUD_MIN_SPEED 0.3f
#define CLOUD_MAX_SPEED 0.8f  // Movement speed range

// Star-related variables
struct Star {
    float x;          // X coordinate
    float y;          // Y coordinate
    float size;       // Size
    float brightness; // Brightness (0.2-1.0)
    float blinkSpeed; // Blinking speed
    float r, g, b;    // Star color
    float bgFactor;   // Background blending factor (0.1-0.3)
};
std::vector<Star> stars;
#define STAR_COUNT 10   // Number of stars displayed simultaneously
#define STAR_MIN_SIZE 2.0f
#define STAR_MAX_SIZE 4.0f  // Size range
#define STAR_MIN_SPEED 0.002f  
#define STAR_MAX_SPEED 0.005f  // Blinking speed range
#define BACKGROUND_R 0.678f  // Background color (light blue)
#define BACKGROUND_G 0.847f  
#define BACKGROUND_B 0.902f  

// Global variables and color definitions
float r = 0;
GLfloat step = 1;
int time_interval = 16;
int colorState = 0;
int textColorState = 0;
int charWidths[MAX_CHAR] = { 0 };
GLuint fontListBase = 0;
#define TEXT_TARGET_COLOR_R 0.6f
#define TEXT_TARGET_COLOR_G 0.7f
#define TEXT_TARGET_COLOR_B 0.9f

bool isWireframe = true;  // Wireframe mode definition
#define LINE_WIDTH 2.5f    // 2.5 width in wireframe mode (for visibility)
#define SCALE_FACTOR 0.9f
#define TRANS_X 210.0f
#define TRANS_Y -60.0f     // Translate or scale graphics
bool shape17UseBgColor = false;
bool shape20UseBgColor = false;
bool shape21UseBgColor = false;
bool shape24UseBgColor = false;
bool shape25UseBgColor = false;
bool shape26UseBgColor = false;
bool shape27UseBgColor = false;
bool shape28UseBgColor = false;
bool shape29UseBgColor = false;
bool shape30UseBgColor = false;
bool shape31UseBgColor = false;
bool shape35UseBgColor = false;
bool shape36UseBgColor = false;
bool shape37UseBgColor = false;
bool shape41UseLightGreen = false;  // Control color transition

// Color constants
#define COLOR_LIGHT_PURPLE_R 204.0f/255.0f
#define COLOR_LIGHT_PURPLE_G 179.0f/255.0f
#define COLOR_LIGHT_PURPLE_B 255.0f/255.0f
#define COLOR_LIGHT_BLUE_R 173.0f/255.0f
#define COLOR_LIGHT_BLUE_G 216.0f/255.0f
#define COLOR_LIGHT_BLUE_B 230.0f/255.0f
#define COLOR_LIGHT_GREEN_R 144.0f/255.0f
#define COLOR_LIGHT_GREEN_G 238.0f/255.0f
#define COLOR_LIGHT_GREEN_B 144.0f/255.0f

// Extended colors
#define COLOR_LIGHT_YELLOW_R 250.0f/255.0f
#define COLOR_LIGHT_YELLOW_G 240.0f/255.0f
#define COLOR_LIGHT_YELLOW_B 200.0f/255.0f
#define COLOR_LIGHT_ORANGE_R 245.0f/255.0f
#define COLOR_LIGHT_ORANGE_G 200.0f/255.0f
#define COLOR_LIGHT_ORANGE_B 180.0f/255.0f
#define COLOR_CIRCLE_LIGHT_GREEN_R 180.0f/255.0f
#define COLOR_CIRCLE_LIGHT_GREEN_G 220.0f/255.0f
#define COLOR_CIRCLE_LIGHT_GREEN_B 180.0f/255.0f

// Star colors
#define STAR_COLOR_YELLOW_R 252.0f/255.0f
#define STAR_COLOR_YELLOW_G 245.0f/255.0f
#define STAR_COLOR_YELLOW_B 205.0f/255.0f
#define STAR_COLOR_PINK_R 255.0f/255.0f
#define STAR_COLOR_PINK_G 208.0f/255.0f
#define STAR_COLOR_PINK_B 221.0f/255.0f
#define STAR_COLOR_BLUE_R 191.0f/255.0f
#define STAR_COLOR_BLUE_G 223.0f/255.0f
#define STAR_COLOR_BLUE_B 255.0f/255.0f
#define STAR_COLOR_GREEN_R 186.0f/255.0f
#define STAR_COLOR_GREEN_G 230.0f/255.0f
#define STAR_COLOR_GREEN_B 201.0f/255.0f
#define COLOR_WHITE 1.0f

// Balloon-related variables
struct Balloon {
    float x, y;       // X, Y coordinates
    float rotation;   // Rotation
    float swing;      // Swing (balloon string for realism)
    float speedX;     // Speed in X direction
    float speedY;     // Speed in Y direction
    float rotSpeed;   // Rotation speed
    float r, g, b;
};
#define BALLOON_NUM 8
#define BALLOON_SCALE 0.7f
Balloon balloons[BALLOON_NUM];
#define M_PI 3.14159265358979323846f
#define BALLOON_RADIUS 15.0f
#define ROPE_LENGTH 25.0f
#define SWING_AMPLITUDE 3.0f

// Draw tree canopy
void drawCenterCircle() {  // First tree
    glPushMatrix();
    glTranslatef(475.0f + 27.0f, 65.0f + 10.0f, 0.0f);

    if (!isWireframe) {  // Toggle between wireframe and filled mode
        glColor3f(COLOR_CIRCLE_LIGHT_GREEN_R, COLOR_CIRCLE_LIGHT_GREEN_G, COLOR_CIRCLE_LIGHT_GREEN_B);
        glBegin(GL_POLYGON);  // Draw using polygon
        for (int i = 0; i < 36; ++i) {
            float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
            glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
        }
        glEnd();
    }

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);  // Line loop connection
    for (int i = 0; i < 36; ++i) {
        float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
        glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
    }
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawNewCenterCircle() {  // Second tree
    glPushMatrix();
    glTranslatef(690.0f, 75.0f, 0.0f);

    if (!isWireframe) {  // Toggle between wireframe and filled mode
        glColor3f(COLOR_CIRCLE_LIGHT_GREEN_R, COLOR_CIRCLE_LIGHT_GREEN_G, COLOR_CIRCLE_LIGHT_GREEN_B);
        glBegin(GL_POLYGON);  // Draw using polygon
        for (int i = 0; i < 36; ++i) {
            float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
            glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
        }
        glEnd();
    }

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);  // Line loop connection
    for (int i = 0; i < 36; ++i) {
        float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
        glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
    }
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawAnotherNewCenterCircle() {  // Third tree
    glPushMatrix();
    glTranslatef(660.0f, 64.0f, 0.0f);

    if (!isWireframe) {  // Toggle between wireframe and filled mode
        glColor3f(COLOR_CIRCLE_LIGHT_GREEN_R, COLOR_CIRCLE_LIGHT_GREEN_G, COLOR_CIRCLE_LIGHT_GREEN_B);
        glBegin(GL_POLYGON);  // Draw using polygon
        for (int i = 0; i < 36; ++i) {
            float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
            glVertex2f(15.0f * cos(angle), 15.0f * sin(angle));
        }
        glEnd();
    }

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);  // Line loop connection
    for (int i = 0; i < 36; ++i) {
        float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
        glVertex2f(15.0f * cos(angle), 15.0f * sin(angle));
    }
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawAnotherNewCenterCircle1() {  // Fourth tree
    glPushMatrix();
    glTranslatef(97.0f, 75.0f, 0.0f);

    if (!isWireframe) {  // Toggle between wireframe and filled mode
        glColor3f(COLOR_CIRCLE_LIGHT_GREEN_R, COLOR_CIRCLE_LIGHT_GREEN_G, COLOR_CIRCLE_LIGHT_GREEN_B);
        glBegin(GL_POLYGON);  // Draw using polygon
        for (int i = 0; i < 36; ++i) {
            float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
            glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
        }
        glEnd();
    }

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);  // Line loop connection
    for (int i = 0; i < 36; ++i) {
        float angle = static_cast<float>(i * 10.0 * M_PI / 180.0);
        glVertex2f(20.0f * cos(angle), 22.0f * sin(angle));
    }
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

// Draw tree trunk
void drawVerticalLine() {  // First trunk
    glPushMatrix();
    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINES);  // Line drawing
    glVertex2f(97.0f, 75.0f);
    glVertex2f(97.0f, 35.0f);
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawVerticalLine1() {  // Second trunk
    glPushMatrix();
    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINES);  // Line drawing
    glVertex2f(690.0f, 75.0f);
    glVertex2f(690.0f, 35.0f);
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawVerticalLine2() {  // Third trunk
    glPushMatrix();
    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINES);  // Line drawing
    glVertex2f(502.0f, 75.0f);
    glVertex2f(502.0f, 35.0f);
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

void drawVerticalLine3() {  // Fourth trunk
    glPushMatrix();
    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINES);  // Line drawing
    glVertex2f(660.0f, 64.0f);
    glVertex2f(660.0f, 35.0f);
    glEnd();
    glLineWidth(1.0f);
    glPopMatrix();
}

// XJTLU landmark building structures (41 graphics total)
GLfloat vertices1[][2] = { {100, 155}, {100, 180}, {250, 205}, {300, 205}, {300, 155} };
GLint indices1[] = { 0,1,2,3,4 };
int count1 = 5;

GLfloat vertices2[][2] = {
    {100, 225}, {100, 375}, {150, 375}, {160, 350}, {170, 350},
    {170, 375}, {300, 375}, {300, 225}, {275, 225}, {275, 300},
    {250, 300}, {200, 225}
};
GLint indices2[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
int count2 = 12;  // Fix extra filling error

GLfloat vertices3[][2] = {
    {110, 182}, {110, 225}, {200, 225}, {250, 300}, {275, 300},
    {275, 225}, {290, 225}, {290, 205}, {250, 205}
};
GLint indices3[] = { 0,1,2,3,4,5,6,7,8 };
int count3 = 9;  // Fix extra filling error

GLfloat vertices4[][2] = { {200, 225}, {250, 300}, {160, 225} };
int count4 = 3;

GLfloat vertices5[][2] = {
    {75, 105}, {75, 125}, {140, 125}, {150, 145},
    {250, 145}, {260, 125}, {325, 125}, {325, 105}
};
GLint indices5[] = { 0,1,2,3,4,5,6,7 };
int count5 = 8;

GLfloat vertices6[][2] = {
    {75, 125}, {75, 145}, {110, 145}, {110, 155},
    {290, 155}, {290, 145}, {325, 145}, {325, 125},
    {260, 125}, {250, 145}, {150, 145}, {140, 125}
};
GLint indices6[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
int count6 = 12;

GLfloat vertices7[][2] = { {140, 125}, {150, 145}, {100, 125} };
int count7 = 3;  // Fix extra filling error

GLfloat vertices8[][2] = { {170, 350}, {170, 375}, {160, 350} };
int count8 = 3;  // Fix extra filling error
// Above are the drawing points for the CB building
GLfloat vertices9[][2] = {
    {75, 105}, {-125, 105}, {-125, 115}, {75, 115}
};
GLint indices9[] = { 0,1,2,3 };
int count9 = 4;

GLfloat vertices10[][2] = {
    {51, 115}, {43, 115}, {43, 190}, {51, 190}
};
GLint indices10[] = { 0,1,2,3 };
int count10 = 4;

GLfloat vertices11[][2] = {
    {27, 115}, {19, 115}, {19, 190}, {27, 190}
};
GLint indices11[] = { 0,1,2,3 };
int count11 = 4;

GLfloat vertices12[][2] = {
    {3, 115}, {-5, 115}, {-5, 190}, {3, 190}
};
GLint indices12[] = { 0,1,2,3 };
int count12 = 4;

GLfloat vertices13[][2] = {
    {-21, 115}, {-29, 115}, {-29, 190}, {-21, 190}
};
GLint indices13[] = { 0,1,2,3 };
int count13 = 4;

GLfloat vertices14[][2] = {
    {-45, 115}, {-53, 115}, {-53, 190}, {-45, 190}
};
GLint indices14[] = { 0,1,2,3 };
int count14 = 4;

GLfloat vertices15[][2] = {
    {-69, 115}, {-77, 115}, {-77, 190}, {-69, 190}
};
GLint indices15[] = { 0,1,2,3 };
int count15 = 4;

GLfloat vertices16[][2] = {
    {-93, 115}, {-101, 115}, {-101, 190}, {-93, 190}
};
GLint indices16[] = { 0,1,2,3 };
int count16 = 4;

GLfloat vertices17[][2] = {
    {75, 190}, {-125, 190}, {-25, 275}
};
GLint indices17[] = { 0,1,2 };
int count17 = 3;

GLfloat vertices18[][2] = {
    {-25, 275}, {-77, 232}, {27, 232}
};
GLint indices18[] = { 0,1,2 };
int count18 = 3;

GLfloat vertices19[][2] = {
    {325, 105}, {325, 130}, {490, 130}, {490, 105}
};
GLint indices19[] = { 0,1,2,3 };
int count19 = 4;

GLfloat vertices20[][2] = {
    {490, 105}, {525, 105}, {525, 250}, {490, 250}
};
GLint indices20[] = { 0,1,2,3 };
int count20 = 4;

GLfloat vertices21[][2] = {
    {490, 130}, {490, 140}, {375, 140}, {375, 130}
};
GLint indices21[] = { 0,1,2,3 };
int count21 = 4;

GLfloat vertices22[][2] = {
    {490, 140}, {490, 340}, {360, 340}, {360, 140}
};
GLint indices22[] = { 0,1,2,3 };
int count22 = 4;

GLfloat vertices23[][2] = {
    {475, 340}, {475, 375}, {375, 375}, {375, 340}
};
GLint indices23[] = { 0,1,2,3 };
int count23 = 4;

GLfloat vertices24[][2] = {
    {465, 350}, {465, 365}, {385, 365}, {385, 350}
};
GLint indices24[] = { 0,1,2,3 };
int count24 = 4;

GLfloat vertices25[][2] = {
    {460, 140}, {460, 340}, {390, 340}, {390, 140}
};
GLint indices25[] = { 0,1,2,3 };
int count25 = 4;

GLfloat vertices26[][2] = {
    {370, 150}, {370, 200}, {380, 200}, {380, 150}
};
GLint indices26[] = { 0,1,2,3 };
int count26 = 4;

GLfloat vertices27[][2] = {
    {370, 210}, {370, 260}, {380, 260}, {380, 210}
};
GLint indices27[] = { 0,1,2,3 };
int count27 = 4;

GLfloat vertices28[][2] = {
    {370, 270}, {370, 320}, {380, 320}, {380, 270}
};
GLint indices28[] = { 0,1,2,3 };
int count28 = 4;

GLfloat vertices29[][2] = {
    {480, 150}, {480, 200}, {470, 200}, {470, 150}
};
GLint indices29[] = { 0,1,2,3 };
int count29 = 4;

GLfloat vertices30[][2] = {
    {480, 210}, {480, 260}, {470, 260}, {470, 210}
};
GLint indices30[] = { 0,1,2,3 };
int count30 = 4;

GLfloat vertices31[][2] = {
    {480, 270}, {480, 320}, {470, 320}, {470, 270}
};
GLint indices31[] = { 0,1,2,3 };
int count31 = 4;

GLfloat vertices32[][2] = {
    {410, 152}, {410, 202}, {440, 202}, {440, 152}
};
GLint indices32[] = { 0,1,2,3 };
int count32 = 4;

GLfloat vertices33[][2] = {
    {410, 212}, {410, 262}, {440, 262}, {440, 212}
};
GLint indices33[] = { 0,1,2,3 };
int count33 = 4;

GLfloat vertices34[][2] = {
    {410, 272}, {410, 322}, {440, 322}, {440, 272}
};
GLint indices34[] = { 0,1,2,3 };
int count34 = 4;

GLfloat vertices35[][2] = {
    {417, 159}, {417, 195}, {433, 195}, {433, 159}
};
GLint indices35[] = { 0,1,2,3 };
int count35 = 4;

GLfloat vertices36[][2] = {
    {417, 219}, {417, 255}, {433, 255}, {433, 219}
};
GLint indices36[] = { 0,1,2,3 };
int count36 = 4;

GLfloat vertices37[][2] = {
    {417, 279}, {417, 315}, {433, 315}, {433, 279}
};
GLint indices37[] = { 0,1,2,3 };
int count37 = 4;

GLfloat vertices38[][2] = {
    {500, 120}, {500, 148}, {515, 148}, {515, 120}
};
GLint indices38[] = { 0,1,2,3 };
int count38 = 4;

GLfloat vertices39[][2] = {
    {500, 163}, {500, 191}, {515, 191}, {515, 163}
};
GLint indices39[] = { 0,1,2,3 };
int count39 = 4;

GLfloat vertices40[][2] = {
    {500, 206}, {500, 234}, {515, 234}, {515, 206}
};
GLint indices40[] = { 0,1,2,3 };
int count40 = 4;

GLfloat vertices41[][2] = {
    {-1000, 105}, {1000, 105}, {1000, 50}, {-1000, 50}
};
GLint indices41[] = { 0,1,2,3 };
int count41 = 4;
// Above are the drawings for the White House and FB building
// XJTLU text drawing function
void drawString(const char* str) {
    for (; *str != '\0'; ++str) {
        glCallList(fontListBase + *str);
    }
}

float calculateStringWidth(const char* str) {
    float totalWidth = 0.0f;
    for (; *str != '\0'; ++str) {
        if (*str >= 0 && *str < MAX_CHAR) {
            totalWidth += charWidths[(unsigned char)*str];
        }
    }
    return totalWidth;
}

void selectFont(int size, int charset, const char* face) {
    if (fontListBase != 0) return;

    HFONT hFont = CreateFontA(
        56, 0, 0, 0, FW_BOLD, 0, 0, 0, charset,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face
    );

    HDC hDC = wglGetCurrentDC();
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);  // Control font style

    fontListBase = glGenLists(MAX_CHAR);
    wglUseFontBitmaps(hDC, 0, MAX_CHAR, fontListBase);
    for (int i = 0; i < MAX_CHAR; ++i) {  // Control size
        SIZE charSize;
        GetTextExtentPoint32A(hDC, (LPCSTR)&i, 1, &charSize);
        charWidths[i] = charSize.cx;
    }

    SelectObject(hDC, hOldFont);
    DeleteObject(hOldFont);
    DeleteObject(hFont);
}

// Windmill drawing
void OnTimer(int value) {
    r += step;
    if (r >= 360) r = 0;
    else if (r <= 0) r = 359;
    glutTimerFunc(time_interval, OnTimer, 1);
}

void drawWindmill() {
    glPushMatrix();

    if (colorState == 0) {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    else {
        glColor3f(COLOR_LIGHT_PURPLE_R, COLOR_LIGHT_PURPLE_G, COLOR_LIGHT_PURPLE_B);
    }

    glTranslatef(100.0f, 410.5f, 0.0f);
    glRotatef(r, 0.0f, 0.0f, 1.0f);

    // Blade drawing
    glBegin(GL_TRIANGLES);  // First blade (by constructing a triangle)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(90.0f, 130.0f);
    glEnd();

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glBegin(GL_TRIANGLES);  // Second blade (by constructing a triangle)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(90.0f, 130.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glBegin(GL_TRIANGLES);  // Third blade (by constructing a triangle)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(90.0f, 130.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(270, 0, 0, 1);
    glBegin(GL_TRIANGLES);  // Fourth blade (by constructing a triangle)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(90.0f, 130.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

// Graphic drawing utility functions
void drawFillLightPurple(GLfloat vertices[][2], GLint indices[], int count) {
    glColor3f(COLOR_LIGHT_PURPLE_R, COLOR_LIGHT_PURPLE_G, COLOR_LIGHT_PURPLE_B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++) {
        glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
    }
    glEnd();
}

void drawFillBackgroundColor(GLfloat vertices[][2], GLint indices[], int count) {
    glColor3f(COLOR_LIGHT_BLUE_R, COLOR_LIGHT_BLUE_G, COLOR_LIGHT_BLUE_B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++) {
        glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
    }
    glEnd();
}

void drawFillLightGreen(GLfloat vertices[][2], GLint indices[], int count) {
    glColor3f(COLOR_LIGHT_GREEN_R, COLOR_LIGHT_GREEN_G, COLOR_LIGHT_GREEN_B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++) {
        glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
    }
    glEnd();
}

void drawOutline(GLfloat vertices[][2], GLint indices[], int count) {
    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < count; i++) {
        glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
    }
    glEnd();
    glLineWidth(1.0f);
}

// Graphic-specific drawing functions
void drawFill4Triangle() {
    glColor3f(COLOR_LIGHT_PURPLE_R, COLOR_LIGHT_PURPLE_G, COLOR_LIGHT_PURPLE_B);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < count4; i++) {
        glVertex2f(vertices4[i][0], vertices4[i][1]);
    }
    glEnd();
}

void drawOutline4Triangle() {
    glLineWidth(LINE_WIDTH);
    GLfloat edge3_r = isWireframe ? COLOR_LIGHT_BLUE_R : COLOR_LIGHT_PURPLE_R;
    GLfloat edge3_g = isWireframe ? COLOR_LIGHT_BLUE_G : COLOR_LIGHT_PURPLE_G;
    GLfloat edge3_b = isWireframe ? COLOR_LIGHT_BLUE_B : COLOR_LIGHT_PURPLE_B;

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices4[0][0], vertices4[0][1]);
    glVertex2f(vertices4[1][0], vertices4[1][1]);
    glEnd();

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices4[2][0], vertices4[2][1]);
    glVertex2f(vertices4[0][0], vertices4[0][1]);
    glEnd();

    glColor3f(edge3_r, edge3_g, edge3_b);
    glBegin(GL_LINES);
    glVertex2f(vertices4[1][0], vertices4[1][1]);
    glVertex2f(vertices4[2][0], vertices4[2][1]);
    glEnd();

    glLineWidth(1.0f);
}
// Below are the drawing functions for XJTLU landmark buildings (Figures 1 to 41)
// Drawing of CB building (purple)
void drawShape4() {
    if (isWireframe) drawOutline4Triangle();
    else { drawFill4Triangle(); drawOutline4Triangle(); }
}

void drawFill7Triangle() {
    glColor3f(COLOR_LIGHT_BLUE_R, COLOR_LIGHT_BLUE_G, COLOR_LIGHT_BLUE_B);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < count7; i++) {
        glVertex2f(vertices7[i][0], vertices7[i][1]);
    }
    glEnd();
}

void drawOutline7Triangle() {
    glLineWidth(LINE_WIDTH);
    GLfloat edge3_r = COLOR_LIGHT_BLUE_R;
    GLfloat edge3_g = COLOR_LIGHT_BLUE_G;
    GLfloat edge3_b = COLOR_LIGHT_BLUE_B;

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices7[0][0], vertices7[0][1]);
    glVertex2f(vertices7[1][0], vertices7[1][1]);
    glEnd();

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices7[2][0], vertices7[2][1]);
    glVertex2f(vertices7[0][0], vertices7[0][1]);
    glEnd();

    glColor3f(edge3_r, edge3_g, edge3_b);
    glBegin(GL_LINES);
    glVertex2f(vertices7[1][0], vertices7[1][1]);
    glVertex2f(vertices7[2][0], vertices7[2][1]);
    glEnd();

    glLineWidth(1.0f);
}

void drawShape7() {
    if (isWireframe) drawOutline7Triangle();
    else { drawFill7Triangle(); drawOutline7Triangle(); }
}

void drawFill8Triangle() {
    glColor3f(COLOR_LIGHT_BLUE_R, COLOR_LIGHT_BLUE_G, COLOR_LIGHT_BLUE_B);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < count8; i++) {
        glVertex2f(vertices8[i][0], vertices8[i][1]);
    }
    glEnd();
}

void drawOutline8Triangle() {
    glLineWidth(LINE_WIDTH);
    GLfloat edge3_r = COLOR_LIGHT_BLUE_R;
    GLfloat edge3_g = COLOR_LIGHT_BLUE_G;
    GLfloat edge3_b = COLOR_LIGHT_BLUE_B;

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices8[0][0], vertices8[0][1]);
    glVertex2f(vertices8[1][0], vertices8[1][1]);
    glEnd();

    glColor3f(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
    glBegin(GL_LINES);
    glVertex2f(vertices8[2][0], vertices8[2][1]);
    glVertex2f(vertices8[0][0], vertices8[0][1]);
    glEnd();

    glColor3f(edge3_r, edge3_g, edge3_b);
    glBegin(GL_LINES);
    glVertex2f(vertices8[1][0], vertices8[1][1]);
    glVertex2f(vertices8[2][0], vertices8[2][1]);
    glEnd();

    glLineWidth(1.0f);
}

void drawShape8() {
    if (isWireframe) drawOutline8Triangle();
    else { drawFill8Triangle(); drawOutline8Triangle(); }
}

void drawShapeLightPurple(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else { drawFillLightPurple(vertices, indices, count); drawOutline(vertices, indices, count); }
}

void drawShapeLightGray(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else { drawFillBackgroundColor(vertices, indices, count); drawOutline(vertices, indices, count); }
}

void drawShapeLightPurple5(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else { drawFillLightPurple(vertices, indices, count); drawOutline(vertices, indices, count); }
}

void drawShapeLightGray6(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else { drawFillBackgroundColor(vertices, indices, count); drawOutline(vertices, indices, count); }
}

// Drawing of White House (yellow) - Figures 9-18
void drawShapeLightPurple9(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple10(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple11(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple12(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple13(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple14(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple15(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple16(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}

void drawShapeLightPurple17(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape17UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}

void drawShapeLightPurple18(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_YELLOW_R, COLOR_LIGHT_YELLOW_G, COLOR_LIGHT_YELLOW_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}

// Drawing of FB building (orange) - Figures 19-41
void drawShapeLightPurple19(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}

void drawShapeLightPurple22(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple23(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}

void drawShape20(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape20UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape21(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape21UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape24(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape24UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape25(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape25UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape26(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape26UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape27(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape27UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape28(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape28UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape29(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape29UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape30(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape30UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape31(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape31UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}

void drawShapeLightPurple32(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple33(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple34(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShape35(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape35UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape36(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape36UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShape37(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape37UseBgColor) drawFillBackgroundColor(vertices, indices, count);
        else {
            glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
            glBegin(GL_POLYGON);
            for (int i = 0; i < count; i++) {
                glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
            }
            glEnd();
        }
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple38(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple39(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}
void drawShapeLightPurple40(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) drawOutline(vertices, indices, count);
    else {
        glColor3f(COLOR_LIGHT_ORANGE_R, COLOR_LIGHT_ORANGE_G, COLOR_LIGHT_ORANGE_B);
        glBegin(GL_POLYGON);
        for (int i = 0; i < count; i++) {
            glVertex2f(vertices[indices[i]][0], vertices[indices[i]][1]);
        }
        glEnd();
        drawOutline(vertices, indices, count);
    }
}


void drawShape41(GLfloat vertices[][2], GLint indices[], int count) {
    if (isWireframe) {
        drawOutline(vertices, indices, count);
    }
    else {
        if (shape41UseLightGreen) drawFillLightGreen(vertices, indices, count);
        else drawFillLightPurple(vertices, indices, count);
        drawOutline(vertices, indices, count);
    }
}

// Balloon-related functions
void initBalloons() {
    srand(glutGet(GLUT_ELAPSED_TIME));
    float colors[BALLOON_NUM][3] = {
        {0.9f, 0.6f, 0.6f}, {0.9f, 0.9f, 0.6f}, {0.6f, 0.7f, 0.9f}, {0.6f, 0.9f, 0.6f},
        {0.9f, 0.6f, 0.9f}, {0.9f, 0.6f, 0.6f}, {0.9f, 0.6f, 0.9f}, {0.9f, 0.9f, 0.6f}
    };

    for (int i = 0; i < BALLOON_NUM; i++) {
        balloons[i].x = 50.0f + rand() % 80;
        balloons[i].y = 50.0f + rand() % 80;
        balloons[i].rotation = 0.0f;
        balloons[i].swing = 0.0f;
        balloons[i].speedX = 0.4f + rand() % 3 * 0.15f;
        balloons[i].speedY = 0.4f + rand() % 3 * 0.15f;
        balloons[i].rotSpeed = 0.15f + rand() % 3 * 0.05f;
        balloons[i].r = colors[i][0];
        balloons[i].g = colors[i][1];
        balloons[i].b = colors[i][2];
    }
}

void drawSingleBalloon(Balloon& balloon) {
    glPushMatrix();
    glTranslatef(balloon.x, balloon.y, 0.0f);
    glScalef(BALLOON_SCALE, BALLOON_SCALE, 1.0f);
    glRotatef(balloon.swing, 0.0f, 0.0f, 1.0f);

    glColor3f(balloon.r, balloon.g, balloon.b);
    glBegin(GL_POLYGON);
    for (int j = 0; j < 36; j++) {
        float angle = 2.0f * static_cast<float>(M_PI) * j / 36.0f;
        glVertex2f(BALLOON_RADIUS * cosf(angle), BALLOON_RADIUS * sinf(angle));
    }
    glEnd();

    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_POLYGON);
    for (int j = 0; j < 20; j++) {
        float angle = 2.0f * static_cast<float>(M_PI) * j / 20.0f;
        glVertex2f(
            BALLOON_RADIUS * 0.3f * cosf(angle) + BALLOON_RADIUS * 0.5f,
            BALLOON_RADIUS * 0.3f * sinf(angle) + BALLOON_RADIUS * 0.5f
        );
    }
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -BALLOON_RADIUS);
    glVertex2f(
        ROPE_LENGTH * 0.2f * sinf(balloon.rotation),
        -BALLOON_RADIUS - ROPE_LENGTH + ROPE_LENGTH * 0.1f * cosf(balloon.rotation)
    );
    glEnd();
    glLineWidth(1.0f);

    glPopMatrix();
}

void drawAllBalloons() {
    for (int i = 0; i < BALLOON_NUM; i++) {
        drawSingleBalloon(balloons[i]);
    }
}

void balloonUpdate(int value) {
    for (int i = 0; i < BALLOON_NUM; i++) {
        balloons[i].x += balloons[i].speedX;
        balloons[i].y += balloons[i].speedY;
        balloons[i].swing = SWING_AMPLITUDE * sinf(balloons[i].x * 0.012f + balloons[i].y * 0.012f + i);
        balloons[i].rotation += balloons[i].rotSpeed * 0.3f;

        if (balloons[i].x > 850 || balloons[i].y > 650) {
            balloons[i].x = 50.0f + rand() % 80;
            balloons[i].y = 50.0f + rand() % 80;
            balloons[i].rotation = 0.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(20, balloonUpdate, 0);
}

// Cloud drawing and updating
void initClouds() {
    srand(glutGet(GLUT_ELAPSED_TIME));
    int cloudCount = 4 + rand() % 3;

    for (int i = 0; i < cloudCount; i++) {
        Cloud cloud;
        cloud.x = -50.0f - rand() % 350;
        cloud.y = 350.0f + rand() % 120;
        cloud.size = 80.0f + rand() % 70;
        cloud.speed = CLOUD_MIN_SPEED + (rand() % 10) * (CLOUD_MAX_SPEED - CLOUD_MIN_SPEED) / 10.0f;
        cloud.segments = 3 + rand() % 3;

        clouds.push_back(cloud);
    }
}

void drawCloud(Cloud& cloud) {
    glPushMatrix();
    glTranslatef(cloud.x, cloud.y, 0.0f);
    glScalef(cloud.size / 100.0f, cloud.size / 100.0f, 1.0f);

    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);

    for (int i = 0; i < cloud.segments; i++) {
        float offsetX = (i - (cloud.segments - 1) / 2.0f) * 40.0f;
        float sizeFactor = 1.0f - abs(i - (cloud.segments - 1) / 2.0f) / (cloud.segments * 0.7f);

        glPushMatrix();
        glTranslatef(offsetX, 0.0f, 0.0f);

        glBegin(GL_TRIANGLE_FAN);  // Construct triangle fan
        glVertex2f(0.0f, 0.0f);
        for (int j = 0; j <= 36; j++) {
            float angle = static_cast<float>(j * 10.0 * M_PI / 180.0);
            float x = cos(angle) * 50.0f * sizeFactor;
            float y = sin(angle) * 30.0f * sizeFactor;
            glVertex2f(x, y);
        }
        glEnd();

        glPopMatrix();
    }

    glBegin(GL_TRIANGLE_FAN);  // Construct triangle fan
    glVertex2f(-(cloud.segments - 1) * 20.0f, -10.0f);
    glVertex2f(-(cloud.segments - 1) * 20.0f, -20.0f);
    glVertex2f((cloud.segments - 1) * 20.0f, -20.0f);
    glVertex2f((cloud.segments - 1) * 20.0f, -10.0f);
    glEnd();

    glPopMatrix();
}

void drawAllClouds() {
    for (auto& cloud : clouds) {
        drawCloud(cloud);
    }
}

void updateClouds(int value) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    for (auto& cloud : clouds) {
        cloud.x += cloud.speed;
        if (cloud.x > windowWidth + cloud.size) {
            cloud.x = -50.0f - rand() % 350;
            cloud.y = 350.0f + rand() % 120;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateClouds, 0);
}

// Star drawing and updating
void initStars() {
    srand(glutGet(GLUT_ELAPSED_TIME));
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float starColors[4][3] = {
        {STAR_COLOR_YELLOW_R, STAR_COLOR_YELLOW_G, STAR_COLOR_YELLOW_B},
        {STAR_COLOR_PINK_R, STAR_COLOR_PINK_G, STAR_COLOR_PINK_B},
        {STAR_COLOR_BLUE_R, STAR_COLOR_BLUE_G, STAR_COLOR_BLUE_B},
        {STAR_COLOR_GREEN_R, STAR_COLOR_GREEN_G, STAR_COLOR_GREEN_B}
    };

    for (int i = 0; i < STAR_COUNT; i++) {
        Star star;
        star.x = rand() % windowWidth;
        star.y = windowHeight * 0.6f + rand() % (int)(windowHeight * 0.4f);
        star.size = STAR_MIN_SIZE + (rand() % 100) / 100.0f * (STAR_MAX_SIZE - STAR_MIN_SIZE);
        star.blinkSpeed = STAR_MIN_SPEED + (rand() % 100) / 100.0f * (STAR_MAX_SPEED - STAR_MIN_SPEED);
        star.bgFactor = 0.1f + (rand() % 100) / 100.0f * 0.2f;  // 0.1-0.3

        int colorIndex = rand() % 4;
        star.r = starColors[colorIndex][0];
        star.g = starColors[colorIndex][1];
        star.b = starColors[colorIndex][2];

        stars.push_back(star);
    }
}

// Make stars blend better with background when blinking
void drawStar(Star& star) {
    glPushMatrix();
    glTranslatef(star.x, star.y, 0.0f);
    glScalef(star.size, star.size, 1.0f);


    float blend = 1.0f - star.brightness;
    float r = star.r * star.brightness + BACKGROUND_R * blend * (0.5f + star.bgFactor);
    float g = star.g * star.brightness + BACKGROUND_G * blend * (0.5f + star.bgFactor);
    float b = star.b * star.brightness + BACKGROUND_B * blend * (0.5f + star.bgFactor);

    r = std::max(0.0f, std::min(1.0f, r));
    g = std::max(0.0f, std::min(1.0f, g));
    b = std::max(0.0f, std::min(1.0f, b));

    glColor3f(r, g, b);

    // Draw star
    glBegin(GL_POLYGON);  // Draw using polygon
    float angle, x, y;
    for (int i = 0; i < 8; i++) {
        angle = i * M_PI / 4.0f;
        float radius = (i % 2 == 0) ? 5.0f : 2.0f;
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}

void drawAllStars() {
    for (auto& star : stars) {
        drawStar(star);
    }
}

// Control star brightness again
void updateStars(int value) {
    for (auto& star : stars) {
        float t = glutGet(GLUT_ELAPSED_TIME) * star.blinkSpeed;
        star.brightness = 0.6f + 0.4f * cos(t);  // Range 0.2 to 1.0
    }
    glutPostRedisplay();
    glutTimerFunc(50, updateStars, 0);
}

// Interactive controls
void keyboard_input(unsigned char key, int x, int y) {  // Special key interaction
    switch (key) {
    case 'q': case 'Q': exit(0); break;  // Q key to close window
    case 'f': case 'F': step = -step; break;  // F key to reverse windmill direction
    case 's': case 'S': step = 0; break;  // S key to stop windmill
    case 'r': case 'R': if (step >= -15) step--; break;  // R key to accelerate windmill in reverse, max 15
    case 't': case 'T': if (step <= 15) step++; break;  // T key to accelerate windmill forward, max 15
    }
}

void myMouse(int button, int state, int x, int y) {  // Mouse interaction
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // Left mouse button toggles wireframe/fill mode for all graphics, and changes text font and windmill color
        colorState = 1 - colorState;
        textColorState = 1 - textColorState;
        isWireframe = !isWireframe;
        shape17UseBgColor = !shape17UseBgColor;
        shape20UseBgColor = !shape20UseBgColor;
        shape21UseBgColor = !shape21UseBgColor;
        shape24UseBgColor = !shape24UseBgColor;
        shape25UseBgColor = !shape25UseBgColor;
        shape26UseBgColor = !shape26UseBgColor;
        shape27UseBgColor = !shape27UseBgColor;
        shape28UseBgColor = !shape28UseBgColor;
        shape29UseBgColor = !shape29UseBgColor;
        shape30UseBgColor = !shape30UseBgColor;
        shape31UseBgColor = !shape31UseBgColor;
        shape35UseBgColor = !shape35UseBgColor;
        shape36UseBgColor = !shape36UseBgColor;
        shape37UseBgColor = !shape37UseBgColor;
        shape41UseLightGreen = !shape41UseLightGreen;
        glutPostRedisplay();
    }
}

// Display function
void display(void) {
    glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawAllClouds();
    drawWindmill();
    drawAllStars();

    const char* text = "XJTLU 20th celebration";  // Text content
    selectFont(56, ANSI_CHARSET, "Tahoma");  // Text font
    if (textColorState == 0) {
        glColor3f(1.0f, 1.0f, 1.0f);  // Initial text color
    }
    else {
        glColor3f(TEXT_TARGET_COLOR_R, TEXT_TARGET_COLOR_G, TEXT_TARGET_COLOR_B);  // Color after transition
    }
    float textWidth = calculateStringWidth(text);
    float startX = 400.0f - textWidth / 2.0f;
    float startY = 375.0f - 28.0f;  // Text position
    glRasterPos2f(startX, startY);
    drawString(text);
    // Below are the drawings of Figures 1 to 41, with positions increasing upward; Figure 1 is the bottom layer, Figure 41 is the top layer
    glPushMatrix();
    glTranslatef(TRANS_X, TRANS_Y, 0.0f);
    glScalef(SCALE_FACTOR, SCALE_FACTOR, 1.0f);
    drawShapeLightPurple(vertices2, indices2, count2);
    drawShape8();
    drawShapeLightGray(vertices3, indices3, count3);
    drawShape4();
    drawShapeLightPurple(vertices1, indices1, count1);
    drawShapeLightGray6(vertices6, indices6, count6);
    drawShapeLightPurple5(vertices5, indices5, count5);
    drawShape7();
    drawShapeLightPurple9(vertices9, indices9, count9);
    drawShapeLightPurple10(vertices10, indices10, count10);
    drawShapeLightPurple11(vertices11, indices11, count11);
    drawShapeLightPurple12(vertices12, indices12, count12);
    drawShapeLightPurple13(vertices13, indices13, count13);
    drawShapeLightPurple14(vertices14, indices14, count14);
    drawShapeLightPurple15(vertices15, indices15, count15);
    drawShapeLightPurple16(vertices16, indices16, count16);
    drawShapeLightPurple17(vertices17, indices17, count17);
    drawShapeLightPurple18(vertices18, indices18, count18);
    drawShapeLightPurple19(vertices19, indices19, count19);
    drawShape20(vertices20, indices20, count20);
    drawShape21(vertices21, indices21, count21);
    drawShapeLightPurple22(vertices22, indices22, count22);
    drawShapeLightPurple23(vertices23, indices23, count23);
    drawShape24(vertices24, indices24, count24);
    drawShape25(vertices25, indices25, count25);
    drawShape26(vertices26, indices26, count26);
    drawShape27(vertices27, indices27, count27);
    drawShape28(vertices28, indices28, count28);
    drawShape29(vertices29, indices29, count29);
    drawShape30(vertices30, indices30, count30);
    drawShape31(vertices31, indices31, count31);
    drawShapeLightPurple32(vertices32, indices32, count32);
    drawShapeLightPurple33(vertices33, indices33, count33);
    drawShapeLightPurple34(vertices34, indices34, count34);
    drawShape35(vertices35, indices35, count35);
    drawShape36(vertices36, indices36, count36);
    drawShape37(vertices37, indices37, count37);
    drawShapeLightPurple38(vertices38, indices38, count38);
    drawShapeLightPurple39(vertices39, indices39, count39);
    drawShapeLightPurple40(vertices40, indices40, count40);
    drawShape41(vertices41, indices41, count41);
    glPopMatrix();

    drawAllBalloons();
    drawCenterCircle();
    drawNewCenterCircle();
    drawAnotherNewCenterCircle();
    drawAnotherNewCenterCircle1();
    drawVerticalLine();
    drawVerticalLine1();
    drawVerticalLine2();
    drawVerticalLine3();
    glutSwapBuffers();
}

// Initialization and main function
void myinit(void) {
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    initBalloons();
    initClouds();
    initStars();
}

void myReshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Xjtlu 20th Anniversary Greeting Card");

    myinit();

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutIdleFunc([]() { glutPostRedisplay(); });
    glutTimerFunc(time_interval, OnTimer, 1);
    glutTimerFunc(0, balloonUpdate, 0);
    glutTimerFunc(0, updateClouds, 0);
    glutTimerFunc(0, updateStars, 0);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(myMouse);

    glutMainLoop();
    return 0;
}