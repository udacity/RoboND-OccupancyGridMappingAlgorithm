[![Udacity - Robotics NanoDegree Program](https://s3-us-west-1.amazonaws.com/udacity-robotics/Extra+Images/RoboND_flag.png)](https://www.udacity.com/robotics)

# RoboND-OccupancyGridMappingAlgorithm
You will visualize the mapped environment through the generated image

### Instruction:
Code the visualization function which will plot the state of each grid cell using the matplotlib python library
``` C++
void visualization()
{
    //Initialize a plot named Map of size 300x150
    
    //Loop over the log odds values of the cells and plot each cell state. 
    //Unkown state: green color, occupied state: black color, and free state: red color 
    
    //Save the image and close the plot 
}
```

### Compiling:
```sh
$ git clone https://github.com/udacity/RoboND-OccupancyGridMappingAlgorithm
$ cd RoboND-OccupancyGridMappingAlgorithm/
$ rm Images/*
$ g++ main.cpp -o app -std=c++11 -I/usr/include/python2.7 -lpython2.7
```
### Running:
```sh
$ ./app
```

Now, wait for the program to generate the map!

### Generated Map:

![alt text](Images/Map.png)

