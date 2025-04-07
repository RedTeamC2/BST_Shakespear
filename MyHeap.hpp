#ifndef MYHEAP__
#define MYHEAP__



//The value associated with the key is stored by the BinTreeElement
//and can be accessed with setValue and getValue. Left and right
//element can be obtained with getLeft() and getRight(), setLeft(),
//setRight().
//Full doc at: http://bridgesuncc.github.io/doc/cxx-api/current/html/classbridges_1_1datastructure_1_1_bin_tree_element.html
template<typename K, typename E>
class MyHeapElement : public BinTreeElement< E> {
  public:
    K k;

    int countleft;
    int countright;
	int size;

    MyHeapElement()
      : countleft(0), countright(0), size(0) {
    }

    virtual const string getElementRepresentation() const override {
      string json = Element<E>::getElementRepresentation();
      stringstream conv;
      conv << k;
      return json.insert(
               json.size() - 1,
               COMMA + QUOTE + "key" + QUOTE + COLON + QUOTE + conv.str() +
               QUOTE
             );
    }

  
};


//TODO: Implement a Heap as a Binary Tree using the provided MyHeapElemnt.
template<typename K, typename E>
class MyHeap {
protected:
    MyHeapElement<K, E>* root;
  
  
public:
  MyHeap()
    :root(nullptr)
  {}
  

    void insert(const K& k, const E& e) {
      //TODO -- still working on
		if (k.empty()) {
			k.push_back(e);
		}
		if (k->getLeft() == nullptr) {
			k->getLeft() = new K(e);
		}
		else if (k->getRight() == nullptr) {
			k->getRight() = new K(e);
		}
		else {
			K* newNode = insert(k->getLeft(), e);
			if (newNode == nullptr) {
				newNode = insert(k->getRight(), e);
			}
		}
    }


    bool empty() const {
      if (this->size != 0) return false;
      return true; //returning something to make scaffold compile
    }

    void visualize(Bridges& b) {
    	if (root == nullptr)
			return;

		b.setDataStructure(root);
		b.visualize();
		//TODO: Make the tree ready for visualization. (such as styling
      	//the tree)

      	//TODO: And visualize it
      if (root != nullptr) {
	b.setDataStructure(root);
	b.visualize();
      }
    }

    std::pair<K, E> pop () {

		}
      //TODO

};

#endif
