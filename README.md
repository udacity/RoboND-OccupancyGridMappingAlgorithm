[![Udacity - Robotics NanoDegree Program](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](https://www.udacity.com/robotics)

# RoboND-OccupancyGridMappingAlgorithm
You will visualize the mapped environment through the generated image

### Instruction
Code the visualization function which will plot the state of each grid cell using the matplotlib python library
``` C++
void visualization()
{
    //TODO: Initialize a plot named Map of size 300x150
    
    //TODO: Loop over the log odds values of the cells and plot each cell state. 
    //Unkown state: green color, occupied state: black color, and free state: red color 
    
    //TODO: Save the image and close the plot 
}
```
Here are some helpful commands you can use to generate plots with the `matplotlib` library:
* *Set Title*: `plt::title("Your Title");`
* *Set Limits*: `plt::xlim(x-axis lower limit, x-axis upper limit );`
* *Plot Data*:`plt::plot({ x-value }, { y-value }, "Color and Shape");`
* *Save Plot*: `plt::save("File name and directory")`;
* *Close Plot*:   `plt::clf()`;

Check out this [link](https://github.com/lava/matplotlib-cpp) for more information on the `matplotlib` C++ library. For information regarding the plot color and shape refer to the LineSpec and LineColor section of the [MATLAB](https://www.mathworks.com/help/matlab/ref/plot.html?requestedDomain=true) documentation. 

### Compiling
```sh
$ cd /home/workspace/
$ git clone https://github.com/udacity/RoboND-OccupancyGridMappingAlgorithm
$ cd RoboND-OccupancyGridMappingAlgorithm/
$ rm -rf Images/* #Delete the folder content and not the folder itself!
$ g++ main.cpp -o app -std=c++11 -I/usr/include/python2.7 -lpython2.7
```

### Running
```sh
$ ./app
```

Now, wait for the program to generate the map!

### Generated Map

![alt text](Images/Map.png)

