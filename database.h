#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "movie_vec.h"

using namespace std;

class database : public movie_vec {
  private:

    bool not_in_arr(const int* arr, const int last, const int key){
      for(int i = 0; i < last; i++){
        if(arr[i] == key){
          return false;
        }
      }
      return true;
    }

  public:

  database (const string filename )
  : movie_vec(filename)
  {}

  string word_lower( const string& word ) {
    string tmp_str;
    for(int i = 0; i < word.length(); i++){
      tmp_str += tolower(word[i]);
    }
    return tmp_str;
  }

  void print_vec( int* arr ) {
    unsigned int index = 0;
    while(arr[index] != -1){
      cout << get(arr[index])->get_movie_name() << "  "
           << get(arr[index])->get_director() << "  "
           << get(arr[index])->get_release_date() << "  "
           << get(arr[index])->get_run_time() << "  "
           << get(arr[index])->get_ratings() << "\n";
      index++;
    }
    delete[] arr;
  } 
  
  int* sort_int( const int& sort, const int& type )
  {
    // Parameters: Sort(0) = ascending, Sort(1) = descending
    //             Type(0) = release date, Type(1) = runtime
    //             Type(2) = ratings
    // Output: A sorted list of indexes for the vector in the database
    int* indexes = new int[size() + 1];
    if(type == 0){
      int previous_value = 0;
      int lowest_idx;
      for(int i = 0; i < size(); i++){
        for(int k = 0; k < size(); k++){
          if(not_in_arr(indexes, i, k)){
            lowest_idx = k;
          }
        }
        for(int j = 0; j < size(); j++){ 
          if(get(j)->get_release_date() < get(lowest_idx)->get_release_date() && get(j)->get_release_date() >= previous_value && not_in_arr(indexes, i, j)){
            lowest_idx = j;
          }
        }
        indexes[i] = lowest_idx;
        previous_value = get(lowest_idx)->get_release_date();
      }
    }
    else if(type == 1){
      int previous_value = 0;
      int lowest_idx;
      for(int i = 0; i < size(); i++){
        for(int k = 0; k < size(); k++){
          if(not_in_arr(indexes, i, k))
          {
            lowest_idx = k;
          }
        }
        for(int j = 0; j < size(); j++){
          if(get(j)->get_run_time() < get(lowest_idx)->get_run_time() && get(j)->get_run_time() >= previous_value && not_in_arr(indexes, i, j)){
            lowest_idx = j;
          }
        }
        indexes[i] = lowest_idx;
        previous_value = get(lowest_idx)->get_run_time();
      }
    }
    else if(type == 2){
      int previous_value = 0;
      int lowest_idx;
      for(int i = 0; i < size(); i++){
        for(int k = 0; k < size(); k++){
          if(not_in_arr(indexes, i, k)){
            lowest_idx = k;
          }
        }
        for(int j = 0; j < size(); j++){
          if(get(j)->get_ratings() < get(lowest_idx)->get_ratings() && static_cast<int>(get(j)->get_ratings()) >= previous_value && not_in_arr(indexes, i, j)){
            lowest_idx = j;
          }
        }
        indexes[i] = lowest_idx;
        previous_value = get(lowest_idx)->get_ratings();
      }
    } 
    else{
      cout << "type parameter not accepted\n";
      return NULL;
    }

    if(sort == 1) {
      int* tmp_arr = reversal_1(indexes, size());
      for(int i =0; i < size(); i++){
        indexes[i] = tmp_arr[i];
      }
      delete[] tmp_arr;
    }
    indexes[size()] = -1;
    return indexes;
  }

  int* reversal_1(int* indexes, int size){
    if (indexes[0] == -1){
      return NULL;
    }
    int* rev_indexes = new int[size];

    for(int j = 0, i = size - 1; j < size && i >= 0; j++, i--){
      rev_indexes[j] = indexes[i];
    } 
    return rev_indexes;
  }


