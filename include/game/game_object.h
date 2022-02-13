/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef OPENGL_EXAMPLE_GAME_OBJECT_H
#define OPENGL_EXAMPLE_GAME_OBJECT_H

#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // Object state
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    // Render state
    std::shared_ptr<Texture2D>   Sprite;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture2D> sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // Draw sprite
    virtual void Draw(std::shared_ptr<SpriteRenderer> &renderer);
};

#endif //OPENGL_EXAMPLE_GAME_OBJECT_H
