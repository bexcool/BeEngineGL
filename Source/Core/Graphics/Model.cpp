//
// Created by Petr Pavlík on 29.09.2025.
//

#include "Model.h"

#include "ShaderProgram.h"

Model::Model(vector<float> *vertices)
{
    _vertices = vertices;

    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices->data()), _vertices->data(), GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));

    _vertexShader = new Shader(GL_VERTEX_SHADER, "../Source/Resources/Shaders/default.vert");
    _vertexShader->Compile();

    _fragmentShader = new Shader(GL_FRAGMENT_SHADER, "../Source/Resources/Shaders/default.frag");
    _fragmentShader->Compile();

    _shaderProgram = new ShaderProgram(_vertexShader, _fragmentShader);
    _shaderProgram->LinkShaders();
}

Model::Model(Shader *fragmentShader, Shader *vertexShader, vector<float> *vertices)
{
    _vertices = vertices;

    //vertex buffer object (VBO)
    glGenBuffers(1, &_VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (_vertices), _vertices, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &_VAO); //generate the VAO
    glBindVertexArray(_VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *) (3 * sizeof(float)));

    _vertexShader = vertexShader;
    _vertexShader->Compile();

    _fragmentShader = fragmentShader;
    _fragmentShader->Compile();

    _shaderProgram = new ShaderProgram(_vertexShader, _fragmentShader);
    _shaderProgram->LinkShaders();
}

void Model::Draw() const
{
    _shaderProgram->Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(_vertices->data()));
}
