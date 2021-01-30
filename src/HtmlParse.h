#ifndef PARSERXML_HTMLPARSE_H
#define PARSERXML_HTMLPARSE_H

#include "IHttpRequest.h"

class HtmlParse: public IHttpRequest {
private:
    CURL* curl;
    string str_response;
    CURLcode response;

    //method for pulling a string from a request
    static size_t getResponseToString(void* contents, size_t size, size_t nmemb, void* userp);

protected:
    string url;

public:

    //method for sending a request to the server and receiving a response from the server
    void getResponse(string url) override;

    string getUrl(){
        return this->url;
    }

    void setUrl(string url){
        this->url = url;
    }

    string getStrResponse(){
        return str_response;
    }

    CURLcode getResponse(){
        return response;
    }
};


#endif //PARSERXML_HTMLPARSE_H
