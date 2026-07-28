// #define GLFW_INCLUDE_NONE
// #include <GLFW/glfw3.h>
// #include <glad/glad.h>
// #include <iostream>
// #include <windows.h>
// #include <vector>

// // ============================================
// // 配置
// // ============================================
// const int WINDOW_WIDTH = 800;
// const int WINDOW_HEIGHT = 600;
// const int MAP_COLS = 10;
// const int MAP_ROWS = 8;

// // 玩家世界坐标（地图上的位置）
// float playerX = 0.0f;
// float playerY = 0.0f;
// const float MOVE_SPEED = 1.5f;

// bool keyW = false, keyA = false, keyS = false, keyD = false;

// // ============================================
// // 着色器源码（玩家 + 网格共用，支持偏移）
// // ============================================
// const char* vertexShaderSource = R"(
// #version 330 core
// layout (location = 0) in vec2 aPos;
// layout (location = 1) in vec3 aColor;

// out vec3 Color;

// uniform vec2 offset;      // 摄像机偏移
// uniform float scale;

// void main() {
//     vec2 pos = (aPos + offset) * scale;
//     gl_Position = vec4(pos, 0.0, 1.0);
//     Color = aColor;
// }
// )";

// const char* fragmentShaderSource = R"(
// #version 330 core
// in vec3 Color;
// out vec4 FragColor;

// void main() {
//     FragColor = vec4(Color, 1.0);
// }
// )";

// // ============================================
// // 顶点数据
// // ============================================
// // 玩家三角形（蓝色）
// float triangleVertices[] = {
//     0.0f, -0.5f,     0.0f, 0.4f, 1.0f,
//     -0.5f,  0.5f,    0.0f, 0.4f, 1.0f,
//      0.5f,  0.5f,    0.0f, 0.4f, 1.0f,
// };

