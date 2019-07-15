#include "GLWidget.h"

GLuint VBO, VAO;
const char *vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n\0";
const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

GLWidget::GLWidget(QWidget* parent,Qt::WindowFlags f)
    :QOpenGLWidget(parent, f)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    unsigned int vertexShader = core->glCreateShader(GL_VERTEX_SHADER);
    core->glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    core->glCompileShader(vertexShader);


    int success;
    char infoLog[512];
    core->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        core->glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    unsigned int fragmentShader = core->glCreateShader(GL_FRAGMENT_SHADER);

    core->glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    core->glCompileShader(fragmentShader);

    core->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        core->glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    shaderProgram = core->glCreateProgram();
    core->glAttachShader(shaderProgram, vertexShader);
    core->glAttachShader(shaderProgram, fragmentShader);
    core->glLinkProgram(shaderProgram);

    core->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        core->glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    core->glDeleteShader(vertexShader);
    core->glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
    };

    core->glGenVertexArrays(1, &VAO);
    core->glGenBuffers(1, &VBO);
    core->glBindVertexArray(VAO);
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<void*>(0));
    core->glEnableVertexAttribArray(0);

    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
    core->glBindVertexArray(0);
}

void GLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    core->glClearColor(0.2f,0.3f,0.3f,1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT);

    core->glUseProgram(shaderProgram);
    core->glBindVertexArray(VAO);
    core->glDrawArrays(GL_TRIANGLES, 0, 3);
    core->glUseProgram(0);
}
