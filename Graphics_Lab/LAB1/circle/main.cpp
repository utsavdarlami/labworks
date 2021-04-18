#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include<math.h>

/// g++  main.cpp -o main -lglfw -lm -lGL -lGLU


void circle_(float r,std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){
    
    int x,y;
    float p;
    float fR = round(r);

    float widthMean = width/2.0;
    float heightMean = height/2.0;

    if(fR == r ){
        p  = 1.0 - r;
    }   
    else{
        p = 1.25 - r;
    }

    x = 0;
    y = int(round(r)); 

    xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
    yPoints.push_back(y+heightMean);
    // xPoints.push_back(x+widthMean);
    // yPoints.push_back(y+heightMean);
    // xPoints.push_back(x);
    // yPoints.push_back(y);


    // print(p);

    while(x<y)
    {
        /* code */
        if(p<0.0){
            x = x + 1;
            p = p + 2*x + 1;
        }   
        else{
            x = x + 1;
            y = y - 1; 
            p = p + 2*x - 2*y +1 ;
        }
        // print(p);
        // std::cout<<p<<" "<<" " <<x<<" "<<y<<std::endl;

        xPoints.push_back(x+widthMean);
        yPoints.push_back(y+heightMean);
        
        // xPoints.push_back(x+widthMean);
        // yPoints.push_back(y+heightMean);
    }
    
}

void draw_circle(int xc,int yc,std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){


    float widthMean = width/2.0;
    float heightMean = height/2.0;

    float x_c = xc/ widthMean*1.0;
    float y_c = yc/ heightMean*1.0;


    // glEnable(GL_POINT_SMOOTH); // make the point circular
    // glPointSize(200);

    glBegin(GL_POINTS);


    for (int i = 0; i < xPoints.size(); i++){

        float x_point = (xPoints[i]- widthMean) / widthMean*1.0;
        float y_point = (yPoints[i]-heightMean) / heightMean*1.0;

        // float x_ = (yPoints[i]-widthMean) / widthMean*1.0;
        // float y_ = (xPoints[i]-heightMean) / heightMean*1.0;
                
        glVertex2f(x_point +x_c,y_point +y_c);
        glVertex2f(-x_point+x_c,y_point +y_c);
        glVertex2f(x_point +x_c,-y_point+y_c);
        glVertex2f(-x_point+x_c,-y_point+y_c);
        
        glVertex2f( y_point+x_c, x_point+y_c);
        glVertex2f(-y_point+x_c,x_point +y_c);
        glVertex2f( y_point+x_c,-x_point+y_c);
        glVertex2f(-y_point+x_c,-x_point+y_c);

        // glVertex2f(x_ +x_c, y_+y_c);
        // glVertex2f(-x_+x_c,y_ +y_c);
        // glVertex2f(x_ +x_c,-y_+y_c);
        // glVertex2f(-x_+x_c,-y_+y_c);

        
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
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
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

    float radius = 40.0;
    int x_center=50,y_center = 50;

    std::vector<int> xPoints;
    std::vector<int> yPoints;

    circle_(radius,xPoints,yPoints,m_viewport[2],m_viewport[3]);


    // for (int i = 0; i < xPoints.size(); i++){

    //     std::cout<<xPoints[i]<<" "<< yPoints[i] <<std::endl ;

    // }

    /*GLFW Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        // y-axis
        glBegin(GL_LINES);
            glVertex2f(0.0, 1.0);
            glVertex2f(0.0, -1.0);
        glEnd();
        
        //x-axis
        glBegin(GL_LINES);
            glVertex2f(1.0, 0.0);
            glVertex2f(-1.0, 0.0);
        glEnd();
        // draw_point();
        draw_circle(x_center,y_center,xPoints,yPoints,m_viewport[2],m_viewport[3]);

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
