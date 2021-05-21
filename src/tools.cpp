/*
 * tools.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: mody
 */

/** @file tools.cpp
 *  @ingroup Tool
 *  @brief Tools class
 */

/**
 *  @addtogroup Tool
 *  @{
 */

#include <iostream>
#include <random>
#include "tools.h"

/**
 * @brief kfApp The constructor for Tools.
 *
 */
Tools::Tools() {}

/**
 * @brief Tools The destructor for Tools.
 *
 */
Tools::~Tools() {}

/**
 * @brief check_files check if file is exist and it can be opened.
 *
 * @param[in] in_file Handle object to file for(read/write) operations {ifstream}.
 * 
 * @param[in] in_name file name {string}.
 *
 */
void Tools::check_files (std::ifstream& in_file, std::string& in_name)
{
    if (!in_file.is_open())
    {
        std::cerr << "Cannot open input file: " << in_name << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief readData Read the data from .txt file and parse all data to class member.
 *
 * @param[in] argc which is number of passed arguments {int}.
 * 
 * @param[in] argv which contains the external arguments {char*}.
 *
 */
void Tools::readMeasurements(const std::string &measurementName, const std::string &posesName, 
                             std::vector<MeasurementData_S> &outputData)
{
    /*******************************************************************************
     *  Parse input file                                                         *
     *******************************************************************************/

    std::string in_measurement_name_ = measurementName;
    std::ifstream in_measurement_(in_measurement_name_.c_str(), std::ifstream::in);
    check_files(in_measurement_, in_measurement_name_);

    std::string in_poses_name_ = posesName;
    std::ifstream in_poses_(in_poses_name_.c_str(), std::ifstream::in);
    check_files(in_poses_, in_poses_name_);

    /**********************************************
     *  Set Measurements & poses             *
     **********************************************/
    // prep the measurement packages (each line represents a measurement at a timestamp)
    std::string poseLine;
    std::string measurementLine;

    while (getline(in_poses_, poseLine) && getline(in_measurement_, measurementLine))
    {
    struct MeasurementData_S data;

    MeasurementData_S meas_package;
    std::istringstream ipp(poseLine);
    std::istringstream imm(measurementLine);

    // read poses file
    ipp >> meas_package.timeStamp;
    ipp >> meas_package.robotX;
    ipp >> meas_package.robotY;
    ipp >> meas_package.robotTheta;

    imm >> meas_package.measurementData[0];

    // read measurement file
    for(int i=0; i< 8; i++)
    {
        imm >> meas_package.measurementData[i];
    }

    //append the package
    outputData.push_back(meas_package);

    }

    if (in_poses_.is_open())
    {
        in_poses_.close();
    }

    if (in_measurement_.is_open())
    {
        in_measurement_.close();
    }
}

/**
 *  @}
 */
