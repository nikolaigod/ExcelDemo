#pragma once
#include "Data.h"

/**
 * @class DoubleData
 * @brief Represents a data object of type double.
 */
class DoubleData : public Data {
public:
	/**
	 * @brief Constructs an empty DoubleData object with a default value of 0.0.
	 */
	DoubleData();

	/**
	 * @brief Constructs a DoubleData object with the specified value.
	 * @param value The value of the DoubleData object.
	 */
	DoubleData(const double value);

	/**
	 * @brief Converts the DoubleData object to a string representation.
	 * @return A string representation of the DoubleData object.
	 */
	virtual std::string stringify() const override;

	/**
	 * @brief Converts the DoubleData object to a string representation for file output.
	 * @return A string representation of the DoubleData object for file output.
	 */
	virtual std::string stringifyFile() const override;

	/**
	 * @brief Retrieves the data type of the DoubleData object.
	 * @return The data type of the DoubleData object (DataType::DOUBLE).
	 */
	virtual DataType getType() const override;

	/**
	 * @brief Retrieves the value of the DoubleData object.
	 * @return The value of the DoubleData object.
	 */
	double getVal() const;

	/**
	 * @brief Destructs the DoubleData object.
	 */
	~DoubleData() override {}

private:
	double val; /**< The value of the DoubleData object. */
};