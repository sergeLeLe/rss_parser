#ifndef PARSERXML_ARTICLE_H
#define PARSERXML_ARTICLE_H

#include <string>
#include <iostream>

using namespace std;

class Article {
private:
    string title;
    string description;
    string link;
    string date;

public:
    Article(string title, string description, string link, string date){
        this->title = title;
        this->description = description;
        this->link = link;
        this->date = date;
    }

    friend std::ostream& operator <<(std::ostream& os, const Article& article);

    string getTitle(){
        return title;
    }

    string getDescription(){
        return description;
    }

    string getLink(){
        return link;
    }

    string getDate(){
        return date;
    }
};


#endif //PARSERXML_ARTICLE_H