  int* search_string(const string& keyword, const unsigned int& x){
    // input x determines what datatype method is searching
    // 0 = movie_name, 1 = director
    // returns an array of all indexes where string is found and ends array with -1 
    // if string not found then array[0] = -1;
    // **** remember to delete array when finish using ****
    int* indexes = new int[size()];
    unsigned int arr_index = 0;
    for(int i = 0; i < size(); i++){
      if(x == 0){
        if( word_lower(keyword) == word_lower(get(i)->get_movie_name()) ){
          indexes[arr_index] = i;
          arr_index++;
        }
      }else if( x == 1 ){
          if( word_lower(keyword) == word_lower(get(i)->get_director()) ){
            indexes[arr_index] = i;
            arr_index++;
          }
      }else {
        // catch for coding error;
        cout << "Second parameter not accepted value\n";
        return NULL;
      }
    }

    if(arr_index == 0){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  } // end search_string()

  int* search_int(const int& key, const unsigned int& x){
    // input x determines what datatype method is searching
    // 2 = release date, 3 = runtime, 4 = ratings
    // release date must match
    // including any movie runtimes within 5 minutes apart from key integer
    // includes ratings of the key integer and up to but not including key + 1
    // returns an array of all indexes on the free store
    // where the key is found and ends array with -1 
    // if key is not found then array[0] = -1;
    // **** remember to delete array when finish using ****
    int* indexes = new int[size()];
    unsigned int arr_index = 0;

    for(int i = 0; i < size(); i++) {
      if(x == 2){
        if(key == get(i)->get_release_date()){
          indexes[arr_index] = i;
          arr_index++;
        }
      }else if( x == 3 ){
          if(get(i)->get_run_time() <= (key + 5) && get(i)->get_run_time() >= (key - 5)){
            indexes[arr_index] = i;
            arr_index++;
          }
      }else if( x == 4 ){
          if(static_cast<int>(get(i)-> get_ratings()) == key){
            indexes[arr_index] = i;
            arr_index++;
          }
      }else{
        // catch for coding error;
        cout << "Second parameter not accepted value\n";
        return NULL;
      }
    }

    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }

  int* sort_alpha_title(){
    int* indexes = new int[size()+1];
    string previous_value = get(0)->get_movie_name();
    int lowest_idx;
    for(int i = 0; i < size(); i++){
      for(int k = 0; k < size(); k++){
        if(not_in_arr(indexes, i, k)){
          lowest_idx = k;
        }
      }
      for(int j = 0; j < size(); j++){ 
        if(get(j)->get_movie_name() < get(lowest_idx)->get_movie_name() && get(j)->get_movie_name() >= previous_value && not_in_arr(indexes, i, j) ){
          lowest_idx = j;
        }
      }
      indexes[i] = lowest_idx;
      previous_value = get(lowest_idx)->get_movie_name();
    }
    indexes[size()] = -1;
    return indexes;
  }
  
  int* sort_rev_alpha_title(){
    return reversal_1(sort_alpha_title(), size());
  }

  int* sort_alpha_director(){
    int* indexes = new int[size()+1];
    for (int a = 0; a< size()+1; a++){
      indexes[a] = a;
    }
    unsigned int arr_index = 0;
    
    for (int i = 0; i <size(); i++){
      for (int j = i+1; j < size(); j++){
        string check1 = get(i)->get_director();
        string check2 = get(j)->get_director();

        if(tolower(check1[0]) > tolower(check2[0]))
        {
          
          indexes[i] = j;
          indexes[j] = i;
          arr_index++;
        }
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }

  int* sort_rev_alpha_director(){
    return reversal_1(sort_alpha_director(), size());
  }

  int* search_int_release_date_range(const int&  key1, const int& key2){
    int* indexes = new int[size()+1];
    unsigned int arr_index = 0;
    for (int i = 0; i < size(); i++){
      if(get(i)->get_release_date() >= key1 && get(i)->get_release_date() <= key2){
        indexes[arr_index] = i;
        arr_index++;
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }

  int* search_int_ratings_range(const double&  key1, const double& key2){
    int* indexes = new int[size()+1];
    unsigned int arr_index = 0;
    for (int i = 0; i < size(); i++){
      if(get(i)->get_ratings() >= key1 && get(i)->get_ratings() <= key2){
        indexes[arr_index] = i;
        arr_index++;
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }
  
  int* search_int_runtime_range(const int&  key1, const int& key2){
    int* indexes = new int[size()+1];
    unsigned int arr_index = 0;
    for (int i = 0; i < size(); i++){
      if(get(i)->get_run_time() >= key1 && get(i)->get_run_time() <= key2){
        indexes[arr_index] = i;
        arr_index++;
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }

int* search_title_substr(const string &keyword){
    int* indexes = new int(size()+1);
    unsigned int arr_index = 0;
    for (int i = 0; i < size(); i++){
      if((word_lower(get(i)->get_movie_name()).find(word_lower(keyword))) != std::string::npos){
        indexes[arr_index] = i;
        arr_index++;
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }

  int* search_director_substr(const string &keyword){
    int* indexes = new int(size()+1);
    unsigned int arr_index = 0;
    for (int i = 0; i < size(); i++){
      if((word_lower(get(i)->get_director()).find(word_lower(keyword))) != std::string::npos){
        indexes[arr_index] = i;
        arr_index++;
      }
    }
    if( arr_index == 0 ){
      indexes[0] = -1;
      delete[] indexes;
      return NULL;
    } 
    else{
      indexes[arr_index] = -1;
      return indexes;
    }
  }
}; // end of class