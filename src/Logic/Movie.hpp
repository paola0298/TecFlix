#ifndef MOVIE_CLASS
#define MOVIE_CLASS

#include <iostream>
#include <gtkmm-3.0/gtkmm/image.h>
using namespace std;

class Movie {
    public:
        string movieTitle;
        string year;
        string score;
        string duration;
        string sinopsis;
        string director;
        string genres;
        string actors;
        string language;
        string keywords;
        string trailerLink;
        string posterDir;
        int index;
        string url;
        
        Movie(string title, string yearMovie, string movieScore, string durationMovie,
        string sinopsisMovie, string directorName, string genre,string actorsName,
        string lang, string keyword, string trailer, string imageDir);
        
};

#endif