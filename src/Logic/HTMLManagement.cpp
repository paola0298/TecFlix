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

int main(int argc, char *argv[]) {
    // std::string html = getHTML("http://www.imdb.com/title/tt1170358/");
    // return 0;
}