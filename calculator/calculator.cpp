// Written by MxBit 04/2025

#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Prototypes
void add(const vector<double>& nums);
void sub(const vector<double>& nums);
void mult(const vector<double>& nums);
void div(const vector<double>& nums);
void extractArgs(std::string& flag, vector<double>& numbers, const int& arg_len, char* arg_array[]);
void calculate(const string& flag, const vector<double>& numbers);

int main(int argc, char* argv[]) {

    cout << "\nProvide a Flag first, than your numbers\n";
    cout << "Flags: -a (addition)\n";
    cout << "       -s (subtraction)\n";
    cout << "       -m (multiplication)\n";
    cout << "       -d (division)\n\n";
    cout << " Example usage: -a 427 73\n\n" << endl;

    string flag;
    vector<double> numbers;
    
    extractArgs(flag, numbers, argc, argv);
    calculate(flag, numbers);
    
    return 0;
}



void extractArgs(std::string& flag, vector<double>& number_vec, const int& arg_len, char* arg_array[]){

    // Get Flag
    for (int i = 1; i < arg_len; i++) {
        if (i == 1) {
            flag = (arg_array[i]);
        }
        // Get Numbers and Covert to Double
        if (i > 1 && i < arg_len) {
            if( isalpha(*arg_array[i]) )  {
                cout << "Arguments Non Numerical! Exiting Gracefully.\n";
                exit(1);
            }
            else {
                number_vec.push_back(stod(arg_array[i]));
        }   }
    }
};

void calculate(const string& flag, const vector<double>& numbers){
    switch(flag[1]){
        case 'a': 
            add(numbers);
            break;
        case 's':
            sub(numbers);
            break;
        case 'm':
            mult(numbers);
            break;
        case 'd':
            div(numbers);
            break;
    }
}

void add(const vector<double>& nums){
    if(nums.empty()) {
        cerr << "No Numbers Provided for Subtraction!" << endl;
        exit(1);
    }
    else {
        double added = std::accumulate(nums.begin(), nums.end(),0.0);
        cout << added << endl;
    }
};

void sub(const vector<double>& nums){
    double rest = nums[0];
    
    if(nums.empty()) {
        cerr << "No Numbers Provided for Subtraction!" << endl;
        exit(1);
    }
    else {
        
        for (int i = 1; i< nums.size(); i++){
            rest = rest-= nums[i];
        }
    }
    cout << rest << endl;
};

void mult(const vector<double>& nums){
    double potency = nums[0];
    
    if(nums.empty()) {
        cerr << "No Numbers Provided for Multiplication!" << endl;
        exit(1);
    }
    else {
        for (int i = 1; i< nums.size(); i++){
            potency = potency*= nums[i];
        }
    }
    cout << potency << endl;
};

void div(const vector<double>& nums){
    double frac = nums[0];
    
    if(nums.empty()) {
        cerr << "No Numbers Provided for Multiplication!" << endl;
        exit(1);
    }
    else {
        for (int i = 1; i< nums.size(); i++){
            if (nums[i] == 0) {
                cerr << "Division by 0 - You Drunk?" << endl;
            }
            else {
            frac = frac /= nums[i];
            }
        }
    }
    cout << frac << endl;
};