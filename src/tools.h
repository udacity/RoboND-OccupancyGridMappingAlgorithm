/*
 * tools.h
 *
 *  Created on: Apr 18, 2019
 *      Author: mody
 */

/** @file tools.h
 *  @ingroup Tool
 *  @brief Tools class
 */

/**
 *  @addtogroup Tool
 *  @{
 */

#ifndef TOOLS_H_
#define TOOLS_H_
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

class MeasurementData_S
{
	public:
	double timeStamp;
    double measurementData[8];
    double robotX, robotY, robotTheta;
};

class Tools 
{
	public:
	/**
	* Constructor.
	*/
	Tools();
	
	/**
	* Destructor.
	*/
	virtual ~Tools();

	//CalculateRMSE Calculates the root mean square error
	void check_files(std::ifstream& in_file, std::string& in_name);

	//CalculateRMSE Calculates the root mean square error
	void readMeasurements(const std::string &measurementName, const std::string &posesName, 
                                 std::vector<MeasurementData_S> &outputData);
	
};

#endif /* TOOLS_H_ */
/**
 *  @}
 */
