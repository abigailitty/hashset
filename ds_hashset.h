#ifndef ds_hashset_h_
#define ds_hashset_h_

#include <string>
#include <vector>
#include <utility>
#include <list>

class ds_hashset 
{
  typedef  std::vector< std::pair<std::string, std::list<int> > > my_hash_table;

  private:
    //member variables
    my_hash_table m_table;                                               // actual table
    float m_overflow;                                             //when to resize
    unsigned int unique_keys;                                            //number of unique keys (entries)

    // member functions
    unsigned int m_hash(const std::string& kmer);                               // hash function
    void resize_table(unsigned int new_size);                            //resize function

  public:

    // Constructor
    ds_hashset(unsigned int init_size, float overflow);
    
    // Copy constructor
    ds_hashset(const ds_hashset& old) 
      : m_table(old.m_table), m_overflow(old.m_overflow), unique_keys(old.unique_keys) {}

   //~ds_hashset() {}

    unsigned int size() const { return m_table.size(); }

    // Insert the key if it is not already there.
    void insert(std::string const& kmer, unsigned int position);
    void print();
    std::vector<int> find(const std::string& query_key);

};
#endif