#include <iostream>
#include <cassert>
#include <cmath>

#include "ds_hashset.h"

typedef  std::vector< std::pair<std::string, std::list<int> > > my_hash_table;

//private functions
void ds_hashset::resize_table(unsigned int new_size) 
{
  my_hash_table old_table = m_table;
  m_table.clear();
  m_table.resize(new_size);

  for(unsigned int i = 0; i < old_table.size(); i++)
  {
    for(my_hash_table::iterator it = old_table.begin(); it != old_table.end(); it++)
    {
    	if(it->first != "")
    	{
		  unsigned int index = m_hash(it->first) % m_table.size(); //find new index of kmer

	      std::list<int> copied_positions;            //copy over positions
	      for(std::list<int>::iterator pos_it = it->second.begin(); pos_it != it->second.end(); pos_it++)
	      copied_positions.push_back(*pos_it);

	      m_table[index] = std::make_pair(it->first, copied_positions);
    	}
    } 
  }
 }

unsigned int ds_hashset::m_hash(const std::string& kmer)
{
  // This implementation comes from
  // http://www.partow.net/programming/hashfunctions/
  unsigned int hash = 1315423911;
  for(unsigned int i = 0; i < kmer.length(); i++)
    hash ^= ((hash << 5) + kmer[i] + (hash >> 2));
  hash = abs(int(hash));
  return hash;
}
//--------------------------------------------------------------------------------------
//public functions
ds_hashset::ds_hashset(unsigned int table_size, float overflow)
{
  m_table = my_hash_table(table_size); 
  m_overflow = overflow;
  unique_keys = 0;
}

void ds_hashset::insert(std::string const& kmer, unsigned int position) 
{
  if (m_overflow <= double(unique_keys) / double(m_table.size()) )
    this->resize_table(2*m_table.size());

  //  Compute the hash value and then the table index
  unsigned int hash_value = m_hash(kmer);
  unsigned int index = hash_value % m_table.size();

  //key is already in table
  if(m_table[index].first == kmer)
    	m_table[index].second.push_back(position); //tack position on to end
  //gotta add key to hashmap
  else
  {
  	while(index <= m_table.size() && m_table[index].first != "")
    {
      if(index == m_table.size()-1)
      	index = 0;
      else
      	index++;
    }

    std::list<int> pos_list;
    pos_list.push_back(position);
    m_table[index] = std::make_pair(kmer, pos_list);
    unique_keys++;
  }
    	
}

std::vector<int> ds_hashset::find(const std::string& query_key)
{
	unsigned int index = m_hash(query_key) % m_table.size();

	if(m_table[index].first == query_key)
	{
		std::vector<int> positions;
		for(std::list<int>::iterator it = m_table[index].second.begin(); it != m_table[index].second.end(); it++)
			positions.push_back(*it);
		return positions;
	}

	unsigned int start_index = index;					//helper int
	index++;

	while(m_table[index].first != query_key)
	{
		if(index == start_index)						//came back around to originial spot
		{
			std::vector<int> empty_vector;
			return empty_vector;
		}

		else if(index == m_table.size() - 1)    	        //hit the end of the table-cycle back to beginning
			index = 0;

		else											//going thru lookin for seed
			index++;
	}

	//found a match later in the table!
	std::vector<int> positions;
	for(std::list<int>::iterator it = m_table[index].second.begin(); it != m_table[index].second.end(); it++)
		positions.push_back(*it);
	return positions;
}

void ds_hashset::print()
    {
      for (unsigned int i = 0; i < m_table.size(); i++) 
      {
        std::cout << i << ": ";
        for (std::list<int>::iterator itr = m_table[i].second.begin(); itr != m_table[i].second.end(); itr++)
          std::cout << ' ' << *itr;
        std::cout << std::endl;
      }
    }