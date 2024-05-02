#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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

string print_menu()
{

    int x_max, y_max;
    getmaxyx(stdscr, y_max,x_max);

    WINDOW * menu = newwin(15,79/2,y_max/2-10,x_max/2-(79/2/2));

    int in_menu = 1;

    while(in_menu)
    {


        box(menu,'|','-');

        mvwaddstr(menu, 1,1,"What what you like to do?");
        mvwaddstr(menu, 4,1,"Search Database: s");
        mvwaddstr(menu, 6,1,"Get Random Entry: r");
        mvwaddstr(menu, 8,1,"Quit: q");


        wrefresh(menu);

        refresh();


        int menu_input =  wgetch(menu);

        if(menu_input == 's')
        {
            in_menu = 0;
            string scp;
            int inputting = 1;
            char input;
            //search specific number
            mvwaddstr(menu,5,2,"Enter Input: scp-");
            while(inputting)
            {
                input = wgetch(menu);
                if(input - '0' >= 0 && input - '0' <= 9)
                {

                    waddch(menu, input);
                    scp+=input;
                }
                else if(input == '\n')
                {
                    delwin(menu);
                    inputting = 0;
                    if(stoi(scp) < 1000)
                    {
                        string output = "";
                        string numstring = scp;
                        for(long unsigned int i = 0; i < 3 - numstring.length(); i++)
                        {
                            output.append("0"); 
                        }
                        output.append(numstring);
                        return "scp-" + output; 


                    }
                    else
                    {
                        return "scp-" + scp;
                    }
                }
                    //gen random number
            }
        }
        else if(menu_input == 'r')
        {
            in_menu = 0;
            
            delwin(menu);


            int random = rand() % 100 + 1;

            if(random < 1000)
            {
                string output = "";
                string numstring = to_string(random);
                for(long unsigned int i = 0; i < 3 - numstring.length(); i++)
                {
                   output.append("0"); 
                }
                output.append(numstring);
                return "scp-" + output; 


            }
            else
            {
                return "scp-" + to_string(random);
            }
            
            //gen random number
        }
        else if(menu_input == 'q')
        {

            delwin(menu);
            endwin();
            exit(0);

        }
    }
 

    return "";
}


string print_sub_menu()
{

    int x_max, y_max;
    getmaxyx(stdscr, y_max,x_max);

    WINDOW * menu = newwin(15,79/2,y_max/2-10,x_max/2-(79/2/2));

    int in_menu = 1;

    while(in_menu)
    {


        box(menu,'|','-');

        mvwaddstr(menu, 1,1,"What what you like to do?");
        mvwaddstr(menu, 4,1,"Search Database: s");
        mvwaddstr(menu, 6,1,"Get Random Entry: r");
        mvwaddstr(menu, 8,1,"Quit: q");
        mvwaddstr(menu, 10,1,"Close Menu: m");


        wrefresh(menu);

        refresh();


        int menu_input =  wgetch(menu);

        if(menu_input == 's')
        {
            in_menu = 0;
            string scp;
            int inputting = 1;
            char input;
            //search specific number
            mvwaddstr(menu,5,2,"Enter Input: scp-");
            while(inputting)
            {
                input = wgetch(menu);
                if(input - '0' >= 0 && input - '0' <= 9)
                {

                    waddch(menu, input);
                    scp+=input;
                }
                else if(input == '\n')
                {
                    delwin(menu);
                    inputting = 0;
                    if(stoi(scp) < 1000)
                    {
                        string output = "";
                        string numstring = scp;
                        for(long unsigned int i = 0; i < 3 - numstring.length(); i++)
                        {
                            output.append("0"); 
                        }
                        output.append(numstring);
                        return "scp-" + output; 


                    }
                    else
                    {
                        return "scp-" + scp;
                    }
                }
                    //gen random number
            }
        }
        else if(menu_input == 'r')
        {
            in_menu = 0;
            
            delwin(menu);


            int random = rand() % 100 + 1;

            if(random < 1000)
            {
                string output = "";
                string numstring = to_string(random);
                for(long unsigned int i = 0; i < 3 - numstring.length(); i++)
                {
                   output.append("0"); 
                }
                output.append(numstring);
                return "scp-" + output; 


            }
            else
            {
                return "scp-" + to_string(random);
            }
            
            //gen random number
        }
        else if(menu_input == 'm')
        {

            in_menu = 0;
            werase(menu);
            delwin(menu);

        }
        else if(menu_input == 'q')
        {

            delwin(menu);
            endwin();
            exit(0);

        }
    }
 

    return "";
}






