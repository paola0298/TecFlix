#include "HTMLManagement.hpp"

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
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
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

string HTMLManagement::getTrailerHTML(string html) {
  string line;
  stringstream ss(html);
  int trailer = 0;

  while (getline(ss, line, '\n')) {
    if (trailer==1) {
      // cout << "Trailer link \n" << line << "\n"; 
      int posI = line.find_first_of("\"");
      int posF = line.find_last_of("\"");   
      string link = line.substr(posI+1, posF-7);
      // cout << "Line \n" << line << "\n";
      link = "https://www.imdb.com" + link;
      string link1 = link.substr(0, link.size()-1);
      // cout << "Trailer link.. " << link1 << "\n"; 
      string htmlTrailer = getHTML(link1);
      return htmlTrailer;
    }
    
    if (line.find("class=\"slate\"") != string::npos) {
      // cout << "Trailer link found\n"<< line << "\n"; 
      trailer++;
    }
  }
  return "";
}

string HTMLManagement::getTrailerLink(string html) {
  // cout << "Getting trailer html.. \n";
  string htmlTrailer = getTrailerHTML(html);

  // cout << htmlTrailer << "\n";

  if (htmlTrailer!="") {
    // cout << "Trailer of html != \"\"\n";
    string line;
    stringstream ss(htmlTrailer);
    int trailer = 0;

    while (getline(ss, line, '\n')) {
      if (trailer == 1) {
        // cout << "Trailer link: " << line << "\n";
        return line;
      }

      if (line.find("jw-video") != string::npos) {
        // cout << "Trailer link found: " << line << "\n";
        trailer++;
      }
    }
  }
  // cout << "Trailer html == \"\"";
  return "";
}

string HTMLManagement::getPosterPath(string html, string imageN) {
   string urlPoster = getPosterLink(html);
   string imageData = getHTML(urlPoster);
   cout << "url poster " << urlPoster << "\n\n";
   ofstream poster;
   poster.open("/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache/image" + imageN + ".png");
   poster << imageData;
   poster.close();
   string url = "/home/paola/Documents/II Semestre 2019/Algoritmos y Estructuras de Datos II/Proyectos programados/TecFlix/res/Cache/image" + imageN + ".png";
   return url;
}


// int main(int argc, char *argv[]) {
//     HTMLManagement html;
  
//     // string stringHtml = html.getHTML("http://www.imdb.com/title/tt1216475/?ref_=fn_tt_tt_1");
//     // string stringHtml = html.getHTML("http://www.imdb.com/title/tt1345836/?ref_=fn_tt_tt_1");
//     // cout << stringHtml << "\n";
//     // string htmll = html.getHTML("https://www.imdb.com/video/imdb/vi2376312089?playlistId=tt1345836&ref_=tt_ov_vi");
//     string htmll = html.getHTML("https://www.traileraddict.com/avatar/extended-collectors-edition-trailer");
//    // string posterPath = html.getTrailerLink(stringHtml);
  
//     cout << htmll << "\n";
    
//     return 0;
// }