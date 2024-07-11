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
};

void initialize(char* argv[], vector<File>& files) {
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return;
    }
    
    string filename;
    while (infile >> filename) {
        files.emplace_back(filename); 
    }
    infile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <Filename>" << endl;
        return 1;
    }

    vector<File> files;
    initialize(argv, files);

    if (files.empty()) {
        cout << "No entries found in the file." << endl;
    } else {
        for (const auto& file : files) {
            cout << file.contentrow() << endl;
        }
    }

    return 0;
}
