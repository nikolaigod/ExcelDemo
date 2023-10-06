#include "Table.h"

/**
	 * @brief Constructs the Table object.
	 * @note This constructor is private to enforce the singleton pattern.
	 */
Table::Table() {
	std::cout << "Enter file path to load table: ";
	std::string filepath;
	while (true) {
		std::cin >> filepath;
		int size = filepath.size();
		if (filepath[size - 1] != 't' || filepath[size - 2] != 'x' || filepath[size - 3] != 't') {
			std::cout << "Wrong file extension, enter again\n";
		}
		else break;
	}
	this->filepath = filepath;
	int maxTokens = Confirmer::maxTokens(filepath);
	int maxRows = Confirmer::maxRows(filepath);
	this->maxCols = maxTokens;
	this->maxRows = maxRows;
	CSVReader reader(filepath, maxTokens);
	std::vector<Data*> realRow;
		while (reader.has_more_data()) {
			std::vector<std::string> row = reader.get_tokens();

			if (row.empty()) {
				continue;
			}
			realRow.clear();
			size_t i = 0;
			try {
				for (i = 0; i < row.size(); i++) {
					if (Confirmer::isNum(row[i])) {
						realRow.push_back(new IntData(std::stoi(row[i])));
					}
					else if (Confirmer::isString(row[i])) {
						std::string clean = "\"";
						if (!row[i].empty() && row[i][1] == '\\') {
							size_t j = 0;
							while (row[i][j] == '"' || row[i][j] == '\\') {
								j++;
							}
							for (size_t k = j; k < row[i].length(); k++) {
								if (row[i][k] == '\\') {
									break;
								}
								clean += row[i][k];
							}
							clean += '\"';
						}
						else if (!row[i].empty() && row[i][1] != '\\') {
							clean = row[i].substr(1, row[i].length() - 2);
						}

						if (clean == "\"") {
							realRow.push_back(new StringData(row[i]));
						}
						else realRow.push_back(new StringData(clean));
					}
					else if (Confirmer::isDouble(row[i])) {
						realRow.push_back(new DoubleData(std::stod(row[i])));
					}
					else if (Confirmer::isFormula1(row[i])) {
						std::vector<int> rows;
						std::vector<int> cols;
						std::string op = "";
						Confirmer::extractData1(row[i], rows, op, cols);
						realRow.push_back(new FormulaData(cols[0], rows[0], cols[1], rows[1], op));
					}
					else if (Confirmer::isFormula2(row[i])) {
						double dval1 = 0;
						double dval2 = 0;
						std::string op = "";
						Confirmer::extractData2(row[i], dval1, op, dval2);
						realRow.push_back(new FormulaData(dval1, dval2, op));
					}
					else if (Confirmer::isFormula3(row[i])) {
						double dval3 = 0;
						int row1 = 0;
						int col1 = 0;
						std::string op = "";
						bool whosFirst = Confirmer::extractData3(row[i], dval3, op, row1, col1);
						realRow.push_back(new FormulaData(dval3, row1, col1, op, whosFirst));
					}
					else {
						realRow.push_back(new StringData(""));
						std::cout << "Invalid data at given\n";
					}
				}
			}
			catch (std::bad_alloc& e) {
				if (realRow.size() != 0) {
					for (size_t i = 0; i < realRow.size(); i++) {
						delete realRow[i];
					}
				}
				this->clean();
			}

			this->data.push_back(realRow);
		}

	std::cout << "Successfuly opened " << filepath << std::endl;
}

/**
	 * @brief Cleans up the table by deleting all data objects.
	 */
void Table::clean()
{
	for (size_t i = 0; i < this->data.size(); i++) {
		for (size_t j = 0; j < this->data[i].size(); j++) {
			delete this->data[i][j];
		}
	}
}

/**
	 * @brief Prints the table to the console.
	 */
