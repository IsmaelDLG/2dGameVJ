#include "MyXMLConverter.h"

	bool MyXMLConverter::convertToMyLevelFile(const string &inputFile, const string &outputFile)
	{
		ifstream ifs;
		stringstream strStream;
		string line;
		size_t pos;
		bool found = false;

		ifs.open(inputFile);
		if (!ifs.is_open()) return false;
		do {
			getline(ifs, line);
			pos = line.find("height");
			if (pos != string::npos) {
				found = true;
				mapHeight = 
			}
		} while (!found);
		pos = line.find("width");

		
		strStream.str(line)



	}

	string MyXMLConverter::getXTilesFromFile(const string inputFile)
	{
		return string();
	}

	string MyXMLConverter::getYTilesFromFile(const string inputFile)
	{
		return string();
	}

	string MyXMLConverter::getTileSizeFromFile(const string inputFile)
	{
		return string();
	}

	string MyXMLConverter::getBlockSizeFromFile(const string inputFile)
	{
		return string();
	}

	void MyXMLConverter::generateFile(const string inputFile, const string outputFile)
	{
	}
