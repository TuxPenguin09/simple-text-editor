#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class File {
private:
    string content;
    int size;
public:
    File(string content, int size = 0) {
        this->content = content;
        this->size = size;
    }
    string contentrow() const {
        return content;
    }
    int getSize() const {
        return size;
    }
    void setContent(const string& newContent) {
        content = newContent;
    }
};

void initialize(char* argv[], vector<File>& files, bool editMode) {
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        files.emplace_back(line);
    }
    infile.close();

    if (editMode && !files.empty()) {
        string newContent, inputLine;
        int emptyLineCount = 0;
        cout << "Enter new content for the first file (press enter twice to finish):" << endl;

        while (true) {
            getline(cin, inputLine);
            if (inputLine.empty()) {
                emptyLineCount++;
                if (emptyLineCount == 2) {
                    break;
                }
            } else {
                emptyLineCount = 0; // reset if a non-empty line is entered
            }
            newContent += inputLine + "\n";
        }

        files[0].setContent(newContent);

        ofstream outfile(argv[1], ios::out | ios::trunc);
        if (!outfile) {
            cerr << "Error opening file for writing: " << argv[1] << endl;
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
        cerr << "Usage: " << argv[0] << " <Filename> [--edit]" << endl;
        return 1;
    }

    bool editMode = (argc > 2 && string(argv[2]) == "--edit");

    vector<File> files;
    initialize(argv, files, editMode);

    if (files.empty()) {
        cout << "No entries found in the file." << endl;
    } else {
        for (const auto& file : files) {
            cout << file.contentrow() << endl;
        }
    }

    return 0;
}
