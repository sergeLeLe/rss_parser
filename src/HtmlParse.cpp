#include "HtmlParse.h"

void HtmlParse::getResponse(string url){
    curl = curl_easy_init(); //иниц. объекта (в случае неудачи сессии возврат NULL)
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //задаем юрл
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResponseToString); //get-запрос для вытягивания строки
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);//буфер для строки
    response = curl_easy_perform(curl); //выполняем запрос
    //        if (CURLE_OK != response){
    //            fprintf(stderr, "HTTP failed: %s\n", curl_easy_strerror(response));
    //        }
    curl_easy_cleanup(curl); //закрытие (очистка сессии)
}

size_t HtmlParse::getResponseToString(void* contents, size_t size, size_t nmemb, void* userp){
    ((string*)userp)->append((char*)contents, size* nmemb);
    return size* nmemb;
}
