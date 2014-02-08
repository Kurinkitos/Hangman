#include "WordGenerator.h"


WordGenerator::WordGenerator(void)
{
}


WordGenerator::~WordGenerator(void)
{
}

void WordGenerator::init(std::string filename)
{
	m_words.resize(200000); //Make it big just to sure

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
	file.close();
}


std::string WordGenerator::getWord()
{
	const int min = 0;
	const int max = m_words.size();
	std::default_random_engine generator;
	generator.seed(time(NULL));
	std::uniform_int_distribution<int> distribution(min,max);
	int random_int = distribution(generator);  // generate random int flat in [min, max]
	//std::cout << m_words[random_int] << std::endl;
	return m_words[random_int];
}