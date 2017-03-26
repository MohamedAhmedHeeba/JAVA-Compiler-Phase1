#include <iostream>
#include<bits/stdc++.h>
#include "State.h"
#include "NFA_to_DFA.h"
#include "D_state.h"
#include "Min_DFA.h"
#include "Matcher.h"
#include "Parser.h"


using namespace std;

int main()
{
    vector<State*> tran_table;
    int size;

    /***
        //example 1 (a|b)*abb
    size = 11;
    for(int i = 0 ; i < size ; i++){
        State* state = new State(false);
        state-> set_id(i);
        tran_table.push_back(state);
    }

    tran_table[0]->add_to_table('@', tran_table[7]);
    tran_table[0]->add_to_table('@', tran_table[1]);
    tran_table[1]->add_to_table('@', tran_table[2]);
    tran_table[1]->add_to_table('@', tran_table[4]);
    tran_table[2]->add_to_table('a', tran_table[3]);
    tran_table[3]->add_to_table('@', tran_table[6]);
    tran_table[4]->add_to_table('b', tran_table[5]);
    tran_table[5]->add_to_table('@', tran_table[6]);
    tran_table[6]->add_to_table('@', tran_table[1]);
    tran_table[6]->add_to_table('@', tran_table[7]);
    tran_table[7]->add_to_table('a', tran_table[8]);
    tran_table[8]->add_to_table('b', tran_table[9]);
    tran_table[9]->add_to_table('b', tran_table[10]);
    tran_table[10] -> set_is_accepted(true);
    tran_table[10] -> set_name("expression");
    */

    /***
        //example 2 a*(b|a)*

    size = 11;
    for(int i = 0 ; i < size ; i++){
        State* state = new State(false);
        state-> set_id(i);
        tran_table.push_back(state);
    }

    tran_table[0]->add_to_table('@', tran_table[1]);
    tran_table[0]->add_to_table('@', tran_table[3]);
    tran_table[1]->add_to_table('a', tran_table[2]);
    tran_table[2]->add_to_table('@', tran_table[1]);
    tran_table[2]->add_to_table('@', tran_table[3]);
    tran_table[3]->add_to_table('@', tran_table[4]);
    tran_table[3]->add_to_table('@', tran_table[6]);
    tran_table[4]->add_to_table('@', tran_table[7]);
    tran_table[4]->add_to_table('@', tran_table[9]);
    tran_table[7]->add_to_table('b', tran_table[8]);
    tran_table[9]->add_to_table('a', tran_table[10]);
    tran_table[8]->add_to_table('@', tran_table[5]);
    tran_table[10]->add_to_table('@', tran_table[5]);
    tran_table[5]->add_to_table('@', tran_table[4]);
    tran_table[5]->add_to_table('@', tran_table[6]);
    tran_table[6] -> set_is_accepted(true);
    tran_table[6] -> set_name("expression");

    */

    //example 3 (a+b+)*

    size = 9;
    for(int i = 0 ; i < size ; i++){
        State* state = new State(false);
        state-> set_id(i);
        tran_table.push_back(state);
    }

    tran_table[0]->add_to_table('@', tran_table[1]);
    tran_table[0]->add_to_table('@', tran_table[3]);
    tran_table[1]->add_to_table('@', tran_table[4]);
    tran_table[4]->add_to_table('a', tran_table[5]);
    tran_table[5]->add_to_table('@', tran_table[4]);
    tran_table[5]->add_to_table('@', tran_table[6]);
    tran_table[6]->add_to_table('@', tran_table[7]);
    tran_table[7]->add_to_table('b', tran_table[8]);
    tran_table[8]->add_to_table('@', tran_table[7]);
    tran_table[8]->add_to_table('@', tran_table[2]);
    tran_table[2]->add_to_table('@', tran_table[1]);
    tran_table[2]->add_to_table('@', tran_table[3]);

    tran_table[3] -> set_is_accepted(true);
    tran_table[3] -> set_name("expression");


    for(int i = 0 ; i < size ; i++){
        tran_table[i]->print();
    }

    set<State*> NFA;
    for(int i = 0 ; i < size ; i++){
        NFA.insert(tran_table[i]);
    }

    NFA_to_DFA *ntd = new NFA_to_DFA();
    set<D_state*> DFA = ntd->convert_NFA_to_DFA(NFA);

    cout << endl;
    cout << endl;
    cout << DFA.size() <<endl;

    for (std::set<D_state*>::iterator it=DFA.begin(); it!=DFA.end(); ++it){
        D_state *state = *it;
        state->print();
    }

    Min_DFA* mdfa= new Min_DFA();
    set<D_state*> mi = mdfa -> DFA_min(DFA);

    for (std::set<D_state*>::iterator it=mi.begin(); it!=mi.end(); ++it){
        D_state *state = *it;
        state->print();
    }

    Parser *parser = new Parser();
    parser->parse("Test.txt");
    vector<string> tokens =parser->get_tokens();

    Matcher *matcher = new Matcher();
    matcher->set_output_file_name("output.txt");

    matcher->match(tokens,mi);

    /*set<State*> set1;
    set<State*> set2;
    set<State*> set3;

    set1.insert(tran_table[0]);
    set1.insert(tran_table[1]);
    set1.insert(tran_table[2]);

    set2.insert(tran_table[3]);
    set2.insert(tran_table[4]);
    set2.insert(tran_table[5]);

    set2.insert(tran_table[6]);
    set2.insert(tran_table[7]);
    set2.insert(tran_table[8]);


    D_state* state1 = new D_state(set1);

    D_state* state2 = new D_state(set2);

    D_state* state3 = new D_state(set3);

    state1->set_next('a',state2);
    state1->set_next('b',state3);
    state1->set_next('c',state1);

    vector<D_state*> table;

    table.push_back(state1);
    table.push_back(state2);
    table.push_back(state3);*/



/*
    State* s1 = new State(false);
    s1->set_id(1);

    State* s2 = new State(false);
    s2->set_id(2);

    State* s3 = new State(false);
    s2->set_id(3);

    set<State*> ss1;
    ss1.insert(s1);
    ss1.insert(s2);
    ss1.insert(s3);

    set<State*> ss2;
    ss2.insert(s3);
    ss2.insert(s1);
    ss2.insert(s2);

    if(ss1 == ss2){
        cout << "yes";
    }else{
        cout << "no";
    }*/

    return 0;
}
