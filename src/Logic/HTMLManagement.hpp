#ifndef _HTML_MANAGEMENT_
#define _HTML_MANAGEMENT_

#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
using namespace std;



class HTMLManagement {
    public:
        HTMLManagement();
        string getHTML(string url);
        string getSummary(string hmtl);
        string getTrailerLink(string html);
        string getPosterPath(string html, string imageN);
    private:
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        string getPosterLink(string hmtl);
        string getTrailerHTML(string html);
};

#endif