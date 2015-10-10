#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;
string word;	// returns one word at a time
map<string,int > dictionary2Map;
	
void printHashMap(map<string,int > dictionary){
	cout << "Map Size " << dictionary.size() << endl;
	for (std::map<string,int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) { // iterate over the entries  
	    string key = it->first;  // Get the key  
	    int value = it->second;  // Get the value  
	    std::cout << "(" << key << "," << value << ")" << std::endl;  
	} 
}

void readFile(){
	ifstream fin("./../bin/Dictionary2.txt");
	if(!fin){
		cout << "Could not open file" << endl;
		return;
	}
	while( fin >> word){
		// cout << word << ": " << word.size() << endl;
		dictionary2Map.insert(std::make_pair(word,word.size()));
	}
	printHashMap(dictionary2Map); 

}



int main(){
	string fileName = "";
	cout <<" Enter the file name " << endl;
	// cin >> fileName;
	// cout << fileName;
	readFile();
}

