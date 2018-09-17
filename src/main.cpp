
#define GLFW_INCLUDE_ES2
#include <imgui.h>
#include <imgui/imgui_glfw.h>
#include <GLFW/glfw3.h>

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    std::vector<int> PINS = { 0, 2, 3, 4 };

    if(PINS.size() < 4) {
        printf("You need to define 4 GPIO pin for softPWM.\n");
        return 1;
    }

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "aquaLED", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);
    ImVec4 color = ImColor(255, 255, 255, 255);

    printf ("PWM test\n") ;

    if (wiringPiSetup () == -1) {
        printf("wiringPiSetup failed\n");
        return 1;
    }

    // create soft PWM control
    for(size_t i = 0; i < PINS.size(); i++) {
        int ret = softPwmCreate(PINS[i], 0, 100);
        if(ret != 0) {
            printf("GPIO: %d error : %d\n", PINS[i], ret);
            return 1;
        }   
    }
        	                                            
    /*for(size_t i = 0; i<PINS.size(); i++) {
        pinMode (PINS[i], PWM_OUTPUT);
    }
    */

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui::Begin("aquaLED");

        ImGui::ColorEdit4("LED color", (float*)&color);
        if(ImGui::Button("R+"))  color.x += 1.0f / 100.0f;
        if(ImGui::Button("R-"))  color.x -= 1.0f / 100.0f;
        if(ImGui::Button("G+"))  color.y += 1.0f / 100.0f;
        if(ImGui::Button("G-"))  color.y -= 1.0f / 100.0f;
        if(ImGui::Button("B+"))  color.z += 1.0f / 100.0f;
        if(ImGui::Button("B-"))  color.z -= 1.0f / 100.0f;
        if(ImGui::Button("W+"))  color.w += 1.0f / 100.0f;
        if(ImGui::Button("W-"))  color.w -= 1.0f / 100.0f;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("profile");
        if(ImGui::Button("zero")) {
            color = ImVec4(0, 0, 0, 0);
        }
        if(ImGui::Button("max")) {
            color = ImVec4(255, 255, 255, 255);
        }
        ImGui::End();

	softPwmWrite(PINS[0], color.x);
	softPwmWrite(PINS[1], color.y);
	softPwmWrite(PINS[2], color.z);
	softPwmWrite(PINS[3], color.w);

	/*
        pwmWrite(PINS[0], color.x);
        pwmWrite(PINS[1], color.y);
        pwmWrite(PINS[2], color.z);
        pwmWrite(PINS[3], color.w);
        */

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
