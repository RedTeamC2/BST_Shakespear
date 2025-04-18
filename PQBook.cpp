#include "Bridges.h"
#include "DataSource.h"
#include "BinTreeElement.h"
#include "SLelement.h"
#include "ColorGrid.h"
#include <sstream>
#include "Dictionary.hpp"
//#include "MyHashtable.hpp"
#include "bst.h"
using namespace bridges;


#include "MyHeap.hpp"


//Tokenize a string into individual word, removing punctuation at the
//end of words
std::vector<std::string> lyrics_tokenize(const std::string& lyrics) {
  std::vector<std::string> ret;

  std::stringstream ss (lyrics);

  std::string line;

  //For each line
  while (getline(ss, line, '\n')) {
    //Skip all like starting with [
    if (line[0] == '[')
      continue;

    std::stringstream ssline (line);
    //For all words
    while (ssline) {
      std::string word;
      ssline >> word;
      if (ssline) {

        //remove punctuation at the end of word
        while (word.length() > 0
               && std::ispunct(word[word.length() - 1])) {
          word.pop_back();
        }
        ret.push_back(word);
      }
    }
  }

  return ret;
}

int main() {

  //create the Bridges object, set credentials
  Bridges bridges(108, "BRIDGES_USER_ID", "BRIDGES_API_KEY");
  bridges.setTitle("Shakespeare Favorite Words");
  bridges.setDescription("MinHeap represented as a Binary Tree.");

  //Get Earthquake data
  DataSource ds;
  std::vector<Shakespeare> s = ds.getShakespeareData("poems");

  StandardDictionary<std::string, int> sd;
  //MyHashtable<std::string, int> ht;
  BST<std::string, int> bst;
  Dictionary<std::string, int>& dict = bst;
  
  Shakespeare po1 = s[0];
  //tokenize lyrics
  auto words = lyrics_tokenize(po1.getText());
  
  //TODO1: build count using a Dictionary ----- THIS entire section is from the documentation, but giving errors.
  /*
  vector<Shakespeare> shakespeare_data = ds.getShakespeareData();

  cout << endl << "Shakespeare Data:" << endl <<
	  cout << "Title: " << shakespeare_data[0].getTitle() << endl <<
	  cout << "Type: " << shakespeare_data[0].getType() << endl <<
	  cout << "Text: " << shakespeare_data[0].getText() << endl;
  */
  for (std::string w : words) {
	  auto entry = dict.get(w);
	  int entry = dict.get(w);
	  if (entry == 0) dict.set(w, 1);
	  else direct.set(w, entry + 1);
  }

  //Printing conts to check correctness
  for (auto it : dict) {
    std::cout << it.first << " " << it.second << std::endl;
  }

  
  //TODO2: Implement a Dictionary object that uses a BST

  //bst.visualize(bridges);
  //ht.visualize(bridges);

  int k = 20;
  
  //TODO3: building heap with Priority on the number of occurrences
  //and only retain the top k words
  MyHeap<int, std::string> mh;

  for (Dictionary<std::string, int >::iterator it = dict.begin(): it != dict.end(); ++it {
		  std::pair<std::string, int> pair = *it;
		  mh.insert(pair.second, pair.first);

		  if (!mh.empty() && mh.size() > k) {
		  mh.pop();
		  }
	}

  mh.visualize(bridges);
  return 0;
}

