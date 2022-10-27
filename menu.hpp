#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "game.hpp"
#include "files.hpp"

class Menu{
private:
   File f;
   int p_choice;
   char p_option;

   void i_menu(); // 'i' -> intro;
   void options(int);
   void start_game();
   void words();
public:
   Menu();
};

Menu::Menu(){
   i_menu();
}

void Menu::i_menu(){
   do{
      system("clear");
      std::cout << "=-=-=-= Hang Man =-=-=-=\n";
      std::cout << "0. Quit\n";
      std::cout << "1. Start\n";
      std::cout << "2. Words\n";
      std::cout << "-> ";
      std::cin >> p_choice;

      options(p_choice);

   }while(p_choice);
}

void Menu::options(int p){
   switch(p){
   case 0:
      std::cout << "Quitting...\n";
      exit(EXIT_SUCCESS);
      break;
   case 1:
      start_game();
      break;
   case 2:
      words();
      break;
   default:
      std::cout << "There is no such option. Press enter to continue...";
      std::cin.ignore().get();
      break;
   }
}

void Menu::start_game(){
   Game g;
}

void Menu::words(){
   do{
      system("clear");
      f.readWordFile();

      std::cout << "List of words: \n";
      f.showWordList();

      std::cout << "\nDo you want to add a word in the file? [Y/N]: ";
      std::cin >> p_option;
      if(p_option == 'y' || p_option == 'Y'){
         f.addWordToFile();
      }
      f.clearWordList();
   }while(p_option == 'y' || p_option== 'Y');
}

#endif // MENU_H_INCLUDED
