#include "../headers/PmergeMe.hpp"

void check_input(int argc,char **argv, std::vector<unsigned int>	&vector) {
	unsigned long	 nb;
	for (int i = 1; i < argc; i++) {
		for (int k = 0; argv[i][k]; k++) {
			if (!std::isdigit(argv[i][k])) {
				throw std::runtime_error("");
			}
		}
		nb = std::strtoul(argv[i], NULL, 10);
		if (errno == ERANGE && nb == ULLONG_MAX) 
			throw std::runtime_error("");
		else if (nb > UINT_MAX)
			throw std::runtime_error("");
		vector.push_back(static_cast<unsigned int>(nb));
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	unsigned int				nb_arguments = argc - 1;
	std::vector<unsigned int>	vector;
	try {
		check_input(argc, argv, vector);
	}
	catch(std::exception& e) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	std::deque<unsigned int>	deque(vector.begin(), vector.end());
	std::cout << "Before: ";
	//Dear corrector, feel free to change the below line to printContainer(deque);
	printContainer(vector);
	clock_t	start_vector = clock();
	mergeInsertSort(vector, 5);
	clock_t	end_vector = clock();
	clock_t	start_deque = clock();
	mergeInsertSort(deque, 5);
	clock_t	end_deque = clock();
	if (!isSorted(vector) || !isSorted(deque)) {
		std::cout << "Sorting failed" << std::endl;
		return 1;
	}
	double elapsed_time_vector = (double)(end_vector - start_vector) / (double)CLOCKS_PER_SEC * 1000000.0;
	double elapsed_time_deque = (double)(end_deque - start_deque) / (double)CLOCKS_PER_SEC * 1000000.0;
	std::cout << "After: ";
	//Dear corrector, feel free to change the below line to printContainer(deque);
	printContainer(vector);	
	std::cout << "Time to process a range of " << nb_arguments << " elements with std::vector : " << elapsed_time_vector << " us" << std::endl;
	std::cout << "Time to process a range of " << nb_arguments << " elements with std::deque : " << elapsed_time_deque << " us" << std::endl;
	return 0;
}

