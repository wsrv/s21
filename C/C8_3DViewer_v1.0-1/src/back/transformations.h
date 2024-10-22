#ifndef SRC_BACK_S21_TRANSFORMATION_H_
#define SRC_BACK_S21_TRANSFORMATION_H_
#include <stdio.h>

#define S21_PI 3.14159265358979323846264338327950288 /**< Число pi  */

typedef struct {
  int count_of_vertexes; /**< Общее число точек */
  int count_of_facets;   /**< Общее число полигонов */
  double* vertexesArr;   /**< Массив координат точек */
  int* facetsArr;        /**< Массив полигонов точек */
} dataNur;

int readFile(char* filename,
             dataNur* outputdata); /**< Считывание данных из файла */
int parsVertexes(dataNur* outputdata, int* index,
                 char* buffer); /**< Считывание координат вершин из файла */
int parsFacets(
    dataNur* outputdata, int* index,
    char* buffer); /**< Считывание порядка соединения точек из файла */
double makeNum(char* content,
               int* i); /**< Перевод числа из строки в тип double */
int countSize(FILE* fp, dataNur* outputdata);
int rotateObj(dataNur* inputdata, double degree,
              char axis); /**< Поворот объекта вокруг оси */
int scalingObj(dataNur* inputdata, double scale); /**< Изменение масштаба */
int shiftObj(dataNur* inputdata, double shift,
             char axis); /**< Сдвиг объекта вдоль оси */
int nurlanization(dataNur* inputdata); /**< Нормализация масштаба объекта */
#endif