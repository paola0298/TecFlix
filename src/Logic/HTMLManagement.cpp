#include "HTMLManagement.h"


//pkg-config libxml++-3.0 --cflags --libs

HTMLManagement::HTMLManagement() {}

size_t HTMLManagement::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string HTMLManagement::getHTML(std::string url) {
    std::cout << url << "\n";
    CURL *curl;
    CURLcode result;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        result = curl_easy_perform(curl);
        //Check for errors
        if (result != CURLE_OK) {
            std::cout << "failed\n";
            std::cout << result << "\n";
        }
        curl_easy_cleanup(curl);

        // std::cout << "result:\n" << readBuffer << "\n";
    }
    
    return readBuffer;
}

std::string HTMLManagement::getSummary(std::string html){
  std::string line;
  std::stringstream ss(html);
  bool summary = false;

  while (getline(ss, line, '\n')) {
    if (summary) {
      std::cout << "Summary \n" << line << "\n"; 
      return line;
    }

    if (line.find("summary_text") != std::string::npos) {
      std::cout << "Summary line found\n"<< line << "\n"; 
      summary = true;
    }
  }
  return "";
}

std::string HTMLManagement::getPosterLink(std::string html){
  std::string line;
  std::stringstream ss(html);
  int poster = 0;

  while(getline(ss, line, '\n')) {
    if (poster == 4){
      int posI = line.find_first_of("\"");
      int posF = line.find_last_of("\"");
      std::cout << "Pos inicial: " << posI << ", Pos final: " << posF << "\n";      
      std::string link = line.substr(posI+1, posF-5);
      std::cout << "Line \n" << line << "\n";
      std::cout << "Poster link.. \n" << link << "\n"; 
      return line;
    }

    if (line.find("poster") != std::string::npos) {
      std::cout << "Poster line found\n"<< line << "\n"; 
      poster++;
    }

    if (poster > 0) {
      poster++;
    }
    
  }
  return "";
}

std::string HTMLManagement::getTrailerLink(std::string html) {
  std::string line;
  std::stringstream ss(html);
  int trailer = 0;

  while (getline(ss, line, '\n')) {
    if (trailer==1) {
      std::cout << "Trailer link \n" << line << "\n"; 
      int posI = line.find_first_of("\"");
      int posF = line.find_last_of("\"");
      std::cout << "Pos inicial: " << posI << ", Pos final: " << posF << "\n";      
      std::string link = line.substr(posI+1, posF-7);
      std::cout << "Line \n" << line << "\n";
      link = "https://www.imdb.com" + link;
      std::string link1 = link.substr(0, link.size()-1);
      std::cout << "Trailer link.. \n" << link1 << "\n"; 
      
      return link;
    }
    
    if (line.find("class=\"slate\"") != std::string::npos) {
      std::cout << "Trailer link found\n"<< line << "\n"; 
      trailer++;
    }
  }
  return "";
}


int main(int argc, char *argv[]) {
    HTMLManagement html;
    // std::string stringHtml = html.getHTML("http://www.imdb.com/title/tt2395427/?ref_=fn_tt_tt_1");
    std::string stringHtml = html.getHTML("http://www.imdb.com/title/tt1216475/?ref_=fn_tt_tt_1");
    // html.getSummary(stringHtml);
    // html.getPosterLink(stringHtml);
    html.getTrailerLink(stringHtml);
    return 0;
}