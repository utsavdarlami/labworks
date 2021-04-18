#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include<vector>

/// g++  main.cpp -o main -lglfw -lm -lGL -lGLU

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void get_resolution()
{
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int window_width=0,window_height=0;

    window_width = mode->width;
    
    window_height = mode->height;

    std::cout<<"width = "<<window_width<<std::endl;
    std::cout<<"height = "<<window_height<<std::endl;
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_TRIANGLE_FAN);
	
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void DrawStar(float cx, float cy, float radius, int numPoints)
{

	const float DegToRad = 3.14159 / 180;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	int count = 1;
	for (int i = 0; i <= 360; i += 360/ (numPoints * 2)) {
		float DegInRad = i * 360.0 / (numPoints*2) * DegToRad;
		if (count % 2 == 0)
			glVertex2d(cx + cos(DegInRad) * radius, cy + sin(DegInRad) * radius);
		else
			glVertex2d((cx + cos(DegInRad) * radius / 2), (cy + sin(DegInRad) * radius / 2));
		count++;
	}
	glEnd();
}


void draw_outer_polygon(){

    glColor3ub(24,12,233);

    glBegin(GL_POLYGON);
    
    glVertex2f( -0.1, 0.8);
    glVertex2f(  0.7, 0.0);
    glVertex2f(  0.2, 0.0);
    glVertex2f( 0.7, -0.8);
    glVertex2f(-0.1, -0.8);

    glEnd();

}

void draw_inner_polygon(){

    glColor3ub(240,12,23);

    glBegin(GL_POLYGON);
    
    glVertex2f(-0.05, 0.7);//top 
    glVertex2f( 0.6, 0.05);//right cor
    glVertex2f( 0.125 , 0.05);//middle
    glVertex2f( 0.6, -0.75);//bottom left cor
    glVertex2f(-0.05, -0.75);//botttom right cor
    // glVertex2i()
    glEnd();

}


int main(void)
{
    GLFWwindow *window;

    /* GLFW Initialize the library */
    if (!glfwInit())
        return -1;


    /*GLFW Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello", NULL, NULL);
    if (!window)
    {
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

    // std::cout << "glewInit =" << glewInit() << "  GLEW_OK =" << GLEW_OK << std::endl;

    // std::cout << glGetString(GL_VERSION) << std::endl;


    //getting resolution of my primary monitor
    std::cout<<" Getting resolution of my primary monitor "<<std::endl;
    get_resolution();

    //querying screen resolution from OpenGL API
    
    /*
    GLint m_viewport[4];
    
    std::cout<<"Querying screen/window resolution from OpenGL API"<<std::endl;
    
    glGetIntegerv( GL_VIEWPORT, m_viewport );

    std::cout <<" Width of Screen : "<<m_viewport[2] << std::endl;
    std::cout <<" Height of Screen : "<< m_viewport[3] << std::endl;
*/
    
    glfwMakeContextCurrent( window );
    
    // drawing polygon;
   

    /*GLFW Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        
        // draw_legacy_triangle();
        
        draw_outer_polygon();
        draw_inner_polygon();
        
        // draw_legacy_polygon();
        glColor3ub(255,255,255);

		    DrawCircle(0.16f, 0.2f, 0.07f, 10000);

        glColor3ub(240,12,23);
		
        DrawCircle(0.16f, 0.235f, 0.07f, 10000);
        DrawStar(0.16, 0.182f, 0.05, 20);
		
        DrawStar(0.16, -0.35, 0.10, 20);

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
