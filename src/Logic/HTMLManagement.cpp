#include "HTMLManagement.hpp"
// #include "ReadCSV.cpp"

HTMLManagement::HTMLManagement() {}

size_t HTMLManagement::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string HTMLManagement::getHTML(string url) {
    // cout << "Url received in getHTML " <<  url << "\n";
    CURL *curl;
    CURLcode result;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // cout << url.c_str() << ", cstr\n";
        // url = replaceBlank(" ", "", url.c_str());
        // cout << url << ", cstr replaced \n";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        result = curl_easy_perform(curl);
        //Check for errors
        if (result != CURLE_OK) {
            cout << "failed\n";
            cout << result << "\n";
        }
        curl_easy_cleanup(curl);
    }
    
    return readBuffer;
}

string HTMLManagement::getSummary(string html){
  string line;
  stringstream ss(html);
  bool summary = false;

  while (getline(ss, line, '\n')) {
    if (summary) 
      return line;

    if (line.find("summary_text") != string::npos)
      summary = true;
  }
  return "";
}

string HTMLManagement::getPosterLink(string html){
  string line;
  stringstream ss(html);
  int poster = 0;

  while(getline(ss, line, '\n')) {
    if (poster == 4){
      int posI = line.find_first_of("\"");
      int posF = line.find_last_of("\"");  
      string link = line.substr(posI+1, posF-5);
      return link;
    }

    if (line.find("div class=\"poster\"") != string::npos) 
      poster++;

    if (poster > 0) 
      poster++;
  }
  return "";
}


string HTMLManagement::getPosterPath(string html, string imageN) {
   string urlPoster = getPosterLink(html);
   string imageData = getHTML(urlPoster);
  //  cout << "url poster " << urlPoster << "\n\n";
   ofstream poster;
   poster.open("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache/image" + imageN + ".png");
   poster << imageData;
   poster.close();
   string url = "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache/image" + imageN + ".png";
   return url;
}

std::string HTMLManagement::getTrailerLink(string movieName) {
  boost::to_lower(movieName);
  movieName = replaceBlank(":", "%3A", movieName);
  movieName = replaceBlank("'", "%27", movieName);
  movieName = replaceBlank("&", "%26", movieName);
  movieName = replaceBlank(" ", "%20", movieName);

  // cout << "Movie name " << movieName << ".\n";
  
  string newMovieName = "";
  int movieNameSize = movieName.size();
  for (int i=0; i<movieNameSize; i++) {
    // if (!isspace(movieName[i])) {
    // cout << movieName[i] << "\n";
    if (ispunct(movieName[i]) || isalnum(movieName[i])) {
      newMovieName+= movieName[i];
    } else {
      break;
    }
  }

  // cout << "New movie name " << newMovieName << ".\n";
  
  string principal = "http://www.sensacine.com";
  std::string searchLink = principal +"/busqueda/?q="+ newMovieName;
  searchLink = replaceBlank(" ", "", searchLink);
  std::string htmlSearch = getHTML(searchLink);

  // cout << htmlSearch << "\n";
  string htmlMovie;
  string trailerPage;
  string htmlTrailer;
  string trailerLink;

  // cout << searchLink << ".\n";
  string moviePageLink = getMoviePage(movieName, htmlSearch);

  // cout << "Movie page " << moviePageLink << "\n";
  if (moviePageLink != "") {
    htmlMovie = getHTML(principal+moviePageLink);
    trailerPage = getTrailerPage(htmlMovie);
    // cout << "Trailer page " << trailerPage << "\n";

  } else {
    return "";  
  }

  // cout <<htmlMovie<<"\n";
  if (trailerPage != "") {
    htmlTrailer = getHTML(trailerPage);
    trailerLink = getTrailerUrl(htmlTrailer);
    // cout << "Trailer page " << trailerLink << "\n";
  } else {
    return "";
  }

  if (trailerLink != "") {
    cout << "TRailer link " << trailerLink << "\n";
    trailerLink = replaceBlank("\\", "/", trailerLink);
    return trailerLink;

  } else {
    return "";
  }
  

  

  // cout << htmlTrailer << "\n";

  

  

}

