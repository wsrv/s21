#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>

#include "../Model/Model.h"

namespace s21 {
//! Фасад
/*! Удобная точка управления программой */
class Object {
 private:
  Model model;
  Memento memento;

 public:
  Object() : model(){};
  ~Object() = default;

 public:
  void Save() { memento.Save(model); };
  void Read(const std::string path) {
    model.Read(path);
    Save();
  };
  double* GetVertex() { return model.GetVertex(); };
  int* GetArea() { return model.GetArea(); };
  int GetVertexSize() { return model.GetVertexSize(); };
  int GetAreaSize() { return model.GetAreaSize(); };
  void RestoreVertex() { memento.RestoreVertex(&model); };
  void RestoreArea() { memento.RestoreArea(&model); };
  void Shift(double shift, char axis) { model.Shift(shift, axis); };
  void Rotate(double degree, char axis) { model.Rotate(degree, axis); };
  void Scaling(double scale) { model.Scaling(scale); };
  void Print() { model.Print(); };
};

}  // namespace s21
#endif