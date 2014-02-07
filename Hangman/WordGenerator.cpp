#include "WordGenerator.h"


WordGenerator::WordGenerator(void)
{
}


WordGenerator::~WordGenerator(void)
{
}

void WordGenerator::init(std::string filename)
{
	m_words.resize(256); //Make it big just to sure

	std::ifstream file(filename);
	if(file.is_open())
	{
		int temp;
		for(int i=0; file.good(); i++)
		{
			std::getline(file, m_words[i]);
			temp = i;
		}
		m_words.resize(temp);
	}
	else
	{
		std::cout << "Could not open wordlist " << filename << std::endl;
	}
	srand(time(NULL));
}


std::string WordGenerator::getWord()
{
	int index = rand() % m_words.size();
	std::cout << index << std::endl;
	return m_words[index];
}