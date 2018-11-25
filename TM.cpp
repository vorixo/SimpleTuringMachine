#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

/**
* Reserved syntax:
* D -> Right movement
* I -> Left movement
* States should be between parenthesis (n), being n the state
* Each dictionary entry should be displayed in order in the 0 row
* Each row identifies one state (not including the 0 row)
* Each column identifies one dictionary entry
**/
vector<vector<string>> rows;
vector<char> InputDictionary;
int indexString(0);
int currentState(0);


int getDictionaryTokenId(char tkn) {
	int tknid(0);
	for(char s : InputDictionary) {
		if(tkn == s) return tknid;
		tknid++;
	}
	return 0;
}


int getNextStateToGo(const string s) {
	string fullstate_num("");
	for(int i = 1; i < s.length(); ++i) {
		if(s[i] == ')') break;
		fullstate_num += s[i];
	}
	stringstream to_num(fullstate_num);  
	int num(0);
	to_num >> num;
    return num;
}

char writeSymbol(const string s) {
	int j(0);
	for(int i = 1; i < s.length(); ++i) {
		j++;
		if(s[i] == ')') break;
	}
	return s[j+1];
}

bool isDirectionRight(const string s) {
	int j(0);
	for(int i = 1; i < s.length(); ++i) {
		j++;
		if(s[i] == ')') break;
	}
	return s[j+2] == 'D';
}

void processMonoInput(string &str) {
	if(currentState == rows.size()-1) {
		cout << "ACCEPT STATE!" << endl;
		return;
	}
	
	int current_Dictionary(getDictionaryTokenId(str[indexString]));
	string cell(rows[currentState][current_Dictionary]);
		
	if(cell != "-") {
		char writeme(writeSymbol(cell));
		bool goRight(isDirectionRight(cell));
		
		// Iteration based on state caching
		currentState = getNextStateToGo(cell);
		str[indexString] = writeme;
		indexString = (goRight) ? indexString + 1 : indexString -1;
		
		// Tail recursion
		processMonoInput(str);
	}
	else {
		cout << "ERROR: EXECUTION DIDN'T CONCLUDE WELL." << endl;
	}
	
}



void processInput(string& str) {
	// Turing machines are infinite on the right, static data would suffice for little programs, however it would require dynamic data if it is desired so.
	// Simply append B's to the end of the original string when it is required.
	str += "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
	
	ifstream myfile("TM.txt");
	string line;
  	if (myfile.is_open())
  	{
  		getline(myfile, line);
  		for(char cc : line) {
  			if(cc!= '\t' && cc!= ' ')
  				InputDictionary.push_back(cc);
		}
   		while(getline(myfile, line))
    	{
    		std::istringstream buf(line);
    		std::istream_iterator<std::string> beg(buf), end;
    		std::vector<std::string> tokens(beg, end);
			rows.push_back(tokens);
    	}
    	myfile.close();
  	} else cout << "Unable to open file"; 
  	
	processMonoInput(str);
	
}


int main() {
	string str;
	cout << "Introduce your input: ";
	getline(cin, str);
	int strlen(str.length());	
	processInput(str);
	// Output
	for(int i = 0; i < strlen; ++i) {
		cout << str[i];
	}
}
