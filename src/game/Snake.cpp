//
// Created by tanku on 14.10.2022.
//

#include "Snake.h"
#include "../engine/Timer.h"

Snake::Snake(float xP, float yP, CubeMesh* mesh) {
    body.emplace_back(xP, yP, mesh, Type::SnakeCube);
    body.emplace_back(xP-0.22 ,yP ,mesh, Type::SnakeCube);
    body.emplace_back(xP-0.44 ,yP ,mesh, Type::SnakeCube);
    body.emplace_back(xP-0.66 ,yP ,mesh, Type::SnakeCube);
}

std::vector<CubeObject> &Snake::getBody() {
    return body;
}

void Snake::setDirection(Direction direction) {
    this->direction = direction;
}

Direction Snake::getDirection() {
    return direction;
}

void Snake::eat() {
    if(canEat) {
        //std::cout << "eat" << std::endl;
        CubeObject newTale = body[body.size() - 1];
        body.emplace_back(newTale);
        canEat = false;
        eatTime = Timer::getTimeSinceStart();
    }
    else if (Timer::getTimeSinceStart() - eatTime > 5){
        canEat = true;
    }
}

void Snake::update() {
    std::vector<std::pair<float,float>> lastPositions;
    for(auto & i : body){
        std::pair<float, float> tmp;
        tmp.first = i.getX();
        tmp.second = i.getY();
        lastPositions.emplace_back(tmp);
    }

    if(moveTimer > 0.4 && body.size()>1){
        if(direction == Direction::RIGHT){
            body[0].setPosition(body[0].getX() + 0.22, body[0].getY());
            for(int i = 1; i < body.size(); i ++){
                body[i].setPosition(lastPositions[i-1].first, lastPositions[i-1].second);
            }
        }
        else if(direction == Direction::LEFT){
            body[0].setPosition(body[0].getX() - 0.22, body[0].getY());
            for(int i = 1; i < body.size(); i ++){
                body[i].setPosition(lastPositions[i-1].first, lastPositions[i-1].second);
            }
        }
        else if(direction == Direction::UP){
            body[0].setPosition(body[0].getX(), body[0].getY() + 0.22);
            for(int i = 1; i < body.size(); i ++){
                body[i].setPosition(lastPositions[i-1].first, lastPositions[i-1].second);
            }

        }
        else if(direction == Direction::DOWN){
            body[0].setPosition(body[0].getX(), body[0].getY() - 0.22);
            for(int i = 1; i < body.size(); i ++){
                body[i].setPosition(lastPositions[i-1].first, lastPositions[i-1].second);
            }
        }
        moveTimer = 0;
    }
    else
        moveTimer += 0.02f;

}




