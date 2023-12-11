#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <map>

using namespace std;

void splitter(string str, stack<string>& stack) {
    string temp;
    for (auto& i : str) {
    if(i == '-')
    return;
        if (i != ',') {
            temp = temp + i;
        } else {
            stack.push(temp);
            temp = "";
        }
    }
    stack.push(temp);
}

//e-clousre function
set<int> e_closure(set<int> input_set,string** arr){
set<int> output_set;
string str;
stack<string> stack;
for (auto& element : input_set) {
output_set.insert(element);

splitter(arr[element][3], stack);
while (!stack.empty()) {
   str = stack.top();
   output_set.insert(stoi(str));
   stack.pop();
   splitter(arr[stoi(str)][3], stack);
}
}
return output_set;
}

//move function
set<int> move(set<int> input_set,string** arr,int i){
set<int> output_set;
string str;
stack<string> stack;
for(auto& element: input_set){
splitter(arr[element][i],stack);
while(!stack.empty()){
output_set.insert(stoi(stack.top()));
stack.pop();
}
}
return output_set;
};
bool checker(vector<set<int>> vec, set<int> set){
for(auto& i:vec){
if(i == set){
return true;
}
}
return false;
}

int main() {
    stack<string> stack;
    set<int> e_set;
set<int> move_set;
map<set<int>,char> hash;
char charList[] = {'A','B','C','D','E','F'};
    //to take a transition table
    string** transition_table = new string*[11];
    for (int i = 0; i < 11; i++) {
    transition_table[i] = new string[4];
        for (int j = 0; j < 4; j++) {
            cin >> transition_table[i][j];
        }
    }

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 4; j++) {
            cout << transition_table[i][j] << "\t";
        }
        cout << endl;
    }
    //end

    string str;
    set<int> Iset;
    map<set<int>,char> setHash;
vector<set<int>> sets;
    Iset.insert(0);
e_set = e_closure(Iset,transition_table);
setHash[e_set] = charList[0];
int counter = 1;
sets.push_back(e_set);
vector<vector<char>> vec;
int columnSize = 3;
vec.push_back(vector<char>(columnSize));
for(int i=1;i<3;i++){
set<int> temp;
temp = e_closure(move(sets[0],transition_table,i),transition_table);
if(!checker(sets,temp)){
sets.push_back(temp);
setHash[temp] = charList[counter];
vec[0][i] = charList[counter];
counter++;
}
else{
vec[0][i]= charList[counter];
}
}
for(int j=0;j<vec.size();j++){
for(int i=0;i<3;i++){
cout<<vec[j][i];
}
}

    // Print the set outside the loop
    for (const int& i : e_set) {
        cout << i << ",";
    }
cout<<endl;
   for (const int& i : move_set) {
        cout << i << ",";
    }
    return 0;
}

//0 - - 1,7
//1 - - 2,4
//2 3 - -
//3 - - 6
//4 - 5 -
//5 - - 6
//6 - - 1,7
//7 8 - -
//8 - 9 -
//9 - 10 -
//10 - - -