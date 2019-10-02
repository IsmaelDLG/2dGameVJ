#ifndef _MYXMLCONVERTER_INCLUDE
#define _MYXMLCONVERTER_INCLUDE

#include <sstream>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

class MyXMLConverter {
public:
	static bool convertToMyLevelFile(const string &inputFile, const string &outputFile);
private:
	//methods
	string getXTilesFromFile(const string inputFile);
	string getYTilesFromFile(const string inputFile);
	string getTileSizeFromFile(const string inputFile);
	string getBlockSizeFromFile(const string inputFile);
	void generateFile(const string inputFile, const string outputFile);
	//variables

};

#endif