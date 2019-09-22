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


class HTMLManagement {
    public:
        HTMLManagement();
        std::string getHTML(std::string url);
    private:
        size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif