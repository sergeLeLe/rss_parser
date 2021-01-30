#include "Article.h"

std::ostream& operator<< (std::ostream& os, const Article& article)
{
    os << "\ntitle: " << article.title << "\ndescription: " << article.description << "\nlink: " << article.link << "\ndata: " << article.date;
    return os;
}
