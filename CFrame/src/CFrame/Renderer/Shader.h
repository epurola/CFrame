#pragma once

#include <glad/glad.h>

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 


namespace CFrame {

    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader
    {
    private:
        std::string filePath;
        unsigned int RendererId;
        /*cashing for uniforms*/
        std::unordered_map<std::string, int> uniformLocationCache;

    public:
        Shader(const std::string filePath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        /*Set uniforms*/
        void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
        void SetUniform2f(const std::string name, float v0, float v1);
        void SetUniform1f(const std::string name, float v0);
        void SetUniform1i(const std::string& name, int value);
        void SetUniformMat4f(const std::string& name, const glm::mat4 proj);

    private:
        unsigned int CompileShader(unsigned int type, const std::string& source);
        int GetuniformLocation(const std::string& name);
        unsigned int CreateShaderProgram(const std::string& vertexShaderSource,
            const std::string& fragmentShaderSource);

        ShaderProgramSource parseShaders(const std::string shaderPath);
    };
}