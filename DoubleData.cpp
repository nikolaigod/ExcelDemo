#include "DoubleData.h"

/**
 * @brief Default constructor for DoubleData.
 * @details Initializes the value to 0.0.
 */
DoubleData::DoubleData():DoubleData(0.0) {}

/**
 * @brief Constructor for DoubleData.
 * @param val The double value to be stored.
 */
DoubleData::DoubleData(const double val):val(val) {
	this->type = DOUBLE;
}

/**
 * @brief Converts the double value to a string representation.
 * @return The string representation of the double value.
 */
std::string DoubleData::stringify() const {
	return std::to_string(this->val);
}

/**
 * @brief Converts the double value to a string representation for file output.
 * @return The string representation of the double value.
 */
std::string DoubleData::stringifyFile() const
{
	return std::to_string(this->val);
}

/**
 * @brief Retrieves the data type of the DoubleData object.
 * @return The data type of the object (DOUBLE).
 */
DataType DoubleData::getType() const {
	return this->type;
}

/**
 * @brief Retrieves the double value stored in DoubleData.
 * @return The double value.
 */
double DoubleData::getVal() const {
	return this->val;
}