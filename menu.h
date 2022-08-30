// menu.h
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include "database.h"

using namespace std;

class menu : public database{
  private:
  string filename;
  bool valid_input = false;
  bool valid_input2 = false;
  string my_input ="";
  string my_input2 = "";
  int input = 0;
  int input2 = 0;

  public:
  menu (const string& fname)
  : database(fname), filename(fname){ 
    main_menu(); 
  }

  virtual ~menu(){};

  void main_menu(){
    bool menu_valid_input = false;
    while(menu_valid_input == false){
      cout << "\nWelcome to the Movie Database!\n";
      cout << "------------------------------\n";
      cout << "(1)Add a movie.\n(2)Find a movie.\n(3)Delete a movie.";
      cout << "\n(4)List movies.\n(5)Quit.";
      cout << "\nEnter the number of your choice: ";
      int int_input;
      string line;
      cin >> std::ws;
      getline(cin, line);
      int_input = stoi(line);
      if (int_input == 1 || int_input == 2 || int_input == 3 || int_input == 4){
        choice_menu(int_input);
      }
      else if(int_input == 5){
        quit_menu();
        menu_valid_input = true;
      }else{
        cout << "Invalid input, please try again: ";
      }
    }
  }

  void add_menu(){
    string title, director_name;
    int release_date, runtime;
    double ratings;
    bool ready = false;
    while (ready == false){
      cout << "\nEnter the movie name: ";
      getline(cin, title);
      if(!cin){
        cout << "Bad value!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, title);
      }
      cout << "\nEnter its director: ";
      getline(cin, director_name);
      if(!cin){
        cout << "Bad value!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, director_name);
      }
      cout << "\nEnter its release date: ";
      cin >> release_date;
      if(!cin){
        cout << "Bad value!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> release_date;
      }
      if(release_date < 1895 || release_date > 2021){
        cout << "\nInvalid entry, please enter a valid value: ";
        cin >> release_date;
      }
      cout << "\nEnter its runtime: ";
      cin >> runtime;
      if(!cin){
        cout << "Bad value!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> runtime;
      }
      if(runtime <= 0){
        cout << "\nInvalid entry, please enter a valid value: ";
        cin >> runtime;
      } 
      cout << "\nEnter its ratings: ";
      cin >> ratings;
      if(!cin){
        cout << "Bad value!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> ratings;
      }
      if(ratings < 0.0 || ratings > 10.0){
        cout << "\nInvalid entry, please enter a valid value: ";
        cin >> ratings;
      }
      ready = true;
    }
    movie* new_movie = new movie(title, director_name, release_date, runtime, ratings);
    for (int i = 0; i < size(); i++){
      if (word_lower(get(i)->get_movie_name()) == word_lower(new_movie->get_movie_name()) 
          && word_lower(get(i)->get_director()) == word_lower(new_movie->get_director())
          && get(i)->get_release_date() == new_movie->get_release_date() ) 
      {
        cout << "\nMovie already exists in database.\n";
      }
    }
    append(new_movie);
    cout << title << " has been successfully added to the database.\n";  
  } // returns to main
     

