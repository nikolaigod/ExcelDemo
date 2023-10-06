#pragma once
#include "Data.h"
#include "Table.h"

/**
 * @class FormulaData
 * @brief Represents a data object of type formula.
 */
class FormulaData : public Data {
public:
	/**
	 * @brief Constructs an empty FormulaData object.
	 */
	FormulaData();

	/**
	 * @brief Constructs a FormulaData object with two row/column coordinates and an operation string.
	 * @param row1 The row coordinate of the first operand.
	 * @param col1 The column coordinate of the first operand.
	 * @param row2 The row coordinate of the second operand.
	 * @param col2 The column coordinate of the second operand.
	 * @param operation The operation string.
	 */
	FormulaData(const int row1, const int col1, const int row2, const int col2, const std::string& operation);

	/**
	 * @brief Constructs a FormulaData object with two double values and an operation string.
	 * @param dval1 The first double value.
	 * @param dval2 The second double value.
	 * @param operation The operation string.
	 */
	FormulaData(const double dval1, const double dval2, const std::string& operation);

	/**
	 * @brief Constructs a FormulaData object with a double value, row/column coordinates, an operation string, and flags.
	 * @param dval1 The double value.
	 * @param row1 The row coordinate.
	 * @param col1 The column coordinate.
	 * @param operation The operation string.
	 * @param digits Flag indicating if the formula contains digit placeholders.
	 * @param courdinates Flag indicating if the formula contains row/column placeholders.
	 * @param mixed Flag indicating if the formula contains a mix of digits and placeholders.
	 * @param whosFirst Flag indicating if the formula starts with row/column placeholders.
	 */
	FormulaData(const double dval1, const int row1, const int col1, std::string& operation, bool whosFirst);

	/**
	 * @brief Converts the FormulaData object to a string representation.
	 * @return A string representation of the FormulaData object.
	 */
	virtual std::string stringify() const override;

	/**
	 * @brief Converts the FormulaData object to a string representation for file output.
	 * @return A string representation of the FormulaData object for file output.
	 */
	virtual std::string stringifyFile() const override;

	/**
	 * @brief Retrieves the data type of the FormulaData object.
	 * @return The data type of the FormulaData object (DataType::FORMULA).
	 */
	virtual DataType getType() const override;

	/**
	 * @brief Destructs the FormulaData object.
	 */
	~FormulaData() override {}

private:
	double dval1; /**< The first double value of the formula. */
	double dval2; /**< The second double value of the formula. */
	double dval3; /**< The third double value of the formula. */
	int row1; /**< The row coordinate of the first operand. */
	int col1; /**< The column coordinate of the first operand. */
	int row2; /**< The row coordinate of the second operand. */
	int col2; /**< The column coordinate of the second operand. */
	std::string operation; /**< The operation string. */
	bool digits; /**< Flag indicating if the formula contains digit placeholders. */
	bool courdinates; /**< Flag indicating if the formula contains row/column placeholders. */
	bool mixed; /**< Flag indicating if the formula contains a mix of digits and placeholders. */
	bool whosFirst; /**< Flag indicating if the formula starts with row/column placeholders. */
};