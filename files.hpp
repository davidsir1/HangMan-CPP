#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <vector>
#include <random>

using std::fstream;

class File{
private:
   fstream file;
   std::string line;
   std::vector<std::string> word_list;
   void verifyWordInFile(std::string);
public:

   void readWordFile();
   void addWordToFile();
   void showWordList();
   void clearWordList();
   std::string returnRandomWord();

};

std::string File::returnRandomWord(){
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> dist(0, word_list.size()-1);

   return word_list[dist(gen)];
}

void File::readWordFile(){
   file.open("words.txt", fstream::in);

   if(!file.is_open()){
      std::cout << "This file doesn't exist!\n";
   }else{
      while(getline(file, line)){
         word_list.push_back(line);
      }

      file.close();
   }
}

void File::addWordToFile(){
   std::string u_word;
   std::cout << "Type a word: ";
   std::cin >> u_word;

   verifyWordInFile(u_word);
}

// Checks to see if this word is already present in the file
void File::verifyWordInFile(std::string t_word){
   file.open("words.txt", fstream::in);

   if(!file.is_open()){
      std::cout << "This file doesn't exist!\n";
   }else{
      while(getline(file, line)){
         if(line == t_word){
            std::cout << "That word already exists. Type another one: ";
            std::cin >> t_word;
         }
      }
      file.close();
   }
   file.open("words.txt", fstream::out | fstream::app);
   file << '\n' << t_word;
   file.close();

}

void File::showWordList(){
   for(auto i = word_list.begin(); i<word_list.end(); i++){
      std::cout << *i << '\n';
   }
}

void File::clearWordList(){
   word_list.clear();
}

#endif // FILES_H
