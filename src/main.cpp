#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>
#include "tools.h"
#include <matplot/matplot.h>


// Sensor characteristic: Min and Max ranges of the beams
double Zmax = 5000, Zmin = 170;

// Defining free cells(lfree), occupied cells(locc), unknown cells(l0) log odds values
double l0 = 0, locc = 0.4, lfree = -0.4;

// Grid dimensions
double gridWidth = 100, gridHeight = 100;

// Map dimensions
double mapWidth = 30000, mapHeight = 15000;

// Robot size with respect to the map 
double robotXOffset = mapWidth / 5, robotYOffset = mapHeight / 3;

// Defining an l vector to store the log odds values of each cell
std::vector< std::vector<double> > l(mapWidth/gridWidth, std::vector<double>(mapHeight/gridHeight));

double inverseSensorModel(double x, double y, double theta, double xi, double yi, double sensorData[])
{
    // Defining Sensor Characteristics
    double Zk, thetaK, sensorTheta;
    double minDelta = -1;
    double alpha = 200, beta = 20;

    //******************Compute r and phi**********************//
    double r (sqrt(pow(xi - x, 2) + pow(yi - y, 2)));
    double phi (atan2(yi - y, xi - x) - theta);

    //Scaling Measurement to [-90 -37.5 -22.5 -7.5 7.5 22.5 37.5 90]
    for (int i = 0; i < 8; i++) 
    {
        if (i == 0) 
        {
            sensorTheta = -90 * (M_PI / 180);
        }
        else if (i == 1) 
        {
            sensorTheta = -37.5 * (M_PI / 180);
        }
        else if (i == 6) 
        {
            sensorTheta = 37.5 * (M_PI / 180);
        }
        else if (i == 7) 
        {
            sensorTheta = 90 * (M_PI / 180);
        }
        else 
        {
            sensorTheta = (-37.5 + (i - 1) * 15) * (M_PI / 180);
        }

        if (fabs(phi - sensorTheta) < minDelta || minDelta == -1) 
        {
            Zk = sensorData[i];
            thetaK = sensorTheta;
            minDelta = fabs(phi - sensorTheta);
        }
    }

    //******************Evaluate the three cases**********************//
    if(r > std::min(static_cast<double>(Zmax),Zk + alpha/2) || fabs(phi - thetaK) > beta/2 || Zk > Zmax || Zk < Zmin)
    {
        return l0;
    }
    else if(Zk <Zmax && fabs(r - Zk)< alpha/2)
    {
        return locc;
    }
    else if (r <= Zk)
    {
        return lfree;
    }
}

void occupancyGridMapping(double Robotx, double Roboty, double Robottheta, double sensorData[])
{
    //1 - TODO: Generate a grid (size 300x150) and then loop through all the cells
    for (int x = 0; x < (mapWidth/gridWidth); x++)
    {
        for (int y = 0; y < (mapHeight/gridHeight); y++)
        {
            //2- TODO: Compute the center of mass of each cell xi and yi 
            double xi (x * gridWidth + gridWidth / 2 - robotXOffset);
            double yi ( -(y * gridHeight + gridHeight / 2) + robotYOffset);

            //3- TODO: Check if each cell falls under the perceptual field of the measurements
            if( sqrt(pow(xi - Robotx,2) + pow(yi - Roboty, 2)) <= Zmax )
            {
                l[x][y] = l[x][y] + inverseSensorModel(Robotx, Roboty, Robottheta, xi, yi, sensorData);
            }
        }
    }    
}

void visualization()
{
    //Figure cfg
    std::string title("Map");
    auto h = matplot::figure(true);
    h->title(title);
    matplot::axis({0, (mapWidth / gridWidth), 0, (mapHeight / gridHeight) });

    // Draw every grid of the map:
    for (double x = 0; x < mapWidth / gridWidth; x++) 
    {
        matplot::hold(matplot::on);
        for (double y = 0; y < mapHeight / gridHeight; y++) 
        {
            //Green unkown state
            if (l[x][y] == 0) 
            { 
                matplot::plot({ x }, { y }, "g.");
            }
            //Black occupied state
            else if (l[x][y] > 0) 
            { 
                matplot::plot({ x }, { y }, "k.");
            }
            //Red free state
            else 
            { 
                matplot::plot({ x }, { y }, "r.");
            }
        }
    }

    matplot::grid(matplot::on);
    matplot::hold(matplot::off);

    //Save the image and close the plot
    matplot:: save("../Images/Map.jpg");
}

int main()
{
    Tools tools; 

    const std::string poses("../Data/poses.txt");
    const std::string measurements("../Data/measurement.txt");
    std::vector<MeasurementData_S> outputData;

    tools.readMeasurements(measurements, poses, outputData);
    const int size(outputData.size());

    for(int i=0; i< size; i++)
    {
        double robotX(outputData[i].robotX);
        double robotY(outputData[i].robotY);
        double robotTheta((outputData[i].robotTheta)/10 *(M_PI / 180));
        occupancyGridMapping(robotX, robotY, robotTheta, outputData[i].measurementData);
    }
    
    // Visualize the map at the final step
    std::cout << "Wait for the image to generate" << std::endl;
    visualization();
    std::cout << "Done!" << std::endl;

    return 0;
}

