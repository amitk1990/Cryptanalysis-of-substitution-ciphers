//============================================================================
// Name        : Cryptoanalysis Substitution Cipher 
// Author      : Amit Karunakaran and Harshini Vijay Kumar
// Version     :
// Copyright   : NYU License
// Description : Cryptoanalysis Substitution Cipher in C++, Ansi-style

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;
string word;	// returns one word at a time
map<string,int > dictionary2;
std::set< std::vector<long> > outerVector;
string cipherText;
int keys;
char alphabetsArray[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
string dictionary1 = "";

/*
 * Combination problem
*/
int comb[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}; 
long choose(int * got, int n_chosen, int len, int at, int max_types)
{
        long i;
        long count = 0;
        if (n_chosen == len) {
                if (!got) return 1;
 				std::vector<long> innerVector;
                for (i = 0; i < len; i++){
                        printf("%d ", comb[got[i]]);
                        innerVector.push_back(comb[got[i]]);
                }
                outerVector.insert(innerVector);
                //cout << "size of outerVector" << outerVector.size() << endl;
                printf("\n");
                return 1;
        }
 
        for (i = at; i < max_types; i++) {
                if (got) got[n_chosen] = i;
                count += choose(got, n_chosen + 1, len, i, max_types);
        }
        return count;
}



/*
 * Check to see present in dictionary2
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
 * Check if present in dictionary 1
*/
bool presentInDictionary1(string substr){
	if(dictionary1.find(substr) != std::string::npos){
		return true;
	}
	return false;
}
/*
 * Read from dictionary to a string
*/
void readDicToString(){
	char ch;

	fstream fin("./../bin/Dictionary1.txt", fstream::in);
	while (fin >> noskipws >> ch) {
		dictionary1 +=ch;
	}
	//cout << dictionary1;
}


/*
 * Shift Cipher Logic
*/
//beheld repress endangers continuum teachable inception eigenstate
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
			cout << "present in dictionary1" << endl;
				return true;
		}
	}
	return false;

}

/*
 * Print Hash Map
*/

void printHashMap(map<string,int > dictionary){
	//cout << "Map Size " << dictionary.size() << endl;
	for (std::map<string,int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) { // iterate over the entries  
	    string key = it->first;  // Get the key  
	    int value = it->second;  // Get the value  
	    //std::cout << "(" << key << "," << value << ")" << std::endl;  
	} 
}



/*
 * Read from Dictionary and store in Hash Map
*/
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
* STARTER  MAIN FUNCTION
*/

int main(){
	readDicToString();
	MapDictionary2();
	//cout << "ENTER THE CIPHER TEXT TO BE DECODED " << endl;
	//getline(cin,cipherText);
	 cout << " Enter the number of keys used " << endl;
	 cin >> keys;
	// if(shiftCipher(cipherText)){
	// 	cout << "PRESENT USING SHIFT CIPHER" << endl;
	// }else{
	// 	cout << "NOT PRESENT" << endl;
	// }
	long value = choose(comb,0,13,0,26);
	// cout << value << endl;
	// std::set< std::vector<long> > ::iterator it;
	// std::cout << "**";
 // 	for(it = outerVector.begin(); it!=outerVector.end(); it++)
 // 	{
 // 		const std::vector<long>& i = (*it);
 // 		for(int j = 0; j<i.size(); j++)
 // 		{
 // 			cout << i[j] << " ";
 // 		}
 // 		cout << endl;
 // 	}
	// std::cout << "**" << endl;
	
}

