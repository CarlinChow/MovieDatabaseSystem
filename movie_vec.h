// movie_vec.h


// movie_vec.h


#include <iostream>      
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>
#include "movie.h" 

using namespace std;

class movie_vec{
  public:

	movie_vec(const string& fname)
	: size_(0), capacity_(10), data_( new movie*[capacity_] ) 
	{
		ifstream fin;
		fin.open( fname );
		string line;
		string title, director;
		int release_date, runtime;
		double ratings;
		while(getline(fin, line)){
			size_t pos = 0;
			pos = line.find("_");
			title = line.substr(0, pos);
			line = line.substr(pos + 1);

			pos = line.find("_");
			director = line.substr(0, pos);
			line = line.substr(pos + 1);

			pos = line.find("_");
			release_date = stoi(line.substr(0, pos));

			pos = line.find("_");
			runtime = stoi(line.substr(0, pos));
			line = line.substr(pos + 1);

			ratings = stod(line.substr(0, line.length()));

			movie* movie_record = new movie(title, director, release_date, runtime, ratings);
			append(movie_record);
		}
	}

	virtual ~movie_vec(){ 
		cout << "movie_vec destructor called\n";
		for(int i = 0; i < size(); i++){
			delete data_[i];
		}
		delete[] data_; 
	}

	int size() const { return size_; } 

	int capacity() const { return capacity_; } 

	double pct_used() const { return size_ / capacity_; } 

	void delete_record(int index){
    if(index >= size() || index < 0){
        cout << "index is out of bounds\n";
    }else{
      data_[index] = data_[size_-1];
      size_--;
    }
  }

	
	movie* get(int i) const{
		return data_[i];
	}

	void set(int i, movie* s){ 
	  data_[i] = s;
	}

  void append(movie* s){ 
		if( size_ >= capacity_){
			double_array();
		}
		data_[size_] = s;
		size_++;
	}

	void prepend(movie* s){ 
		if(size_ >= capacity_){
			double_array();
		}
		for(int i = size_-1, j = size_; i >= 0; i--, j--){
			data_[j] = data_[i];
		}
		data_[0] = s;
		size_++;
	}

	void clear(){ 
		size_ = 0;
	}

  private:

  int size_;
  int capacity_;
  movie** data_;
  
  void double_array(){
    movie** result;
    capacity_ = capacity_ * 2;
    result = new movie*[capacity_];
    for(int i = 0; i < size_; i++){
      result[i] = data_[i];
    }
    delete[] data_;
    data_ = result;
  }
}; // class movie_vec