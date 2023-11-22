#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class NaiveBayes{
private:
    unordered_map<string, unordered_map<string, int>> word_counts;    // number of each word in train with label
    unordered_map<string, int> class_counts;    // number of each class
    unordered_map<string, int> word_total_counts;  // number of words for each class in train
    unordered_map<string, double> class_probabilities; // probability for each class
    
    // parsing a string into tokens
    vector<string> tokenize(const string& input) {
        vector<string> tokens;
        string token;
        for (char c : input) {
            if (c == ' ') {
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
    
public:
    void fit(const vector<string>& X, const vector<string>& y) {
        for (int i = 0; i < y.size(); i++) {
            const string& object = X[i];
            const string& label = y[i];
            class_counts[label]++;
            vector<string> tokens = tokenize(object);
            
            for (const string& token : tokens) {
                word_counts[token][label]++;
                word_total_counts[label]++;
            }
        }
        
        int len_X = X.size();
        for (auto& it : class_counts) {
            const string& label = it.first;
            int count = it.second;
            class_probabilities[label] = (double)count / len_X;
        }
    }
    
    string predict(const string& object) {
        vector<string> tokens = tokenize(object);
        
        string best_class;
        double best_score = -1;

        
        for (const auto& it : class_counts) {
            const string& label = it.first;
            double score = class_probabilities[label];   // P(y_i = label)
            
            for (const string& token : tokens) {
                int word_count = word_counts[token][label];   
                int total_words = word_total_counts[label];   
                // cout << token << " " << label << " " << word_count << " " << total_words << '\n';
                score *= (double)(word_count + 0.01) / (total_words); // P(x_i | y_i = label)
                
            }
            
            if (best_score == -1 || score > best_score) {
                best_score = score;
                best_class = label;
            }
        }
        
        return best_class;
    }
};

int main() {
    int len_train, len_test;
    vector<string>X;
    vector<string>y;
    cin >> len_train >> len_test;
    cin.get();
    for(int i=0; i<len_train; ++i){
        string label, object;
        getline(cin, label);
        getline(cin,object);
        X.push_back(object);
        y.push_back(label);

    }
    
    NaiveBayes model;
    model.fit(X, y);
    
    for(int i=0; i<len_test; ++i){
        string test_object;
        getline(cin,test_object);
        cout << model.predict(test_object) << endl;
    }
    
    return 0;
}