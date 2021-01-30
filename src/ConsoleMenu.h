#ifndef PARSERXML_CONSOLEMENU_H
#define PARSERXML_CONSOLEMENU_H

#include "Article.h"
#include "ParseObjectRSS.h"
#include <cctype>
#include "fstream"

class ConsoleMenu {
public:
    ConsoleMenu() {}

    //method for forming articles without filter
    map<string*, Article*> findAll(map<string*, Article*> &articles, map<string*, Article*> &articlesAfterFiltring);

    //method for forming articles with filtering by keywords in the title
    map<string*, Article*> findByTitle(map<string*, Article*> &articles, map<string*, Article*> &articlesAfterFiltring, string keyword);

    //method for displaying
    void show(map<string*, Article*> &articles);

    //method to export to file
    static void exportToTxt(map<string*, Article*> &articles, string nameTxt);

    //main function
    void start();
};


#endif //PARSERXML_CONSOLEMENU_H
