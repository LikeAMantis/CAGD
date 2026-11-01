#pragma once

#include "ObjData.hpp"
#include "PointVector.hpp"
#include <GLFW/glfw3.h>
#include <gl/gl.h>
#include <iostream>

struct Render {
    static GLFWwindow* createWindow(const char* title) {
        if (!glfwInit()) {
            std::cerr << "GLFW init error\n";
            return nullptr;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // V-Sync
        return window;
    }

    static void run(GLFWwindow* window, ObjData& objData) {
        if (!window) {
            std::cerr << "Render::run GLFWindow missing \n";
            return;
        }

        float zoom = 10.0f;
        glfwSetWindowUserPointer(window, &zoom);

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yoffset) {
            auto* zoom = static_cast<float*>(glfwGetWindowUserPointer(window));
            *zoom -= yoffset;
        });

        auto& polygon = objData.vertices;
        while (!glfwWindowShouldClose(window)) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            // handle Zoom
            const float aspect = static_cast<float>(width) / height;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-zoom * aspect, zoom * aspect, -zoom, zoom, -1.0, 1.0);

            // Clear
            glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glLineWidth(1.0f);
            glBegin(GL_LINES);
            // X-Axis
            glColor3f(0.8f, 0.2f, 0.2f);
            glVertex2f(-1.0f * zoom * aspect, 0.0f);
            glVertex2f(1.0f * zoom * aspect, 0.0f);
            // Y-Axis
            glColor3f(0.2f, 0.8f, 0.2f);
            glVertex2f(0.0f, -1.0f * zoom);
            glVertex2f(0.0f, 1.0f * zoom);
            glEnd();

            // Draw Linestrip
            glLineWidth(2.5f);
            glColor3f(0.3f, 0.7f, 1.0f);
            glBegin(GL_LINE_STRIP);
            for (const auto& p : polygon) {
                glVertex2f(p.x, p.y);
            }
            glEnd();

            // Draw Vertices
            glPointSize(8.0f);
            glColor3f(1.0f, 0.85f, 0.2f);
            glBegin(GL_POINTS);
            for (const auto& p : polygon) {
                glVertex2f(p.x, p.y);
            }
            glEnd();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
};
