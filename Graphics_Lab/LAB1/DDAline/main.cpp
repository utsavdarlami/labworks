#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include<math.h>

/// g++  main.cpp -o main -lglfw -lm -lGL -lGLU

void DDA_line(int x1,int y1,int x2,int y2,std::vector<int>& xPoints,std::vector<int>& yPoints){
    
    // std::cout<<x1<<y1<<x2<<y2<<std::endl;
    int dx,dy;
    float stepsize;

    dx= x2-x1;
    dy= y2-y1;

    if(abs(dx)>abs(dy)){
        stepsize = dx;
    }
    else{
        stepsize = dy;
    }

    float x = x1;
    float y = y1;

    xPoints.push_back(int(x));
    yPoints.push_back(int(y));

    float xinc = dx/stepsize;
    float yinc = dy/stepsize;


    // std::cout<<xinc<<" "<<yinc<<"   "<<inc<<std::endl;

    for(int i=1;i<=stepsize;i++){
    
        x = x + xinc;
        y = y + yinc;
        
        xPoints.push_back(int(round(x)));
        yPoints.push_back(int(round(y)));

    }

}


void draw_DDA(std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){


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
    window = glfwCreateWindow(680, 480, "Hello", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    //GLFW  OpenGL rendering context
    glfwMakeContextCurrent(window);

    // glfwSwapInterval(2);

    /* Initialize the GLEW library */

    if (glewInit() != GLEW_OK) // GLEW_OK == 0;
    {
        std::cout << "Error.." << std::endl;
    };



    //querying screen resolution from OpenGL API
    GLint m_viewport[4];
    
    glGetIntegerv( GL_VIEWPORT, m_viewport );

//    std::cout <<" Width of Screen : "<<m_viewport[2] << std::endl;
  //  std::cout <<" Height of Screen : "<< m_viewport[3] << std::endl;


//DDA

    std::vector<int> xPoints;
    std::vector<int> yPoints;

    DDA_line(200,200,180,300,xPoints,yPoints);

//End DDA

    /*GLFW Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        
        // draw_point();
        draw_DDA(xPoints,yPoints,m_viewport[2],m_viewport[3]);
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
