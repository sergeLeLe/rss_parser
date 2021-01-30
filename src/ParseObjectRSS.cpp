#include "ParseObjectRSS.h"

void ParseObjectRSS::getItems(string str, vector<string*>& items){
    int position = 0;
    int begin = 0;
    int end = 0;
    while (position != -1){
        begin = str.find("<item>", end, 6);
        end = str.find("</item>", begin, 7) + 7;
        items.push_back(new string(str.substr(begin, end - begin)));
        position = str.find("<item>", end + 1, 6);
    }
}

void ParseObjectRSS::doParse(){
    getResponse(url);

    vector<string*> items;

    getItems(getStrResponse(), items);

    string title;
    string description;
    string link;
    string date;

    regex regOpeningTags("(<[a-zA-Z_][\\w.-]*[^>]*>)");
    regex regClosingTags("(</[a-zA-Z_][\\w.-]*[^>]*>)");
    //regex clearSpace("^[ \\s]+|[ \\s]+$");

    string pL = "&lt;";
    string pR = "&gt;";

    string t = "<title>";
    string d = "<description>";
    string l = "<link>";
    string pd = "<pubDate>";

    for(auto item: items){
        title = item->substr(item->find(t) + t.size(),item->find("</title>") - item->find(t) - t.size());
        description = item->substr(item->find(d) + d.size(), item->find("</description>") - item->find(d) - d.size());
        link = item->substr(item->find(l) + l.size(),item->find("</link>") - item->find(l) - l.size());
        date = item->substr(item->find(pd) + pd.size(),item->find("</pubDate>") - item->find(pd) - pd.size());

        for (std::string::size_type n = 0; ( n = description.find(pL, n ) ) != std::string::npos; ++n )
        {
            description.replace(n, pL.size(), 1, '<' );
        }
        for (std::string::size_type n = 0; ( n = description.find(pR, n ) ) != std::string::npos; ++n )
        {
            description.replace(n, pL.size(), 1, '>' );
        }

        description = regex_replace(description, regOpeningTags, "");
        description = regex_replace(description, regClosingTags, "");
        //description = regex_replace(description, clearSpace, "");

        if (title.find("<![CDATA[") > -1){
            title.replace(title.find("<![CDATA["), 9, "");
            title.replace(title.find("]]>"), 3, "");
        }

        if (description.find("<![CDATA[") > -1){
            description.replace(description.find("<![CDATA["), 9, "");
            description.replace(description.find("]]>"), 3, "");
        }


        string *temp = new string (title);
        if (articles.find(temp) == articles.end()){
            articles.insert(make_pair(new string(title), new Article(title, description, link, date)));
        }
        delete temp;

    }
    clearItems(items);
}

void ParseObjectRSS::clearItems(vector<string*>& items){
    for (auto p : items)
    {
        delete p;
    }
    items.clear();
}

void ParseObjectRSS::clearArticles(map<string*, Article*>& articles){
    for (auto p : articles)
    {
        delete p.second;
        delete p.first;
    }
    articles.clear();
}