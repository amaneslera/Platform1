#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void displayMenu();
void listFiles();
void createDirectory();
void changeDirectory();

int main() {
    int choice;

    do {
        displayMenu();
        std::cout << "Enter the number: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                std::cout << "Exiting....\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    std::cout << "\n\t\t\tMain menu\n\t\t-----------------\n";
    std::cout << "1. Display List of Files\n";
    std::cout << "2. Create a new Directory\n";
    std::cout << "3. Change the Working Directory\n";
    std::cout << "4. Exit\n";
}

void listFiles() {
    int option;
    std::string extension;
    std::string name;

    std::cout << "\t\tLIST FILE DETAILS\n\t-----------------------\n";
    std::cout << "1. List All Files\n";
    std::cout << "2. List Files by Extension\n";
    std::cout << "3. List Files by Name Pattern\n";
    std::cout << "Enter the number: ";
    std::cin >> option;

    switch(option) {
        case 1:
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                std::cout << entry.path().filename().string() << "\n";
            }
            break;
        case 2:
            std::cout << "Enter the extension (e.g., .txt): ";
            std::cin >> extension;
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().extension() == extension) {
                    std::cout << entry.path().filename().string() << "\n";
                }
            }
            break;
        case 3:
            std::cout << "Enter the name pattern (e.g., file*): ";
            std::cin >> name;
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().filename().string().find(name) != std::string::npos) {
                    std::cout << entry.path().filename().string() << "\n";
                }
            }
            break;
        default:
            std::cout << "Invalid option, returning to the main menu.\n";
    }
}

void createDirectory() {
    std::string dirName;
    std::cout << "Enter directory name: ";
    std::cin >> dirName;

    if (fs::exists(dirName)) {
        std::cout << dirName << " already exists.\n";
    } else {
        if (fs::create_directory(dirName)) {
            std::cout << dirName << " directory successfully created\n";
        } else {
            std::cout << "Failed to create directory\n";
        }
    }
}

void changeDirectory() {
    int option;
    std::string newDir;

    std::cout << "\nCurrent Directory: " << fs::current_path().string() << "\n";
    std::cout << "\t\tChange Directory\n\t\t---------------------------\n";
    std::cout << "1. Step by Step Backward\n";
    std::cout << "2. Go to Root Directory\n";
    std::cout << "3. Forward Directory\n";
    std::cout << "Enter the number: ";
    std::cin >> option;

    switch (option) {
        case 1:
            fs::current_path(fs::current_path().parent_path());
            break;
        case 2:
            fs::current_path(fs::path("/"));
            break;
        case 3:
            std::cout << "Enter the directory name: ";
            std::cin >> newDir;
            if (fs::exists(newDir) && fs::is_directory(newDir)) {
                fs::current_path(newDir);
            } else {
                std::cout << "Directory does not exist.\n";
            }
            break;
        default:
            std::cout << "Invalid option, returning to the main menu.\n";
    }

    std::cout << "Current Directory: " << fs::current_path().string() << "\n";
}