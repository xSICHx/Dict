#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
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


vector<string> findSameWords(string& word, unordered_set<string>& dict){
    string checkWord;
    unordered_set<string> result;
    
    if (word.size() <= 1)
        return vector<string>(result.begin(), result.end());

    // удаление буквы
    for (size_t pos = 0; pos < word.size(); ++pos)
    {
        checkWord = word;
        checkWord.erase(pos, 1);
        if (dict.find(checkWord) != dict.end()){
            // cout << "delete pos " << pos << endl;
            result.insert(checkWord);
            // result.push_back(checkWord);
        }
        // cout << checkWord << endl;
    }

    // добавление буквы
    for (char letter = 'a'; letter <= 'z'; ++letter){
        for (size_t pos = 0; pos <= word.size(); ++pos) {
            checkWord = word;
            checkWord.insert(pos, 1, letter);
            if (dict.find(checkWord) != dict.end()){
                // cout << "add pos " << pos << " letter " << letter << endl;
                result.insert(checkWord);
                // result.push_back(checkWord);
            }
            // cout << checkWord << endl;
        }
    }

    // замена буквы
    for (char letter = 'a'; letter <= 'z'; ++letter){
        for (size_t pos = 0; pos < word.size(); ++pos) {
            checkWord = word;
            checkWord.replace(pos, 1, 1, letter);
            if (dict.find(checkWord) != dict.end()){
                // cout << "change pos " << pos << " letter " << letter << endl;
                result.insert(checkWord);
                // result.push_back(checkWord);
            }
            // cout << checkWord << endl;
        }
    }

    return vector<string>(result.begin(), result.end());
}


void handleWord(string& word, unordered_set<string>& dict){
    string lowercasedWord = word;
    transform(lowercasedWord.begin(), lowercasedWord.end(), lowercasedWord.begin(), 
        [](char c){ return tolower(c); }
    );


    // если есть слово в словаре
    if (dict.find(lowercasedWord) != dict.end())
        return;

    vector<string> sameWords = findSameWords(lowercasedWord, dict);

    // Обработка ответа пользователя
    int choice;
    string input;

    cout << "What would you like to do with the word " << word <<":\n" 
        << "1. Ignore;\n" 
        << "2. Add to dictionary\n";
    if (!sameWords.empty()){
        for (size_t i = 0; i < sameWords.size(); i++)
        {
            cout << to_string(i+3) + ". Replace with a similar one: " << sameWords[i] << ".\n";
        }
    }
    cout << "Enter a single number.\n";
    cin >> input;

    // Проверяем, является ли ввод числом и находится ли он в нужном диапазоне
    istringstream iss(input);
    if (!(iss >> choice) || choice < 0 || choice > (sameWords.size()+2)) {
        // Если строка не является числом или число вне диапазона, устанавливаем его в 1
        choice = 1;
    }
    
    
    switch (choice) {
        case 1:
            break;
        case 2:
            dict.insert(lowercasedWord);
            break;
        default:
            string sameWord = sameWords[choice-3];
            if (isupper(word[0])){ // если первая заглавная
                sameWord[0] = toupper(sameWord[0]);
            }
            word = sameWord;
            break;
    }
}



// Считывает и обрабатывает только слова, все остальное выводит в файл out.txt
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


// Считает словарик из src/words.txt, обработает текст по вводу пользователя и запишет результат в src/out.txt
int main(int argc, char *argv[])
{
    unordered_set<string> dict = readDict("src/words.txt", '\n');
    
    readText("src/text.txt", "src/out.txt", dict);

    return 0;
}
