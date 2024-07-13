#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Function to create a new file
bool createFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to create the file. Please check the permissions." << endl;
        return false;
    }
    file.close();
    cout << "File created successfully." << endl;
    return true;
}

// Function to delete a file
bool deleteFile(const string& filename) {
    if (fs::remove(filename)) {
        cout << "File deleted successfully." << endl;
        return true;
    } else {
        cout << "Unable to delete the file. Please check the file exists and you have the necessary permissions." << endl;
        return false;
    }
}

int main() {
    string filename, content;
    char choice;

    // Get the filename from the user
    cout << "Enter the filename: ";
    getline(cin, filename);

    // Open the file
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "File not found. Would you like to create a new file? (y/n) ";
        cin >> choice;
        if (tolower(choice) == 'y') {
            if (createFile(filename)) {
                // Open the file again
                file.open(filename);
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    }

    // Read the contents of the file
    string line;
    while (getline(file, line)) {
        content += line + "\n";
    }

    // Close the file
    file.close();

    // Display the contents of the file
    cout << "Current content of the file:\n" << content << endl;

    // Allow the user to edit the content
    cout << "Do you want to edit the content? (y/n) ";
    cin >> choice;

    if (tolower(choice) == 'y') {
        // Get the new content from the user
        cout << "Enter the new content (press Ctrl+D to finish):\n";
        getline(cin, content, '\x04');

        // Open the file for writing
        ofstream outFile(filename);

        // Check if the file was opened successfully
        if (!outFile.is_open()) {
            cout << "Unable to open the file for writing. Please check the permissions." << endl;
            return 1;
        }

        // Write the new content to the file
        outFile << content;

        // Close the file
        outFile.close();

        cout << "File saved successfully." << endl;
    } else {
        cout << "No changes made." << endl;
    }

    // Allow the user to delete the file
    cout << "Do you want to delete the file? (y/n) ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        if (deleteFile(filename)) {
            cout << "File deleted successfully." << endl;
        } else {
            cout << "Failed to delete the file." << endl;
        }
    }

    return 0;
}