#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * @class CSVReader
 * @brief Reads and parses data from a CSV file.
 */
class CSVReader {
public:
    /**
     * @brief Constructs a CSVReader object.
     * @param filename The name of the CSV file to read.
     * @param maxTokens The maximum number of tokens row has.
     */
    CSVReader(const std::string& filename, const int maxTokens);

    /**
     * @brief Checks if there is more data to be read from the CSV file.
     * @return `true` if there is more data, `false` otherwise.
     */
    bool has_more_data() const;

    /**
     * @brief Retrieves the tokens of the next line from the CSV file.
     * @return A vector of strings representing the tokens in the line.
     */
    std::vector<std::string> get_tokens();

    /**
     * @brief Destructs the CSVReader object.
     */
    ~CSVReader();

private:
    std::ifstream in; /**< The input file stream used for reading the CSV file. */
    size_t maxTokens; /**< The maximum number of tokens to parse per line. */
};