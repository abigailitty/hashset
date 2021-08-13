#include <iostream>
#include <cmath>

using namespace std;

unsigned int m_hash(const std::string& kmer)
{
  // This implementation comes from
  // http://www.partow.net/programming/hashfunctions/
  unsigned int hash = 1315423911;
  for(unsigned int i = 0; i < kmer.length(); i++)
    hash ^= ((hash << 5) + kmer[i] + (hash >> 2));
  //hash = abs(int(hash));
  return hash;
}

int main()
{
	int test1 = m_hash("TTTTTTTTTT");
	int index1 = test1 % 12800;
	cout << "first: " << index1 << endl;

	int test2 = m_hash("TTTTTTTTTT");
	int index2 = test2 % 12800;
	cout << "second: " << index2 << endl;

	int test3 = m_hash("TTTTTTTTTT");
	int index3 = test3 % 12800;
	cout << "third: " << index3 << endl;

	return 0;
}