#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> sequence(n);
    vector<int> count(4);
    
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        sequence[i] = t;
        count[t]++;
    }

    vector<int> place1(3), place2(3), place3(3);
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();

    for(int i=0; i<n; ++i){
        // 1
        if(sequence[i]==1 && i<count[1]){
            place1[0]++;
        }
        if(sequence[i]==1 && (i<count[2]+count[1] && i>=count[1])){
            place1[1]++;
        }
        if(sequence[i]==1 && i>=count[2]+count[1]){
            place1[2]++;
        }

        // 2
        if(sequence[i]==2 && i<count[1]){
            place2[0]++;
        }
        if(sequence[i]==2 && (i<count[2]+count[1] && i>=count[1])){
            place2[1]++;
        }
        if(sequence[i]==2 && i>=count[2]+count[1]){
            place2[2]++;
        }

        // 3
        if(sequence[i]==3 && i<count[1]){
            place3[0]++;
        }
        if(sequence[i]==3 && (i<count[2]+count[1] && i>=count[1])){
            place3[1]++;
        }
        if(sequence[i]==3 && i>=count[2]+count[1]){
            place3[2]++;
        }

    }
    


    int swap = 0;

    // cout <<"1\n";
    // cout << place1[0] << " " << place1[1] << " " << place1[2] << '\n';
    // cout <<"2\n";
    // cout << place2[0] << " " << place2[1] << " " << place2[2] << '\n';
    // cout <<"3\n";
    // cout << place3[0] << " " << place3[1] << " " << place3[2] << "\n\n";



    while ((place1[1]>0 && place2[0]>0) || (place1[2]>0 && place3[0]>0) || (place3[1]>0 && place2[2]>0)){
        if(place1[1]>0 && place2[0]>0){
            place1[1]--;
            place2[0]--;

            place1[0]++;
            place2[1]++;
            
            swap++;
            // cout << "TYT3\n";
            
        }
        if(place3[1]>0 && place2[2]>0){
            place3[1]--;
            place2[2]--;

            place2[1]++;
            place3[2]++;

            // cout << "TYT4\n";


            swap++;
        }
        if(place1[2]>0 && place3[0]>0){
            place1[2]--;
            place3[0]--;

            place1[0]++;
            place3[2]++;

            // cout << "TYT5\n";

            swap++;
            
        }
        

    }


    
    while(place1[1]>0 && place2[2]>0 && place3[0]>0 || place1[2]>0 && place2[0]>0 && place3[1]>0){
        if(place1[1]>0 && place2[2]>0 && place3[0]>0){
            place1[1]--;
            place2[2]--;
            place3[0]--;

            place1[0]++;
            place2[1]++;
            place3[2]++;
            // cout << "TYT1\n";

            swap += 2;
            
        }
        if(place1[2]>0 && place2[0]>0 && place3[1]>0){
            place1[2]--;
            place2[0]--;
            place3[1]--;

            place1[0]++;
            place2[1]++;
            place3[2]++;
            // cout << "TYT2\n";

            swap += 2;
        }
        

    }

    // cout <<"1\n";
    // cout << place1[0] << " " << place1[1] << " " << place1[2] << '\n';
    // cout <<"2\n";
    // cout << place2[0] << " " << place2[1] << " " << place2[2] << '\n';
    // cout <<"3\n";
    // cout << place3[0] << " " << place3[1] << " " << place3[2] << '\n';
    
    steady_clock::time_point end = steady_clock::now();
    steady_clock::duration dur = end - start;
 
    cout << "timing in milliseconds: " << duration<double, milli>(dur).count() << " ms" << endl;


    cout << swap << '\n';


    return 0;
}