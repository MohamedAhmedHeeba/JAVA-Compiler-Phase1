#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include"State.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include "D_state.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Parser
{
    public:
        Parser();
        virtual ~Parser();

        void parse(string file_name);

        vector<string> get_tokens();

    protected:

    private:

        vector<string> tokens;

};

#endif // PARSER_H
