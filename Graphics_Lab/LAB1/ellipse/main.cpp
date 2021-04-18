#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>
#include<math.h>

/// g++  main.cpp -o main -lglfw -lm -lGL -lGLU

void ellipse_(float rx,float ry,std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){
    
    float widthMean = width/2.0;
    float heightMean = height/2.0;

    // x = 0;
    // y = int(round(rx)); 


    float x=0,y=ry;//     x , y = 0 , ry
    float p1,p2;
    float dx,dy;
    
    //for region 1
    p1 = pow(ry,2.0) - pow(rx,2.0) * ry + (1/4)*pow(rx,2.0);
    dx= 2*pow(ry,2)*x;
    dy= 2*pow(rx,2)*y;

    while(dx<dy){
        if(p1<0.0){
            x= x + 1;
            y = y;
            dx = dx + 2 * pow(ry,2.0);
            p1 = p1 + dx + pow(ry,2.0);
            // gfxdraw.pixel(screen_surface, x + xc, y + yc, BLACK)
            // draw_other_points(x, y, xc, yc)
            xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
            yPoints.push_back(y+heightMean);

        }
        else{
            x   = x + 1;
           y= y -1;
            dx = dx + (2*pow(ry,2.0));
            dy = dy - (2*pow(rx,2.0));
            p1 = p1 + dx - dy + pow(ry,2);

            xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
            yPoints.push_back(y+heightMean);
   //         gfxdraw.pixel(screen_surface, x + xc, y + yc, BLACK)
        }
    }
    //for region 2

    p2 = pow(ry,2) * pow(x +0.5,2.0) +pow(rx,2.0) * pow(y-1,2.0) - pow(rx,2) * pow(ry,2);

    while (y>=0){
        if(p2 > 0){

            x = x;
            y =  y-1;
            dy = dy - (2*pow(rx,2.0));
            p2 = p2 + pow(rx,2.0) - dy;
            xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
            yPoints.push_back(y+heightMean);
        }

        else{
            x = x+1;
            y = y-1;
            dx = dx + (2*pow(ry,2.0));
            dy = dy - (2*pow(rx,2.0));
            p2 = p2 + dx -dy + pow(rx,2.0);
            xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
            yPoints.push_back(y+heightMean);

        }
    }

  


    xPoints.push_back(x+widthMean);//our coordinate = top left corner = 0,0
    yPoints.push_back(y+heightMean);
    // xPoints.push_back(x+widthMean);
    // yPoints.push_back(y+heightMean);
    // xPoints.push_back(x);
    // yPoints.push_back(y);


    // print(p);

    
}

void draw_ellipse(int xc,int yc,std::vector<int>& xPoints,std::vector<int>& yPoints,int width,int height){


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
        
        // glVertex2f( y_point+x_c, x_point+y_c);
        // glVertex2f(-y_point+x_c,x_point +y_c);
        // glVertex2f( y_point+x_c,-x_point+y_c);
        // glVertex2f(-y_point+x_c,-x_point+y_c);

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

    float radiusX = 100.0,radiusY= 50.0;
    int x_center=0,y_center = 0;

    std::vector<int> xPoints;
    std::vector<int> yPoints;

    ellipse_(radiusX,radiusY,xPoints,yPoints,m_viewport[2],m_viewport[3]);


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
        draw_ellipse(x_center,y_center,xPoints,yPoints,m_viewport[2],m_viewport[3]);

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