void print_page(string scp)
{


    int x_max, y_max;
    getmaxyx(stdscr, y_max,x_max);

    std::string link = "https://scp-wiki.wikidot.com/" + scp;
    std::string html_document = get_request(link);
    //std::cout << html_document;

    curl_global_cleanup();

    htmlDocPtr doc = htmlReadMemory(html_document.c_str(), html_document.length(), nullptr, nullptr, HTML_PARSE_NOERROR);

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr product_html_elements = xmlXPathEvalExpression((xmlChar *) "//div[contains(@id, 'page-content')]/*", context);


    int count = 0;
    for (int j = 0; j < product_html_elements->nodesetval->nodeNr; j++) {
        count++;
    }

    WINDOW * read = newpad(20000,x_max/2);
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

                }
                else if (child->type == XML_ELEMENT_NODE &&
                        xmlStrcmp(child->name, (const xmlChar *)"strong") == 0) {
                    string content = reinterpret_cast<char*>(child->children->content);
                    wattron(read ,A_BOLD | A_UNDERLINE);
                    waddstr(read, content.c_str());
                    wattroff(read, A_BOLD | A_UNDERLINE);
                }
                child = child->next;
            }
            waddstr(read, "\n");
        }
        //if element is not a p
        //else if(element->type == XML_ELEMENT_NODE &&
        //        xmlStrcmp(element->name, (const xmlChar *)"div") == 0) {
        //    xmlNodePtr child = element->children;
        //    xmlAttrPtr attribute = element->properties;

        //    while (attribute != NULL) {
        //        if (xmlStrcmp(attribute->name, (const xmlChar *)"class") == 0 &&
        //               xmlStrcmp(attribute->name, (const xmlChar *)"collapsible-block") == 0)
        //        {
        //            while(child != NULL) {

        //                if(xmlStrcmp(attribute->name, (const xmlChar *)"class") == 0 &&
        //               xmlStrcmp(attribute->name, (const xmlChar *)"collapsible-block-content") == 0)
        //                {
        //                    


        //                }
        //            }
        //            attribute = attribute->next;
        //        }
        //        child = child->next;
        //    }
        //    waddstr(read, "\n");
        //}
    }

    int x, y;

    getyx(read, y, x);



    prefresh(read,0,0,0,x_max/2 - x_max/2/2,y_max - 2,x_max/2 + x_max/2/2);

    WINDOW * sub_menu = newwin(0,x_max,y_max-1,0);
    init_pair(2,COLOR_BLACK,COLOR_RED);

    wbkgd(sub_menu, COLOR_PAIR(2));
    string menu_options = " - Menu: m  -  Scroll Up: j - Scroll Down: k - Quit: q - ";
    mvwaddstr(sub_menu,0,x_max/2 - menu_options.length()/2, menu_options.c_str() );
    wrefresh(sub_menu);


    int input;
    int pad_location = 0;
    int in_menu = 1;
    while(in_menu)
    {
        input = wgetch(read);

        if(input == 'j' && pad_location >= 0)
        {
            pad_location--;
            prefresh(read, pad_location,0,0,x_max/2-x_max/2/2,y_max - 2,x_max/2+x_max/2/2);

        }
        else if(input == 'k' && pad_location <= y*2)
        {
            pad_location++;            
            prefresh(read, pad_location,0,0,x_max/2-x_max/2/2,y_max - 2,x_max/2+x_max/2/2);
        }
        else if(input == 'm')
        {
            string new_page = print_sub_menu();

            if(new_page != "")
            {
                in_menu = 0;
                delwin(sub_menu);
                delwin(read);
                print_page(new_page);
            }
            else
            {
            prefresh(read, pad_location,0,0,x_max/2-x_max/2/2,y_max - 2,x_max/2+x_max/2/2);
            }
        }
        else if(input == 'q')
        {

            delwin(sub_menu);
            delwin(read);
            endwin();
            exit(0);

        }



    }
}






int main() {
    //initialize curl globally
    curl_global_init(CURL_GLOBAL_ALL);
    
    //std::string html_document = get_request("https://scp-wiki.wikidot.com/scp-5000");
    ////std::cout << html_document;

    //curl_global_cleanup();

    //htmlDocPtr doc = htmlReadMemory(html_document.c_str(), html_document.length(), nullptr, nullptr, HTML_PARSE_NOERROR);

    //xmlXPathContextPtr context = xmlXPathNewContext(doc);
    //xmlXPathObjectPtr product_html_elements = xmlXPathEvalExpression((xmlChar *) "//div[contains(@id, 'page-content')]/p", context);

    srand(time(NULL));


    initscr();
    cbreak();
    noecho();
    refresh();
    set_escdelay(0);
    
    start_color();
    refresh();
    init_pair(1,COLOR_RED,COLOR_BLACK);

   int x_max, y_max;
    getmaxyx(stdscr, y_max,x_max);

 

    attron(COLOR_PAIR(1));
    mvaddstr(1,x_max/2-79/2," _____  _____  _____    ____   _____  _____  _____  _____  _____  _____  _____ ");
    mvaddstr(2,x_max/2-79/2,"|   __||     ||  _  |  |    \\ |  _  ||_   _||  _  || __  ||  _  ||   __||   __|");
    mvaddstr(3,x_max/2-79/2,"|__   ||   --||   __|  |  |  ||     |  | |  |     || __ -||     ||__   ||   __|");
    mvaddstr(4,x_max/2-79/2,"|_____||_____||__|     |____/ |__|__|  |_|  |__|__||_____||__|__||_____||_____|");
    attroff(COLOR_PAIR(1));
    
    //create original menu
    
   
    




    string scp = print_menu();


    clear();
    refresh();
  
    print_page(scp);
    refresh();
    



    return 0;



}
