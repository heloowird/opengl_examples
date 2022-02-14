#ifndef OPENGL_EXAMPLE_POWERUP_OBJECT_H
#define OPENGL_EXAMPLE_POWERUP_OBJECT_H
#include <glm/glm.hpp>

#include "game_object.h"

const glm::vec2 SIZE(60, 20);
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp : public GameObject
{
public:
    // 道具类型
    std::string Type;
    GLfloat     Duration;
    GLboolean   Activated;
    // 构造函数
    PowerUp(std::string type, glm::vec3 color, GLfloat duration,
            glm::vec2 position, std::shared_ptr<Texture2D> texture)
            : GameObject(position, SIZE, texture, color, VELOCITY),
              Type(type), Duration(duration), Activated()
    { }
};

#endif //OPENGL_EXAMPLE_POWERUP_OBJECT_H
