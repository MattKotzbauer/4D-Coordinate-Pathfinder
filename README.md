Video URL: https://www.youtube.com/watch?v=9MhAILPIRpk

I think this is my best attempt yet of the Coordinate Pathfinder in the Mathematical Fourth Dimension. This is a pure C++ file that can be run on any standard C++ compiler. To run this program, go to Visual Studio Code or CS50’s visual studio code. Run the following command into the terminal: “code 4DPathfinder.cpp”. This should create a C++ file named ‘4DPathfinder.cpp’ in your Explorer. Click on the file and copy / paste the code from the main file. Next, run the following terminal command: “make 4DPathfinder.cpp”. Finally, run “./4DPathfinder” in the terminal to run the project. 


If this method of running the project does not work for you, you can alternatively use any online C++ compiler to run the program, which you can find by googling “Online C++ Compiler” (and copying / pasting in the code). Note that this method may cause the program to run a bit slower due to the limited speed of these platforms. 


Once you’ve successfully run the program, the terminal will display prompts for the following inputs: grid size, starting point, ending point, and blocked points. Entering in the size of the grid will, as the title implies, create an n-by-n-by-n-by-n 4D grid. Next, entering in the four coordinates of the starting point will initialize an (x, y, z, a) point as your starting point. Note that, as we are working with array values, they cannot be negative, cannot go beyond the grid size, and start from index 0. Next, entering in the coordinates of your ending point will similarly initialize an (x, y, z, a) point as your ending point. 


Next, you will be prompted to enter the amount of ‘blocked points’ that the path will not be allowed to cross. Note that the pathfinder moves adjacently, so for example, a point surrounded on all 8 sides by blocked points cannot be reached. The program will run regardless of whether or not the ending point can be reached: if it can be reached, the program will output the path of coordinates, and if it cannot, the program will output that the target point cannot be reached.


Note that the program will take a relatively long time to compute large grid sizes and faraway points: as we’re working in 4 dimensions, the runtime of the program is O(N^4).