void Table::print() const {
	for (size_t i = 0; i < this->data.size() - 1; i++) {
		for (size_t j = 0; j < this->data[i].size(); j++) {
			int maxCol = Confirmer::biggestData(j);
			int dif = maxCol - data[i][j]->stringify().length();
			std::cout << "|" << data[i][j]->stringify();
			for (size_t k = 0; k < dif; k++) {
				std::cout << " ";
			}
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "\n";
}

/**
	 * @brief Saves the table to the default file path.
	 */
void Table::save() const
{
	std::ofstream file(this->filepath);
	try {
		if (!file.is_open()) {
			throw std::ofstream::failure("File didnt open");
		}
	}
	catch (const std::ofstream::failure& e) {
		std::cout << e.what();
	}

	for (size_t i = 0; i < this->data.size() - 1; i++) {
		for (size_t j = 0; j < this->data[i].size(); j++) {
			file << data[i][j]->stringifyFile();
			if (j != this->data[i].size() - 1) {
				file << ',';
			}
		}
		file << std::endl;
	}
	file.close();
}

/**
	 * @brief Saves the table to a specified file path.
	 * @param filePath The file path to save the table to.
	 */
void Table::saveAs(const std::string& filepath) const
{
	std::ofstream file(filepath);
	try {
		if (!file.is_open()) {
			throw std::ofstream::failure("File didnt open");
		}
	}
	catch (const std::ofstream::failure& e) {
		std::cout << e.what();
	}

	for (size_t i = 0; i < this->data.size() - 1; i++) {
		for (size_t j = 0; j < this->data[i].size(); j++) {
			file << data[i][j]->stringifyFile();
			if (j != this->data[i].size() - 1) {
				file << ',';
			}
		}
		file << std::endl;
	}
	file.close();
}

/**
	 * @brief Retrieves the table data.
	 * @return The table data as a 2D vector of Data pointers.
	 */
std::vector<std::vector<Data*>> Table::getTable() const
{
	return this->data;
}

/**
	 * @brief Retrieves the maximum number of rows in the table.
	 * @return The maximum number of rows.
	 */
int Table::getMaxRows() const
{
	return this->maxRows;
}

/**
	 * @brief Retrieves the maximum number of columns in the table.
	 * @return The maximum number of columns.
	 */
int Table::getMaxCols() const
{
	return this->maxCols;
}

/**
	 * @brief Edits the value of a cell in the table.
	 * @param row The row index of the cell.
	 * @param col The column index of the cell.
	 * @param value The new value for the cell.
	 */
void Table::editCell(const unsigned row, const unsigned col, const std::string& data){
	if (row > this->maxRows || col > this->maxCols) {
		std::cout << "Wrong courdinates given\n";
		return;
	}
	if (Confirmer::isNum(data)) {
		delete this->data[row][col];
		this->data[row][col] = new IntData(std::stoi(data));
	}
	else if (Confirmer::isDouble(data)) {
		delete this->data[row][col];
		this->data[row][col] = new DoubleData(std::stod(data));
	}
	else if (Confirmer::isString(data)) {
		delete this->data[row][col];
		this->data[row][col] = new StringData(data);
	}
	else if (Confirmer::isFormula1(data)) {
		delete this->data[row][col];
		std::vector<int> rows;
		std::vector<int> cols;
		std::string op = "";
		Confirmer::extractData1(data, rows, op, cols);
		this->data[row][col] = new FormulaData(cols[0], rows[0], cols[1], rows[1], op);
	}
	else if (Confirmer::isFormula2(data)) {
		delete this->data[row][col];
		double dval1 = 0;
		double dval2 = 0;
		std::string op = "";
		Confirmer::extractData2(data, dval1, op, dval2);
		this->data[row][col] = new FormulaData(dval1, dval2, op);
	}
	else if (Confirmer::isFormula3(data)) {
		double dval3 = 0;
		int row1 = 0;
		int col1 = 0;
		std::string op = "";
		bool whosFirst = Confirmer::extractData3(data, dval3, op, row1, col1);
		this->data[row][col] = new FormulaData(dval3, row1, col1, op, whosFirst);
	}
	else {
		std::cout << "Data type was invalide" << std::endl;
	}
}

/**
	 * @brief Retrieves the singleton instance of the Table.
	 * @return Reference to the singleton Table instance.
	 */
Table& Table::getInstance() {
	static Table instance;
	return instance;
}

/**
	 * @brief Destructs the Table object.
	 * @note This destructor is private to enforce the singleton pattern.
	 */
Table::~Table() {
	this->clean();
}