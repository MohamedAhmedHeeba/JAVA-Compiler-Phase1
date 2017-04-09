#include <iostream>
#include<bits/stdc++.h>
#include "State.h"
#include "NFA_to_DFA.h"
#include "D_state.h"
#include "Min_DFA.h"
#include "Parser.h"
#include "NFA.h"
#include "Reader.h"
#include "Matcher.h"

using namespace std;
void print_DFA(D_state* startingNode)
{
    int counter = 0;
    stack < D_state* > current;
    current.push(startingNode);
    set < D_state* > vis;
    //counter++;
    //vis.insert(startingNode);
    /*if (startingNode -> is_accept())
    {
        cout << "NOde << prio = " << startingNode -> get_priority() << endl;
        cout << "NOde << Name = " << startingNode -> get_name() << endl;
    }*/
    while(!current.empty())
    {
        D_state* x = current.top();
        vis.insert(x);
        x->print();
        current.pop();
        for(map <char, D_state* > :: iterator it = (x -> next).begin(); it != (x -> next).end(); ++it)
        {
            if(vis.find((it -> second)) == vis.end())
            {
                //vis.insert((it -> second));
                current.push((it -> second));
                //cout << "heebaaaaaaaaaaaaaaa\n";
                //D_state *temp = (it -> second);
                //temp->print();

                /*if ( (it -> second)-> is_accept())
                {
                    cout << "NOde << prio = " << (it -> second) -> get_priority() << endl;
                    cout << "NOde << Name = " << (it -> second) -> get_name() << endl;
                }*/
                counter++;
            }
        }
    }
    cout << "NFA >>>>>>>>>>> :" << counter << endl;
}
int main()
{

    cout << "\n---------------new NFA----------------------------\n";
    ifstream grammer ("grammer.txt");
    Parser nfaGenerator;
    NFA *nf = nfaGenerator.run (grammer);
    grammer.close();
    nf -> print();

    cout << "\n\n--------------------------------DFA-----------------------\n";
    NFA_to_DFA *ntd = new NFA_to_DFA();
    set<D_state*> DFA = ntd->convert_NFA_to_DFA(nf -> startingNode);
    cout << "\nSize = " << DFA.size() <<endl;

    cout << "\n----------------------------After min--------------------\n";
    Min_DFA* mdfa= new Min_DFA();
    D_state* mi = mdfa -> DFA_min(DFA);
    cout << endl;
    print_DFA(mi);


    /** HEEBA ADD THIS CODE */

    Reader *reader = new Reader();
    reader->parse("Test.txt");
    vector<string> tokens =reader->get_tokens();

    Matcher *matcher = new Matcher();
    matcher->set_output_file_name("output.txt");

    matcher->match(tokens,mi);

    /** END HEEBA */

    return 0;
}
