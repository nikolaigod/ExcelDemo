#pragma once
#include"Data.h"

/**
 * @class StringData
 * @brief Represents a data object of type string.
 */
class StringData : public Data {
public:
	/**
	 * @brief Constructs an empty StringData object with an empty string value.
	 */
	StringData();

	/**
	 * @brief Constructs a StringData object with the specified string value.
	 * @param value The string value of the StringData object.
	 */
	StringData(const std::string& value);

	/**
	 * @brief Converts the StringData object to a string representation.
	 * @return A string representation of the StringData object.
	 */
	virtual std::string stringify() const override;

	/**
	 * @brief Converts the StringData object to a string representation for file output.
	 * @return A string representation of the StringData object for file output.
	 */
	virtual std::string stringifyFile() const override;

	/**
	 * @brief Retrieves the data type of the StringData object.
	 * @return The data type of the StringData object (DataType::STRING).
	 */
	virtual DataType getType() const override;

	/**
	 * @brief Retrieves the value of the StringData object.
	 * @return The value of the StringData object.
	 */
	std::string getVal() const;

	/**
	 * @brief Destructs the StringData object.
	 */
	~StringData() override {}

private:
	std::string val; /**< The string value of the StringData object. */
};