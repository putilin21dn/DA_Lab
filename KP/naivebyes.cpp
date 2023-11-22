#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
#include "nlohmann/json.hpp"
#include <math.h>
#include "naivebyes.hpp"

using namespace std;
const string file_name = "file_stats";


vector<string> tokenize(const string& input) {
        vector<string> tokens;
        string token;
        for (char c : input) {
            if (c == ',' || c=='\n' ) {
                if (!token.empty()) {
                    
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                if(!token.empty() && c == ' '){
                    continue;
                }

                if (c>='A' && c <='Z'){
                    token += char(c+32);
                    }
                    else{
                        token += c;
                    }       
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
}



NaiveBayes model;



int main(int argc, char * argv[]) {
    
    bool action;
    string stats_name="", input_name="", output_name="";
    for(int i=1; i<argc; ++i){

        if (string(argv[i]) == "learn") action = true;
        if(string(argv[i]) == "classify") action = false;

        if(string(argv[i]) == "--stats") stats_name = string(argv[i+1]);
        if(string(argv[i]) == "--input") input_name = string(argv[i+1]);
        if(string(argv[i]) == "--output") output_name = string(argv[i+1]);
    }

    if(action){

        ifstream out(input_name);
                int n;
                string s;

                if(out.is_open()){
                    
                    while(!out.eof()){
                        out >> n;                 
                        string str;
                        getline(out, str);
                        getline(out, str);
                        vector<string> tegs = tokenize(str);
                        vector<string> X;
                        for (int i = 0; i<n+1; ++i){
                            getline(out,s);
                            X.push_back(s);
                        }
                        model.fit(X,tegs);

                    }
                    
                    model.save_json(output_name);
                    fstream File;
                    File.open(file_name, std::ios::out);
                    File << output_name;
                    File.close();           
                    
                }
                out.close();
        
    }
    else{

        if(stats_name!=""){
            model.load_json(stats_name);
            model.output();
        }

        if(input_name!=""){

                ifstream File(file_name);
                string name_file_stats;
                getline(File, name_file_stats);
                File.close();
                model.load_json(name_file_stats);

                ifstream out(input_name);
                int n;
                string s;

                if(out.is_open()){
                    vector<vector<string>> predicts;
                    while(!out.eof()){
                        out >> n;                 
                        string str;
                        getline(out,str);
                        vector<string> X;
                        for (int i = 0; i<n+1; ++i){
                            getline(out,s);
                            X.push_back(s);
                        }
                        vector<string> predict = model.predict(X);
                        predicts.push_back(predict);
                        }
                    model.save_predict(output_name, predicts);
                }
                out.close();
        }

        if(output_name!=""){
            vector<vector<string>> predicts = model.load_predict(output_name);

            for(auto el : predicts){
                model.print_predict(el);
            }
        }

    }

    return 0;
}