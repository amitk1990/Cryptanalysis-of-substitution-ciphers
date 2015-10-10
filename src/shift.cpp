#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
string word;	// returns one word at a time
map<string,int > dictionary2Map;
string cipherText;
int keys;
char alphabetsArray[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 

void shiftCipher(string cipherText){
	for(int i=1;i<=27;i++){
		std::string plain_text="";
		std::stringstream ss ;
		for(int j=0;j<cipherText.length();j++){
			int index = std::distance(std::begin(alphabetsArray), std::find(begin(alphabetsArray),std::end(alphabetsArray), cipherText[j]));
			int after_index = (index + i)% 27;
			plain_text+=alphabetsArray[after_index];
		}
		cout << plain_text << endl;
	}

}
void printHashMap(map<string,int > dictionary){
	cout << "Map Size " << dictionary.size() << endl;
	for (std::map<string,int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) { // iterate over the entries  
	    string key = it->first;  // Get the key  
	    int value = it->second;  // Get the value  
	    std::cout << "(" << key << "," << value << ")" << std::endl;  
	} 
}

void MapDictionary2(){
	ifstream fin("./../bin/Dictionary2.txt");
	if(!fin){
		cout << "Could not open file" << endl;
		return;
	}
	while( fin >> word){
		// cout << word << ": " << word.size() << endl;
		dictionary2Map.insert(std::make_pair(word,word.size()));
	}
	// printHashMap(dictionary2Map); 

}



int main(){

	MapDictionary2();
	cout << "Enter the cipher text " << endl;
	getline(cin,cipherText);
	cout << cipherText << endl;
	// cout << " Enter the number of keys used " << endl;
	// cin >> keys;
	int len = cipherText.length();
	//cout << len;
	shiftCipher(cipherText);
}

