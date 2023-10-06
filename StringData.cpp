#include "StringData.h"

/**
 * @brief Default constructor for StringData.
 * @details Initializes the value to an empty string.
 */
StringData::StringData() : StringData("") {}

/**
 * @brief Constructor for StringData.
 * @param val The string value to be stored.
 */
StringData::StringData(const std::string& val) :val(val) {
	this->type = STRING;
}

/**
 * @brief Converts the string value to a string representation.
 * @return The string value itself.
 */
std::string StringData::stringify() const {
	return this->val;
}

/**
 * @brief Converts the string value to a string representation for file output.
 * @return The string value surrounded by double quotes, with proper escaping if needed.
 */
std::string StringData::stringifyFile() const
{
	std::string tmp = "\"";
	if (this->val.empty()) {
		return this->val;
	}
	else if (this->val[0] == '\"') {
		tmp += '\\';
		tmp += this->val.substr(0, this->val.size() - 1);
		tmp += '\\';
		tmp += "\"";
		tmp += "\"";
	}
	else {
		tmp += this->val;
		tmp += "\"";
	}
	return tmp;
}

/**
 * @brief Retrieves the data type of the StringData object.
 * @return The data type of the object (STRING).
 */
DataType StringData::getType() const {
	return this->type;
}

/**
 * @brief Retrieves the string value stored in StringData.
 * @return The string value.
 */
std::string StringData::getVal() const {
	return this->val;
}