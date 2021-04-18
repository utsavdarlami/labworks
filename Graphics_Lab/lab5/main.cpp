/*
    #implement 3d transformation for a shape of your choice :
    a) translation 
    b) rotation 
    c) Scaling 
*/

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include<vector>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define PI 3.14159265

void dot(float product[4][1] , float mat1[4][4] ,float mat2[4][1]){
    float sum = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<1;j++){
            sum= 0;
            for(int k=0;k<4;k++){
                sum += mat1[i][k]*mat2[k][j];
            }
            product[i][j] = sum;
            // std::cout<<sum<<std::endl;
        }        
    }
}

void newCord(float *newPosx,float *newPosy,float *newPosz,
            float *xpoint,float*ypoint,float *zpoint,
            float transform[4][4])
{
    for(int i=0;i<5;i++){
        float p[4][1] = {{xpoint[i]},{ypoint[i]},{zpoint[i]},{1}};
        float newPos[4][1];
        dot(newPos,transform,p);
        // std::cout<<newPos[0][0]<<std::endl;
        // std::cout<<newPos[0][1]<<std::endl;
        newPosx[i]=newPos[0][0];
        newPosy[i]=newPos[0][1];
        newPosz[i]=newPos[0][2];
    }    
}

void translation(float *newPosx,float *newPosy,float *newPosz,
                float *xpoint,float *ypoint,float *zpoint,
                float tx,float ty,float tz)
{
    float trans_mat[4][4] = {
        {1,0,0,tx},
        {0,1,0,ty},
        {0,0,1,tz},
        {0,0,0,1}
    };

    newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,trans_mat);
    
}

void scaling(float *newPosx,float *newPosy,float *newPosz,
            float *xpoint,float *ypoint,float *zpoint,
            float sx,float sy,float sz){
    float scale_mat[4][4] = {
        {sx,0,0,0},
        {0,sy,0,0},
        {0,0,sz,0},
        {0,0,0,1}
    };

    newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,scale_mat);

}

void rotation(float *newPosx,float *newPosy,float *newPosz,
            float *xpoint,float *ypoint,float *zpoint,
            float theta,int axis=0)
{
    //x-axis rotation
    float rotate_mat_x[4][4] = {
        {1,0,0,0},
        {0,cos((theta*PI)/180),-sin((theta*PI)/180),0},
        {0,sin((theta*PI)/180),cos((theta*PI)/180),0},
        {0,0,0,1}
    };

    //y-axis rotation
    float rotate_mat_y[4][4] = {

        {cos((theta*PI)/180),0,sin((theta*PI)/180),0},
        {0,1,0,0},
        {-sin((theta*PI)/180),0,cos((theta*PI)/180),0},
        {0,0,0,1}

    };
    //z-axis rotation
    float rotate_mat_z[4][4] = {

        {cos((theta*PI)/180),-sin((theta*PI)/180),0,0},
        {sin((theta*PI)/180),cos((theta*PI)/180),0,0},
        {0,0,1,0},
        {0,0,0,1}

    };
    switch (axis)
    {
    case 0 /* constant-expression */:
        newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,rotate_mat_x);
        break;
    case 1:
        newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,rotate_mat_y);
        break;
    case 2:
        newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,rotate_mat_z);
        break;
    default:
        newCord(newPosx,newPosy,newPosz,xpoint,ypoint,zpoint,rotate_mat_x);
        break;
    }

}


void draw_3d_triangle(float *xpoint,float *ypoint,float *zpoint,int r=255,int g=255, int b=255)
{
    glEnable(GL_POLYGON_OFFSET_LINE);

    glPolygonOffset(-1,-1);
    // draw the wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw the same polygons again
    // should be in the back.
    glPushMatrix();

    // glNormal3f(1.0f, 0.f, 0.0f);
    // glTranslatef(0.2f, 0.0f, 0.0f);
    glRotatef(20.0, 1.0, 1.0, 0.0);
    
    glColor3ub(r,g,b);

    glBegin(GL_TRIANGLES);
        // Front Face
        // glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(xpoint[0],ypoint[0],zpoint[0]);//v0        
        glVertex3f(xpoint[1],ypoint[1],zpoint[1]);//v1
        glVertex3f(xpoint[2],ypoint[2],zpoint[2]); //v2

        // Right Face
        glVertex3f(xpoint[0],ypoint[0],zpoint[0]);// ///v0        
        glVertex3f(xpoint[2],ypoint[2],zpoint[2]); //v2
        glVertex3f(xpoint[3],ypoint[3],zpoint[3]); //v3

        // Left Face
        glVertex3f(xpoint[0],ypoint[0],zpoint[0]);//  ///v0        
        glVertex3f(xpoint[1],ypoint[1],zpoint[1]);//v1
        glVertex3f(xpoint[4],ypoint[4],zpoint[4]); //v2
        // Back Face
        glVertex3f(xpoint[0],ypoint[0],zpoint[0]);//  ///v0        
        glVertex3f(xpoint[3],ypoint[3],zpoint[3]); //v3
        glVertex3f(xpoint[4],ypoint[4],zpoint[4]); //v4

    glEnd();
    glPopMatrix();

}

int main(){
    GLFWwindow *window;
    if(!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Transformation",NULL,NULL);
    
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

    
    float tri_X[] = {0.0,-0.3, 0.3, 0.3,-0.3};
    float tri_Y[] = {0.4,-0.3,-0.3,-0.3,-0.3};
    float tri_Z[] = {0.0, 0.5, 0.5,-0.5,-0.5};
    
    float trans_tri_X[5],trans_tri_Y[5],trans_tri_Z[5]; 
    translation(trans_tri_X,trans_tri_Y,trans_tri_Z,tri_X,tri_Y,tri_Z,0.2,0.2,0.2);//tx= 0.2,ty=0.2

    float scaling_tir_X[5],scaling_tir_Y[5],scaling_tir_Z[5];
    scaling(scaling_tir_X,scaling_tir_Y,scaling_tir_Z,tri_X,tri_Y,tri_Z,0.2,0.2,0.2);

    float rotate_tir_X[5],rotate_tir_Y[5],rotate_tir_Z[5];
    rotation(rotate_tir_X,rotate_tir_Y,rotate_tir_Z,tri_X,tri_Y,tri_Z,60,2);

    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // draw_3d_triangle();
        // triangularPrism();
        draw_3d_triangle(tri_X,tri_Y,tri_Z,255,100,0);
        // Green For Translation
        draw_3d_triangle(trans_tri_X,trans_tri_Y,trans_tri_Z,13,240,13);

        // Blue for Scaling
        draw_3d_triangle(scaling_tir_X,scaling_tir_Y,scaling_tir_Z,12,13,240);
        
        //Pink for Rotation 
        draw_3d_triangle(rotate_tir_X,rotate_tir_Y,rotate_tir_Z,240,0,240);

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