// // ============================================
// // 键盘回调
// // ============================================
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if (action == GLFW_PRESS) {
//         if (key == GLFW_KEY_W) keyW = true;
//         if (key == GLFW_KEY_A) keyA = true;
//         if (key == GLFW_KEY_S) keyS = true;
//         if (key == GLFW_KEY_D) keyD = true;
//     }
//     if (action == GLFW_RELEASE) {
//         if (key == GLFW_KEY_W) keyW = false;
//         if (key == GLFW_KEY_A) keyA = false;
//         if (key == GLFW_KEY_S) keyS = false;
//         if (key == GLFW_KEY_D) keyD = false;
//     }
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//         glfwSetWindowShouldClose(window, true);
//     }
// }

// // ============================================
// // 着色器工具
// // ============================================
// unsigned int compileShader(const char* source, int type) {
//     unsigned int shader = glCreateShader(type);
//     glShaderSource(shader, 1, &source, nullptr);
//     glCompileShader(shader);

//     int success;
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetShaderInfoLog(shader, 512, nullptr, infoLog);
//         std::cerr << "❌ 着色器编译失败: " << infoLog << std::endl;
//     }
//     return shader;
// }

// unsigned int createShaderProgram() {
//     unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
//     unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

//     unsigned int program = glCreateProgram();
//     glAttachShader(program, vertexShader);
//     glAttachShader(program, fragmentShader);
//     glLinkProgram(program);

//     int success;
//     glGetProgramiv(program, GL_LINK_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetProgramInfoLog(program, 512, nullptr, infoLog);
//         std::cerr << "❌ 着色器链接失败: " << infoLog << std::endl;
//     }

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
//     return program;
// }

// // ============================================
// // 创建 VAO
// // ============================================
// unsigned int createTriangleVAO() {
//     unsigned int VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     return VAO;
// }

// // ============================================
// // 创建网格线 VAO（只有位置）
// // ============================================
// unsigned int createGridVAO() {
//     std::vector<float> vertices;

//     float mapWidth = 1.8f;
//     float mapHeight = 1.8f;
//     float startX = -mapWidth / 2.0f;
//     float startY = -mapHeight / 2.0f;
//     float stepX = mapWidth / MAP_COLS;
//     float stepY = mapHeight / MAP_ROWS;

//     // 竖线
//     for (int i = 0; i <= MAP_COLS; i++) {
//         float x = startX + i * stepX;
//         vertices.push_back(x);
//         vertices.push_back(startY);
//         vertices.push_back(x);
//         vertices.push_back(startY + mapHeight);
//     }

//     // 横线
//     for (int i = 0; i <= MAP_ROWS; i++) {
//         float y = startY + i * stepY;
//         vertices.push_back(startX);
//         vertices.push_back(y);
//         vertices.push_back(startX + mapWidth);
//         vertices.push_back(y);
//     }

//     unsigned int VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     return VAO;
// }

// // ============================================
// // 主函数
// // ============================================
// int main() {
//     SetConsoleOutputCP(CP_UTF8);

//     if (!glfwInit()) {
//         std::cerr << "❌ GLFW 初始化失败！" << std::endl;
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RPG_Game - 摄像机跟随", NULL, NULL);
//     if (!window) {
//         std::cerr << "❌ 窗口创建失败！" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);
//     glfwSetKeyCallback(window, key_callback);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "❌ GLAD 初始化失败！" << std::endl;
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     std::cout << "✅ GLFW + OpenGL 初始化成功！" << std::endl;
//     std::cout << "   WASD 移动玩家 | ESC 退出" << std::endl;
//     std::cout << "   玩家居中，网格跟随移动" << std::endl;

//     unsigned int shaderProgram = createShaderProgram();
//     int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
//     int scaleLoc = glGetUniformLocation(shaderProgram, "scale");

//     unsigned int triangleVAO = createTriangleVAO();
//     unsigned int gridVAO = createGridVAO();

//     // 网格颜色（直接在顶点颜色中设置）
//     // 但网格 VAO 没有颜色属性，所以需要额外处理
//     // 我们用一个单独的 uniform 来控制网格颜色
//     // 但为了简单，我们在绘制网格时用 glLineWidth + 单独的颜色 uniform
//     // 由于着色器里用了 aColor，网格 VAO 没有颜色，会出问题
//     // 所以网格使用另一个着色器（只含位置 + uniform 颜色）

//     // 简化的方式：网格使用单独的着色器
//     const char* gridVertex = R"(
// #version 330 core
// layout (location = 0) in vec2 aPos;
// uniform vec2 offset;
// uniform float scale;
// void main() {
//     vec2 pos = (aPos + offset) * scale;
//     gl_Position = vec4(pos, 0.0, 1.0);
// }
// )";
//     const char* gridFragment = R"(
// #version 330 core
// uniform vec3 color;
// out vec4 FragColor;
// void main() {
//     FragColor = vec4(color, 1.0);
// }
// )";

//     unsigned int gridShader = glCreateProgram();
//     unsigned int gv = compileShader(gridVertex, GL_VERTEX_SHADER);
//     unsigned int gf = compileShader(gridFragment, GL_FRAGMENT_SHADER);
//     glAttachShader(gridShader, gv);
//     glAttachShader(gridShader, gf);
//     glLinkProgram(gridShader);
//     glDeleteShader(gv);
//     glDeleteShader(gf);

//     int gridOffsetLoc = glGetUniformLocation(gridShader, "offset");
//     int gridScaleLoc = glGetUniformLocation(gridShader, "scale");
//     int gridColorLoc = glGetUniformLocation(gridShader, "color");

//     float gridColor[3] = {0.6f, 0.6f, 0.6f};
//     float playerScale = 0.12f;
//     float gridScale = 1.0f;

//     // 摄像机偏移 = -玩家位置（玩家居中）
//     float cameraOffsetX = 0.0f;
//     float cameraOffsetY = 0.0f;

//     double lastTime = glfwGetTime();
//     float deltaTime = 0.0f;

//     while (!glfwWindowShouldClose(window)) {
//         double currentTime = glfwGetTime();
//         deltaTime = (float)(currentTime - lastTime);
//         lastTime = currentTime;

//         float moveAmount = MOVE_SPEED * deltaTime;

//         // 更新玩家世界坐标
//         if (keyW) playerY += moveAmount;
//         if (keyS) playerY -= moveAmount;
//         if (keyA) playerX -= moveAmount;
//         if (keyD) playerX += moveAmount;

//         // 边界限制（防止跑出地图）
//         float limit = 0.9f;
//         if (playerX < -limit) playerX = -limit;
//         if (playerX > limit) playerX = limit;
//         if (playerY < -limit) playerY = -limit;
//         if (playerY > limit) playerY = limit;

//         // 摄像机偏移 = -玩家位置（玩家居中）
//         cameraOffsetX = -playerX;
//         cameraOffsetY = -playerY;

//         glClearColor(0.15f, 0.15f, 0.2f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // ---- 绘制网格（带摄像机偏移） ----
//         glUseProgram(gridShader);
//         glUniform2f(gridOffsetLoc, cameraOffsetX, cameraOffsetY);
//         glUniform1f(gridScaleLoc, gridScale);
//         glUniform3fv(gridColorLoc, 1, gridColor);
//         glBindVertexArray(gridVAO);
//         glDrawArrays(GL_LINES, 0, (MAP_COLS + 1) * 2 + (MAP_ROWS + 1) * 2);

//         // ---- 绘制玩家（居中，无偏移） ----
//         glUseProgram(shaderProgram);
//         glUniform2f(offsetLoc, 0.0f, 0.0f);  // 玩家在屏幕中心
//         glUniform1f(scaleLoc, playerScale);
//         glBindVertexArray(triangleVAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     std::cout << "✅ 程序正常退出" << std::endl;
//     return 0;
// }

#include "core/ConfigManager.hpp"
#include "monster/Monster.hpp"
#include "utils/Logger.hpp"
#include <iostream>
#include <windows.h>

void testMonster(Logger& logger, ConfigManager& config, const std::string& alias) {
    auto data = config.getByAlias(alias);
    if (data.has_value()) {
        Monster monster;
        monster.loadFromJson(data.value());

        logger.Info("👹 " + monster.getName());
        logger.Info("   HP: " + std::to_string(monster.getStats().hp) + 
                    " | 攻击: " + std::to_string(monster.getStats().attack) +
                    " | 防御: " + std::to_string(monster.getStats().defense) +
                    " | 经验: " + std::to_string(monster.getStats().expReward));
        logger.Info("   种族: " + monster.getRace() + " | 等级: " + std::to_string(monster.getLevel()));
        logger.Info("   技能: " + (monster.getSkills().empty() ? "无" : monster.getSkills()[0]));
        logger.Info("");
    } else {
        logger.Warning("⚠️ 找不到怪物: " + alias);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Logger logger(LogLevel::Info);

    auto& config = ConfigManager::getInstance();
    config.initialize("../config/");

    logger.Info("📋 加载所有怪物...");
    logger.Info("");

    // 测试所有已有的怪物
    testMonster(logger, config, "slime");
    testMonster(logger, config, "goblin_warrior");
    testMonster(logger, config, "skeleton");

    logger.Info("📊 总配置文件数: " + std::to_string(config.getFileCount()));
    logger.Info("✅ 测试完成！");

    std::cout << "\n按 Enter 退出...";
    std::cin.get();
    return 0;
}