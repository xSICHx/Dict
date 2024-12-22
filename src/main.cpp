#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cctype>

using namespace std;


unordered_set<string> readDict(const string& filename, const char& separator){
    ifstream file(filename);
    if (!file.is_open()){
        throw ios_base::failure("Error: Unable to open file.");
    }

    unordered_set<string> result;
    string line;

    while(getline(file, line, separator)){
        result.insert(line);
    }

    return result;
}


string findSameWord(string& word, unordered_set<string>& dict){
    string checkWord;
    
    if (word.size() <= 1)
        return "";

    // �������� �����
    for (size_t pos = 0; pos < word.size(); ++pos)
    {
        checkWord = word;
        checkWord.erase(pos, 1);
        if (dict.find(checkWord) != dict.end()){
            return checkWord;
        }
        // cout << checkWord << endl;
    }

    // ���������� �����
    for (char letter = 'a'; letter <= 'z'; ++letter){
        for (size_t pos = 0; pos <= word.size(); ++pos) {
            checkWord = word;
            checkWord.insert(pos, 1, letter);
            if (dict.find(checkWord) != dict.end()){
                return checkWord;
            }
            // cout << checkWord << endl;
        }
    }

    // ������ �����
    for (char letter = 'a'; letter <= 'z'; ++letter){
        for (size_t pos = 0; pos < word.size(); ++pos) {
            checkWord = word;
            checkWord.replace(pos, 1, 1, letter);
            if (dict.find(checkWord) != dict.end()){
                return checkWord;
            }
            // cout << checkWord << endl;
        }
    }

    return "";
}


void handleWord(string& word, unordered_set<string>& dict){
    string lowercasedWord = word;
    transform(lowercasedWord.begin(), lowercasedWord.end(), lowercasedWord.begin(), 
        [](char c){ return tolower(c); }
    );


    // ���� ���� ����� � �������
    if (dict.find(lowercasedWord) != dict.end())
        return;

    string sameWord = findSameWord(lowercasedWord, dict);

    // ��������� ������ ������������
    int choice;
    string input;

    cout << "What would you like to do with the word " << word <<":\n" 
        << "1. Ignore;\n" 
        << "2. Add to dictionary\n";
    if (!sameWord.empty()){
        cout << "3. Replace with a similar one: " << sameWord << ".\n";
    }
    cout << "Enter a single digit.\n";
    cin >> input;

    // ���������, �������� �� ���� ������ � ��������� �� �� � ��������� 1-3
    if (input.length() == 1 && input[0] >= '1' && input[0] <= '3') {
        choice = input[0] - '0';
    } else {
        choice = 1; // ���� ���� ������������, �������� ������� 1
    }
    if (sameWord.empty() and choice == 3) // ��������, ����� ��� ��������, �� ������� 3
        choice = 1;

    
    switch (choice) {
        case 2:
            dict.insert(lowercasedWord);
            break;
        case 3:
            if (isupper(word[0])){ // ���� ������ ���������
                sameWord[0] = toupper(sameWord[0]);
            }
            word = sameWord;
            break;
    }
}



// ��������� � ������������ ������ �����, ��� ��������� ������� � ���� out.txt
void readText(const string& inFilename, const string& outFilename, unordered_set<string>& dict){
    ifstream inFile(inFilename);
    if (!inFile.is_open()){
        throw ios_base::failure("Error: Unable to open input file.");
    }

    ofstream outfile(outFilename);
    if (!outfile.is_open()) {
        throw ios_base::failure("Error: Unable to open output file.");
    }

    string word;
    char c;

    while(inFile.get(c)){
        if (isalpha(c)){
            word += c;
        }
        else{
            if (!word.empty()){
                handleWord(word, dict);
                outfile << word;
                
                word.clear();
            }
            outfile << c;
        }
    }
}


// ������� �������� �� src/words.txt, ���������� ����� �� ����� ������������ � ������� ��������� � src/out.txt
int main(int argc, char *argv[])
{
    unordered_set<string> dict = readDict("src/words.txt", '\n');
    
    readText("src/text.txt", "src/out.txt", dict);

    return 0;
}
