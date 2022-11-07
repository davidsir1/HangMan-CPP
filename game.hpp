#ifndef GAME_H
#define GAME_H

#include "files.hpp"
#include <vector>

class Game{
private:
   File f;
   std::vector<char> letters;
   std::string word, convertedWord;
   int attempt;
   char p_letter;
   char hangMan[7][9] = {{'+','-','-','-','-','-','-','+',' '},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'+','=','=','=','=','=','=','+',' '}};


public:
   Game();
   void game();
   void drawHangMan();
   void drawStick(int);
   bool verifyRepeatedLetter(char);
   bool is_correctAnswer(char);
   std::string convertCharToString(char*);

};

void Game::game(){
   char h_word[word.size()];
   for(int i = 0; i<word.size(); i++){
      h_word[i] = '_';
   }

   do{
      system("clear");
      drawHangMan();
//      std::cout << "Word: ";
//      for(auto i = 0; i<word.length(); i++){
//         std::cout << h_word[i];
//      }
      std::cout << "Word: " << convertCharToString(h_word);
      std::cout << '\n';

      std::cout << "Letters: ";
      for(auto i = letters.begin(); i<letters.end(); i++){
         std::cout << *i << ' ';
      }
      std::cout << '\n';

      std::cout << "Type a letter: ";
      std::cin >> p_letter;
      if(verifyRepeatedLetter(p_letter)){
         while(verifyRepeatedLetter(p_letter)){
            std::cout << "You have already entered this letter! Type another one: ";
            std::cin >> p_letter;
         }
      }else{
         letters.push_back(p_letter);
      }

      if(!is_correctAnswer(p_letter)){
         attempt+=1;
         drawStick(attempt);
      }else{
         for(int i = 0; i<word.size(); i++){
            if(word[i] == p_letter){
               h_word[i] = p_letter;
            }
         }
         convertedWord = convertCharToString(h_word);
      }

   }while(attempt < 7 && convertedWord != word);

   if(attempt == 7){
      system("clear");
      drawHangMan();
      std::cout << "You lost!\n";
      std::cout << "Hidden word: " << word << '\n';
      std::cout << "Press enter to continue...";
      std::cin.ignore().get();
   }else{
      system("clear");
      drawHangMan();
      std::cout << "You win!\n";
      std::cout << "Hidden word: " << word << '\n';
      std::cout << "Press enter to continue...";
      std::cin.ignore().get();
   }
}

std::string Game::convertCharToString(char* c){
   std::string s = "";
   for(int i = 0; i<word.size(); i++){
      s+=c[i];
   }
   return s;
}

bool Game::is_correctAnswer(char letter){
   int count_letters = 0;

   for(int i = 0; i<word.size(); i++){
      if(word[i] == p_letter){
         count_letters++;
      }
   }

   if(count_letters != 0){
      return true;
   }else{
      return false;
   }

}

bool Game::verifyRepeatedLetter(char letter){
   for(int i = 0; i<letters.size(); i++){
      if(letters[i] == letter){
         return true;
      }
   }
   return false;
}

void Game::drawHangMan(){
   for(int i = 0; i<7; i++){
      for(int j = 0; j<9; j++){
         std::cout << hangMan[i][j];
      }
      std::cout << '\n';
   }
}

// Function that will add parts of Stickman if the player gets the lyrics wrong
void Game::drawStick(int a){
   switch(a){
      case 1:
         hangMan[1][7] = '|';
         break;
       case 2:
         hangMan[2][7] = 'O';
         break;
       case 3:
         hangMan[3][7] = '|';
         break;
       case 4:
         hangMan[3][6] = '/';
         break;
       case 5:
         hangMan[3][8] = '\\';
         break;
       case 6:
         hangMan[4][6] = '/';
         break;
       case 7:
         hangMan[4][8] = '\\';
         break;
       default:
         return;
   }
}

Game::Game(){
   f.readWordFile();
   word = f.returnRandomWord();
   attempt = 0;

   game();
}

#endif // GAME_H
