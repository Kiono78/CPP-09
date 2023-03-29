#include "../headers/BitcoinExchange.hpp"

void loadDataMap(std::map<std::string, std::string> &data)
{
	std::ifstream file("data.csv");
	if (file.fail())
		throw std::runtime_error("Error opening file");
	else if (file.is_open()) {
		std::string	line;
		std::getline(file, line);
		while (std::getline(file, line))
			data[line.substr(0, line.find(','))] = line.substr(line.find(',') + 1, line.length());
		file.close();
	}
	else
		throw std::runtime_error("Error opening file");
}

std::string	checkDate(std::string date_str) {
	std::stringstream ss(date_str);
    int year, month, day;
	char sep1, sep2;

	ss >> year >> sep1 >> month >> sep2 >> day;

    if (ss.fail() || sep1 != '-' || sep2 != '-')
       throw std::runtime_error("Error: bad input => " + date_str);
	std::tm timeIn;
	memset(&timeIn, 0, sizeof(timeIn));
	timeIn.tm_mday = day;
	timeIn.tm_mon = month - 1;
	timeIn.tm_year = year - 1900;
	std::time_t time = std::mktime(&timeIn);
	std::tm *timeOut = std::localtime(&time);
	if (time == -1)
		throw std::runtime_error("Error: bad input => " + date_str);
	char buffer[11];
    std::strftime(buffer, 11, "%Y-%m-%d", timeOut);
	if (date_str.compare(buffer))
		throw std::runtime_error("Error: bad input => " + date_str);
	return date_str;
}

size_t	countOccurences(std::string str, std::string chars) {
	size_t count = 0;
	for (size_t i = 0; i < str.length(); i++) {
		for (size_t j = 0; j < chars.length(); j++) {
			if (str[i] == chars[j])
				count++;
		}
	}
	return count;
}

std::string	checkValue(std::string value, std::string valuation) {
	if (value.empty() || value.at(0) == '-')
		throw std::runtime_error("Error: not a positive number.");
	else if (size_t decimal_sep = countOccurences(value, ".,")) {
		if (decimal_sep > 1)
			throw std::runtime_error("Error: bad input => " + value);
		if (value.find(',') != std::string::npos)
			value[value.find(',')] = '.';
	}
	//replace 
	std::stringstream	ss_quantity(value);
	std::stringstream	ss_price(valuation);
	std::stringstream	output;
	float				quantity, price;
	ss_quantity >> quantity;
	if (quantity >= 1000)
		throw std::runtime_error("Error: too large a number.");
	ss_price >> price;
	output << quantity;
	output << " = ";
	output << quantity * price;
	return (output.str());
}

void	readInput(char *filename, std::map<std::string, std::string> &data) {
	std::ifstream									file(filename);
	std::map<std::string, std::string>::iterator 	it;
	bool											header_accepted = true;
	struct stat sb;
	if (file.fail())
		throw std::runtime_error("Error: could not open file.");
    else if (stat(filename, &sb) == 0 && S_ISDIR(sb.st_mode))
        throw std::runtime_error("Error: could not open file.");
	else if (file.is_open()) {
		std::string	line;
		std::string	date, value, pipe;
		while (std::getline(file, line)) {
			std::stringstream	ss(line);
			std::stringstream	output;
			std::getline(ss, date, ' ');
			std::getline(ss, pipe, ' ');
			std::getline(ss, value);
			if (header_accepted && date == "date" && value == "value") {
				header_accepted = false;
				continue;
			}
			header_accepted = false;
			if (date.find(" ") !=  std::string::npos || value.find(" ") != std::string::npos) {
				std::cout << "Error: format, leading or trailing spaces" << std::endl;
				continue;
			}
			else {
				for (size_t i = 0; i < value.length(); i++) {
					if (!std::isdigit(value[i]) && value[i] != '.' && value[i] != ',') {
						std::cout << "value in input file must be a number" << std::endl;
						break;
					}
				}
			}
			try {
				output << checkDate(date);
				output << " => ";
				it = data.lower_bound(date);
				if (it != data.begin() && it->first != date)
					--it;
				output << checkValue(value, it->second) << std::endl;
			}
			catch(std::exception& e) {
				output.str("");
				std::cout << e.what() << std::endl;
			}
			std::cout << output.str();
		}
	}
}

int main(int argc, char **argv) {
	std::map<std::string, std::string>	data;
	if (argc != 2) {
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	try {
		loadDataMap(data);
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	try {
		readInput(argv[1], data);
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}