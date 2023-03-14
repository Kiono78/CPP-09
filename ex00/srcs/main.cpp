#include "../headers/BitcoinExchange.hpp"

int main(int argc, char **argv) {
	(void)argv;
	std::ifstream file("data.csv");
	if (argc != 2) {
		std::cout << "Input file expected" << std::endl;
		return 1;
	}
	if (file.fail()) {
		std::cout << "Data file loading failed" << std::endl;
		return 1;
	}
	else if (file.is_open()) {
		std::map<std::string, std::string>	data;
		std::string							line;
		while (std::getline(file, line)) {
			// std::cout << line << std::endl;
			std::stringstream	ss(line);
			while (ss.good()) {
				std::string field;
				std::getline(ss, field, ',');
				std::cout << line << std::endl;
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Unknown error" << std::endl;
		return 1;
	}
	return 0;
}