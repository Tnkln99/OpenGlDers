//
// Created by tanku on 14.10.2022.
//

#ifndef OPENGLTRAINING_SNAKE_H
#define OPENGLTRAINING_SNAKE_H

#include <iostream>
#include <vector>
#include "CubeObject.h"
#include "CubeMesh.h"

enum Direction{
    RIGHT, LEFT, UP, DOWN
};


class Snake {
private:
    std::vector<CubeObject> body;
    Direction direction = Direction::RIGHT;
    float moveTimer{0};

    double eatTime;
    bool canEat{true};
public:
    explicit Snake(float xP, float yP, CubeMesh* mesh);

    void setDirection(Direction direction);
    Direction getDirection();

    std::vector<CubeObject>& getBody();
    void eat();

    void update();
};


#endif //OPENGLTRAINING_SNAKE_H
