#include "FormulaData.h"
using namespace std;

/**
 * @brief Default constructor for the FormulaData class.
 *
 * This constructor initializes the FormulaData object with default values.
 */
FormulaData::FormulaData():FormulaData(0,0,"") {
	this->type = FORMULA;
}

/**
 * @brief Constructor for the FormulaData class that initializes formula data with coordinates and operation.
 *
 * @param col1 The column index of the first cell.
 * @param row1 The row index of the first cell.
 * @param col2 The column index of the second cell.
 * @param row2 The row index of the second cell.
 * @param operation The operation to be performed on the cell values.
 */
FormulaData::FormulaData(const int col1, const int row1, const int col2, const int row2, const std::string& operation) :col1(col1), row1(row1),
col2(col2), row2(row2), operation(operation), dval1(0.0), dval2(0.0), courdinates(true), digits(false), dval3(0), mixed(false), whosFirst(false) {
	this->type = FORMULA;
}

/**
 * @brief Constructor for the FormulaData class that initializes formula data with numerical values and operation.
 *
 * @param dval1 The first numerical value.
 * @param dval2 The second numerical value.
 * @param operation The operation to be performed on the numerical values.
 */
FormulaData::FormulaData(const double dval1, const double dval2, const std::string& operation):col1(0), row1(0),
col2(0), row2(0), operation(operation), dval1(dval1), dval2(dval2), courdinates(false), digits(true), dval3(0), mixed(false), whosFirst(false) {
	this->type = FORMULA;
}

/**
 * @brief Constructor for the FormulaData class that initializes formula data with a single numerical value, cell coordinates, and operation.
 *
 * @param dval3 The numerical value used in the formula.
 * @param row The row coordinate of the cell.
 * @param col The column coordinate of the cell.
 * @param operation The operation to be performed on the cell value.
 * @param whosFirst A boolean value indicating whether the cell value comes first in the operation.
 */
FormulaData::FormulaData(const double dval3, const int row, const int col, std::string& operation, bool whosFirst) :col1(col), row1(row),
col2(0), row2(0), operation(operation), dval1(dval3), dval2(0), courdinates(false), digits(false), mixed(true), dval3(dval3), whosFirst(whosFirst) {
	this->type = FORMULA;
}

