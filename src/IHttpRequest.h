#ifndef PARSERXML_IHTTPREQUEST_H
#define PARSERXML_IHTTPREQUEST_H

#include <string>
#include <curl/curl.h>

using namespace std;

class IHttpRequest {
public:
    virtual void getResponse(string url) = 0;

};


#endif //PARSERXML_IHTTPREQUEST_H
