 
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <htmlcxx/html/ParserDom.h>

//pkg-config libxml++-3.0 --cflags --libs

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getHTML(std::string url) {
    CURL *curl;
    CURLcode result;
    std::string readBuffer = "";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        result = curl_easy_perform(curl);
        //Check for errors
        if (result != CURLE_OK) {
            std::cout << "failed\n";
        }
        curl_easy_cleanup(curl);

        std::cout << "result:\n" << readBuffer << "\n";
    }
    
    return readBuffer;
}

int main(void) {
    std::string html = getHTML("https://imdb.com/title/tt0499549/?ref_=fn_tt_tt_1");

//     //parse html code
//     HTML::ParserDom parser;
//   tree<HTML::Node> dom = parser.parseTree(html);
  
//   //Print whole DOM tree
//   cout << dom << endl;
  
//   //Dump all links in the tree
//   tree<HTML::Node>::iterator it = dom.begin();
//   tree<HTML::Node>::iterator end = dom.end();
//   for (; it != end; ++it)
//   {
//   	if (it->tagName() == "A")
//   	{
//   		it->parseAttributes();
//   		cout << it->attributes("href");
//   	}
//   }
  
//   //Dump all text of the document
//   it = dom.begin();
//   end = dom.end();
//   for (; it != end; ++it)
//   {
//   	if ((!it->isTag()) && (!it->isComment()))
//   	{
//   		cout << it->text();
//   	}
//   }


    return 0;
}