// Include the node implementation
#ifndef BST_H

#define BST_H

#include "BSTElement.h"
#include "Dictionary.hpp"

using namespace bridges;

// Include the dictionary ADT

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
  typedef typename Dictionary<Key, E>::dict_iter dict_iter;

  // iterator support
  struct bst_iter: public dict_iter {
    BSTElement<Key, E>* cur;

    //May have to change somethign there.
    bst_iter (BSTElement<Key, E>* bste) : dict_iter(), cur(bste) {}

    //todo -- probably done
    virtual bool operator==(dict_iter& ite) {
		if (cur == ite) return true;
      return false;
    }
    //todo -- Probably done
    virtual bool operator!=(dict_iter& ite) {
		if (cur != ite) return true;
      return false;
    }
    
    //todo -- Probably done
    virtual dict_iter& operator++() {
      return cur++;
    }

    //todo
    virtual std::pair<Key,E> operator*() {
      return std::make_pair(Key(), E());
    }
  };

    
  private:
    BSTElement<Key, E>* root;  // Root of the BS
  //Documentation of the BSTElement class at http://bridgesuncc.github.io/doc/cxx-api/current/html/classbridges_1_1datastructure_1_1_b_s_t_element.html
  
  

  E defaultValue;


  
  public:
  
  
  BST(E defaultvalue = E())
    : defaultValue(defaultvalue) {
      root = NULL; 
    }

  ~BST() {
    }


  //TODO -- Probably done
  virtual E get(const Key& k) const {
	  return root;
  }

  //TODO -- Probably done
  virtual void set(const Key& k, const E& e) {
	  root = e;
  }


  
  //already written function to make visualizing the BST in BRIDGES
  void visualize(Bridges& b) {
    if (root == nullptr)
      return;
      
    vishelp(root);
    b.setDataStructure(root);
    b.visualize();
  }


protected:

    void vishelp(BSTElement<Key, E>* b) {
    if (b == nullptr) return;
    
    b->setLabel(std::to_string(b->getValue()));
    
    vishelp(b->getLeft());
    vishelp(b->getRight());
  }

  
  virtual std::unique_ptr<dict_iter> realBegin() {return std::make_unique<bst_iter>(root);}
  virtual std::unique_ptr<dict_iter> realEnd() {return std::make_unique<bst_iter>(nullptr);}
  
};

#endif
