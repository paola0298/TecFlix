#ifndef HTML_MANAGEMENT
#define HTML_MANAGEMENT

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <htmlcxx/html/ParserDom.h>

#include <tidy.h>
#include <buffio.h>
#include <stdio.h>
#include <errno.h>

#include <htmlstreamparser.h>
#include <sstream>
#include <fstream>



class HTMLManagement {
    public:
        HTMLManagement();
        std::string getHTML(std::string url);
        std::string getSummary(std::string hmtl);
        std::string getPosterLink(std::string hmtl);
        std::string getTrailerLink(std::string html);
    private:
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif