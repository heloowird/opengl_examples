#ifndef OPENGL_EXAMPLE_TEXTURE_H
#define OPENGL_EXAMPLE_TEXTURE_H

#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace deprecated {
    class Texture {
    public:
        // 纹理ID
        unsigned int ID;

        Texture(const char *img_path, GLint img_color_mode = -1) {
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
                GLenum format;
                if (img_color_mode != -1)
                    format = img_color_mode;
                else if (nrChannels == 1)
                    format = GL_RED;
                else if (nrChannels == 3)
                    format = GL_RGB;
                else if (nrChannels == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture: " << img_path << std::endl;
            }
            stbi_image_free(data);
        }

        void del() {
            glDeleteTextures(1, &ID);
        }
    };
}
#endif //OPENGL_EXAMPLE_TEXTURE_H
