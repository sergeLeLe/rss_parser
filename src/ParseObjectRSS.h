#ifndef PARSERXML_PARSEOBJECTRSS_H
#define PARSERXML_PARSEOBJECTRSS_H

#include "HtmlParse.h"
#include "Article.h"
#include <algorithm>
#include "map"
#include <regex>
#include <iostream>

class ParseObjectRSS: public HtmlParse{
private:
    map<string*, Article*> articles;

    void getItems(string str, vector<string*>& items);

public:

    ParseObjectRSS(string url){
        this->url = url;
    }

    //method for processing xml structure
    void doParse();

    map<string*, Article*>& getArticles(){
        return articles;
    }

    void clearItems(vector<string*>& items);

    static void clearArticles(map<string*, Article*>& articles);
};


#endif //PARSERXML_PARSEOBJECTRSS_H
