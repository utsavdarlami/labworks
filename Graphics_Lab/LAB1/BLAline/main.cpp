#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include<math.h>

/// g++  main.cpp -o main -lglfw -lm -lGL -lGLU


void BLA_line(int x1,int y1,int x2,int y2,std::vector<int>& xPoints,std::vector<int>& yPoints){
    
    int dx,dy,p;
    float slope;

    dx= x2-x1;
    dy= y2-y1;
    slope = dy/(dx*1.0f);
    

    int x = x1;
    int y = y1;   
    xPoints.push_back(int(x));
    yPoints.push_back(int(y));
    
    if(slope<1.0){
        p = 2*dy - dx;
        do
        {
            x = x + 1 ;
            // /*
            if(p < 0){

                y = y;
                p = p + 2*dy;

            }   
            else{

                p = p + (2*dy) -(2*dx);
                y = y + 1;

            }

            xPoints.push_back(x);
            yPoints.push_back(y);
            /* code */
        } while (x<x2);

    }
    else{
        p = 2*dx - dy;
        do
        {
            y = y + 1 ;
            // /*
            if(p < 0){

                x = x;
                p = p + 2*dx;

            }   
            else{

                x = x + 1;
                p = p + (2*dx) - (2*dy);


            }

            xPoints.push_back(x);
            yPoints.push_back(y);
            /* code */
        } while (y<y2);

    }

}

void draw_BLA(std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){


    float widthMean = width/2.0;
    float heightMean = height/2.0;

    // glEnable(GL_POINT_SMOOTH); // make the point circular
    // glPointSize(1);

    glBegin(GL_POINTS);


    for (int i = 0; i < xPoints.size(); i++){

        float x_point = ( xPoints[i] - widthMean ) / widthMean;
        float y_point = ( heightMean - yPoints[i]) / heightMean;

        glVertex2f(x_point,y_point);
        // std::cout<<x_point<<" "<< y_point <<std::endl ;

    }
    glEnd();
}

int main(void)
{
    GLFWwindow *window;

    /* GLFW Initialize the library */
    if (!glfwInit())
        return -1;


    /*GLFW Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(680, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    //GLFW  OpenGL rendering context
    glfwMakeContextCurrent(window);


    /* Initialize the GLEW library */

    if (glewInit() != GLEW_OK) // GLEW_OK == 0;
    {
        std::cout << "Error.." << std::endl;
    };

    //querying screen resolution from OpenGL API
    GLint m_viewport[4];
        
    glGetIntegerv( GL_VIEWPORT, m_viewport );

//DDA

    std::vector<int> xPoints;
    std::vector<int> yPoints;

    BLA_line(200,100,300,180,xPoints,yPoints);


    // for (int i = 0; i < xPoints.size(); i++){

    //     std::cout<<xPoints[i]<<" "<< yPoints[i] <<std::endl ;

    // }
//End DDA

    /*GLFW Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        
        // draw_point();
        draw_BLA(xPoints,yPoints,m_viewport[2],m_viewport[3]);
        // draw_legacy_triangle();
    
        // Swap front and back buffers   
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
 
        //if q is pressed closed the glfw window by breaking the while loop

        int state = glfwGetKey(window, GLFW_KEY_Q);
        
        if (state == GLFW_PRESS)
        {
            break;
        }
    
    }   

    glfwTerminate();
    return 0;
}
