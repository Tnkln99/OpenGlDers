#include "CubeObject.h"
#include "../engine/Shader.h"
#include "CubeMesh.h"
#include "../engine/Timer.h"

CubeObject::CubeObject(float xP, float yP, CubeMesh* cubeMeshP, Type type)
: cubeMesh { cubeMeshP }, cubeType{ type }
{
  setPosition(xP, yP);
}

void CubeObject::update() {
    if(cubeType == Type::AppleCube){
        const float t = Maths::abs(Maths::sin(Timer::getTimeSinceStart() * 0.5f)) - 0.8f;

        transform = transform
                    * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
                    * Matrix4::createRotationX(t * Maths::toRadians(21.0f));
    }
}

void CubeObject::draw(Shader& shader) {
  shader.setMatrix4("mv_matrix", transform);
  cubeMesh->draw();
}

void CubeObject::setPosition(float xP, float yP) {
  x = xP;
  y = yP;
  transform = computeTransform();
}

Matrix4 CubeObject::computeTransform() {
    if(cubeType == Type::SnakeCube){
        return Matrix4::createTranslation(Vector3(x, y, -4.0f));
    }
    else if(cubeType == Type::AppleCube){
        return Matrix4::createTranslation(Vector3(x, y, -4.0f)) * Matrix4::createScale(0.3);
    }
}

Type CubeObject::getType() {
    return cubeType;
}
