
#ifndef NAIVEBYES_HHP
#define NAIVEBYES_HHP
#include <bits/stdc++.h>

using namespace std;
using json = nlohmann::json;
using ll = long long;
const double EPS = 1;


json ConvertToJsonSingleInt(unordered_map<string, ll> map )
{
    json js;

    for(auto& element : map)
    {
        js[element.first] = element.second;

    }
    return js;
}

json ConvertToJsonSingleDouble(unordered_map<string, double> map )
{
    json js;

    for(auto& element : map)
    {
        js[element.first] = element.second;

    }
    return js;
}

json ConvertToJson(unordered_map<string, unordered_map<string, ll> > map)
{
    json js;

    for(auto& element : map)
    {
        js[element.first] = ConvertToJsonSingleInt(element.second);

    }
    return js;
}

bool compare(const pair<string,double> &p1, const pair<string,double> &p2 ){
        return p1.second < p2.second;
    }


class NaiveBayes{
private:
    unordered_map<string, unordered_map<string, ll>> word_counts;    // number of each word in train with label
    unordered_map<string, ll> class_counts;    // number of each class
    unordered_map<string, ll> word_total_counts;  // number of words for each class in train
    unordered_map<string, double> class_probabilities; // probability for each class
    multiset<string> all_tegs; // all tegs from file
    bool flag_load = true;
    vector<long double> scores;
    ll count = 0;
    string name_file = "stop_words";


    set<string> stop_symbol = {" ", ",", ".", "!", "<", ">", ":", "(", ")", "/", "-", "_", "=", "?", ";", "&", "^", "#"};
    set<string> stop_words = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", \
    "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", \
    "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were",\
     "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as",\
      "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", \
      "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", \
      "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very",\
       "s", "t", "can", "will", "just", "don", "should", "now"};
    

