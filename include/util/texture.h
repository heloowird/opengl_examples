#ifndef OPENGL_EXAMPLE_TEXTURE_H
#define OPENGL_EXAMPLE_TEXTURE_H

#include <iostream>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class Texture {
public:
    // 纹理ID
    unsigned int ID;

    Texture(const char* img_path, GLint img_color_mode) {
        // 创建纹理
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(img_path, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, img_color_mode, width, height, 0, img_color_mode, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void del() {
        glDeleteTextures(1, &ID);
    }
};
#endif //OPENGL_EXAMPLE_TEXTURE_H
