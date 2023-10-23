#include"Graphics.h"
#include"Grid.h"
#include<chrono>
#include<thread>

using std::cout, std::endl, std::vector, std::array;


//=====================================================================================================================
// Variables and Objects declaration-----------------------------------------------------------------------------------
//=====================================================================================================================

bool left_mouse_button;
bool right_mouse_button;

array<int, 2> windowSize{1000, 600};
float g_xpos, g_ypos;
float wc_x;
float wc_y;

float Scale_x;
float Scale_y;

double previousTime{ 0.0 };
double DeltaT{ 0.0 };
double runtime{ 0.0 };
int timer{ 0 };


struct Colors
{
	glm::vec3 Amber{glm::vec3(1.0f, 0.75f, 0.0f)};
	glm::vec3 White{glm::vec3(1.0f, 1.0f, 1.0f)};
	glm::vec3 Black{glm::vec3(0.0f, 0.0f, 0.0f)};
};



//=====================================================================================================================
// CallBacks ----------------------------------------------------------------------------------------------------------
//=====================================================================================================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void cursor_pos_callBack(GLFWwindow* window, double xpos, double ypos)
{
	g_xpos = xpos;
	g_ypos = ypos;
	wc_x = (2 * (xpos / windowSize[0]) - 1) / Scale_x;
	wc_y = (-2 * (ypos / windowSize[1]) + 1) / Scale_y;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{

	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{

	}
}

void mouse_clicked(GLFWwindow* window, int button, int action, int mod)
{
	// Dropping Particles
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
	{

	}

	left_mouse_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
	right_mouse_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);

	if (right_mouse_button)
	{

	}
}


//=====================================================================================================================
// Main ---------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
int main()
{
	using namespace std::this_thread;
	using namespace std::chrono;

	//=================================================================================================================
	// GLFW initialization --------------------------------------------------------------------------------------------
	//=================================================================================================================
	glfwInit();

	// setting window hints aka OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// setting up the window and error handling
	GLFWwindow* window = glfwCreateWindow(windowSize[0], windowSize[1], "PDBSolver", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "window failed to Initialize";
		return -1;
	}

	// setting the window as OpendGl's current context
	glfwMakeContextCurrent(window);

	//Turning VSync Off! :/
	glfwSwapInterval(0);

	// glad loading error handling
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//=================================================================================================================
	// CallBacks ------------------------------------------------------------------------------------------------------
	//=================================================================================================================
	// updating viewport size if window size is changed CallBack
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callBack);
	glfwSetMouseButtonCallback(window, mouse_clicked);
	glfwSetKeyCallback(window, key_callback);

	//=================================================================================================================
	// Shader Compilation ---------------------------------------------------------------------------------------------
	//=================================================================================================================
	Shader MainShader;

	//=================================================================================================================
	// Graphical Objects Declaration ----------------------------------------------------------------------------------
	//=================================================================================================================
	GraphicalObj rectangle(MainShader, "./Textures/GlowDotFilled.png");
	Colors color;

	bool start_flag{ true };

	//=================================================================================================================
	// Program Loop ---------------------------------------------------------------------------------------------------
	//=================================================================================================================
	int cols = 100;
	int rows = 60;
	
	Grid grid(cols, rows, windowSize[0],windowSize[1]);
	cout << grid.getCells()[0].size();
	cout << grid.getCells().size();
	cout << endl;

	// Visualizing the Grid
	for(vector<cell> vc: grid.getCells())
	{
		for (cell c : vc)
		{
			cout << c.state << " ";
		}
		cout << endl;
	}

	
	cout << endl;
	cout << grid.getCells()[0][0].pos[0] << " " << grid.getCells()[0][0].pos[1] << endl;

	float global_scale = 5.0f;
	float Scale_x = float(1.0f / windowSize[0]) * global_scale;
	float Scale_y = float(1.0f / windowSize[1]) * global_scale;

	while (!glfwWindowShouldClose(window))
	{
		// input
		process_input(window);

		// rendering commands
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Timing
		runtime = glfwGetTime();
		DeltaT = runtime - previousTime;

		//if (DeltaT > 0.05)
		{
			previousTime = runtime;

			// Render
			rectangle.getShader().use();
			for(vector<cell> vc: grid.getCells())
			{
				for (cell c : vc)
				{
					grid.checkNeighbors(&c);
					grid.step += 1;

					if (c.state)
					{
						rectangle.transform(glm::vec3(Scale_x, Scale_y, 0.0f), c.pos);
						rectangle.DrawShape(color.Amber);
					}
					else
					{
						rectangle.transform(glm::vec3(Scale_x, Scale_y, 0.0f), c.pos);
						rectangle.DrawShape(color.Black);
					}
				}
			}
		}

		// Print FPS
		//if (timer > 500)
		//{
		//	//system("CLS");
		//	cout << "FPS: " << 1 / DeltaT << endl;
		//	timer = 0;
		//}
		//++timer;
	}

	// Unbinding and closing all glfw windows and clearing opbjects
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwTerminate();
	return 0;
}