    // parsing a string into tokens
    vector<string> tokenize(const string& input) {
        vector<string> tokens;
        string token;
        for (char c : input) {
            if (stop_symbol.count(string(&c))!=0) {
                if (!token.empty()) {
                    
                    tokens.push_back(token);
                    token = "";
                }
            } else {
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

    void print_map(const unordered_map<string,ll> mapp){
         for(auto& element : mapp)
        {
            cout << element.first << " " <<  element.second << '\n';

        }
    }
    void print_map(const unordered_map<string,double> mapp){
         for(auto& element : mapp)
        {
            cout << element.first << " " <<  element.second << '\n';

        }
    }
    void print_mmap(const unordered_map<string, unordered_map<string,ll>> mapp){
        for(auto &elem : mapp){
            cout << elem.first << " : ";
            print_map(elem.second);
        }
    }

     double soft_max(vector<pair<string, double>> scores,  double score){

        double all_score = 0.;

        for(int i=0; i<scores.size();++i){
            all_score += scores[i].second;
        }

        return score/all_score;

        
    }



    
public:

    void fit(const vector<string>& X, const vector<string>& y) {
        count += X.size();
        for(int j = 0; j < y.size(); ++j){

            

            for (int i = 0; i < X.size(); i++) {
                const string& object = X[i];
                // cout << object << '\n';
                vector<string> tokens = tokenize(object);
                
                string label = y[j];
                // cout << label << '\n';
                all_tegs.insert(label);
                class_counts[label]++;
                
            
                for (const string& token : tokens) {
                    if(stop_words.count(token)==0){
                        word_counts[token][label]++;
                        word_total_counts[label]++;
                    }
                    
                }
            }
            
        }
    
    }

    void save_json(string file) {
        ll len_y = all_tegs.size();
        // cout << len_y << '\n';
        for (auto& it : class_counts) {
            const string label = it.first;
            int count_label = it.second;
            class_probabilities[label] = (double)count_label /len_y ;   
            
        }

        // Save map to json
        json word_counts_json = ConvertToJson(word_counts);
        json class_counts_json = ConvertToJsonSingleInt(class_counts);
        json word_total_counts_json = ConvertToJsonSingleInt(word_total_counts);
        json class_probabilities_json = ConvertToJsonSingleDouble(class_probabilities);
        fstream File;
        File.open(file, std::ios::out);
        flag_load = true;

        File << word_counts_json << '\n' << class_counts_json << '\n' << word_total_counts_json << '\n' << class_probabilities_json;
        File.close();
    }

    void load_json(string file){
        // Read from json stats
        ifstream i(file);

        if(i.is_open()){
            json word_counts_json, class_counts_json, word_total_counts_json, class_probabilities_json;
            i >> word_counts_json >> class_counts_json >> word_total_counts_json >> class_probabilities_json;

            word_counts =  word_counts_json.get<unordered_map<string, unordered_map<string, ll>>>();
            class_counts = class_counts_json.get<unordered_map<string, ll>>();
            word_total_counts = word_total_counts_json.get<unordered_map<string, ll>>();
            class_probabilities = class_probabilities_json.get<unordered_map<string, double>>();
        }
        else{
            cout << "Don't find file!\n";
            flag_load = false;
        }
    }

    void output(){
        
        if(flag_load){
            print_mmap(word_counts);
            print_map(class_counts);
            print_map(word_total_counts);
            print_map(class_probabilities);
        }
        else{
            cout << "Don't find file!\n";
        }
        
    }
    
    vector<string> predict(const vector<string>& X) {     

        vector<pair<string,double>> scores;

        set<string> unique_word;
        int N = 0;
        for(int i = 0; i<X.size(); ++i){
            vector<string> tokens = tokenize(X[i]);
            N += tokens.size();

            
            for(auto elem : tokens){
                unique_word.insert(elem);
            }
        }
        
        for (const auto& it : class_probabilities) {
            const string label = it.first;
            
            long double score = log(it.second);   // P(y_i = label)
            // cout <<it.first << " " << log(it.second) << '\n'; 
            // long double score = it.second;
            
            ll uniq_size = unique_word.size();
            for(int i = 0; i<X.size(); ++i){

                vector<string> tokens = tokenize(X[i]);

                for (string token : tokens) {
                    if(stop_words.count(token)==0){
                        int word_count = word_counts[token][label];   
                        // cout << word_count << '\n';
                        int total_words = word_total_counts[label];   
                        // cout << token << " " << word_count << " " << total_words << '\n';
                        score += log((long double)(word_count+EPS) / (total_words + EPS*uniq_size)); // P(x_i | y_i = label)
                        // score *= (word_count+EPS) / (total_words + EPS*uniq_size);
                    }
                    
                    
                }
                
            }

            scores.push_back({label,pow(2.718281828, score/N)});

            
            // cout << label << " " << score << '\n';

        }

        sort(rbegin(scores), rend(scores), compare);


        const double treshold = 0.254;
        vector<string> res;

        for(int i = 0; i < scores.size(); ++i){
            // cout << scores[i].first << " " << soft_max(scores,scores[i].second) << '\n';
            if(soft_max(scores,scores[i].second) > treshold) res.push_back(scores[i].first);
        }

        return res;
    }

    void save_predict(string file, vector<vector<string>> res){

        fstream File;
        File.open(file, std::ios::out);
        string text = "Not find!";

        for (int j=0; j<res.size(); ++j){
            vector<string> elem = res[j];
            if(elem.size()==0){
                if(j!=res.size()-1){
                    File << text << '\n';
                }
                else File << text;
            }
            
            else{
                for(int i=0; i<elem.size()-1; ++i){
                File << elem[i] << ",";
                }
                if(j!=res.size()-1){
                    File << elem[elem.size()-1] << '\n';
                }
                else File << elem[elem.size()-1];
            }
        }
        

        File.close();
    }

    vector<vector<string>> load_predict(string file){
        ifstream out(file);
        vector<vector<string>> s;
        vector<string> tokens;
        while(!out.eof()){
            string score;
            getline(out,score);
            if(score == "Not find!"){
                 tokens = {"Not find!"};
            }
            else{
                 tokens = tokenize(score);
            }
            
            s.push_back(tokens);
        }
        return s;

    }

    void print_predict(vector<string> res){
        for(int i=0; i<res.size()-1; ++i){
            cout << res[i] << ", ";
        }
        
        cout << res[res.size()-1]  << '\n';
    }


};

#endif