string HTMLManagement::getMoviePage(string movieName, string html) {
  string line;
  stringstream ss(html);
  int trailer = 0;
  
  // cout << "Getting movie page \n"; 

  while (getline(ss, line, '\n')) {
    if (trailer == 2) {
      int posI = line.find("href");
      int posF = line.find("><");
      string link = line.substr(posI+6, posF-10);
      // cout << "Line " << line << "\n";
      // cout << "Link " << link << "\n";
      return link;
      
    }

    if (trailer > 0)
      trailer++;

    if (line.find("totalwidth noborder purehtml") != string::npos) {
      // cout << "Line found " << line << "\n";
      trailer++;
    }
  }

  return "";
}

string HTMLManagement::getTrailerPage(string htmlMovie) {
  string line;
  stringstream ss(htmlMovie);
  int trailer = 0;

  while (getline(ss, line, '\n')) {
    if (trailer == 11) {
      
      // if (line.find("trailer") != string::npos) {
        // cout << line <<"\n";
        
        int posI = line.find(":");
        string link = line.substr(posI+3, line.size()-2);
        string link2 = link.substr(0, link.find("\""));
        // cout << "Trailer link 2 " << link2 << "\n";
        // cout << "Trailer link " << link << "\n";
        return link2;
      // }
      
    }

    if (trailer > 0) 
      trailer++;

    if (line.find("VideoObject") != string::npos) {
      // cout << "Line " << line << "\n";
      trailer ++;
    }
  }

  return "";

}

string HTMLManagement::getTrailerUrl(string htmlTrailer) {
  string line;
  stringstream ss(htmlTrailer);
  int trailer = 0;

  while (getline(ss, line, '\n')) {
    

    if (trailer == 1) {
      
      int posI = line.find("es.");
      int posE = line.find("quot;,&quot");

      string link = line.substr(posI, posE);
      string link2 = link.substr(0, link.find("mp4")+3);
      
      
      // cout << "link " << link2 << "\n";

      return link2;
    }

    // if (trailer > 0) {
    //   trailer++;
    // }

    if (line.find("Publica este vídeo") != string::npos) {
      // cout << "line " << line << "\n";
      trailer++;
    }

  }
  return "";
}

std::string HTMLManagement::replaceBlank(string toReplace, string replaceBy, string word) { 
    int n = 0; 
  
    // loop till all space are replaced 
    while ((n = word.find(toReplace, n)) != string::npos ) 
    { 
        word.replace(n, 1, replaceBy); 
        n += replaceBy.length(); 
    } 
    return word; 
} 


// int main(int argc, char *argv[]) {
//     HTMLManagement htmlObj;
//     CSVReader reader("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/movie_metadata.csv");
//     std::vector<std::string> list = reader.getData(0, 2);
//     std::vector<std::string> record = reader.getRecord(2, list);

//     // string name = record[11];
//     string name = "Star Wars: Episode VII - The Force Awakens             ";
  
//     // string stringHtml = html.getHTML("http://www.imdb.com/title/tt1216475/?ref_=fn_tt_tt_1");
//     // string stringHtml = html.getHTML("http://www.imdb.com/title/tt1345836/?ref_=fn_tt_tt_1");
//     // cout << stringHtml << "\n";
//     // string htmll = html.getHTML("https://www.imdb.com/video/imdb/vi2376312089?playlistId=tt1345836&ref_=tt_ov_vi");
//     // string htmll = html.getHTML("https://www.traileraddict.com/avatar/extended-collectors-edition-trailer");
//    // string posterPath = html.getTrailerLink(stringHtml);
//     // string html = htmlObj.getTrailerLink("Pirates of the Caribbean: At World's End");
//     // string name = "Avatar";
//     // cout << "size :" << name.size() << ".\n";

//     // name = name.substr(0, name.size()-14);
//     // cout << name << ". name\n";
    
//     string html = htmlObj.getTrailerLink(name);
//     // string html = htmlObj.getTrailerLink("Captain America: Civil War");
    
//     // string html = htmlObj.getTrailerLink("Cars");
//     cout << html << "\n";
//     // cout << htmlObj.getHTML("http://www.sensacine.com/peliculas/pelicula-55774/");
    
//     return 0;
// }