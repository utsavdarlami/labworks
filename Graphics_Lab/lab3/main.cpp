#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include<vector>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600


std::vector<float> WindowtoViewport(int x_w, int y_w, int x_wmax, 
                      int y_wmax, int x_wmin, int y_wmin, 
                      int x_vmax, int y_vmax, int x_vmin, 
                      int y_vmin) 
{ 
    // point on viewport 
    float x_v, y_v; 
  
    // scaling factors for x coordinate and y coordinate 
    float sx, sy; 
  
    // calculatng Sx and Sy 
    sx = (float)(x_vmax - x_vmin) / (x_wmax - x_wmin); 
    sy = (float)(y_vmax - y_vmin) / (y_wmax - y_wmin); 
  
    // calculating the point on viewport 
    x_v = x_vmin + (float)((x_w - x_wmin) * sx); 
    y_v = y_vmin + (float)((y_w - y_wmin) * sy); 

    std::vector<float> points = {x_v,y_v};
    return points;
} 


void draw_line_view(std::vector<int>& xPoints,std::vector<int>& yPoints,
                    int width,int height,int xwMin,int ywMin,int xwMax,int ywMax)
{


    float widthMean = width/2.0;
    float heightMean = height/2.0;

    // glEnable(GL_POINT_SMOOTH); // make the point circular
    // glPointSize(1);


    glBegin(GL_LINES);
    for (int i = 0; i < xPoints.size(); i++){
        std::vector<float> viewPoints;
        viewPoints = WindowtoViewport(xPoints[i],yPoints[i],xwMax,ywMax,xwMin,ywMin,width,height,0,0);
        float x_point = ( viewPoints[0] - widthMean ) / widthMean;
        float y_point = ( heightMean - viewPoints[1]) / heightMean;

        glVertex2f(x_point,y_point);
        // std::cout<<x_point<<" "<< y_point <<std::endl ;
    }
    glEnd();
}
  

int main(){

    GLFWwindow *window;
    if(!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Viewport",NULL,NULL);
    
    if(!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    //GLFW  OpenGL rendering context
    glfwMakeContextCurrent(window);

    glfwSwapInterval(2);

    /* Initialize the GLEW library */

    if (glewInit() != GLEW_OK) // GLEW_OK == 0;
    {
        std::cout << "Error.." << std::endl;
    };

    glfwMakeContextCurrent( window );
    int x1,y1,x2,y2;
    int xwMin,xwMax,ywMin,ywMax;

    std::cout<<"Enter World X Min cordinate : " ;
    std::cin >> xwMin;   
    
    std::cout<<"Enter World Y Min cordinate  : " ;
    std::cin >> ywMin;   

    std::cout<<"Enter World X Max cordinate  : " ;
    std::cin >> xwMax;   

    std::cout<<"Enter World Y Max cordinate  : " ;
    std::cin >> ywMax;   

    std::cout<<"Enter World X1 cordinate of the line : " ;
    std::cin>> x1;   
    
    std::cout<<"Enter World Y1 cordinate of the line : " ;
    std::cin >> y1;   

    std::cout<<"Enter World X2 cordinate of the line : " ;
    std::cin >> x2;   

    std::cout<<"Enter World Y2 cordinate of the line : " ;
    std::cin >> y2;   

	std::vector<int> xpoints = {x1,x2};
	std::vector<int> ypoints = {y1,y2};

    std::vector<float> view_xpoints1 = WindowtoViewport(x1,y1,xwMax,ywMax,xwMin,ywMin,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
    std::vector<float> view_xpoints2 = WindowtoViewport(x2,y2,xwMax,ywMax,xwMin,ywMin,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);

    std::cout<<"The view coordinates of " << x1<<" And " << y1<< " is :" <<view_xpoints1[0]<<" , " << view_xpoints1[1]<<std::endl;

    std::cout<<"The view coordinates of " << x2 <<" And "<< y2 << " zis :" <<view_xpoints2[0]<< " , " <<view_xpoints2[1]<<std::endl;

    /*GLFW Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        //x-axis
        glBegin(GL_LINES);
            glVertex2f(1.0,0.0);
            glVertex2f(-1.0,0.0);
        glEnd();

        //y-axis
        glBegin(GL_LINES);
            glVertex2f(0.0,1.0);
            glVertex2f(0.0,-1.0);
        glEnd();

        draw_line_view(xpoints,ypoints,SCREEN_WIDTH,SCREEN_HEIGHT,xwMin,ywMin,xwMax,ywMax);
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

