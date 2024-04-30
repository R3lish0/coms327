#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"
#include "ncurses.h"


using namespace std;



static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


std::string get_request(std::string url) {
    // initialize curl locally
    CURL *curl = curl_easy_init();
    std::string result;

    if (curl) {
        // perform the GET request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_perform(curl);

        // free up the local curl resources
        curl_easy_cleanup(curl);
    }

    return result;
}



void print_page(xmlXPathObjectPtr product_html_elements)
{



}




int main() {
    //initialize curl globally
    curl_global_init(CURL_GLOBAL_ALL);
    
    std::string html_document = get_request("https://scp-wiki.wikidot.com/scp-5000");
    //std::cout << html_document;

    curl_global_cleanup();

    htmlDocPtr doc = htmlReadMemory(html_document.c_str(), html_document.length(), nullptr, nullptr, HTML_PARSE_NOERROR);

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr product_html_elements = xmlXPathEvalExpression((xmlChar *) "//div[contains(@id, 'page-content')]/p", context);

    initscr();
    cbreak();
    noecho();
    refresh();
    start_color();
    set_escdelay(0);
    
    int x_max, y_max;
    getmaxyx(stdscr, y_max,x_max);
    cout << y_max;

  
    int count = 0;
    for (int j = 0; j < product_html_elements->nodesetval->nodeNr; j++) {
        count++;
    }
    
    WINDOW * read = newpad(count*3,x_max);
    scrollok(read, TRUE);
    keypad(read,TRUE);
    idlok(read,TRUE);
 
    int i;

    for (i = 0; i < product_html_elements->nodesetval->nodeNr; i++) {

        xmlNodePtr element = product_html_elements->nodesetval->nodeTab[i];

        if(element->type == XML_ELEMENT_NODE &&
                xmlStrcmp(element->name, (const xmlChar *)"p") == 0) {
            xmlNodePtr child = element->children;

            while(child != NULL) {
                if(child->type == XML_TEXT_NODE) {
                    string content = reinterpret_cast<char*>(child->content);
                    waddstr(read, content.c_str());
                    waddstr(read, "\n");
                }
                else if (child->type == XML_ELEMENT_NODE &&
                        xmlStrcmp(child->name, (const xmlChar *)"strong") == 0) {
                    string content = reinterpret_cast<char*>(child->children->content);
                    waddstr(read, content.c_str());
                    waddstr(read, "\n");
                }
                
                child = child->next;
            }
        }
    }
    prefresh(read,0,0,0,0,y_max - 1,x_max - 1);
    int input;
    int pad_location = 0;
    while(1)
    {
        input = wgetch(read);

        if(input == 'Q')
        {
            delwin(read);
            endwin();
            exit(0);
        }
        else if(input == 'j' && pad_location >= 0)
        {
            pad_location--;
            prefresh(read, pad_location,0,0,0,y_max - 1,x_max - 1);

        }
        else if(input == 'k' && pad_location <= count)
        {
            pad_location++;            
            prefresh(read, pad_location,0,0,0,y_max - 1,x_max - 1);
        }




    }


    //xmlNodePtr paragraph_html = xmlXPathEvalExpression((xmlChar *) ".//", context)->nodesetval->nodeTab[0];
    //std::string paragraph = std::string(reinterpret_cast<char *>(xmlNodeGetContent(paragraph_html)));
        //std::string paragraph = std::string(xmlXNodeGetContent(context));
        //std::cout << reinterpret_cast<char*>(product_html_element->content)<<"aaaaah" << std::endl;
        //xmlNodePtr strong_html = xmlXPathEvalExpression((xmlChar *) ".//strong", context)->nodesetval->nodeTab[0];
        //std::string strong = std::string(reinterpret_cast<char *>(xmlNodeGetContent(strong_html)));
        //std::cout << strong << std::endl;

        //PokemonProduct pokemon_product = {url, image, name, price};
        //pokemon_products.push_back(pokemon_product);xmlNodePtr url_html_element = xmlXPathEvalExpression((xmlChar *) ".//a", context)->nodesetval->nodeTab[0];
        //std::string url = std::string(reinterpret_cast<char *>(xmlGetProp(url_html_element, (xmlChar *) "href")));
        //xmlNodePtr image_html_element = xmlXPathEvalExpression((xmlChar *) ".//a/img", context)->nodesetval->nodeTab[0];
        //std::string image = std::string(reinterpret_cast<char *>(xmlGetProp(image_html_element, (xmlChar *) "src")));
        //xmlNodePtr name_html_element = xmlXPathEvalExpression((xmlChar *) ".//a/h2", context)->nodesetval->nodeTab[0];
        //std::string name = std::string(reinterpret_cast<char *>(xmlNodeGetContent(name_html_element)));
        //xmlNodePtr price_html_element = xmlXPathEvalExpression((xmlChar *) ".//a/span", context)->nodesetval->nodeTab[0];
        //std::string price = std::string(reinterpret_cast<char *>(xmlNodeGetContent(price_html_element)));

        //PokemonProduct pokemon_product = {url, image, name, price};
        //pokemon_products.push_back(pokemon_product);
   // }





    return 0;



}
