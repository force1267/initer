#ifndef INITER_H
#define INITER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

namespace initer {
    typedef vector<string> strings;
    typedef pair<string, strings> cfg;
    typedef vector<cfg> ini;

    string statemachine(ini& o, strings& tokens);
    ini parse(strings tokens, int& retcode, string& output);

    strings readFile(string filename, int& retcode);
    void writeFile(string filename, ini p, int& retcode);
    
    int load(string filename, ini& file, string& parse_error);
    int save(string filename, ini& file);
};

#endif // INITER_H
