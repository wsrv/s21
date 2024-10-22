#include <gtest/gtest.h>

#include "../Controller/Controller.h"
#include "../Model/Model.h"

TEST(start, test_1) {
  s21::Object object;
  double vertex[] = {0.5, -0.5, -0.5, 0.5,  -0.5, 0.5,  -0.5, -0.5,
                     0.5, -0.5, -0.5, -0.5, 0.5,  0.5,  -0.5, 0.5,
                     0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, 0.5,  -0.5};

  int face[] = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  object.Read("../ObjectFile/cube.obj");
  double* vertex_ = object.GetVertex();
  int* face_ = object.GetArea();
  for (int i = 0; i < 24; i++) {
    EXPECT_EQ(face_[i], face[i]);
    EXPECT_EQ(vertex_[i], vertex[i]);
  }
  // object.Print();
}

TEST(start, test_2) {
  double vertex[] = {

      1.5, 0.5, 0.5, 1.5, 0.5, 1.5, 0.5, 0.5, 1.5, 0.5, 0.5, 0.5,
      1.5, 1.5, 0.5, 1.5, 1.5, 1.5, 0.5, 1.5, 1.5, 0.5, 1.5, 0.5};
  int face[] = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  s21::Object object;
  object.Read("../ObjectFile/cube.obj");
  object.Shift(100, 'x');
  object.Shift(100, 'y');
  object.Shift(100, 'z');
  double* vertex_ = object.GetVertex();
  int* face_ = object.GetArea();
  for (int i = 0; i < 24; i++) {
    EXPECT_EQ(face_[i], face[i]);
    EXPECT_EQ(vertex_[i], vertex[i]);
  }
  // object.Print();
}

TEST(start, test_3) {
  s21::Object object;
  double vertex[] = {0.25, -0.25, -0.25, 0.25,  -0.25, 0.25,  -0.25, -0.25,
                     0.25, -0.25, -0.25, -0.25, 0.25,  0.25,  -0.25, 0.25,
                     0.25, 0.25,  -0.25, 0.25,  0.25,  -0.25, 0.25,  -0.25};
  int face[] = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  object.Read("../ObjectFile/cube.obj");
  object.Scaling(0.5);

  double* vertex_ = object.GetVertex();
  int* face_ = object.GetArea();
  for (int i = 0; i < 24; i++) {
    EXPECT_EQ(face_[i], face[i]);
    EXPECT_EQ(vertex_[i], vertex[i]);
  }
  // object.Print();
}

TEST(start, test_4) {
  s21::Object object;
  double vertex[] = {-0.5, 0.5,  0.5, 0.5,  0.5,  0.5,  0.5,  0.5,
                     -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5,  0.5,
                     -0.5, 0.5,  0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
  int face[] = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  object.Read("../ObjectFile/cube.obj");
  object.Rotate(90, 'x');
  object.Rotate(90, 'y');
  object.Rotate(90, 'z');

  double* vertex_ = object.GetVertex();
  int* face_ = object.GetArea();
  for (int i = 0; i < 24; i++) {
    EXPECT_NEAR(vertex_[i], vertex[i], 10E-7);
    EXPECT_EQ(face_[i], face[i]);
  }
  // object.Print();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}