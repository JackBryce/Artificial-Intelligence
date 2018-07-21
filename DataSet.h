#pragma once

class DataSet {
	public:
		string id;
		vector<double> memoryMatrixOutput;
		vector<double> memoryMatrixInputS;		    //For Text and Audio.
		vector<vector<double>> memoryMatrixInputL;  //For Images and Videos due to RGB.
};