  void find_menu(){
    cout << "Find a movie.\n"
         << "--------------\n"
         << "You can search by: \n"
         << "(1)Movie name.\n(2)Director name.\n(3)Release date.\n(4)Runtime\n"
         << "(5)Ratings.\n(6)Return to main menu.\n"
         << "Enter the number of your choice: ";

    while(valid_input == false){     
      getline(cin, my_input);
      input = stoi(my_input);
      if(input >= 1 && input <= 6){
        valid_input = true;
      }
      else{
        cout << "\nInvalid input, please try again: ";
      }
    }
    
    if(input == 1){//Search by movie name
      cout << "How would you like to search by movie name?\n"
           << "(1)Exact name.\n(2)By substring.\n(3)Return to options.\n"
           << "Enter the number of your choice: ";
      
      while(valid_input2 == false){      
        getline(cin, my_input2);
        input2 = stoi(my_input2);
        if (input2 >= 1 && input2 <= 3){
          valid_input2 = true;
        }
        else if (input2 == 0){
          cout << "\nAgain? Enter the number of your choice: ";
        }
        else{
          cout << "\nInvalid input, please try again: ";
        }
      }
      if (input2 == 1){
        string name;
        cout << "Enter the name: ";
        getline(cin, name);
        print_vec(search_string(name, 0));
      }
      else if(input2 == 2){
        string substr;
        cout << "\nEnter your substring: ";
        getline(cin, substr);
      }
      else if(input2 == 3){
        main_menu();
      }
      input2 = 0;
    }
    else if(input == 2){ // Search by director name
      cout << "How would you like to search by director name?\n"
           << "(1)Exact name.\n(2)By substring.\n(3)Return to options.\n"
           << "Enter the number of your choice: ";
      while(valid_input2 == false){      
        getline(cin, my_input2);
        input2 = stoi(my_input2);
        if (input2 >= 1 && input2 <= 3){
          valid_input2 = true;
        }
        else{
          cout << "\nInvalid input, please try again: ";
        }
      }
      if(input2 == 1){
        string name;
        cout << "Enter the name: ";
        getline(cin, name);
        print_vec(search_string(name, 1));
      }
      else if(input2 == 2){
        string substr;
        cout << "\nEnter your substring: ";
        getline(cin, substr);
      }
      else if(input2 == 3){
        main_menu();
      }
    }
    else if(input == 3){ // Search by release date
      cout << "How would you like to search by release date?\n"
           << "(1)Exact year.\n(2)By a range.\n(3)Return to options.\n"
           << "Enter the number of your choice: ";
      
      while(valid_input2 == false){      
        getline(cin, my_input2);
        input2 = stoi(my_input2);
      
        if (input2 >= 1 && input2 <= 3)
        {
          valid_input2 = true;
        }
        else
        {
          cout << "\nInvalid input, please try again: ";
        }
      }
      if(input2 == 1){
        string date;
        cout << "\nEnter the year: ";
        getline(cin, date);
        print_vec(search_int(stoi(date), 2));
      }
      else if(input2 == 2){
        string range1 = "99999", range2 = "-1";
        while(stoi(range1) > stoi(range2) && stoi(range1) >= 0){
          cout << "\nEnter your lower range: ";
          getline(cin, range1);
          cout << "\nEnter your upper range: ";
          getline(cin,range2);
        }
        print_vec(search_int_release_date_range(stoi(range1), stoi(range2)));
      }
      else if(input2 == 3){
        main_menu();
      }
    }
    else if(input == 4){ // Search by runtime
      cout << "How would you like to search by runtime?\n"
           << "(1)Exact minute.\n(2)By a range.\n(3)Return to options.\n"
           << "Enter the number of your choice: ";
      
      while(valid_input2 == false){      
        getline(cin, my_input2);
        input2 = stoi(my_input2);
        if(input2 >= 1 && input2 <= 3){
          valid_input2 = true;
        }
        else{
          cout << "\nInvalid input, please try again: ";
        }
      }
      if (input2 == 1){
        string minutes;
        cout << "\nEnter the runtime: ";
        getline(cin, minutes);
        print_vec(search_int(stoi(minutes), 3));
      }
      else if(input2 == 2){
        string range1 = "99999", range2 = "-1";
        while(stoi(range1) > stoi(range2) && stoi(range1) >= 0){
          cout << "\nEnter your lower range: ";
          getline(cin, range1);
          cout << "\nEnter your upper range: ";
          getline(cin,range2);
        }
        print_vec(search_int_runtime_range(stoi(range1), stoi(range2)));
      }
      else if(input2 == 3){
        main_menu();
      }
    }
    else if(input == 5){ // Search by ratings
      cout << "How would you like to search by ratings?\n"
           << "(1)Exact rating.\n(2)By a range.\n(3)Return to options.\n"
           << "Enter the number of your choice: ";
      
      while(valid_input2 == false){      
        getline(cin, my_input2);
        input2 = stoi(my_input2);
        if (input2 >= 1 && input2 <= 3){
          valid_input2 = true;
        }
        else{
          cout << "\nInvalid input, please try again: ";
        }
      }
      if(input2 == 1){
        string rating_value;
        cout << "\nEnter the rating: ";
        getline(cin, rating_value);
        print_vec(search_int(stod(rating_value), 4));
      }
      else if(input2 == 2){
        string range1 = "99999", range2 = "-1";
        cout << "\nEnter your lower range: ";
        getline(cin, range1);
        cout << "\nEnter your upper range: ";
        getline(cin,range2);
        print_vec(search_int_ratings_range(stod(range1), stod(range2)));
      }
      else if(input2 == 3){
        main_menu();
      }
    }
    else if(input == 6){ // Return to main menu
      main_menu();
    }
  }

  void delete_menu(){
      cout << "\nDelete entry by:\n---------------\n(1)exact movie title\n(2)substring of movie title\n"
         << "(3)exact director\n(4)substring of director\n(5)exact release date\n"
         << "(6)exact rating\n(7)exact runtime\n(8)range of runtime\n"
         << "(9)range of release date\n(10)range of rating\n(11)Return to Main Menu\n" 
         << "Please enter an number indicating your choice: ";
    bool delete_input = false;
    int input;
    while(delete_input == false){
      string str_input;
      cin >> std::ws;
      getline(cin, str_input);
      input = stoi(str_input);
      if (input >= 1 && input <= 10){
        delete_choices(input);
        delete_input = true;
      }else if(input == 11){
        return;
      } else {
        cout << "Input is invalid, please try again: ";
      }
    }
  }

