//
// Created by gaetz on 04/12/2019.
//

#include "Scene_007_SpinningCube.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <random>

#include "CubeMesh.h"
#include "Snake.h"


Scene_007_SpinningCube::Scene_007_SpinningCube()
{
}

Scene_007_SpinningCube::~Scene_007_SpinningCube() {
    clean();
}

void Scene_007_SpinningCube::setGame(Game *_game) {
    game = _game;
}

void Scene_007_SpinningCube::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->load();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    snake = new Snake(0,0,cubeMesh);

    apples.emplace_back(-2.5, 0, cubeMesh, Type::AppleCube);
}

void Scene_007_SpinningCube::clean() {
    cubeMesh->clean();
    delete cubeMesh;
}

void Scene_007_SpinningCube::pause() {
}

void Scene_007_SpinningCube::resume() {
}

void Scene_007_SpinningCube::handleEvent(const InputState &inputState) {
}

void Scene_007_SpinningCube::update(float dt) {
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_W] && snake->getDirection() != Direction::DOWN)
        snake->setDirection(Direction::UP);
    else if(keyboardState[SDL_SCANCODE_S] && snake->getDirection() != Direction::UP)
        snake->setDirection(Direction::DOWN);
    else if (keyboardState[SDL_SCANCODE_D] && snake->getDirection() != Direction::LEFT)
        snake->setDirection(Direction::RIGHT);
    else if (keyboardState[SDL_SCANCODE_A] && snake->getDirection() != Direction::RIGHT)
        snake->setDirection(Direction::LEFT);


    for (int i = 1; i < snake->getBody().size(); i++) {
        if (snake->getBody()[0].getX() == snake->getBody()[i].getX() && snake->getBody()[0].getY() == snake->getBody()[i].getY())
            std::cout<<"game over"<<std::endl;
    }

    for (auto& cube : snake->getBody()) {
        cube.update();
    }

    for (auto& apple : apples) {
        apple.update();
        if (checkForCollision(snake->getBody()[0], apple)){
            snake->eat();
            apples.clear();
        }
    }

    //std::cout<<"snake head coord "<< snake->getBody()[0].getX()<<" " << snake->getBody()[0].getY()<<std::endl;
    //std::cout<<"food coord "<<apples->getApples()[0].getX()<<" "<<apples->getApples()[0].getY()<<std::endl;

    snake->update();
    spawnApple();
    /*float formerXPosition = snake->getBody()[0].getX();
    float newXPosition = formerXPosition + 0.02f;
    snake->getBody()[0].setPosition(newXPosition, snake->getBody()[0].getY());*/
}

void Scene_007_SpinningCube::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    for (auto& cube : snake->getBody()) {
        cube.draw(shader);
    }

    for (auto& apple : apples) {
        apple.draw(shader);
    }
}

bool Scene_007_SpinningCube::checkForCollision(CubeObject& cube_1, CubeObject& cube_2) {
    // collision x-axis?
    bool collisionX = cube_1.getX() + 0.22f >= cube_2.getX() &&
                      cube_2.getX() + 0.22f >= cube_1.getX();
    // collision y-axis?
    bool collisionY = cube_1.getY() + 0.22f >= cube_2.getY() &&
                      cube_2.getY() + 0.22f >= cube_1.getY();
    // collision only if on both axes
    return collisionX && collisionY;
}

void Scene_007_SpinningCube::spawnApple() {
    if(apples.size() == 0){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-2.5f, 2.5f);

        apples.emplace_back(dist(gen), dist(gen), cubeMesh, Type::AppleCube);
    }
}
