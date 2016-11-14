/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    Dict<string, int> dic(9999999);
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
    while(infile.good()){
	string w=infile.getNextWord();
	dic[w]++;
    }
    for(auto it=dic.begin();it!=dic.end();it++)
	if(it->second>=threshold)
		ret.push_back(*it);
    return ret;
}
