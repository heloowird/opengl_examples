/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include<iostream>
#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager
{
public:
    // Resource storage
    static std::map<std::string, std::shared_ptr<Shader>>    Shaders;
    static std::map<std::string, std::shared_ptr<Texture2D>> Textures;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static std::shared_ptr<Shader>  LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    // Retrieves a stored sader
    static std::shared_ptr<Shader>  GetShader(std::string name);
    // Loads (and generates) a texture from file
    static std::shared_ptr<Texture2D> LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
    // Retrieves a stored texture
    static std::shared_ptr<Texture2D> GetTexture(std::string name);
    // Properly de-allocates all loaded resources
    static void      Clear();
private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // Loads and generates a shader from file
    static void loadShaderFromFile(std::shared_ptr<Shader> shader, const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    // Loads a single texture from file
    static void loadTextureFromFile(std::shared_ptr<Texture2D> texture, const GLchar *file, GLboolean alpha);
};

#endif //OPENGL_EXAMPLE_RESOURCE_MANAGER_H
