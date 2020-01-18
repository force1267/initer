#include <vector>
#include <string>
// #include <iostream>
#include <fstream>
#include <sstream>
#include "./initer.h"

using namespace std;

string initer::statemachine(ini& o, strings& tokens) {
    int pos = 0;
    int state = 0;
    string key;
    strings values;
    while(pos <= tokens.size() + 1) {
        string t = tokens.size() > pos ? tokens[pos] : "";
        switch (state) {
            case 0:
                if(t == "=") return "started with `=`";
                if(t != "") {
                    key = t;
                    state = 1;
                } else return "empty file";
                break;
            case 1:
                if(t != "=") return "started list without `=`";
                if(t != "") {
                    state = 2;
                } else {
                    return "did not start a list";
                }
                break;
            case 2:
                if(t == "=") return "two `=`";
                if(t != "") {
                    values.push_back(t);
                    state = 3;
                } else {
                    state = 4;
                }
                break;
            case 3:
                if(t == "=") {
                    string tmpkey = values[values.size() - 1];
                    values.pop_back();
                    o.push_back(cfg(key, values));
                    key = tmpkey;
                    values = strings();
                    state = 2;
                } else if(t != "") {
                    values.push_back(t);
                    state = 3;
                } else {
                    state = 4;
                }
                break;
            case 4:
                o.push_back(cfg(key, values));
                return "";

            default:
                return "unexpected token";
        }

        pos ++;
    }
    return "";
}

initer::ini initer::parse(strings tokens, int& retcode, string& output) {
    ini empty;
    ini res;
    output = statemachine(res, tokens);
    if(output == "") {
        retcode = 0;
        return res;
    } else {
        retcode = 1;
        return empty;
    }
}

initer::strings initer::readFile(string filename, int& retcode) {
    fstream file;
    strings tokens;
    file.open(filename, ios::out | ios::app);
    file.close();
    file.open(filename, ios::in);
    if(!file) {
        retcode = 2;
        return tokens;
    }
    while(!file.eof()) {
        string line;
        getline(file, line);
        istringstream ls(line);
        string token;
        while(ls >> token) {
            tokens.push_back(token);
        }
    }
    file.close();
    return tokens;
}

void initer::writeFile(string filename, ini p, int& retcode) {
    ofstream file;
    strings tokens;
    file.open(filename);
    if(!file) {
        retcode = 2;
        return;
    }
    for(auto c: p) {
        file << c.first << " =" << endl;
        for(auto cc: c.second) {
            file << cc << endl;
        }
        file << endl;
    }
    retcode = 0;
    file.close();
}

int initer::load(string filename, ini& file, string& parse_error) {
    int code = 0;
    strings tokens = readFile(filename, code);
    if(code != 0) { return code; }
    file = parse(tokens, code, parse_error);
    return code;
}

int initer::save(string filename, ini& file) {
    int code = 0;
    writeFile(filename, file, code);
    return code;
}

// using namespace initer;
// int main(int argc, char **argv) {
//     if(!argv[1]) return 1;
//     string filename = argv[1];
//     ini file;
//     string parse_error;
//     int code = load(filename, file, parse_error);
//     if(code == 0) {
//         code = save(filename + ".tmp.ini", file);
//     } else {
//         cout << parse_error << endl;
//     }
//     return code;
// }
