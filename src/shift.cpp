#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
string word;	// returns one word at a time
map<string,int > dictionary2;
string cipherText;
int keys;
char alphabetsArray[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
string dictionary1 = "";


/*
 * split string to words delimitor whitespace
*/


bool presentInDictionary2(string substr){
	string buf;
	stringstream ss(substr);
	std::vector<string> tokens;
	while(ss >> buf){
		tokens.push_back(buf);
	}
	for (std::vector<string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i){
    		//std::cout << *i << ' ';
    		if(dictionary2.find(*i) == dictionary2.end()){
    			return false;
    		}
	}
	return true;
	
}
/*
* check if present in dictionary 1
*/
bool presentInDictionary1(string substr){
	if(dictionary1.find(substr) != std::string::npos){
		return true;
	}
	return false;
}
/*
* read from dictionary to a string
*/
void readDicToString(){
	char ch;

	fstream fin("./../bin/Dictionary1.txt", fstream::in);
	while (fin >> noskipws >> ch) {
		dictionary1 +=ch;
	}
	//cout << dictionary1;
}

// shift cipher logic
bool shiftCipher(string cipherText){
	for(int i=1;i<=27;i++){
		std::string plain_text="";
		std::stringstream ss ;
		for(int j=0;j<cipherText.length();j++){
			int index = std::distance(std::begin(alphabetsArray), std::find(begin(alphabetsArray),std::end(alphabetsArray), cipherText[j]));
			int after_index = (index + i)% 27;
			plain_text+=alphabetsArray[after_index];
		}
		//cout << "**" << plain_text << "**" << endl;
		if(presentInDictionary2(plain_text)){
			cout << "present in dictionary2" << endl;
			return true;

		}else if(presentInDictionary1(plain_text)){
				return true;
		}
	}
	return false;

}
// display hash map
void printHashMap(map<string,int > dictionary){
	//cout << "Map Size " << dictionary.size() << endl;
	for (std::map<string,int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) { // iterate over the entries  
	    string key = it->first;  // Get the key  
	    int value = it->second;  // Get the value  
	    //std::cout << "(" << key << "," << value << ")" << std::endl;  
	} 
}


// read from dictionary to hash map
void MapDictionary2(){
	ifstream fin("./../bin/Dictionary2.txt");
	if(!fin){
		cout << "Could not open file" << endl;
		return;
	}
	while( fin >> word){
		// cout << word << ": " << word.size() << endl;
		dictionary2.insert(std::make_pair(word,word.size()));
	}
	// printHashMap(dictionary2); 

}




/*
* Starter function
*/

int main(){
	readDicToString();
	MapDictionary2();
	cout << "Enter the cipher text " << endl;
	getline(cin,cipherText);
	int len = cipherText.length();
	if(shiftCipher(cipherText))
		cout << "present" << endl;
	// cout << " Enter the number of keys used " << endl;
	// cin >> keys;
}

