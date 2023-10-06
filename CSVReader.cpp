#include"CSVReader.h"

/**
 * @brief Constructs a CSVReader object with the given filename and maximum token size.
 *
 * The constructor opens the specified CSV file and initializes the `maxTokens` member variable
 * with the provided maximum token size.
 *
 * @param filename The name of the CSV file to open.
 * @param maxSize The maximum size of tokens in the CSV file.
 *
 * @throws std::ifstream::failure If the file fails to open.
 */
CSVReader::CSVReader(const std::string& filename, int maxSize) : maxTokens(maxSize) {
    try {
        in.open(filename);
        if (!in.is_open()) {
            throw std::ifstream::failure("File didnt open");
        }
    }
    catch (const std::ifstream::failure& e) {
        std::cout << e.what();
    }
}

/**
 * @brief Checks if there is more data available to be read from the CSV file.
 *
 * The method checks the status of the input stream and returns a boolean value indicating
 * whether there is more data available to be read from the CSV file.
 *
 * @return True if there is more data available, False otherwise.
 */
bool CSVReader::has_more_data() const{
    return in.good();
}

/**
 * @brief Retrieves the tokens from the current line of the CSV file.
 *
 * The method reads a line from the CSV file and extracts the tokens separated by commas.
 * It handles cases where tokens may be enclosed in double quotes and ignores leading and trailing spaces.
 * If the number of tokens in the line is less than the maximum number of tokens specified during object initialization,
 * the remaining tokens are filled with empty strings.
 *
 * @return A vector of strings representing the tokens in the current line of the CSV file.
 */
std::vector<std::string> CSVReader::get_tokens(){
    std::vector<std::string> tokens;
    std::string line;
    if (std::getline(in, line)) {
        size_t i = 0;
        while (i < line.size()) {
            std::string token = "";
            bool inText = false;
            bool commaInside = false;
            while (i < line.size() && line[i] != ',') {
                if (inText) {
                    token += line[i];
                }
                else {
                    if (line[i] != ' ') {
                        token += line[i];
                    }
                }
                if ((line[i] == '"' && i == 0) || (line[i] == '"' && line[i - 1] != '\\')) {
                    inText ? inText = false : inText = true;
                }
                i++;
            }
            tokens.push_back(token);
            i++;
        }
    }
    if (tokens.size() < this->maxTokens) {
        while (tokens.size() < this->maxTokens) {
            tokens.push_back("");
        }
    }
    return tokens;
}

/**
 * @brief Destructor for the CSVReader class.
 *
 * The destructor closes the input file stream associated with the CSVReader object.
 */
CSVReader::~CSVReader() {
    this->in.close();
}