#pragma once

#include "ObjData.hpp"
#include "PointVector.hpp"
#include <GLFW/glfw3.h>
#include <gl/gl.h>
#include <iostream>

struct Vec2d {
    double x, y;
};

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

        struct RenderState {
            float zoom{ 10.0f };
            Vec2d mouseDragStart{ 0, 0 };
            Vec2d mouseDelta{ 0, 0 };
            bool lButtonPressed{};
            bool mButtonPressed{};
        } state;
        glfwSetWindowUserPointer(window, &state);
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yoffset) {
            auto* state = static_cast<RenderState*>(glfwGetWindowUserPointer(window));
            state->zoom -= static_cast<float>(yoffset);
        });

        glfwSetMouseButtonCallback(window,
            [](GLFWwindow* window, int button, int action, int) {
                double x, y;
                glfwGetCursorPos(window, &x, &y);

                auto* state = static_cast<RenderState*>(glfwGetWindowUserPointer(window));
                if (button == GLFW_MOUSE_BUTTON_LEFT) {
                    if (action == GLFW_PRESS) {
                        state->lButtonPressed = true;
                        state->mouseDragStart = { x, y };

                        std::cout << "Linksklick bei (" << x << ", " << y << ")\n";
                    } else {
                        state->lButtonPressed = false;
                    }
                } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                    std::cout << "Rechtsklick bei (" << x << ", " << y << ")\n";
                }
            });

        glfwSetCursorPosCallback(window,
            [](GLFWwindow* window, double x, double y) {
                auto* state = static_cast<RenderState*>(glfwGetWindowUserPointer(window));
                glfwGetCursorPos(window, &x, &y);

                if (state->lButtonPressed) {
                    state->mouseDelta = { x - state->mouseDragStart.x, y - state->mouseDragStart.y };
                }
            });

        glfwSetKeyCallback(window,
            [](GLFWwindow*, int key, int, int action, int) {
                if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
                    std::cout << "Space pressed\n";
                } else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
                    std::cout << "Space released\n";
                }
            });

        auto& polygon = objData.vertices;
        while (!glfwWindowShouldClose(window)) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(state.mouseDelta.x, -state.mouseDelta.y, width, height);

            // handle Zoom
            const float aspect = static_cast<float>(width) / height;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-state.zoom * aspect, state.zoom * aspect, -state.zoom, state.zoom, -1.0, 1.0);

            // Clear
            glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glLineWidth(1.0f);
            glBegin(GL_LINES);
            // X-Axis
            glColor3f(0.8f, 0.2f, 0.2f);
            glVertex2f(-1.0f * state.zoom * aspect, 0.0f);
            glVertex2f(1.0f * state.zoom * aspect, 0.0f);
            // Y-Axis
            glColor3f(0.2f, 0.8f, 0.2f);
            glVertex2f(0.0f, -1.0f * state.zoom);
            glVertex2f(0.0f, 1.0f * state.zoom);
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
