#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class File {
private:
    string content;
public:
    File(string content = "") : content(content) {}
    string contentrow() const {
        return content;
    }
    void setContent(const string& newContent) {
        content = newContent;
    }
};

void initialize(const string& filename, vector<File>& files, bool editMode) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        if (editMode) {
            cout << "Creating a new file: " << filename << endl;
            files.emplace_back("");
        }
        return;
    }

    string line;
    while (getline(infile, line)) {
        files.emplace_back(line);
    }
    infile.close();

    if (editMode) {
        string newContent, inputLine;
        int emptyLineCount = 0;
        cout << "Enter new content for the first file (press enter twice to finish):" << endl;

        cin.ignore();
        while (true) {
            getline(cin, inputLine);
            if (inputLine.empty()) {
                emptyLineCount++;
                if (emptyLineCount == 2) {
                    break;
                }
            } else {
                emptyLineCount = 0;
            }
            newContent += inputLine + "\n";
        }

        if (!files.empty()) {
            files[0].setContent(newContent);
        } else {
            files.emplace_back(newContent);
        }

        ofstream outfile(filename, ios::out | ios::trunc);
        if (!outfile) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }
        for (const auto& file : files) {
            outfile << file.contentrow();
        }
        outfile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <Filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    int choice = 0;
    
    cout << "Enter 1 for read, 2 for edit: ";
    cin >> choice;
    if (choice != 1 && choice != 2) {
        cerr << "Invalid choice. Use 1 for read, 2 for edit." << endl;
        return 1;
    }

    bool editMode = (choice == 2);

    vector<File> files;
    initialize(filename, files, editMode);

    if (files.empty() && !editMode) {
        cout << "No entries found in the file." << endl;
    } else {
        for (const auto& file : files) {
            cout << file.contentrow() << endl;
        }
    }

    return 0;
}