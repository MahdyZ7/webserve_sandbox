#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/stat.h>

static bool isdate(std::string str)
{
	int		year,  month, day;
	size_t	dash = 0;
	size_t	i = 0;

	while (true)
	{
		if(!std::isdigit(str[i]))
			return false;
		for(int num_len = 0; str[i]; ++i, ++num_len)
		{
			if (num_len > 4)
				return false;
			if (!std::isdigit(str[i]))
				break;
		}
		if (!str[i] && dash == 2)
			break;
		if (str[i] == '-' && dash < 2)
		{
			++dash;
			++i;
			continue;
		}
		return false;
	}
	return true;
}

static bool isvaliddate(std::string str)
{
	std::string			word;
	int					date[3]; 
	std::stringstream	ss(str);

	for(int i = 0; i < 3; ++i)
	{
		std::getline(ss, word, '-');
		std::stringstream s_temp(word);
		s_temp >> date[i];
		if (date[i] <= 0)
			return false;
	}
	if (date[1] > 12 || date[2] > 31)
		return false;
	if (date[1] >= 8)
		++date[1];
	if (date[1] % 2 == 0 && date[2] > 30)
		return false;
	if (date[1] != 2)
		return true;
	if (date[0] % 400 == 0 || (date[0] % 100 != 0  && date[0] % 4 == 0))
		--date[2];
	if (date[1] == 2 && date[2] > 28)
		return false;
	return true;
}

int main()
{
	std::string x="";

	while (x != "x"){
		std::cin >> x;
		try
		{
			if (x == "c")
				throw(std::invalid_argument("LALALA"));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return 0;
		}
		
		if (isdate(x))
			std::cout << "THIS IS A DATE\n";
		else
			std::cout << "NOT A DATE\n";
		if (isvaliddate(x))
			std::cout << "THIS IS VALID\n";
		else
			std::cout << "NOT VAlID\n";
	}
}