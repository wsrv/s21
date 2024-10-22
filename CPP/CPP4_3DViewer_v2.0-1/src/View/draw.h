#ifndef DRAW_H
#define DRAW_H

#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

#include "../Controller/Controller.h"

class draw : public QOpenGLWidget {
  Q_OBJECT

 public:
  draw(QWidget *parent = Q_NULLPTR);
  ~draw();

  s21::Object object; /**< Структура данных */

  void initializeGL();    /**< Инициализация */
  void paintGL();         /**< Отрисовка окна */
  void displayVertices(); /**< Отрисовка вершин */
  void displayLines();    /**< Отрисовка линий */

  int projection; /**<  включена ли центральная проекция */

  double translation[3]{}; /**<  Смещение по осям */
  int rotation[3]{};       /**<  Вращение по осям */

  double scale{}; /**<  Масштаб */

  int typeVertices; /**<  Вид вершин */
  int typeLines;    /**<  Вид линий */

  int sizeVertices; /**<  Размер вершин */
  int sizeLines;    /**< Размер линий */

  QColor colorVertices;   /**<  Цвет вершин */
  QColor colorLines;      /**< Цвет линий */
  QColor colorBackground; /**< Цвет фона */
};

// class Image {
//  public:
//    Image(){};
//   ~Image() = default;
// };

#endif  // DRAW_H
