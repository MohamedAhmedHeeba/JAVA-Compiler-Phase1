#include "Parser.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}


void Parser::parse(string file_name)
{
    /*reading from file*/
    string str = "", line;
    ifstream myfile (file_name.c_str());
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            str = str +' '+line;
        }
        myfile.close();
    }

    /*splits str on spaces*/
    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);

    /*handle special cases for each token*/
    for(int i = 0; i < tokens.size(); i++ )
    {
        /*Handel the special cases here*/
        /*  {str}     ,str,      (str)     op str op      ;str;*/
    }

    this->tokens = tokens;

}


vector<string> Parser::get_tokens(){
    return this->tokens;
}
