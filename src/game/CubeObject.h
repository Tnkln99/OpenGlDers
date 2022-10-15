#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "../engine/maths/Matrix4.h"

enum Type{
    AppleCube, SnakeCube
};

class Shader;
class CubeMesh;

class CubeObject {
public:
  CubeObject(float xP, float yP, CubeMesh* cubeMeshP, Type type);

  void update();
  void draw(Shader& shader);

  float getX() const { return x; }
  float getY() const { return y; }
  Type getType();

  void setPosition(float xP, float yP);
  Matrix4 computeTransform();

private:
  float x { 0.0f };
  float y { 0.0f };
  Matrix4 transform {};

  CubeMesh* cubeMesh { nullptr };

  Type cubeType;
};

#endif