/**
* @brief Converts the FormulaData object to a string representation.
* @return A string representation of the FormulaData object.
*/
std::string FormulaData::stringify() const {
	std::string tmp = "";
	int integer1 = 0;
	double floater1 = 0.0;
	int integer2 = 0;
	double floater2 = 0.0;
	bool intFlag1 = false;
	bool intFlag2 = false;
	if (this->courdinates) {
		if (this->row1 > Table::getInstance().getMaxRows() || this->col1 > Table::getInstance().getMaxCols()) {
			integer1 = 0;
			intFlag1 = true;
		}
		else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == FORMULA) {
			std::string tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringifyFile();
			if (Confirmer::isFormula1(tmp)) {
				std::vector<int> rows, cols;
				std::string op;
				Confirmer::extractData1(tmp, rows, op, cols);
				if (this->row1 == rows[0] && this->col1 == cols[0]) {
					integer1 = 0;
					intFlag1 = true;
				}
				else if (this->row2 == rows[1] && this->col2 == cols[1]) {
					integer1 = 0;
					intFlag1 = true;
				}
				else {
					std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
					if (Confirmer::isNum(tmp2)) {
						integer1 = std::stoi(tmp2);
						intFlag1 = true;
					}
					else if (Confirmer::isDouble(tmp2)) {
						floater1 = std::stod(tmp2);
					}
					else {
						integer1 = 0;
						intFlag1 = true;
					}
				}
			}
			else if (Confirmer::isFormula2(tmp)) {
				std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
				floater1 = std::stod(tmp2);
			}
			else if (Confirmer::isFormula3(tmp)) {
				double dval3;
				int row, col;
				std::string op;
				bool flag = Confirmer::extractData3(tmp, dval3, op, row, col);
				if (this->row1 == row && this->col1 == col) {
					integer1 = 0;
					intFlag1 = true;
				}
				else if (this->row2 == row && this->col2 == col) {
					integer1 = 0;
					intFlag1 = true;
				}
				else {
					std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
					if (Confirmer::isNum(tmp2)) {
						integer1 = std::stoi(tmp2);
						intFlag1 = true;
					}
					else if (Confirmer::isDouble(tmp2)) {
						floater1 = std::stod(tmp2);
					}
					else {
						integer1 = 0;
						intFlag1 = true;
					}
				}
			}
		}
		else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == STRING) {
			tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
			if (Confirmer::isDouble(tmp)) {
				floater1 = std::stod(tmp);
			}
			else if (Confirmer::isNum(tmp)) {
				integer1 = std::stoi(tmp);
				intFlag1 = true;
			}
			else {
				integer1 = 0;
				intFlag1 = true;
			}
		}
		else {
			tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
			if (Confirmer::isDouble(tmp)) {
				floater1 = std::stod(tmp);
			}
			else if (Confirmer::isNum(tmp)) {
				integer1 = std::stoi(tmp);
				intFlag1 = true;
			}
		}
		if (this->row2 > Table::getInstance().getMaxRows() || this->col2 > Table::getInstance().getMaxCols()) {
			integer2 = 0;
			intFlag2 = true;
		}
		else if (Table::getInstance().getTable()[this->row2][this->col2]->getType() == STRING) {
			tmp = Table::getInstance().getTable()[this->row2][this->col2]->stringify();
			if (Confirmer::isDouble(tmp)) {
				floater2 = std::stod(tmp);
			}
			else if (Confirmer::isNum(tmp)) {
				integer2 = std::stoi(tmp);
				intFlag2 = true;
			}
			else {
				integer2 = 0;
				intFlag2 = true;
			}
		}
		else if (Table::getInstance().getTable()[this->row2][this->col2]->getType() == FORMULA) {
			std::string tmp = Table::getInstance().getTable()[this->row2][this->col2]->stringifyFile();
			if (Confirmer::isFormula1(tmp)) {
				std::vector<int> rows, cols;
				std::string op;
				Confirmer::extractData1(tmp, rows, op, cols);
				if (this->row1 == rows[0] && this->col1 == cols[0]) {
					integer1 = 0;
					intFlag1 = true;
				}
				else if (this->row2 == rows[1] && this->col2 == cols[1]) {
					integer1 = 0;
					intFlag1 = true;
				}
				else {
					std::string tmp2 = Table::getInstance().getTable()[this->row2][this->col2]->stringify();
					if (Confirmer::isNum(tmp2)) {
						integer1 = std::stoi(tmp2);
						intFlag1 = true;
					}
					else if (Confirmer::isDouble(tmp2)) {
						floater1 = std::stod(tmp2);
					}
					else {
						integer1 = 0;
						intFlag1 = true;
					}
				}
			}
			else if (Confirmer::isFormula2(tmp)) {
				std::string tmp2 = Table::getInstance().getTable()[this->row2][this->col2]->stringify();
				floater1 = std::stod(tmp2);
			}
			else if (Confirmer::isFormula3(tmp)) {
				double dval3;
				int row, col;
				std::string op;
				bool flag = Confirmer::extractData3(tmp, dval3, op, row, col);
				if (this->row1 == row && this->col1 == col) {
					integer1 = 0;
					intFlag1 = true;
				}
				else if (this->row2 == row && this->col2 == col) {
					integer1 = 0;
					intFlag1 = true;
				}
				else {
					std::string tmp2 = Table::getInstance().getTable()[this->row2][this->col2]->stringify();
					if (Confirmer::isNum(tmp2)) {
						integer1 = std::stoi(tmp2);
						intFlag1 = true;
					}
					else if (Confirmer::isDouble(tmp2)) {
						floater1 = std::stod(tmp2);
					}
					else {
						integer1 = 0;
						intFlag1 = true;
					}
				}
			}
		}
		else {
			tmp = Table::getInstance().getTable()[this->row2][this->col2]->stringify();
			if (Confirmer::isDouble(tmp)) {
				floater2 = std::stod(tmp);
			}
			else if (Confirmer::isNum(tmp)) {
				integer2 = std::stoi(tmp);
				intFlag2 = true;
			}
		}
	}
	else if (this->mixed) {
		if (this->whosFirst) {
			if (this->row1 > Table::getInstance().getMaxRows() || this->col1 > Table::getInstance().getMaxCols()) {
				integer1 = 0;
				intFlag1 = true;
			}
			else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == FORMULA) {

				std::string tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringifyFile();
				if (Confirmer::isFormula1(tmp)) {
					std::vector<int> rows, cols;
					std::string op;
					Confirmer::extractData1(tmp, rows, op, cols);
					if (this->row1 == rows[0] && this->col1 == cols[0]) {
						integer1 = 0;
						intFlag1 = true;
					}
					else {
						std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
						if (Confirmer::isNum(tmp2)) {
							integer1 = std::stoi(tmp2);
							intFlag1 = true;
						}
						else if (Confirmer::isDouble(tmp2)) {
							floater1 = std::stod(tmp2);
						}
						else {
							integer1 = 0;
							intFlag1 = true;
						}
					}
				}
				else if (Confirmer::isFormula2(tmp)) {
					std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
					floater1 = std::stod(tmp2);
				}
				else if (Confirmer::isFormula3(tmp)) {
					double dval3;
					int row, col;
					std::string op;
					bool flag = Confirmer::extractData3(tmp, dval3, op, row, col);
					if (this->row1 == row && this->col1 == col) {
						integer1 = 0;
						intFlag1 = true;
					}
					else {
						std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
						if (Confirmer::isNum(tmp2)) {
							integer1 = std::stoi(tmp2);
							intFlag1 = true;
						}
						else if (Confirmer::isDouble(tmp2)) {
							floater1 = std::stod(tmp2);
						}
						else {
							integer1 = 0;
							intFlag1 = true;
						}
					}
				}
			}
			else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == STRING) {
				tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
				if (Confirmer::isDouble(tmp)) {
					floater1 = std::stod(tmp);
				}
				else if (Confirmer::isNum(tmp)) {
					integer1 = std::stoi(tmp);
					intFlag1 = true;
				}
				else {
					integer1 = 0;
					intFlag1 = true;
				}
			}
			else {
				tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
				if (Confirmer::isDouble(tmp)) {
					floater1 = std::stod(tmp);
				}
				else if (Confirmer::isNum(tmp)) {
					integer1 = std::stoi(tmp);
					intFlag1 = true;
				}
			}
			floater2 = this->dval3;
		}
		else {
			floater1 = this->dval1;
			if (this->row1 > Table::getInstance().getMaxRows() || this->col1 > Table::getInstance().getMaxCols()) {
				integer2 = 0;
				intFlag2 = true;
			}
			else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == FORMULA) {
				std::string tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringifyFile();
				if (Confirmer::isFormula1(tmp)) {
					std::vector<int> rows, cols;
					std::string op;
					Confirmer::extractData1(tmp, rows, op, cols);
					if (this->row1 == rows[0] && this->col1 == cols[0]) {
						integer1 = 0;
						intFlag1 = true;
					}
					else {
						std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
						if (Confirmer::isNum(tmp2)) {
							integer1 = std::stoi(tmp2);
							intFlag1 = true;
						}
						else if (Confirmer::isDouble(tmp2)) {
							floater1 = std::stod(tmp2);
						}
						else {
							integer1 = 0;
							intFlag1 = true;
						}
					}
				}
				else if (Confirmer::isFormula2(tmp)) {
					std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
					floater1 = std::stod(tmp2);
				}
				else if (Confirmer::isFormula3(tmp)) {
					double dval3;
					int row, col;
					std::string op;
					bool flag = Confirmer::extractData3(tmp, dval3, op, row, col);
					if (this->row1 == row && this->col1 == col) {
						integer1 = 0;
						intFlag1 = true;
					}
					else {
						std::string tmp2 = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
						if (Confirmer::isNum(tmp2)) {
							integer1 = std::stoi(tmp2);
							intFlag1 = true;
						}
						else if (Confirmer::isDouble(tmp2)) {
							floater1 = std::stod(tmp2);
						}
						else {
							integer1 = 0;
							intFlag1 = true;
						}
					}
				}
			}
			else if (Table::getInstance().getTable()[this->row1][this->col1]->getType() == STRING) {
				tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
				if (Confirmer::isDouble(tmp)) {
					floater2 = std::stod(tmp);
				}
				else if (Confirmer::isNum(tmp)) {
					integer2 = std::stoi(tmp);
					intFlag2 = true;
				}
				else {
					integer2 = 0;
					intFlag2 = true;
				}
			}
			else {
				tmp = Table::getInstance().getTable()[this->row1][this->col1]->stringify();
				if (Confirmer::isDouble(tmp)) {
					floater2 = std::stod(tmp);
				}
				else if (Confirmer::isNum(tmp)) {
					integer2 = std::stoi(tmp);
					intFlag2 = true;
				}
			}
		}
	}
	std::string result = "";
	if ((this->courdinates || this->mixed) && intFlag1 && intFlag2) {
		if (this->operation == "+") {
			result += to_string(integer1 + integer2);
		}
		else if (this->operation == "-") {
			result += to_string(integer1 - integer2);
		}
		else if (this->operation == "*") {
			result += to_string(integer1 * integer2);
		}
		else if (this->operation == "/") {
			if (integer2 == 0) {
				result += "ERROR";
			}
			else result += to_string(integer1 / integer2);
		}
		else if (this->operation == "<") {
			result += to_string(integer1 < integer2);
		}
		else if (this->operation == ">") {
			result += to_string(integer1 > integer2);
		}
		else if (this->operation == "<=") {
			result += to_string(integer1 <= integer2);
		}
		else if (this->operation == ">=") {
			result += to_string(integer1 >= integer2);
		}
		else if (this->operation == "==") {
			result += to_string(integer1 == integer2);
		}
		else if (this->operation == "!=") {
			result += to_string(integer1 != integer2);
		}
	}
	else if ((this->courdinates || this->mixed) && intFlag1 && !intFlag2) {
		if (this->operation == "+") {
			result += to_string(integer1 + floater2);
		}
		else if (this->operation == "-") {
			result += to_string(integer1 - floater2);
		}
		else if (this->operation == "*") {
			result += to_string(integer1 * floater2);
		}
		else if (this->operation == "/") {
			if (floater2 == 0) {
				result += "ERROR";
			}
			else result += to_string(integer1 / floater2);
		}
		else if (this->operation == "<") {
			result += to_string(integer1 < floater2);
		}
		else if (this->operation == ">") {
			result += to_string(integer1 > floater2);
		}
		else if (this->operation == "<=") {
			result += to_string(integer1 <= floater2);
		}
		else if (this->operation == ">=") {
			result += to_string(integer1 >= floater2);
		}
		else if (this->operation == "==") {
			result += to_string(integer1 == floater2);
		}
		else if (this->operation == "!=") {
			result += to_string(integer1 != floater2);
		}
	}
	else if ((this->courdinates || this->mixed) && !intFlag1 && intFlag2) {
		if (this->operation == "+") {
			result += to_string(floater1 + integer2);
		}
		else if (this->operation == "-") {
			result += to_string(floater1 - integer2);
		}
		else if (this->operation == "*") {
			result += to_string(floater1 * integer2);
		}
		else if (this->operation == "/") {
			if (integer2 == 0) {
				result += "ERROR";
			}
			else result += to_string(floater1 / integer2);
		}
		else if (this->operation == "<") {
			result += to_string(floater1 < integer2);
		}
		else if (this->operation == ">") {
			result += to_string(floater1 > integer2);
		}
		else if (this->operation == "<=") {
			result += to_string(floater1 <= integer2);
		}
		else if (this->operation == ">=") {
			result += to_string(floater1 >= integer2);
		}
		else if (this->operation == "==") {
			result += to_string(floater1 == integer2);
		}
		else if (this->operation == "!=") {
			result += to_string(floater1 != integer2);
		}
	}
	else if ((this->courdinates || this->mixed) && !intFlag1 && !intFlag2) {
		if (this->operation == "+") {
			result += to_string(floater1 + floater2);
		}
		else if (this->operation == "-") {
			result += to_string(floater1 - floater2);
		}
		else if (this->operation == "*") {
			result += to_string(floater1 * floater2);
		}
		else if (this->operation == "/") {
			if (floater2 == 0) {
				result += "ERROR";
			}
			result += to_string(floater1 / floater2);
		}
		else if (this->operation == "<") {
			result += to_string(floater1 < floater2);
		}
		else if (this->operation == ">") {
			result += to_string(floater1 > floater2);
		}
		else if (this->operation == "<=") {
			result += to_string(floater1 <= floater2);
		}
		else if (this->operation == ">=") {
			result += to_string(floater1 >= floater2);
		}
		else if (this->operation == "==") {
			result += to_string(floater1 == floater2);
		}
		else if (this->operation == "!=") {
			result += to_string(floater1 != floater2);
		}
	}
	else {
		if (this->operation == "+") {
			result += std::to_string(this->dval1 + this->dval2);
		}
		else if (this->operation == "-") {
			result += to_string(this->dval1 - this->dval2);
		}
		else if (this->operation == "*") {
			result += to_string(this->dval1 * this->dval2);
		}
		else if (this->operation == "/") {
			if (this->dval2 == 0) {
				result += "ERROR";
			}
			result += to_string(this->dval1 / this->dval2);
		}
		else if (this->operation == "<") {
			result += to_string(this->dval1 < this->dval2);
		}
		else if (this->operation == ">") {
			result += to_string(this->dval1 > this->dval2);
		}
		else if (this->operation == "<=") {
			result += to_string(this->dval1 <= this->dval2);
		}
		else if (this->operation == ">=") {
			result += to_string(this->dval1 >= this->dval2);
		}
		else if (this->operation == "==") {
			result += to_string(this->dval1 == this->dval2);
		}
		else if (this->operation == "!=") {
			result += to_string(this->dval1 != this->dval2);
		}
	}
	return result;
}

/**
* @brief Converts the FormulaData object to a string representation for file output.
* @return A string representation of the FormulaData object for file output.
*/
std::string FormulaData::stringifyFile() const {
	std::string tmp = "";
	tmp += '=';
	if (this->courdinates) {
		tmp += "R" + std::to_string(this->row1) + "C" + std::to_string(this->col1) + " " + this->operation + " " + "R" + std::to_string(this->row2) + "C" + std::to_string(this->col2);
	}
	else if (this->mixed && this->whosFirst) {
		tmp += "R" + std::to_string(this->row1) + "C" + std::to_string(this->col1) + " " + this->operation + " " + std::to_string(this->dval3);
	}
	else if (this->mixed && !this->whosFirst) {
		tmp += std::to_string(this->dval3) + " " + this->operation + " " + "R" + std::to_string(this->row1) + "C" + std::to_string(this->col1);
	}
	else {
		tmp += std::to_string(this->dval1) + " " + this->operation + " " + std::to_string(this->dval2);
	}
	return tmp;
}

/**
* @brief Retrieves the data type of the FormulaData object.
* @return The data type of the FormulaData object (DataType::FORMULA).
*/
DataType FormulaData::getType() const {
	return this->type;
}