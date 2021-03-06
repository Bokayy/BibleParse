#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <ostream>
#include <fstream>
#include <iterator> 
#include <map>
#include <algorithm>
#include <iomanip>
#include <regex>
#include "bits.h"

constexpr auto FILETOREAD = ("C:\\Users\\BOKAYY\\Desktop\\Shortcuts\\bible.txt");

using namespace std;


string Lowercase(string upTxt)
{
	for (int i = 0; i < upTxt.length(); i++)
	{
		upTxt[i] = tolower(upTxt[i]);
	}
	return upTxt;
}


void AddWordtoMap(string str, map<string, int> &themap)
{
	map<string, int>::iterator it = themap.find(str);

	if (it!= themap.end())
	{
		it->second = it->second + 1;	//second je zapravo value iz mape u ovom slucaju
	}
	else
	{
		themap.insert(make_pair(str, 1));
	}
}

void writeIndex(map<string, int> WordMap) {
	for (map<string, int>::iterator itr = WordMap.begin();
		itr != WordMap.end(); ++itr) {
		std::cout << "\n "
		<< setw(30) << itr->first
		<< setw(10) << itr->second
		<< endl;
	}
}



void RemoveNonAlphanumeric(string& ligma)
{
	char nonalpha[40] = { ')' ,'(' ,'!' ,'?','$','\\','.','|',';',':',',','~','@','#', '%','^','&','*','_','+','=','-','{','}','[',']','<','>','/','0','1','2','3','4','5','6','7','8','9','"' };
	ligma.erase(remove_if(ligma.begin(), ligma.end(), [](char nonalpha) { return !isalpha(nonalpha); }), ligma.end());
	//ligma.erase(remove(ligma.begin(), ligma.end(), alphanumeric), ligma.end()); //remove nonalpha[iterator] from string
}


// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<string, int>& M)
{
	// Declare a multimap
	multimap<int, string> MM;

	// Insert every (key-value) pairs from
	// map M to multimap MM as (value-key)
	// pairs
	for (auto& it : M) {
		MM.insert({ it.second, it.first });
	}

	// Print the multimap
	for (auto& it : MM) {
		cout << it.second << ' '
			<< it.first << endl;
	}
}

 void RemoveEmpty(map<string, int>& map)
{
	 string tocheck = "";
	 for (auto it = map.begin(); it != map.end();)
	 {
		 tocheck = it->first;
		 if (tocheck.empty())
		 {
			 it = map.erase(it);
		 }
		 else
		 {
			 it++;
		 }
	 }
}


int main()
{
	fstream file_stream;
	file_stream.open(FILETOREAD);
	vector<string> content;
	string current_word;
	int number_of_words = 0;
	map<string, int> frequency;

	//ubaci u vector iz fajla
	do
	{
		file_stream >> current_word;
		current_word = Lowercase(current_word);
		content.push_back(current_word);

	} while (!file_stream.eof());

	//izbrisi sve delimitere
	for_each(content.begin(), content.end(), RemoveNonAlphanumeric);

	//upis u mapu
	auto MapPopulationLambda = [&frequency](const string& n)
	{ 
		AddWordtoMap(n, frequency);
	};
	
	//populiraj mapu
	for_each(content.begin(), content.end(), MapPopulationLambda);
	RemoveEmpty(frequency);

	sort(frequency);
}

//https://www.gutenberg.org/cache/epub/7999/pg7999.txt