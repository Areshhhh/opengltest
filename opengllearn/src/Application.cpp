#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "TestClearColor.h"
#include "TestCube.h"

#include <iostream>



int main()
{
    GLFWwindow* window;
    if (!glfwInit()) return -1;                //initilize the libary
                                               //core version 3.3.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "bad project name", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;


    //  headless scope for window termination  //
    {
        GLCall(glEnable(GL_BLEND));            //enable blend
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        ImGui::CreateContext();                //initialize imgui
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();


        Renderer renderer;                     //renderer class

        test::TestClearColor clearcolortest;   //test class
        test::TestCube cubetest;





        while (!glfwWindowShouldClose(window)) //rendering loop
        {
            renderer.Clear();

            clearcolortest.onUpdate(0.0f);     //clear color rendering
            clearcolortest.onOpenglRender();

            static int cubepositions[2] = { 0, 0 };
            cubetest.updatePositons(cubepositions[0] + 900, cubepositions[1] + 500);
            cubetest.onUpdate(0.0f);
            cubetest.onOpenglRender();         //cube rendering



            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();         //imgui new frame
            ImGui::NewFrame();

            ImGui::SliderInt2("cubepositions", cubepositions, -300, 300);

            clearcolortest.onImguiRender();
            ImGui::Render();                   //imgui render
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            


            GLCall(glfwSwapBuffers(window));   //swap front and back buffers
            GLCall(glfwPollEvents());          //poll for and process events
        }
    }





    ImGui_ImplOpenGL3_Shutdown();              //imgui shutdown
    ImGui_ImplGlfw_Shutdown();                 //
    ImGui::DestroyContext();                   //

    glfwDestroyWindow(window);                 //glfw  shutdown
    glfwTerminate();                           //
    return 0;                                  //
}