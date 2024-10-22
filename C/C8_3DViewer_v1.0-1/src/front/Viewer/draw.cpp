#include "draw.h"

#include <QOpenGLFunctions>

extern "C" {
#include "../../back/transformations.h"
}

draw::draw(QWidget *parent) : QOpenGLWidget(parent) {
  rotation[0] = 0.0;
  rotation[1] = 0.0;
  rotation[2] = 0.0;

  translation[0] = 0.0;
  translation[1] = 0.0;
  translation[2] = 0.0;

  scale = 1.0;

  typeVertices = 0;
  typeLines = 1;

  sizeVertices = 10.0;
  sizeLines = 1.0;

  projection = 1;

  colorVertices.setRedF(1.0f);
  colorVertices.setGreenF(0.0f);
  colorVertices.setBlueF(1.0f);

  colorLines.setRedF(1.0f);
  colorLines.setGreenF(1.0f);
  colorLines.setBlueF(1.0f);

  colorBackground.setRedF(0.0f);
  colorBackground.setGreenF(0.0f);
  colorBackground.setBlueF(0.0f);
}

draw::~draw() {}

void draw::initializeGL() {
  glClearColor(colorBackground.redF(), colorBackground.greenF(),
               colorBackground.blueF(), 1.0f);

  glEnable(GL_DEPTH);
}
void draw ::resizeGL(int w, int h) {}

void draw::paintGL() {
  glClearColor(colorBackground.redF(), colorBackground.greenF(),
               colorBackground.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (firstOpen != 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (!projection) {
      float winHeight = 0.5;
      float winWidth = 0.5;
      float fov = 60.0 * M_PI / 180;
      float heapHeight = winHeight / (2 * tan(fov / 2));
      glFrustum(-winWidth, winWidth, -winHeight, winHeight, heapHeight, 10);
      glTranslated(0, 0, -heapHeight * 3);
    } else
      glOrtho(-1, 1, -1, 1, 1, -1);

    glEnableVertexAttribArray(0);
    glEnableClientState(GL_VERTEX_ARRAY);

    displayVertices();
    displayLines();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableVertexAttribArray(0);
  }

  //    glEnableClientState(GL_VERTEX_ARRAY);
  //    glVertexPointer(3, GL_DOUBLE, 0, test.vertexesArr);
  //    glDrawElements(GL_LINES, (test.count_of_facets),
  //    GL_UNSIGNED_INT,test.facetsArr);
}

void draw::displayVertices() {
  if (typeVertices == 1) {
    glDisable(GL_POINT_SPRITE);
    glEnable(GL_POINT_SMOOTH);
  } else if (typeVertices == 0) {
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SPRITE);
  } else if (typeVertices == 2) {
    glDisable(GL_POINT_SMOOTH);
  }

  if (typeVertices != 0) {
    glColor3f(colorVertices.redF(), colorVertices.greenF(),
              colorVertices.blueF());
    glPointSize(sizeVertices);
    //    glVertexPointer(3, GL_DOUBLE, 0, model.vertices);
  }
  glVertexPointer(3, GL_DOUBLE, 0, test.vertexesArr);
  glDrawArrays(GL_POINTS, 0, test.count_of_vertexes / 3);
}

void draw::displayLines() {
  if (typeLines == 1) {
    glLineStipple(3, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (typeLines <= 1) {
    glColor3f(colorLines.redF(), colorLines.greenF(), colorLines.blueF());
    glLineWidth(sizeLines);
    glDrawElements(GL_LINES, (test.count_of_facets), GL_UNSIGNED_INT,
                   test.facetsArr);
  }
}
