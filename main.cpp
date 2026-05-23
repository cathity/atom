#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

//ZMIENNE GLOBALNE
Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
float lastX = 1280.0f / 2.0;
float lastY = 720.0f / 2.0;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
const float PI = 3.14159265359f;

//STRUKTURY I GENEROWANIE GEOMETRII 
struct MeshData { std::vector<float> vertices; std::vector<unsigned int> indices; };

MeshData generateSphere(float radius, int sectors, int stacks) {
    MeshData data;
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = PI / 2 - i * (PI / stacks);
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);
        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * (2 * PI / sectors);
            
            data.vertices.push_back(xy * cosf(sectorAngle));
            data.vertices.push_back(xy * sinf(sectorAngle));
            data.vertices.push_back(z);
            
            data.vertices.push_back(cosf(sectorAngle) * cosf(stackAngle));
            data.vertices.push_back(sinf(sectorAngle) * cosf(stackAngle));
            data.vertices.push_back(sinf(stackAngle));
           
            data.vertices.push_back((float)j / sectors);
            data.vertices.push_back((float)i / stacks);
        }
    }
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1); int k2 = k1 + sectors + 1;
        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) { data.indices.push_back(k1); data.indices.push_back(k2); data.indices.push_back(k1 + 1); }
            if (i != (stacks - 1)) { data.indices.push_back(k1 + 1); data.indices.push_back(k2); data.indices.push_back(k2 + 1); }
        }
    }
    return data;
}

std::vector<float> generateCube() {
    return {
        // Tylna ściana
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        // Przednia ściana
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        // Lewa ściana
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        // Prawa ściana
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         // Dolna ściana
         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         // Górna ściana
         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
}

std::vector<float> generateOrbit(float radius, int segments) {
    std::vector<float> vertices;
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        vertices.push_back(radius * cosf(angle));
        vertices.push_back(0.0f);
        vertices.push_back(radius * sinf(angle));
    }
    return vertices;
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos; lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime);
}

//FUNKCJA GŁÓWNA
int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Model Atomu - Kompletny Projekt", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("vertex_shader.vs", "fragment_shader.fs");

    //BUFORY SFERY 
    MeshData sphere = generateSphere(1.0f, 36, 18);
    unsigned int sphereVAO, sphereVBO, sphereEBO;
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphere.vertices.size() * sizeof(float), sphere.vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere.indices.size() * sizeof(unsigned int), sphere.indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    std::vector<float> cube = generateCube();
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(float), cube.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    std::vector<float> orbit = generateOrbit(1.0f, 100);
    unsigned int orbitVAO, orbitVBO;
    glGenVertexArrays(1, &orbitVAO);
    glGenBuffers(1, &orbitVBO);
    glBindVertexArray(orbitVAO);
    glBindBuffer(GL_ARRAY_BUFFER, orbitVBO);
    glBufferData(GL_ARRAY_BUFFER, orbit.size() * sizeof(float), orbit.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::vec3 lightPos(0.0f, 0.0f, 0.0f); 

    // Tablica stałych przesunięć dla 12 cząstek jądra 
    glm::vec3 nucleusPositions[] = {
        glm::vec3(0.00f,  0.00f,  0.00f), glm::vec3(0.25f,  0.10f, -0.10f),
        glm::vec3(-0.20f,  0.20f,  0.15f), glm::vec3(0.15f, -0.25f,  0.20f),
        glm::vec3(-0.15f, -0.15f, -0.20f), glm::vec3(0.30f, -0.10f,  0.10f),
        glm::vec3(-0.25f,  0.05f, -0.25f), glm::vec3(0.10f,  0.30f, -0.15f),
        glm::vec3(0.05f, -0.30f, -0.10f), glm::vec3(-0.30f, -0.20f,  0.05f),
        glm::vec3(0.20f,  0.25f,  0.25f), glm::vec3(-0.10f,  0.15f, -0.30f)
    };

    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.02f, 0.02f, 0.05f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        //SZEŚCIAN 
        glBindVertexArray(cubeVAO);
        glm::mat4 modelCube = glm::mat4(1.0f);
        modelCube = glm::translate(modelCube, glm::vec3(0.0f, -6.0f, 0.0f)); 
        modelCube = glm::scale(modelCube, glm::vec3(20.0f, 0.2f, 20.0f)); 
        lightingShader.setMat4("model", modelCube);
        lightingShader.setVec3("objectColor", glm::vec3(0.3f, 0.3f, 0.3f)); 
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //  SFERY (Jądro atomu - 12 kulek)
        glBindVertexArray(sphereVAO);
        for (int i = 0; i < 12; i++) {
            glm::mat4 modelNucleus = glm::mat4(1.0f);
            modelNucleus = glm::rotate(modelNucleus, currentFrame * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
            modelNucleus = glm::translate(modelNucleus, nucleusPositions[i]);
            modelNucleus = glm::scale(modelNucleus, glm::vec3(0.25f)); 

            lightingShader.setMat4("model", modelNucleus);

            if (i % 2 == 0)
                lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.2f, 0.2f)); // Proton 
            else
                lightingShader.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.6f)); // Neutron 

            glDrawElements(GL_TRIANGLES, (unsigned int)sphere.indices.size(), GL_UNSIGNED_INT, 0);
        }

        //  ORBITY I ELEKTRONY
        for (int i = 0; i < 3; i++) {
            float orbitRadius = 2.5f + i * 1.2f; 

            
            glm::mat4 baseOrbitModel = glm::mat4(1.0f);
            baseOrbitModel = glm::rotate(baseOrbitModel, glm::radians(i * 60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            baseOrbitModel = glm::rotate(baseOrbitModel, glm::radians(i * 45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            
            glBindVertexArray(orbitVAO);
            glm::mat4 modelOrbitLine = baseOrbitModel;
            modelOrbitLine = glm::scale(modelOrbitLine, glm::vec3(orbitRadius));
            lightingShader.setMat4("model", modelOrbitLine);
            lightingShader.setVec3("objectColor", glm::vec3(0.4f, 0.4f, 0.4f)); 
            glDrawArrays(GL_LINE_LOOP, 0, 100);

            // Rysowanie 2 elektronów 
            glBindVertexArray(sphereVAO);
            float speed = 2.0f + i * 0.5f;

            for (int e = 0; e < 2; e++) {
                glm::mat4 modelElectron = baseOrbitModel;
                float phaseShift = e * PI; 

                modelElectron = glm::rotate(modelElectron, currentFrame * speed + phaseShift, glm::vec3(0.0f, 1.0f, 0.0f));
                modelElectron = glm::translate(modelElectron, glm::vec3(orbitRadius, 0.0f, 0.0f));
                modelElectron = glm::scale(modelElectron, glm::vec3(0.12f));

                lightingShader.setMat4("model", modelElectron);
                lightingShader.setVec3("objectColor", glm::vec3(0.0f, 0.8f, 1.0f)); 
                glDrawElements(GL_TRIANGLES, (unsigned int)sphere.indices.size(), GL_UNSIGNED_INT, 0);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // CZYSZCZENIE PAMIĘCI
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &sphereVBO);
    glDeleteBuffers(1, &sphereEBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &orbitVAO);
    glDeleteBuffers(1, &orbitVBO);

    glfwTerminate();
    return 0;
}
