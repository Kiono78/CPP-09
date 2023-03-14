#include "../headers/RPN.hpp"

int compute_element(char ope, int first, int second) {
	switch (ope) {
		case '+': return first + second;
		case '-': return first - second;
		case '*': return first * second;
		case '/': return first / second;
		default: throw std::invalid_argument("Error parsing operator");
	}
}

int parse_expression(char *arguments) {
	std::stack<int>	operand_stack;
	std::istringstream	tokens(arguments);
	std::string			token;

	while (tokens >> token) {
		int	operand;

		if (std::istringstream(token) >> operand && operand < 10 && operand >= 0)
			operand_stack.push(operand);
		else if (token.length() == 1 && std::string("+-*/").find(token) != std::string::npos) {
			if (operand_stack.size() < 2) //or != 2
				throw std::invalid_argument("Missing operands before operator");
			int second = operand_stack.top();
			operand_stack.pop();
			int first = operand_stack.top();
			operand_stack.pop();
			operand_stack.push(compute_element(token[0], first, second));
		}
		else
			throw std::invalid_argument("cannot parse expression");
	}
	return operand_stack.top();
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	try {
		int result = parse_expression(argv[1]);
		std::cout << result << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << "Error" << std::endl;
		return 1;
	}
	return 0;
}