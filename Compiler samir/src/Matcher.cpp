#include "Matcher.h"
#include <iostream>
#include <fstream>
#include"State.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include "D_state.h"


using namespace std;

Matcher::Matcher()
{
    //ctor
}

Matcher::~Matcher()
{
    //dtor
}

void Matcher::match(vector<string> token,D_state* start)
{
    /*for all tokens try to match them*/
    for(int i = 0 ; i < token.size() ; i++)
    {
        this->fun(token[i], start);
    }
    /*write in the output file*/
    write_output_file(this->output_file_name);
}

vector<string> Matcher::get_sym_table()
{
    return this->symbol_table;
}

void Matcher::set_output_file_name(string output_file_name)
{
    this->output_file_name = output_file_name;
}

void Matcher::write_output_file(string name)
{
    /*open file*/
    ofstream myfile (name.c_str());
    if (myfile.is_open())
    {
        /*write in file*/
        myfile << this->out;
        /*close file*/
        myfile.close();
    }
}

bool Matcher::error_recovery(string &str, D_state* start)
{

    if(str.size() == 1) return false;

    for(int i = 1 ; i < str.size() ; i++)
    {
        //string str = str.substr (i);
        str = str.substr(i);
        if(this->fun(str,start))
        {
            return true;
        }
    }
    return false;
}





bool Matcher::fun(string &str, D_state* start)
{
    int pos = 0;
    /**try to match string str*/
    /*get the start state*/
    //set<D_state*>::iterator start = DFA.begin();
    /*temp use as iterator*/
    D_state * temp = start;
    D_state * last_accept = nullptr;
    for(std::string::size_type i = 0; i < str.size(); ++i)
    {
        if(temp->is_accept()){
            last_accept = temp;
            pos = i;
        }
        /*follow the sequance of str chars*/
        temp = temp->get_next(str[i]);                   ///**MAY BE ERROR*/
        if(temp->get_id() == -1){
            /*generate error to output file*/
            this->out = this->out + "ERROR11 in symbol  " + str[i] + '\n';
            if(this->error_recovery(str,start)){
                return true;
            }else{
                 /*generate error to output file*/
                //this->out = this->out + "ERROR in symbol  " + str + '\n';
                return false;
            }
        }
    }
    /*once exit str for loop = check if temp is acceptance state */
    if(temp->is_accept()){
        /*get the type matched from temp name*/
        string type = temp->get_name();
        /*write pattern in the output file*/
        if(type == "Keyword" || type == "Punctuation"){
            this->out = this->out + str + '\n';
        }else{
            this->out = this->out + type + '\n';
        }
        if(type == "id")                                 ///**MAY BE ERROR*/
        {
            /*add to sym table*/
            this->symbol_table.push_back(str);
        }
        return true;
    }else if(last_accept != nullptr && last_accept->is_accept()){
        /*get the type matched from temp name*/
        string type = last_accept->get_name();
        /*write pattern in the output file*/
        if(type == "Keyword" || type == "Punctuation"){
            this->out = this->out + str.substr(0,pos) + '\n';
        }else{
            this->out = this->out + type + '\n';
        }
        if(type == "id"){
            /*add to sym table*/
            this->symbol_table.push_back(str);
        }
        /*seperate str and call back fun again with the reminder*/
        string reminder = str.substr (pos);
        return this->fun(reminder, start);
    }else{
        if(this->error_recovery(str,start)){      /*deleted from start done :D and write good in file*/
        }else{
            /*generate error to output file*/
            this->out = this->out + "ERROR22 in symbol  " + str + '\n';
            return false;
        }
    }

}
