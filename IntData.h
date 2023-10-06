#pragma once
#include "Data.h"

/**
 * @class IntData
 * @brief Represents a data object of type integer.
 */
class IntData : public Data {
public:
	/**
	 * @brief Constructs an empty IntData object with a default value of 0.
	 */
	IntData();

	/**
	 * @brief Constructs an IntData object with the specified value.
	 * @param value The value of the IntData object.
	 */
	IntData(const int value);

	/**
	 * @brief Converts the IntData object to a string representation.
	 * @return A string representation of the IntData object.
	 */
	virtual std::string stringify() const override;

	/**
	 * @brief Converts the IntData object to a string representation for file output.
	 * @return A string representation of the IntData object for file output.
	 */
	virtual std::string stringifyFile() const override;

	/**
	 * @brief Retrieves the data type of the IntData object.
	 * @return The data type of the IntData object (DataType::INT).
	 */
	virtual DataType getType() const override;

	/**
	 * @brief Retrieves the value of the IntData object.
	 * @return The value of the IntData object.
	 */
	int getVal() const;

	/**
	 * @brief Destructs the IntData object.
	 */
	~IntData() override {}

private:
	int val; /**< The value of the IntData object. */
};