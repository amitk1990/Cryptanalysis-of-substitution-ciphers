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
#include <regex>
using namespace std;

int lengthOfText;
string word;	// returns one word at a time
map<string, int > dictionary2;
std::vector<int> innerVector;
std::set< std::vector<int> > outerVector;
string cipherText;
int numberOfKeys;
char alphabetsArray[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
string dictionary1 = "";
vector<int> comb = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };

/*
* Check to see present in dictionary2
*/
bool presentInDictionary2(string substr){
	string buf;
	stringstream ss(substr);
	std::vector<string> tokens;
	while (ss >> buf){
		tokens.push_back(buf);
	}
	std::vector<string>::const_iterator it;
	for (it = tokens.begin(); it != (tokens.end()); ++it){
		//std::cout << *i << ' ';
		if (dictionary2.find(*it) == dictionary2.end()){
			return false;
		}
	}
}
/*
* Check if present in dictionary 1
*/
bool presentInDictionary1(string substr){
	if (dictionary1.find(substr) != std::string::npos){
		return true;
	}
	return false;
}
/*
* Read from dictionary to a string
*/
void readDicToString(){
	char ch;

	fstream fin("Dictionary1.txt", fstream::in);
	while (fin >> noskipws >> ch) {
		dictionary1 += ch;
	}
	//cout << dictionary1;
}


/*
* Recursive Logic to find all possible plaintexts 
*/
bool recursiveSearch(vector<int> cipherText, int index, vector<int> plainTextTest, vector<int> testKeys)
{
	if (index == lengthOfText - 1)
	{
		for (int i = 0; i < testKeys.size(); i++)
		{
			plainTextTest[index] = (cipherText[index] - testKeys[i] - cipherText[index - 1] + 27) % 27;
			//plainTextTest[index] = (cipherText[index] + testKeys[i] + plainTextTest[index - 1] + 27) % 27;
			string plainText;
			for (int j : plainTextTest)
			{
				plainText = plainText + alphabetsArray[j];
			}
			cout << endl << "**" << plainText << "**" << endl;
			if (presentInDictionary1(plainText))
			{
				cout << "Plain text is" << endl << plainText << endl;
				string buffer;
				cin >> buffer;
				return true;
			}
			else if (presentInDictionary2(plainText))
			{
				cout << "Plain text is" << endl << plainText << endl;
				string buffer;
				cin >> buffer;
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < testKeys.size(); i++)
		{
			plainTextTest[index] = (index == 0) ? ((0 + cipherText[index] - testKeys[i]) % 27) : ((cipherText[index] - cipherText[index - 1] - testKeys[i] + 27) % 27);
			//plainTextTest[index] = (index == 0) ? ((0 + cipherText[index] + testKeys[i])%27) : ((cipherText[index] + plainTextTest[index - 1] + testKeys[i] + 27) % 27);
			recursiveSearch(cipherText, index + 1, plainTextTest, testKeys);
		}
	}
}

/*
* Shift Cipher Logic
*/
//beheld repress endangers continuum teachable inception eigenstate
bool shiftCipher(string cipherText){
	for (int i = 1; i <= 27; i++){
		std::string plain_text = "";
		std::stringstream ss;
		for (int j = 0; j<cipherText.length(); j++){
			int index = std::distance(std::begin(alphabetsArray), std::find(begin(alphabetsArray), std::end(alphabetsArray), cipherText[j]));
			int after_index = (index + i) % 27;
			plain_text += alphabetsArray[after_index];
		}
		cout << "**" << plain_text << "**" << endl;
		if (presentInDictionary2(plain_text)){
			cout << "present in dictionary2" << endl;
			return true;

		}
		else if (presentInDictionary1(plain_text)){
			cout << "present in dictionary1" << endl;
			return true;
		}
	}
	return false;

}

/*
* Print Hash Map
*/

void printHashMap(map<string, int > dictionary){
	//cout << "Map Size " << dictionary.size() << endl;
	for (std::map<string, int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) { // iterate over the entries  
		string key = it->first;  // Get the key  
		int value = it->second;  // Get the value  
		//std::cout << "(" << key << "," << value << ")" << std::endl;  
	}
}



/*
* Read from Dictionary and store in Hash Map
*/
void MapDictionary2(){
	ifstream fin("Dictionary2.txt");
	if (!fin){
		cout << "Could not open file" << endl;
		return;
	}
	while (fin >> word){
		// cout << word << ": " << word.size() << endl;
		dictionary2.insert(std::make_pair(word, word.size()));
	}
	// printHashMap(dictionary2); 

}

/*
*Convert cipherText to int vector
*/
vector<int> convertCipher(string cipherText)
{
	vector<int> integerCipher(lengthOfText);
	for (int j = 0; j < cipherText.length(); j++)
	{
		int index = std::distance(std::begin(alphabetsArray), std::find(begin(alphabetsArray), std::end(alphabetsArray), cipherText[j]));
		integerCipher[j] = index;
	}
	return integerCipher;
}

/*
* Combination problem
*/
void pretty_print(const vector<int> v) {
	//outerVector.insert(v);
	vector<int> plainTextTest(lengthOfText);
	recursiveSearch(convertCipher(cipherText), 0, plainTextTest, v);
}
void go(int offset, int k) {
	if (k == 0) {
		pretty_print(innerVector);
		return;
	}
	for (int i = offset; i <= comb.size() - k; ++i) {
		innerVector.push_back(comb[i]);
		go(i + 1, k - 1);
		innerVector.pop_back();
	}
}



/*
* STARTER  MAIN FUNCTION
*/

int main(){
	readDicToString();
	MapDictionary2();
	cout << "ENTER THE CIPHER TEXT TO BE DECODED " << endl;
	getline(cin,cipherText);
	lengthOfText = cipherText.length();
	cout << " Enter the number of keys used " << endl;
	cin >> numberOfKeys;
	//go(0, numberOfKeys);
	vector<int> plainTextTest(lengthOfText);
	/*for (set< vector<int> >::iterator it = outerVector.begin(); it != outerVector.end(); ++it) {
		recursiveSearch(convertCipher(cipherText), 0, plainTextTest, *it);
	}*/
	vector<int> testKeys = {0,1};
	if(shiftCipher(cipherText)){ 
		cout << "PRESENT USING SHIFT CIPHER" << endl;
	}else{
		cout << "NOT PRESENT" << endl;
	}
	/*long value = choose(comb, 0, 3, 0, 3);
	cout << value << endl;
	std::set< std::vector<int> > ::iterator it;
	std::cout << "**";
	for (it = outerVector.begin(); it != outerVector.end(); it++)
	{
		const std::vector<int>& i = (*it);
		for (int j = 0; j<i.size(); j++)
		{
			cout << i[j] << " ";
		}
		cout << endl;
	}
	std::cout << "**" << endl;*/
	string buffer;
	cin >> buffer;
}