  void delete_choices(const int& option) {
    string key_str;
    int key_int_1;
    int key_int_2;
    int* results;
    if(option < 5){
      cout << "--> ";
      cin >> std::ws;
      getline(cin, key_str);
      if(option == 1){
        results = search_string(key_str, 0);
      } else if(option == 2) {
        results = search_title_substr(key_str);
      } else if(option == 3) {
        results = search_string(key_str, 1);
      } else if(option == 4) {
        results = search_director_substr(key_str);
      }
      cout << "Are you sure you want to delete the following entries(Y/N): \n";
      print_vec(results);
      getline(cin, key_str);
      if(word_lower(key_str) == "y") {
        unsigned int i = 0;
        while(results[i] != -1){
          delete_record(results[i]);
          i++;
        }
        cout << "Entries Deleted\n";
        delete[] results;
      } else{
        cout << "Entries NOT Deleted\n";
        delete[] results;
        return;
      }
    } else if(option < 8){
        cout << "--> ";
        cin >> std::ws;
        getline(cin, key_str);
        key_int_1 = stoi(key_str);
        if(option == 5){
          results = search_int(key_int_1, 2);
        } else if(option == 6) {
          results = search_int(key_int_1, 4);
        } else if(option == 7) {
          results = search_int(key_int_1, 3);
        } 
        cout << "Are you sure you want to delete the following entries(Y/N): \n";
        print_vec(results);
        cin >> std::ws;
        getline(cin, key_str);

        if(word_lower(key_str) == "y") {
          unsigned int i = 0;
          while(results[i] != -1){
            delete_record(results[i]);
            i++;
          }
          cout << "Entries Deleted\n";
          delete[] results;
        } else{
        cout << "Entries NOT Deleted\n";
        delete[] results;
        return;
      }
    } else if(option < 11){
        cout << "--> (low) ";
        cin >> std::ws;
        getline(cin, key_str);
        key_int_1 = stoi(key_str);
        cout << "--> (high) ";
        cin >> std::ws;
        getline(cin, key_str);
        key_int_2 = stoi(key_str);

        if(option == 8){
          results = search_int_runtime_range(key_int_1, key_int_2);
        } else if(option == 9) {
          results = search_int_release_date_range(key_int_1, key_int_2);
        } else if(option == 1) {
          results = search_int_ratings_range(key_int_1, key_int_2);
        } 
        cout << "Are you sure you want to delete the following entries(Y/N): \n";
        print_vec(results);
        cin >> std::ws;
        getline(cin, key_str);
        if(word_lower(key_str) == "y") {
          unsigned int i = 0;
          while(results[i] != -1){
            delete_record(results[i]);
            i++;
          }
          cout << "Entries Deleted\n";
          delete[] results;
        } else{
        cout << "Entries NOT Deleted\n";
        delete[] results;
        return;
      }
    }
  }

  void list_menu(){
    cout << "How would you like the movies to be listed?\n"
         << "(1)By title, alphabetically.\n(2)By title, reverse alphabetically.\n"
         << "(3)By director, alphabetically.\n(4)By director, reverse alphabetically.\n"
         << "(5)By release date, oldest to newest.\n(6)By release date, newest to oldest.\n"
         << "(7)By runtime, shortest to longest.\n(8)By runtime, longest to shortest.\n"
         << "(9)By ratings, lowest to highest.\n(10)By ratings, highest to lowest.\n"
         << "Enter the number of your choice: ";

    bool valid_input = false;
    while(valid_input == false){
      getline(cin, my_input);
      input = stoi(my_input);
      if (input >= 1 && input <= 10){
        valid_input = true;
      }
      else{
        cout << "\nInvalid input, please try again: ";
      }
    }
    if (input == 5){
      print_vec(sort_int(0, 0));
    }
    else if (input == 6){
      print_vec(sort_int(1, 0));
    }
    else if (input == 7){
      print_vec(sort_int(0, 1));
    }
    else if (input == 8){
      print_vec(sort_int(1, 1));
    }
    else if(input == 9){
      print_vec(sort_int(0, 2));
    }
    else if (input == 10){
      print_vec(sort_int(1, 2));
    }
  }

  void quit_menu()
  {
    // should write vector into text file
    ofstream outfile;
    outfile.open(filename);
    for(int i = 0; i < size(); i++){
      outfile << get(i)->get_movie_name()  << "_" 
              << get(i)->get_director()    << "_"
              << get(i)->get_release_date()<< "_"
              << get(i)->get_run_time()    << "_"
              << get(i)->get_ratings()     << "\n";
    }
    outfile.close();
  }

  void choice_menu(int input){
    if (input == 1){
      add_menu();
    }
    else if(input == 2){ 
      input2 = 0;
      valid_input = false;
      valid_input2 = false;
      find_menu();
    }
    else if(input == 3){
      delete_menu();
    }
    else if(input == 4){
      list_menu();
    }
    else if(input == 5){
      quit_menu();
    }
  }
}; // end of menu class