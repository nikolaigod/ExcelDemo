#pragma once
#include <vector>
#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Confirmer.h"
#include "IntData.h"
#include "DoubleData.h"
#include "StringData.h"
#include "FormulaData.h"
#include "CSVReader.h"
#include<stdexcept>
#include<exception>

/**
 * @class Table
 * @brief Represents a table of data.
 */
class Table {
public:
	/**
	 * @brief Retrieves the singleton instance of the Table.
	 * @return Reference to the singleton Table instance.
	 */
	static Table& getInstance();

	/**
	 * @brief Prints the table to the console.
	 */
	void print() const;

	/**
	 * @brief Saves the table to the default file path.
	 */
	void save() const;

	/**
	 * @brief Saves the table to a specified file path.
	 * @param filePath The file path to save the table to.
	 */
	void saveAs(const std::string& filePath) const;

	/**
	 * @brief Retrieves the table data.
	 * @return The table data as a 2D vector of Data pointers.
	 */
	std::vector<std::vector<Data*>> getTable() const;

	/**
	 * @brief Retrieves the maximum number of rows in the table.
	 * @return The maximum number of rows.
	 */
	int getMaxRows() const;

	/**
	 * @brief Retrieves the maximum number of columns in the table.
	 * @return The maximum number of columns.
	 */
	int getMaxCols() const;

	/**
	 * @brief Edits the value of a cell in the table.
	 * @param row The row index of the cell.
	 * @param col The column index of the cell.
	 * @param value The new value for the cell.
	 */
	void editCell(const unsigned row, const unsigned col, const std::string& value);

private:
	std::string filepath; /**< The file path of the table. */
	int maxRows; /**< The maximum number of rows in the table. */
	int maxCols; /**< The maximum number of columns in the table. */
	std::vector<std::vector<Data*>> data; /**< The data stored in the table. */

	/**
	 * @brief Cleans up the table by deleting all data objects.
	 */
	void clean();

	/**
	 * @brief Constructs the Table object.
	 * @note This constructor is private to enforce the singleton pattern.
	 */
	Table();

	Table(const Table&) = delete; /**< Disable copy constructor. */
	Table& operator=(const Table&) = delete; /**< Disable assignment operator. */

	/**
	 * @brief Destructs the Table object.
	 * @note This destructor is private to enforce the singleton pattern.
	 */
	~Table();
};