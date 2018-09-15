#include <imgui.h>
#include <imgui/imgui_glfw.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

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

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui::Begin("aquaLED");
        {
            static float f = 0.0f;
            ImGui::Text("turn on");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
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
