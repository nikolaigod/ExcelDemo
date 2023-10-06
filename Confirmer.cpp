#include "Confirmer.h"

/**
 * @brief Checks if a string represents a numeric value.
 *
 * This method determines whether a string represents a numeric value by checking if all characters in the string are digits.
 * The string may include an optional leading '+' or '-' sign for positive or negative numbers.
 *
 * @param str The string to be checked.
 * @return `true` if the string represents a numeric value, `false` otherwise.
 */
bool Confirmer::isNum(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	if (str[0] == '+' || str[0] == '-') {
		for (size_t i = 1; i < str.length(); i++) {
			if (!std::isdigit(str[i])) {
				return false;
			}
		}
		return true;
	}

	for (size_t i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Checks if a string represents a double value.
 *
 * This method determines whether a string represents a double value by checking if it can be parsed as a valid double.
 * The string may include an optional leading '+' or '-' sign for positive or negative numbers, and may contain a single '.' as the decimal separator.
 *
 * @param str The string to be checked.
 * @return `true` if the string represents a double value, `false` otherwise.
 */
bool Confirmer::isDouble(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	bool dot = false;
	if (str[0] == '+' || str[0] == '-') {
		for (size_t i = 1; i < str.length(); i++) {
			if (!std::isdigit(str[i])) {
				if (str[i] == '.' && !dot) {
					dot = true;
				}
				else return false;
			}
		}
		return true;
	}
	for (size_t i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i])) {
			if (str[i] == '.' && !dot) {
				dot = true;
			}
			else return false;
		}
	}
	return true;
}

/**
 * @brief Checks if a character represents an arithmetic operator.
 *
 * This method determines whether a character represents an arithmetic operator, such as '+', '-', '*', or '/'.
 *
 * @param op The character to be checked.
 * @return `true` if the character represents an arithmetic operator, `false` otherwise.
 */
bool Confirmer::isArithmetic(const char op){
	return op == '+' || op == '-' || op == '*' || op == '/';
}

/**
 * @brief Checks if a character represents a comparison operator.
 *
 * This method determines whether a character represents a comparison operator, such as '<', '>', '=', or '!'.
 *
 * @param op The character to be checked.
 * @return `true` if the character represents a comparison operator, `false` otherwise.
 */
bool Confirmer::isComparing(const char op) {
	return op == '<' || op == '>' || op == '=' || op == '!';
}

/**
 * @brief Calculates the maximum number of tokens in each line of a CSV file.
 *
 * This method reads the specified CSV file and determines the maximum number of tokens (comma-separated values) in each line.
 *
 * @param filename The name of the CSV file.
 * @return The maximum number of tokens found in any line of the CSV file.
 * @throws std::ifstream::failure if the file fails to open.
 */
int Confirmer::maxTokens(const std::string& filename)
{
	std::ifstream file(filename);
	try {
		if (!file.is_open()) {
			throw std::ifstream::failure("File didnt open");
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << e.what();
	}

	unsigned maxTokens = 1;
	std::string line;
	bool inText = false;
	while (std::getline(file, line)) {
		int currMax = 1;
		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] == ',' && !inText) {
				currMax++;
			}
			if (line[i] == '\\') {
				inText ? inText = false : inText = true;
			}
		}
		if (currMax > maxTokens) {
			maxTokens = currMax;
		}
	}
	file.close();
	return maxTokens;
}

/**
 * @brief Calculates the maximum number of rows in a CSV file.
 *
 * This method reads the specified CSV file and counts the number of lines, which corresponds to the number of rows in the CSV file.
 *
 * @param filename The name of the CSV file.
 * @return The maximum number of rows in the CSV file.
 * @throws std::ifstream::failure if the file fails to open.
 */
