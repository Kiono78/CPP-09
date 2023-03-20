#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <cctype>
# include <cstdlib>
# include <vector>
# include <deque>
# include <climits>
# include <cerrno>
# include <algorithm>
# include <ctime>

template<typename Container>
void	printContainer(const Container & container) {
	typename	Container::const_iterator	it;
	for (it = container.begin(); it != container.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template<typename ptr>
void	insertSort(ptr beginning, ptr end) {
	for (ptr i = beginning; i != end; ++i) {
		for (ptr j = i; j != beginning && (*(j - 1) > *j); --j)
			std::swap(*(j -1), *j);
	}
}

template<typename Container>
void	mergeInsertSort(Container& container, size_t threshold) {
	size_t	size = container.size();
	if (size < threshold) 
		insertSort(container.begin(), container.end());
	else {
		typename	Container::iterator	mid = container.begin() + ((size / 50) + 2);
		Container left(container.begin(), mid);
		Container right(mid, container.end());
		mergeInsertSort(left, threshold);
		mergeInsertSort(right, threshold);
		std::merge(left.begin(), left.end(), right.begin(), right.end(), container.begin());
	}
}

template<typename Container>
bool	isSorted(const Container & container) {
	typename	Container::const_iterator	it = container.begin();
	typename	Container::const_iterator	end = container.end();

	while((it + 1) != end) {
		if (*it > *(it + 1))
			return false;
		++it;
	}
	return true;
}


#endif