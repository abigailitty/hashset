#include <iostream>
#include <fstream>
#include "ds_hashset.h"

using namespace std;

//forward declaration
vector<string> find_kmers(const string& genome, unsigned int k);

int main()
{
	//reading in string
	string str;

	//variables needed for first while loop
	string genome;
	unsigned int table_size = 100;
	float occupancy = 0.5;
	unsigned int k;
	
	while(cin >> str && str != "query")
	{
		if(str == "genome") //read in genome
		{
			string filename;
			cin >> filename; //move to next word

			ifstream istr(filename); //check if file works
		  	if(!istr) 
		  	{
		    	cerr << "ERROR: Could not open " << filename << " for reading." << endl;
		    	return 1;
		  	}

		  	string base_temp; //read in genome as one big string
		  	while(istr >> base_temp)
		  		genome += base_temp;
		}

		else if(str == "table_size")
			cin >> table_size;

		else if(str == "occupancy")
			cin >> occupancy;

		else // str == "kmer"
			cin >> k;
	}
	
	//make hash_set
	vector<string> kmers = find_kmers(genome, k);
	ds_hashset my_hashset(table_size, occupancy);

	for(unsigned int i = 0; i < kmers.size(); i++)
		my_hashset.insert(kmers[i], i);

	//variables for second while loop
	unsigned int mismatches;
	string query;

	//str is already query, so we have to have one iteration outside the while loop--------------
	cin >> mismatches;
	cin >> query;

	cout << "Query: " << query << endl;
	vector<int> positions = my_hashset.find(query.substr(0,k));

	if(positions.size() == 0)
		cout << "No Match" << endl;
	else
	{
		int unprinted = 0;
		for(unsigned int i = 0; i < positions.size(); i++)
		{
			string possible_match = genome.substr(positions[i], query.size());

			unsigned int base_mismatches = 0;
			for(unsigned int j = 0; j < possible_match.size(); j++)
				if(possible_match[j] != query[j])
					base_mismatches++;

			if(base_mismatches > mismatches)
				unprinted++;
			else
				cout << positions[i] << " " << base_mismatches << " " << possible_match << endl;
		}

		if(unprinted == int(positions.size()))
			cout << "No Match" << endl;
	}
	//----------------------------------------------------------------

	while(cin >> str && str != "quit")
	{
		cin >> mismatches;
		cin >> query;

		cout << "Query: " << query << endl;
		vector<int> positions = my_hashset.find(query.substr(0,k));

		if(positions.size() == 0)
			cout << "No Match" << endl;
		else
		{
			int unprinted = 0;
			for(unsigned int i = 0; i < positions.size(); i++)
			{
				string possible_match = genome.substr(positions[i], query.size());

				unsigned int base_mismatches = 0;
				for(unsigned int j = 0; j < possible_match.size(); j++)
					if(possible_match[j] != query[j])
						base_mismatches++;

				if(base_mismatches > mismatches)
					unprinted++;
				else
					cout << positions[i] << " " << base_mismatches << " " << possible_match << endl;
			}

			if(unprinted == int(positions.size()))
				cout << "No Match" << endl;
		}
	}

	return 0;
}

vector<string> find_kmers(const string& genome, unsigned int k)
{
	vector<string> kmers;
	unsigned int index = 0;
	while(index + k <= genome.size())
	{
		kmers.push_back(genome.substr(index, k));
		index++;
	}

	return kmers;
}