int Confirmer::maxRows(const std::string& filename)
{
	std::ifstream file(filename);
	try {
		if (!file.is_open()) {
			throw std::ifstream::failure("File didnt open");
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << e.what();
	}
	int maxRows = 0;
	std::string line;
	while (std::getline(file, line)) {
		maxRows++;
	}
	file.close();
	return maxRows;
}

/**
 * @brief Checks if a given string represents a valid formula in the format type 1.
 *
 * The method checks if the string follows the specified formula format and validates the row and column numbers and arithmetic operations.
 *
 * @param str The string to check.
 * @return `true` if the string represents a valid formula, `false` otherwise.
 */
bool Confirmer::isFormula1(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	std::string result = "";
	int rows1 = 0;
	int cols1 = 0;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}

	if (result[0] == '=' && result[1] == 'R') {
		size_t i = 2;
		if (!std::isdigit(result[i])) {
			return false;
		}
		while (std::isdigit(result[i])) {
			i++;
		}
		if (result[i++] == 'C') {
			if (!std::isdigit(result[i])) {
				return false;
			}
			while (std::isdigit(result[i])) {
				i++;
			}
			if (isArithmetic(result[i])) {
				i++;
				if (result[i++] == 'R') {
					if (!std::isdigit(result[i])) {
						return false;
					}
					while (std::isdigit(result[i])) {
						i++;
					}
					if (result[i++] == 'C') {
						for (size_t j = i; j < result.length(); j++) {
							if (!std::isdigit(result[j])) {
								return false;
							}
						}
						return true;
					}
				}
				return false;
			}
			else if (isComparing(result[i++])) {
				if (isComparing(result[i])) {
					i++;
					if (result[i++] == 'R') {
						if (!std::isdigit(result[i])) {
							return false;
						}
						while (std::isdigit(result[i])) {
							i++;
						}
						if (result[i++] == 'C') {
							for (size_t j = i; j < result.length(); j++) {
								if (!std::isdigit(result[j])) {
									return false;
								}
							}
							return true;
						}
					}
				}
				else if (result[i++] == 'R') {
					if (!std::isdigit(result[i])) {
						return false;
					}
					while (std::isdigit(result[i])) {
						i++;
					}
					if (result[i++] == 'C')
						for (size_t j = i; j < result.length(); j++) {
							if (!std::isdigit(result[j])) {
								return false;
							}
						}
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

/**
 * @brief Checks if a given string represents a valid formula in the format type 2.
 *
 * The method checks if the string follows the specified formula format and validates the row numbers and arithmetic operations.
 *
 * @param str The string to check.
 * @return `true` if the string represents a valid formula, `false` otherwise.
 */
bool Confirmer::isFormula2(const std::string& str) {
	if (str.empty()) {
		return false;
	}
	std::string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}
	if (result[0] == '=') {
		size_t i = 1;
		if (!std::isdigit(result[i])) {
			return false;
		}
		while (std::isdigit(result[i])) {
			i++;
		}
		if (isArithmetic(result[i++])) {
			for (size_t j = i; j < result.length(); j++) {
				if (!std::isdigit(result[j])) {
					return false;
				}
			}
			return true;
		}
		else if (isComparing(result[i++])) {
			if (isComparing(result[i++])) {
				for (size_t j = i; j < result.length(); j++) {
					if (!std::isdigit(result[j])) {
						return false;
					}
				}
				return true;
			}
		}
	}
}

/**
 * @brief Checks if a given string represents a valid formula in the format type 3.
 *
 * The method checks if the string follows the specified formula format and validates the row numbers and arithmetic operations.
 *
 * @param str The string to check.
 * @return `true` if the string represents a valid formula, `false` otherwise.
 */
bool Confirmer::isFormula3(const std::string& str)
{
	if (str.empty()) {
		return false;
	}
	std::string result = "";
	int rows1 = 0;
	int cols1 = 0;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}

	if (result[0] == '=' && result[1] == 'R') {
		size_t i = 2;
		if (!std::isdigit(result[i])) {
			return false;
		}
		while (std::isdigit(result[i])) {
			i++;
		}
		if (result[i++] == 'C') {
			if (!std::isdigit(result[i])) {
				return false;
			}
			while (std::isdigit(result[i])) {
				i++;
			}
			if (isArithmetic(result[i])) {
				i++;
				for (size_t j = i; j < result.length(); j++) {
					if (!std::isdigit(result[j])) {
						return false;
					}
				}
				return true;
			}
			else if (isComparing(result[i++])) {
				for (size_t j = i; j < result.length(); j++) {
					if (!std::isdigit(result[j])) {
						return false;
					}
				}
				return true;
			}
		}
	}
	else if (result[0] == '=' && std::isdigit(result[1])) {
		size_t i = 1;
		while (std::isdigit(result[i])) {
			i++;
		}
		if (isArithmetic(result[i])) {
			i++;
			if (result[i++] == 'R') {
				if (!std::isdigit(result[i])) {
					return false;
				}
				while (std::isdigit(result[i])) {
					i++;
				}
				if (result[i++] == 'C') {
					for (size_t j = i; j < result.length(); j++) {
						if (!std::isdigit(result[j])) {
							return false;
						}
					}
					return true;
				}
			}
		}
		else if (isComparing(result[i++])) {
			if (isComparing(result[i])) {
				i++;
				if (result[i++] == 'R') {
					if (!std::isdigit(result[i])) {
						return false;
					}
					while (std::isdigit(result[i])) {
						i++;
					}
					if (result[i++] == 'C') {
						for (size_t j = i; j < result.length(); j++) {
							if (!std::isdigit(result[j])) {
								return false;
							}
						}
						return true;
					}
				}
			}
			else if (result[i++] == 'R') {
				if (!std::isdigit(result[i])) {
					return false;
				}
				while (std::isdigit(result[i])) {
					i++;
				}
				if (result[i++] == 'C')
					for (size_t j = i; j < result.length(); j++) {
						if (!std::isdigit(result[j])) {
							return false;
						}
					}
				return true;
			}
			else return false;
		}
		else return false;
	}
}

/**
 * @brief Checks if a given string represents a string value.
 *
 * The method checks if the string is empty or if it is enclosed in double quotation marks.
 *
 * @param str The string to check.
 * @return `true` if the string represents a string value, `false` otherwise.
 */

bool Confirmer::isString(const std::string& str) {
	if (str.empty()) {
		return true;
	}
	return str[0] == '"' && str[str.length() - 1] == '"';
}

/**
 * @brief Determines the length of the longest string representation in a given column of the table.
 *
 * The method iterates over the rows of the table and retrieves the string representation of the data
 * in the specified column. It compares the length of each string representation and keeps track of
 * the maximum length found.
 *
 * @param col The column index.
 * @return The length of the longest string representation in the column.
 */
int Confirmer::biggestData(const int col) {
	int maxSize = 0;
	for (size_t i = 0; i < Table::getInstance().getTable().size(); i++) {
		int size = Table::getInstance().getTable()[i][col]->stringify().length();
		if (size > maxSize) {
			maxSize = size;
		}
	}
	return maxSize;
}

/**
 * @brief Extracts data from a formula of the form "=R[row1]C[col1][op]R[row2]C[col2]".
 *
 * The method takes a formula string and extracts the row indices, column indices, and operator
 * information from it. The formula should be in the format "=R[row1]C[col1][op]R[row2]C[col2]".
 *
 * @param str The formula string.
 * @param row Vector to store the extracted row indices.
 * @param op String to store the extracted operator.
 * @param col Vector to store the extracted column indices.
 */
void Confirmer::extractData1(const std::string& str, std::vector<int>& row, std::string& op, std::vector<int>& col) {
	std::string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}
	std::string row1, row2, col1, col2;
	size_t i = 2;
	while (std::isdigit(result[i])) {
		row1 += result[i++];
	}
	i++;
	while (std::isdigit(result[i])) {
		col1 += result[i++];
	}
	while (result[i] != 'R') {
		op += result[i++];
	}
	i++;
	while (std::isdigit(result[i])) {
		row2 += result[i++];
	}
	i++;
	for (size_t j = i; j < result.length(); j++) {
		col2 += result[j];
	}
	row.push_back(std::stoi(row1));
	row.push_back(std::stoi(row2));
	col.push_back(std::stoi(col1));
	col.push_back(std::stoi(col2));
}

/**
 * @brief Extracts data from a formula of the form "=dval1[op]dval2".
 *
 * The method takes a formula string and extracts the numerical values and operator
 * information from it. The formula should be in the format "=dval1[op]dval2".
 *
 * @param str The formula string.
 * @param dval1 Reference to a double variable to store the extracted first numerical value.
 * @param op String to store the extracted operator.
 * @param dval2 Reference to a double variable to store the extracted second numerical value.
 */
void Confirmer::extractData2(const std::string& str, double& dval1, std::string& op, double& dval2) {
	std::string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}
	std::string d1, d2;
	size_t i = 1;
	while (std::isdigit(result[i])) {
		d1 += result[i++];
	}
	while (!std::isdigit(result[i])) {
		op += result[i++];
	}
	for (size_t j = i; j < result.length(); j++) {
		d2 += result[j];
	}
	dval1 = std::stod(d1);
	dval2 = std::stod(d2);
}

/**
 * @brief Extracts data from a formula of the form "=dval3[op]Rrow1Ccol1" or "=dval3[op]row1Ccol1".
 *
 * The method takes a formula string and extracts the numerical value, operator, row number,
 * and column number from it. The formula can be in two formats: "=dval3[op]Rrow1Ccol1" or "=dval3[op]row1Ccol1".
 *
 * @param str The formula string.
 * @param dval3 Reference to a double variable to store the extracted numerical value.
 * @param operation String to store the extracted operator.
 * @param row1 Reference to an integer variable to store the extracted row number.
 * @param col1 Reference to an integer variable to store the extracted column number.
 * @return True if the formula is in the format "=dval3[op]Rrow1Ccol1", False if it is in the format "=dval3[op]row1Ccol1".
 */
bool Confirmer::extractData3(const std::string& str, double& dval3, std::string& operation, int& row1, int& col1)
{
	bool f = false;
	bool t = false;
	std::string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			result += str[i];
		}
	}
	std::string d1, row, col, op;
	if (result[1] == 'R') {
		size_t i = 2;
		while (std::isdigit(result[i])) {
			row += result[i++];
		}
		i++;
		while (std::isdigit(result[i])) {
			col += result[i++];
		}
		while (!std::isdigit(result[i])) {
			op += result[i++];
		}
		for (size_t j = i; j < result.length(); j++) {
			d1 += result[j];
		}
		t = true;
	}
	else if (std::isdigit(result[1])) {
		size_t i = 1;
		while (std::isdigit(result[i])) {
			d1 += result[i++];
		}
		while (result[i] != 'R') {
			op += result[i++];
		}
		i++;
		while (std::isdigit(result[i])) {
			row += result[i++];
		}
		i++;
		for (size_t j = i; j < result.length(); j++) {
			col += result[j];
		}
		f = true;
	}

	dval3 = std::stod(d1);
	row1 = std::stoi(row);
	col1 = std::stoi(col);
	operation = op;
	if (f) {
		return false;
	}
	return true;
}

