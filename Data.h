#pragma once
#include <iostream>
#include <string>

/**
 * @enum DataType
 * @brief Represents the possible data types.
 */
enum DataType {
	INT, /**< Integer data type. */
	DOUBLE, /**< Double data type. */
	STRING, /**< String data type. */
	FORMULA /**< Formula data type. */
};

/**
 * @class Data
 * @brief Represents an abstract data object.
 */
class Data {
public:
	Data() {};
	/**
	 * @brief Converts the data object to a string representation.
	 * @return A string representation of the data.
	 */
	virtual std::string stringify() const = 0;

	/**
	 * @brief Converts the data object to a string representation for file output.
	 * @return A string representation of the data for file output.
	 */
	virtual std::string stringifyFile() const = 0;

	/**
	 * @brief Retrieves the data type of the object.
	 * @return The data type of the object.
	 */
	virtual DataType getType() const = 0;

	/**
	 * @brief Destructs the Data object.
	 */
	virtual ~Data() {};

protected:
	DataType type; /**< The data type of the object. */
};