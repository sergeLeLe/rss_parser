cmake_minimum_required(VERSION 3.17)
project(ParserXML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -lcurl")

add_executable(ParserXML src/main.cpp src/HtmlParse.cpp src/HtmlParse.h src/ParseObjectRSS.cpp src/ParseObjectRSS.h src/IHttpRequest.cpp src/IHttpRequest.h src/Article.cpp src/Article.h src/ConsoleMenu.cpp src/ConsoleMenu.h)
target_link_libraries(ParserXML /Users/admin/LibsC++/curl-7.74.0)