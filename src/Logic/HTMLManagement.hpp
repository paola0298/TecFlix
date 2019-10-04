#ifndef _HTML_MANAGEMENT_
#define _HTML_MANAGEMENT_

#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find.hpp>
#include <ctype.h>
using namespace std;



class HTMLManagement {
    public:
        HTMLManagement();
        string getHTML(string url);
        string getSummary(string hmtl);
        // string getTrailerLink(string html);
        string getPosterPath(string html, string imageN);
        string getTrailerLink(string movieName);
    private:
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        string getPosterLink(string hmtl);
        string getTrailerHTML(string html);
        string replaceBlank(string toReplace, string replaceBy, string word);
        string getMoviePage(string movieName, string html);
        string getTrailerPage(string htmlMovie);
        string getTrailerUrl(string htmlTrailer);
};

#endif