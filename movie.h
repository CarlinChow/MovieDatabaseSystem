//  movie.h
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class movie
{
  private:
  
    const string movie_name;
    const string director;
    const int release_date; 
    const int runtime; // Runtime in minutes
    const double ratings; // 0 - 10

  public:
  
  movie(const string a, const string b, const int c,
        const int d, const double e)
  : movie_name(a), director(b), release_date(c), runtime(d),ratings(e)
  {}

  // implement getters for data
  string get_movie_name() const { return movie_name; }

  string get_director() const { return director; }

  int get_release_date() const { return release_date; }

  int get_run_time() const { return runtime; }

  double get_ratings() const { return ratings; }
};
