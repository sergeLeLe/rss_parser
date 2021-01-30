#include "ConsoleMenu.h"

map<string*, Article*> ConsoleMenu::findAll(map<string*, Article*> &articles, map<string*, Article*> &articlesAfterFiltring){
    for (pair<string*, Article*> article: articles){
        articlesAfterFiltring.insert(make_pair(new string(*(article.first)), new Article(article.second->getTitle(), article.second->getDescription(), article.second->getLink(), article.second->getDate())));
    }
    return articlesAfterFiltring;
}

map<string*, Article*> ConsoleMenu::findByTitle(map<string*, Article*> &articles, map<string*, Article*> &articlesAfterFiltring, string keyword){
    for (pair<string*, Article*> article: articles){
        if(article.first->find(keyword.c_str(), 0, keyword.size()) != -1){
            articlesAfterFiltring.insert(make_pair(new string(*(article.first)), new Article(article.second->getTitle(), article.second->getDescription(), article.second->getLink(), article.second->getDate())));
        }
    }
    return articlesAfterFiltring;
}

void ConsoleMenu::show(map<string*, Article*> &articles){
    for_each(articles.begin(), articles.end(), [] (pair<string*, Article*> s){
        cout << *(s.second) << endl;
    });
}

void ConsoleMenu::exportToTxt(map<string*, Article*> &articles, string nameTxt){
    ofstream fout(nameTxt.c_str()); // создаём объект класса ofstream для записи и связываем его с файлом
    for(pair<string*, Article*> article : articles){
        fout << *(article.second) << endl;
        fout << endl;
    }
    fout.close();
}

void ConsoleMenu::start(){
    vector<ParseObjectRSS> sites;

    bool doing = true;
    char command;

    map<string*, Article*> allArticles;
    map<string*, Article*> articlesByFilter;

    string nameTxt;
    string keyword;

    while (doing)
    {
        cout << "\nEnter number of command:" << endl
             << "\t1 - Enter sites" << endl
             << "\t2 - Print of entered sites" << endl
             << "\t3 - Parsing" << endl
             << "\t4 - Initializing and Print" << endl
             << "\t5 - Export articles to txt" << endl
             << "\t6 - Stop running" << endl
             << "Command:";
        cin >> command;

        switch (command)
        {
            case '1':
            {
                string url_site;
                bool more;

                while(true){
                    cout << "Enter site:" << endl;
                    cin >> url_site;

                    regex checkUrl("https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,4}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

                    if (regex_match(url_site, checkUrl)){
                        sites.emplace_back(ParseObjectRSS(url_site));
                    }
                    else{
                        cout << "Bad entered URL" << endl;
                        break;
                    }

                    cout << "Add more? (1 - Yes, 0 - No)" << endl;
                    cin >> more;
                    if (!more){
                        break;
                    }
                }
                break;
            }
            case '2':
            {
                int index = 0;
                for_each(sites.begin(), sites.end(), [index](ParseObjectRSS s) mutable{
                    cout << index << " - " << s.getUrl() << endl;
                    index++;
                });
                break;
            }

            case '3':
                for (int i = 0; i < sites.size(); i++){
                    if (!sites[i].getArticles().empty()){
                        ParseObjectRSS::clearArticles(sites[i].getArticles());
                        sites[i].setUrl("");
                    }
                    sites[i].doParse();
                }
                break;

            case '4':
                bool temp;
                cout << "Use filter by keyword? (1 - Yes, 0 - No)" << endl;
                cin >> temp;

                if (!articlesByFilter.empty()){
                    ParseObjectRSS::clearArticles(articlesByFilter);
                }
                if (!allArticles.empty()){
                    allArticles = {};
                }

                if (!temp){
                    for(ParseObjectRSS s: sites){
                        allArticles = s.getArticles();
                        articlesByFilter = findAll(allArticles, articlesByFilter);
                    }
                }
                else {
                    cout << "Enter keyword" << endl;
                    cin >> keyword;
                    for(ParseObjectRSS s: sites){
                        allArticles = s.getArticles();
                        articlesByFilter = findByTitle(allArticles, articlesByFilter, keyword);
                    }

                }

                show(articlesByFilter);

                break;

            case '5':
                cout << "Enter name of file:" << endl;
                cin >> nameTxt;

                exportToTxt(articlesByFilter, nameTxt);
                break;

            case '6':
                if (!allArticles.empty()){
                    allArticles = {};
                }
                if(!articlesByFilter.empty())
                    ParseObjectRSS::clearArticles(articlesByFilter);
                for (int i = 0; i < sites.size(); i++){
                    if (!sites[i].getArticles().empty()){
                        ParseObjectRSS::clearArticles(sites[i].getArticles());
                    }
                }
                doing = false;
                break;

            default:
                cout << "\aEnter correct command!\n";
                break;
        }
    }
}

