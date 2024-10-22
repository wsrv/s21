#ifndef DRAW_H
#define DRAW_H

#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

extern "C" {
#include "../../back/transformations.h"
}

class draw : public QOpenGLWidget {
  Q_OBJECT

 public:
  draw(QWidget *parent = Q_NULLPTR);
  ~draw();
  void initializeGL();         /**< Инициализация */
  void resizeGL(int w, int h); /**< Изменение общего масштаба */
  void paintGL();              /**< Отрисовка окна */
  void displayVertices(); /**< Отрисовка вершин */
  void displayLines();    /**< Отрисовка линий */

  dataNur test;    /**< Структура данных */
  char *file_name; /**< Имя файла */

  int zoom = 0; /**<  отношение текущего состояния масштаба к предыдущему */
  int firstOpen = 0; /**<  было ли это открыте файла в первый раз */
  int projection = 0; /**<  включена ли центральная проекция */
  int lastValueZ = 0; /**<  предыдущее значение координаты по z */
  int error =
      1; /**<  наличие ошибок, изначально, до открытия файла считаем что есть */

  double translation[3] = {0, 0, 0}; /**<  Смещение по осям */
  int rotation[3] = {0, 0, 0};       /**<  Вращение по осям */

  double scale = 100.0; /**<  Масштаб */

  int typeVertices = 0; /**<  Вид вершин */
  int typeLines = 1;    /**<  Вид линий */

  int sizeVertices = 10; /**<  Размер вершин */
  int sizeLines = 1;     /**< Размер линий */

  QColor colorVertices;   /**<  Цвет вершин */
  QColor colorLines;      /**< Цвет линий */
  QColor colorBackground; /**< Цвет фона */

 private:
};

#endif  // DRAW_H
