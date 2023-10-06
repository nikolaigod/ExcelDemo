#include <iostream>
#include "Table.h"

/**
 * @brief Opens the table.
 * @note This function retrieves the singleton instance of the Table class without performing any specific operations.
 */
void open() {
    Table::getInstance();
}

/**
 * @brief Saves the table to the default file path and displays a success message.
 */
void save() {
    Table::getInstance().save();
    std::cout << "Table successfuly saved\n";
}

/**
 * @brief Saves the table to a specified file path after validating the file extension.
 * @note This function prompts the user to enter a file path and ensures that the extension is ".txt".
 * If the file extension is incorrect, the user is prompted to enter a valid file path.
 * After a valid file path is entered, the table is saved to that location, and a success message is displayed.
 */
void saveAs() {
    std::cout << "Enter file path to save the file in: ";
    std::string filepath;
    while (true) {
        std::cin >> filepath;
        int size = filepath.size();
        if (filepath[size - 1] != 't' || filepath[size - 2] != 'x' || filepath[size - 3] != 't') {
            std::cout << "Wrong file extension, enter again\n";
        }
        else break;
    }
    Table::getInstance().saveAs(filepath);
    std::cout << "Table successfuly saved\n";
}


/**
 * @brief The main function that serves as the entry point of the program.
 * @return An integer representing the exit status of the program.
 */
int main()
{
    int choice = 0;
    int choice2 = 0;
    unsigned row, col;
    std::string data;
    bool opened = false;

    while (true) {
        std::cout << "Choose a command:" << std::endl;
        std::cout << "1. Open" << std::endl;
        std::cout << "2. Save As" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "4. Save" << std::endl;
        std::cout << "5. Edit Cell" << std::endl;
        std::cout << "6. Print" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (opened) {
                continue;
            }
            open();
            break;
        case 2:
            saveAs();
            break;
        case 3:
            std::cout << "Do you want to save before you exit? 1.yes/2.no/3.saveAs";
            std::cin >> choice2;
            if (choice2 == 1) {
                save();
            }
            else if (choice2 == 3) {
                saveAs();
            }
            return 0;
        case 4:
            save();
            break;
        case 5:
            std::cout << "Enter the row: ";
            std::cin >> row;
            std::cout << "Enter the column: ";
            std::cin >> col;
            std::cout << "Enter the data: ";
            std::cin.ignore();
            std::getline(std::cin, data);
            Table::getInstance().editCell(row, col, data);
            break;
        case 6:
            Table::getInstance().print();
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }

        std::cout << std::endl;
    }
}


