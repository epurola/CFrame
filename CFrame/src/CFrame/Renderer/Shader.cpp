#include "Shader.h"
#include "../Log.h"
namespace CFrame
{
    Shader::Shader(const std::string filePath)
        : filePath(filePath), RendererId(0)
    {
        ShaderProgramSource source = parseShaders(filePath);
        RendererId = CreateShaderProgram(source.VertexSource, source.FragmentSource);
        GLint textureLocation = glGetUniformLocation(RendererId, "u_Texture");
    }

    Shader::~Shader()
    {
        glDeleteProgram(RendererId);
    }

    void Shader::Bind() const
    {
        glUseProgram(RendererId);
    }

    void Shader::UnBind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetuniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::SetUniform2f(const std::string name, float v0, float v1)
    {
        glUniform2f(GetuniformLocation(name), v0, v1);
    }

    void Shader::SetUniform1f(const std::string name, float v0)
    {
        glUniform1f(GetuniformLocation(name), v0);
    }

    void Shader::SetUniform1i(const std::string& name, int value)
    {
        glUniform1i(GetuniformLocation(name), value);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 proj)
    {
        glUniformMatrix4fv(GetuniformLocation(name), 1, GL_FALSE, &proj[0][0]);
    }

    unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource,
        const std::string& fragmentShaderSource)
    {
        unsigned int programObject = glCreateProgram();

        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, fragmentShader);
        glLinkProgram(programObject);
        // validate program
        glValidateProgram(programObject);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return programObject;
    }

    ShaderProgramSource Shader::parseShaders(const std::string shaderPath)
    {
        std::ifstream stream(filePath);

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };
        ShaderType type = ShaderType::NONE;
        std::string line;
        std::stringstream ss[2];

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }
        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        GLuint shaderObject;

        if (type == GL_VERTEX_SHADER)
        {
            shaderObject = glCreateShader(GL_VERTEX_SHADER);
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        }

        const char* src = source.c_str();
        glShaderSource(shaderObject,
            1,
            &src,
            nullptr);
        glCompileShader(shaderObject);

        GLint success;
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderObject, 512, nullptr, infoLog);
            std::cerr << "Shader Compilation Error:\n"
                << infoLog << std::endl;
        }
        return shaderObject;
    }

    int Shader::GetuniformLocation(const std::string& name)
    {
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
        {
            return uniformLocationCache[name];
        }
        int location = glGetUniformLocation(RendererId, name.c_str());
        if (location == -1)
        {
            std::cout << "Uniform does not exist!" << std::endl;
        }
        else
        {
            uniformLocationCache[name] = location;
        }
        return location;
    }
}