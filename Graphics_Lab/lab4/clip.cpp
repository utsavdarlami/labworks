//Cohen Sutherland Line Clipping Algorithm

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <cmath>
using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int x_max = 80;
const int y_max = 80;
const int x_min = 10;
const int y_min = 10;

//Escape key is used to exit window
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//window changes accordingly when resized
void window_resize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int computeCode(double x, double y)
{
	// initialized as being inside 
	int code = INSIDE;

	if (x < x_min)       // to the left of rectangle
		code |= LEFT;
	else if (x > x_max)  // to the right of rectangle
		code |= RIGHT;
	if (y < y_min)       // below the rectangle
		code |= BOTTOM;
	else if (y > y_max)  // above the rectangle
		code |= TOP;

	return code;
}

void cohenSutherlandClip(double x1, double y1,
	double x2, double y2)
{
	// Compute region codes for P1, P2
	int code1 = computeCode(x1, y1);
	int code2 = computeCode(x2, y2);

	// Initialize line as outside the rectangular window
	bool accept = false;

	while (true)
	{
		if ((code1 == 0) && (code2 == 0))
		{
			// If both endpoints lie within rectangle
			accept = true;
			break;
		}
		else if (code1 & code2)
		{
			// If both endpoints are outside rectangle,
			// in same region
			break;
		}
		else
		{
			// Some segment of line lies within the
			// rectangle
			int code_out;
			double x, y;

			// At least one endpoint is outside the 
			// rectangle, pick it.
			if (code1 != 0)
				code_out = code1;
			else
				code_out = code2;

			// Find intersection point;
			// using formulas y = y1 + slope * (x - x1),
			// x = x1 + (1 / slope) * (y - y1)
			if (code_out & TOP)
			{
				// point is above the clip rectangle
				x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
				y = y_max;
			}
			else if (code_out & BOTTOM)
			{
				// point is below the rectangle
				x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
				y = y_min;
			}
			else if (code_out & RIGHT)
			{
				// point is to the right of rectangle
				y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
				x = x_max;
			}
			else if (code_out & LEFT)
			{
				// point is to the left of rectangle
				y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
				x = x_min;
			}

			// Now intersection point x,y is found
			// We replace point outside rectangle
			// by intersection point
			if (code_out == code1)
			{
				x1 = x;
				y1 = y;
				code1 = computeCode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				code2 = computeCode(x2, y2);
			}
		}
	}
	if (accept)
	{
		cout << "Line accepted from " << x1 << ", "
			<< y1 << " to " << x2 << ", " << y2 << endl;
		// Here the user can add code to display the rectangle
		// along with the accepted (portion of) lines
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f((float)x1 / 100, (float)y1 / 100);
		glVertex2f((float)x2 / 100, (float)y2 / 100);

		////Drawing Clipping window
		//Vertical min line
		glVertex2f((float)x_min / 100, (float)y_min / 100);
		glVertex2f((float)x_min / 100, (float)y_max / 100);
		//Horizantal min line
		glVertex2f((float)x_min / 100, (float)y_min / 100);
		glVertex2f((float)x_max / 100, (float)y_min / 100);
		//Horizantal max line
		glVertex2f((float)x_min / 100, (float)y_max / 100);
		glVertex2f((float)x_max / 100, (float)y_max / 100);
		//Vertical min line
		glVertex2f((float)x_max / 100, (float)y_min / 100);
		glVertex2f((float)x_max / 100, (float)y_max / 100);
		//glEnd();
		glEnd();
	}
	else
		cout << "Line rejected" << endl;
}





int main() {

	int x_min, y_min, x_max, y_max;
	//Initialize window
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(width, height, "New Window", NULL, NULL);

	if (!window) {
		std::cout << "Failed to initialize window";
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, window_resize);
	glewInit();

	/*cout << "Enter xmin , ymin : ";
	cin >> x_min >> y_min;

	cout << "Enter xmax , ymax : ";
	cin >> x_max >> y_max;*/
	


	//main loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		cohenSutherlandClip(5,7,90 ,95 );

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
