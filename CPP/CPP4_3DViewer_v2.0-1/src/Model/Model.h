#ifndef MODEL_H
#define MODEL_H

#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

/*!
\mainpage Документация проекта

Это документация моего проекта для работы с 3D моделями.

@section intro Введение
Этот проект предназначен для работы с 3D моделями.

@section usage Правила использования
\liФайлы объектов должны быть в формате .obj.
\liВершины должны быть в формате x y z.
\liПоследовательность соединения точек должна быть целой.

@section author Авторы проекта: macygabr, roddstat
*/

namespace s21 {
class Vertex;
class Facets;
class Memento;
//! Общий класс модели
/*! Хранит информацию о считанной модели и предоставляет доступ к методам для
 * работы с ней
 */
class Model {
 private:
  friend class Vertex;
  friend class Memento;
  friend class Facets;
  std::vector<double> vertexesArr; /*!< Массив вершин */
  std::vector<int> facetsArr;      /*!< Массив поверхностей */

 public:
  Model() : vertexesArr(), facetsArr() {
    vertexesArr.reserve(3000000);
    facetsArr.reserve(3000000);
    // originaFacetsArr.reserve(3000000);
  };
  ~Model() = default;
  void Shift(double shift, char axis) noexcept; /*!< Функция сдвига */
  void Rotate(double degree, char axis) noexcept; /*!< Функция поворота */
  void Scaling(double scale) noexcept; /*!< Функция масштабирования */
  void Read(const std::string path); /*!< Функция считывания */
  int GetAreaSize() {
    return facetsArr.size();
  }; /*!< Функция рассчета полигонов */
  int GetVertexSize() {
    return vertexesArr.size();
  } /*!< Функция рассчета вершин */
  double *GetVertex() {
    return &vertexesArr[0];
  } /*!< Функция считывания массива вершин */
  int *GetArea() {
    return &facetsArr[0];
  } /*!< Функция считывания массива полигонов */
  void Print();

 private:
  void CheckFormat(const std::string &line);
};

//! Класс для работы с вершинами
/*! Хранит и обрабатывает информацию о вершинах */
class Vertex {
 public:
  Vertex(const std::string line, Model *model) { Nurlanization(line, model); }
  ~Vertex() = default;
  void Nurlanization(std::string line, Model *model);
};

//! Класс для работы с поверхностями
/*! Хранит и обрабатывает информацию о поверхностях */
class Facets {
 public:
  Facets(const std::string line, Model *model) { Nurlanization(line, model); }
  ~Facets() = default;
  void Nurlanization(std::string line, Model *model);
};

//! Класс хранитель
/*! Хранит информацию об объекте */
class Memento {
 public:
  std::vector<double> vertexesArr1;
  std::vector<int> facetsArr1;

  Memento() : vertexesArr1(), facetsArr1(){};
  ~Memento() = default;

  void Save(Model model) {
    this->vertexesArr1 = model.vertexesArr;
    this->facetsArr1 = model.facetsArr;
  };
  void RestoreVertex(Model *model) { model->vertexesArr = vertexesArr1; };
  void RestoreArea(Model *model) { model->facetsArr = facetsArr1; };
};

}  // namespace s21

#endif
