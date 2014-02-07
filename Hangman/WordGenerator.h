#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>
class WordGenerator
{
public:
	WordGenerator(void);
	~WordGenerator(void);

	void init(std::string);

	std::string getWord();
private:
	std::vector<std::string> m_words;
};

