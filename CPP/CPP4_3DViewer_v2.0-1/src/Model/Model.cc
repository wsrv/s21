#include "Model.h"

namespace s21 {

void Model::Read(const std::string path) {
  try {
    std::ifstream file(path);
    std::string line;
    vertexesArr.clear();
    facetsArr.clear();
    if (file.is_open())
      while (std::getline(file, line)) CheckFormat(line);
    else
      throw std::invalid_argument("File not found");
    file.close();

    auto max = *(std::max_element(vertexesArr.begin(), vertexesArr.end()));
    for (int i = 0; i < int(vertexesArr.size()); i++) vertexesArr[i] /= 2 * max;
  } catch (const std::exception &e) {
    vertexesArr.clear();
    facetsArr.clear();
    throw std::invalid_argument(e.what());
  }
}

void Model::Shift(double shift, char axis) noexcept {
  shift /= 100.0;
  int add = 0;
  if (axis == 'x') add = 0;
  if (axis == 'y') add = 1;
  if (axis == 'z') add = 2;
  for (int i = 0; i < int(vertexesArr.size()); i += 3)
    vertexesArr[i + add] += shift;
}

void Model::Rotate(double degree, char axis) noexcept {
  int add1 = 0, add2 = 0;
  degree *= M_PI / 180.0;
  if (axis == 'x') {
    add1 = 1;
    add2 = 2;
  }
  if (axis == 'y') {
    add1 = 0;
    add2 = 2;
  }
  if (axis == 'z') {
    add1 = 0;
    add2 = 1;
  }

  for (int i = 0; i < int(vertexesArr.size()); i += 3) {
    double axis1 = vertexesArr[i + add1];
    double axis2 = vertexesArr[i + add2];
    vertexesArr[i + add1] = cos(degree) * axis1 - sin(degree) * axis2;
    vertexesArr[i + add2] = sin(degree) * axis1 + cos(degree) * axis2;
  }
}

void Model::Scaling(double scale) noexcept {
  for (int i = 0; i < int(vertexesArr.size()); i++) vertexesArr[i] *= scale;
}

void Model::CheckFormat(const std::string &line) {
  try {
    if (!line.compare(0, 2, "v ", 0, 2)) Vertex vertex(line, this);
    if (!line.compare(0, 2, "f ", 0, 2)) Facets facets(line, this);
  } catch (const std::exception &e) {
    throw std::invalid_argument(e.what());
  }
}

void Vertex::Nurlanization(std::string line, Model *model) {
  int count = 0;
  for (std::size_t i = 1; line.size() && count < 3; i = 1) {
    if (isdigit(line.front()) || line.front() == '-') {
      model->vertexesArr.emplace_back(stod(line, &i));
      count++;
    }
    line = line.substr(i, line.size() - i);
  }
  if (count != 3) throw std::invalid_argument("Invalid format");
}

void Facets::Nurlanization(std::string line, Model *model) {
  int j = 0;
  int buf = 0;
  for (std::size_t i = 1; line.size(); i = 1) {
    if ((line.front() == ' ') &&
        (isdigit(*(++line.begin())) || (*(++line.begin())) == '-')) {
      auto integer = std::stoi(line);
      if (integer < 0) {
        if (abs(integer) > model->vertexesArr.size() / 3)
          throw std::invalid_argument("Invalid format");
        integer = model->vertexesArr.size() / 3 + integer;
      } else
        integer--;
      if (j == 0)
        buf = integer;
      else
        model->facetsArr.emplace_back(integer);
      model->facetsArr.emplace_back(integer);
      i++;
      j++;
    }
    line = line.substr(i, line.size() - i);
  }
  model->facetsArr.emplace_back(buf);
}

void Model::Print() {
  for (int i = 0; i < int(vertexesArr.size()); i++) {
    if (i % 3 == 0) std::cout << "\n";
    std::cout << vertexesArr[i] << " ";
  }
  for (int i = 0; i < int(facetsArr.size()); i++) {
    if (i % 6 == 0) std::cout << "\n";
    if (i % 2 == 0) std::cout << " ";
    std::cout << facetsArr[i];
  }
}

}  // namespace s21
