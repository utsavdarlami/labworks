/*
    #implement 2d transformation for a shape of your choice :
    a) translation 
    b) rotation 
    c) Scaling 
    d) Reflection
    e) Shearing
*/

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include<vector>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define PI 3.14159265

void dot(float product[3][1] , float mat1[3][3] ,float mat2[3][1]){
    float sum = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<1;j++){
            sum= 0;
            for(int k=0;k<3;k++){
                sum += mat1[i][k]*mat2[k][j];
            }
            product[i][j] = sum;
            // std::cout<<sum<<std::endl;
        }        
    }
}

void newCord(float *newPosx,float *newPosy,float *xpoint,float*ypoint,float transform[3][3],int arraySize){
    for(int i=0;i<arraySize;i++){
        float p[3][1] = {{xpoint[i]},{ypoint[i]},{1}};
        float newPos[3][1];
        dot(newPos,transform,p);
        // std::cout<<newPos[0][0]<<std::endl;
        // std::cout<<newPos[0][1]<<std::endl;
        newPosx[i]=newPos[0][0];
        newPosy[i]=newPos[0][1];
    }    
}

void translation(float *newPosx,float *newPosy,float *xpoint,float *ypoint,float tx,float ty,int arraySize){

    // float tx=0.2;
    // float ty=0.2;

    float trans_mat[3][3] = {
        {1,0,tx},
        {0,1,ty},
        {0,0,1}
    };

    newCord(newPosx,newPosy,xpoint,ypoint,trans_mat,3);

    
}

void scaling(float *newPosx,float *newPosy,float *xpoint,float *ypoint,float sx,float sy,int arraySize){
    float scale_mat[3][3] = {
        {sx,0,0},
        {0,sy,0},
        {0,0,1}
    };

    newCord(newPosx,newPosy,xpoint,ypoint,scale_mat,3);

}

void rotation(float *newPosx,float *newPosy,float *xpoint,float *ypoint,float theta,int arraySize){
    
    float rotate_mat[3][3] = {
        {cos((theta*PI)/180),-sin((theta*PI)/180),0},
        {sin((theta*PI)/180),cos((theta*PI)/180),0},
        {0,0,1}
    };

    newCord(newPosx,newPosy,xpoint,ypoint,rotate_mat,3);

}

void shearing(float *newPosx,float *newPosy,float *xpoint,float *ypoint,int axis,float shear,int arraySize){
    
    float shear_mat[3][3] = {
        {1,0,0},
        {shear,1,0},
        {0,0,1}
    };
    
    if(axis==1){ //axis 1 means : shearing in Y axis
        float shear_mat[3][3] = {
            {1,shear,0},
            {0,1,0},
            {0,0,1}
        };
    }

    newCord(newPosx,newPosy,xpoint,ypoint,shear_mat,3);

}

void reflection(float *newPosx,float *newPosy,float *xpoint,float *ypoint,int axis,int arraySize){
    
    float reflection_mat[3][3] = { ///about x axis
            {1,0,0},
            {0,-1,0},
            {0,0,1}
    };

    if(axis==1)
    {
        float reflection_mat[3][3] = {
            {-1,0,0},
            {0,1,0},
            {0,0,1}
        };    
    }
    newCord(newPosx,newPosy,xpoint,ypoint,reflection_mat,3);

}

void draw_triangle(float *xpoint,float *ypoint,int arraySize,int r=255,int g=255, int b=255){
    glColor3ub(r,g,b);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<arraySize;i++){
        glVertex2f(xpoint[i],ypoint[i]);
    }
    glEnd();
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

    glfwMakeContextCurrent( window );
    
    float tri_X[] ={ 0.1,0.2,0.3};
    float tri_Y[]= {-0.3,-0.5,-0.3};
    
    float trans_tri_X[3],trans_tri_Y[3]; 
    translation(trans_tri_X,trans_tri_Y,tri_X,tri_Y,0.2,0.2,3);//tx= 0.2,ty=0.2

    float scaling_tir_X[3],scaling_tir_Y[3];
    scaling(scaling_tir_X,scaling_tir_Y,tri_X,tri_Y,0.2,0.2,3);

    float rotate_tir_X[3],rotate_tir_Y[3];
    rotation(rotate_tir_X,rotate_tir_Y,tri_X,tri_Y,30,3);

    float shear_tri_x[3],shear_tri_y[3];
    shearing(shear_tri_x,shear_tri_y,tri_X,tri_Y,0,0.2,3);

    float reflec_tri_x[3],reflec_tri_y[3];
    reflection(reflec_tri_x,reflec_tri_y,tri_X,tri_Y,1,3);

    // for(int k=0;k<3;k++){
    //     std::cout<<reflec_tri_x[k]<<" | "<<reflec_tri_y[k]<<std::endl;
    // }

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



        draw_triangle(tri_X,tri_Y,3,240,240,240);

        // Green For Translation
        draw_triangle(trans_tri_X,trans_tri_Y,3,13,240,13);

        //Blue for Scaling
        draw_triangle(scaling_tir_X,scaling_tir_Y,3,12,13,240);
        
        //Pink for Rotation 
        draw_triangle(rotate_tir_X,rotate_tir_Y,3,240,0,240);

        // Yellow Is Shearing
        draw_triangle(shear_tri_x,shear_tri_y,3,240,240,0);
        
        //Light Blue is fore reflection 
        draw_triangle(reflec_tri_x,reflec_tri_y,3,100,180,180);


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
