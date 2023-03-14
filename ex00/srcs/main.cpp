#include "../headers/BitcoinExchange.hpp"

int main(int argc, char **argv) {
	(void)argv;
	std::ifstream file("data.csv");
	std::map<std::string, std::string>	data;
	if (argc != 2) {
		std::cout << "Input file expected" << std::endl;
		return 1;
	}
	if (file.fail()) {
		std::cout << "Data file loading failed" << std::endl;
		return 1;
	}
	else if (file.is_open()) {
		std::string							line;
		while (std::getline(file, line)) {
			std::stringstream	ss(line);
			data[line.substr(0, line.find(','))] = line.substr(line.find(',') + 1, line.length());
		}
		file.close();
	}
	else
	{
		std::cout << "Unknown error" << std::endl;
		return 1;
	}
	std::map<std::string, std::string>::iterator end = data.end();
	for (std::map<std::string, std::string>::iterator it = data.begin(); it != end; it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}