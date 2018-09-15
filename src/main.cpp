
#define GLFW_INCLUDE_ES2
#include <imgui.h>
#include <imgui/imgui_glfw.h>
#include <GLFW/glfw3.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "aquaLED", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);

    bool show_test_window = true;
    bool show_calibration_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);


   int bright = 0;

    printf ("PWM test\n") ;

    if (wiringPiSetup () == -1)
        return 1;

    pinMode (1, PWM_OUTPUT) ;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui::Begin("aquaLED");
        {
            static float f = 0.0f;
            ImGui::Text("turn on");
            if(ImGui::SliderFloat("float", &f, 0.0f, 1024.0f)) {
               pwmWrite(1, f);
	    }

            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            if (ImGui::Button("Calibration")) show_calibration_window ^= 1;
            if (ImGui::Button("LED test")) show_test_window ^= 1;

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();

        if (show_calibration_window)
        {
            ImGui::SetNextWindowSize(ImVec2(50,50), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Calibration", &show_test_window);
            ImGui::Text("rasberry");
            ImGui::End();
	    
	    /*for (bright = 0 ; bright < 1024 ; ++bright)
	    {
	        pwmWrite (1, bright) ;
	    }

	    for (bright = 1023 ; bright >= 0 ; --bright)
	    {
	        pwmWrite (1, bright) ;
            }*/

        }

        if (show_test_window)
        {
            ImGui::Begin("test");
            ImGui::Button("start");
            ImGui::End();
        }

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
