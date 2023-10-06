#include "IntData.h"

/**
 * @brief Default constructor for IntData.
 * @details Initializes the value to 0.
 */
IntData::IntData() :IntData(0) {}

/**
 * @brief Constructor for IntData.
 * @param val The integer value to be stored.
 */
IntData::IntData(const int val) : val(val) {
	this->type = INT;
}

/**
 * @brief Converts the integer value to a string representation.
 * @return The string representation of the integer value.
 */
std::string IntData::stringify() const {
	return std::to_string(this->val);
}

/**
 * @brief Converts the integer value to a string representation for file output.
 * @return The string representation of the integer value.
 */
std::string IntData::stringifyFile() const
{
	return std::to_string(this->val);
}

/**
 * @brief Retrieves the data type of the IntData object.
 * @return The data type of the object (INT).
 */
DataType IntData::getType() const {
	return this->type;
}

/**
 * @brief Retrieves the integer value stored in IntData.
 * @return The integer value.
 */
int IntData::getVal() const {
	return this->val;
}