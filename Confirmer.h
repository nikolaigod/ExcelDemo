#pragma once
#include <string>
#include "Data.h"
#include <vector>
#include "Table.h"

/**
 * @class Confirmer
 * @brief Provides utility functions for confirming data types and performing data extractions.
 */
class Confirmer {
public:
    /**
     * @brief Checks if a string represents an integer number.
     * @param str The string to check.
     * @return `true` if the string is a valid integer, `false` otherwise.
     */
    static bool isNum(const std::string& str);

    /**
     * @brief Checks if a string represents a double number.
     * @param str The string to check.
     * @return `true` if the string is a valid double, `false` otherwise.
     */
    static bool isDouble(const std::string& str);

    /**
     * @brief Checks if a string represents a string data type.
     * @param str The string to check.
     * @return `true` if the string represents a string, `false` otherwise.
     */
    static bool isString(const std::string& str);

    /**
     * @brief Checks if a string represents formula type 1.
     * @param str The string to check.
     * @return `true` if the string represents formula type 1, `false` otherwise.
     */
    static bool isFormula1(const std::string& str);

    /**
     * @brief Checks if a string represents formula type 2.
     * @param str The string to check.
     * @return `true` if the string represents formula type 2, `false` otherwise.
     */
    static bool isFormula2(const std::string& str);

    /**
     * @brief Checks if a string represents formula type 3.
     * @param str The string to check.
     * @return `true` if the string represents formula type 3, `false` otherwise.
     */
    static bool isFormula3(const std::string& str);

    /**
     * @brief Returns the biggest data value among the specified number of values.
     * @param count The number of values to compare.
     * @return The biggest data value.
     */
    static int biggestData(const int count);

    /**
     * @brief Extracts data from a formula of type 1.
     * @param formula The formula string.
     * @param row The extracted row values.
     * @param op The extracted operator.
     * @param col The extracted column values.
     */
    static void extractData1(const std::string& formula, std::vector<int>& row, std::string& op, std::vector<int>& col);

    /**
     * @brief Extracts data from a formula of type 2.
     * @param formula The formula string.
     * @param dval1 The extracted first double value.
     * @param op The extracted operator.
     * @param dval2 The extracted second double value.
     */
    static void extractData2(const std::string& formula, double& dval1, std::string& op, double& dval2);

    /**
     * @brief Extracts data from a formula of type 3.
     * @param formula The formula string.
     * @param dval3 The extracted double value.
     * @param op The extracted operator.
     * @param row The extracted row value.
     * @param col The extracted column value.
     * @return `true` if the extraction was successful, `false` otherwise.
     */
    static bool extractData3(const std::string& formula, double& dval3, std::string& op, int& row, int& col);

    /**
     * @brief Checks if a character represents an arithmetic operator.
     * @param c The character to check.
     * @return `true` if the character is an arithmetic operator, `false` otherwise.
     */
    static bool isArithmetic(const char c);

    /**
     * @brief Checks if a character represents a comparison operator.
     * @param c The character to check.
     * @return `true` if the character is a comparison operator, `false` otherwise.
     */
    static bool isComparing(const char c);

    /**
     * @brief Returns the maximum number of cols in a string.
     * @param str The string to analyze.
     * @return The maximum number of tokens.
     */
    static int maxTokens(const std::string& str);

    /**
     * @brief Returns the maximum number of rows in a string.
     * @param str The string to analyze.
     * @return The maximum number of rows.
     */
    static int maxRows(const std::string& str);
};