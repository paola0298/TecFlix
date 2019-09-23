#include "Movie.h"

Movie::Movie(string title, string yearMovie, string movieScore, string durationMovie,
        string sinopsisMovie, string directorName, string genre,string actorsName,
        string lang, string keyword, string trailer, string imageDir) : 
movieTitle(title), year(yearMovie), score(movieScore), duration(durationMovie),
sinopsis(sinopsisMovie), director(directorName), genres(genre), actors(actorsName),
language(lang), keywords(keyword), trailerLink(trailer), posterDir(imageDir) { }
    

