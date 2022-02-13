/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game/sprite_renderer.h"
#include "game/game.h"
#include "game/resource_manager.h"

std::shared_ptr<SpriteRenderer>  Renderer;
std::shared_ptr<GameObject> Player;

Game::Game(GLuint width, GLuint height)
        : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    //delete Renderer;
}

void Game::Init()
{
    // 加载着色器
    ResourceManager::LoadShader("resources/shaders/sprite.vs", "resources/shaders/sprite.fs", nullptr, "sprite");
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
                                      static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Use()->SetInteger("image", 0);
    ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);

    // 加载纹理
    ResourceManager::LoadTexture("resources/textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("resources/textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("resources/textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("resources/textures/paddle.png", GL_TRUE, "paddle");

    // 设置专用于渲染的控制
    Renderer = std::make_shared<SpriteRenderer>(ResourceManager::GetShader("sprite"));

    GameLevel one; one.Load("resources/levels/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two; two.Load("resources/levels/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three; three.Load("resources/levels/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four; four.Load("resources/levels/four.lvl", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    glm::vec2 playerPos = glm::vec2(
            this->Width / 2 - PLAYER_SIZE.x / 2,
            this->Height - PLAYER_SIZE.y
    );
    Player = std::make_shared<GameObject>(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // 移动挡板
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Render()
{
//    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
//                         glm::vec2(200, 200),
//                         glm::vec2(300, 400),
//                         45.0f,
//                         glm::vec3(0.0f, 1.0f, 0.0f));
    if(this->State == GAME_ACTIVE)
    {
        // 绘制背景
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                             glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
        );
        // 绘制关卡
        this->Levels[this->Level].Draw(Renderer);

        // 绘制档板
        Player->Draw(Renderer);
    }
}

