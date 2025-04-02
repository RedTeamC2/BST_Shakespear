#ifndef _MY_HASHTABLE_H
#define _MY_HASHTABLE_H

#include <functional>
#include <iostream>
#include <vector>
#include <SymbolCollection.h>
#include <Label.h>
#include <Polyline.h>
#include <Rectangle.h>
#include <Bridges.h>

template<class K, class V>
struct Node {
  K key;
  V value;
  Node* next;
  
  Node(const K& key, const V& value)
    : key(key), value(value), next(nullptr)
  {}
  
  Node() = default;
};

template<class K, class V>
class MyHashtable : public Dictionary<K, V> {
protected:
  typedef typename Dictionary<K, V>::dict_iter dict_iter;

  //TODO: You'll certainly need some variables and a constructor and destructor.
  
  
  //TODO: Implement a hashtable iterator with these functions
  struct hashtable_iter : public dict_iter {
    
    virtual bool operator==(dict_iter& ite) {
    }
    virtual bool operator!=(dict_iter& ite) {
    }
    virtual dict_iter& operator++() {
    }
    virtual std::pair<K,V> operator*() {
    }
  };
  


public:
  /**
   * Returns the node at key
   * @param key key of node to get
   * @return node of type Node at key
   */
  virtual V get(const K& key) const {
    //TODO
  }
  /**
   * sets the value of node at key with value
   * @param key key of node to be set
   * @param value new value of node
   */
  virtual void set(const K& key, const V& value) {
    //TODO
  }

  void visualize(bridges::Bridges& bridges_inst) {
    using namespace bridges;
    SymbolCollection* vis = new SymbolCollection();
    Rectangle* rect;
    Label* label;
    Polyline* line;

    double xmax = 0;

            
    double label_width=100;
    double label_height=25;
    double spacing_width=100;


    for (int i = 0; i < this->capacity; ++i) {
      double x = 0;
      double y = (this->capacity - i) * 30;

      rect = new Rectangle(x, y, 25, 25);
      rect->setFillColor("white");
      vis->addSymbol(rect);

      label = new Label(std::to_string(i));
      label->setLocation((float)(x+25./2.), (float)(y+25./2.));
      label->setFontSize(12);
      vis->addSymbol(label);

      x += 62.5;

      Node<K,V>* node = &this->table[i];
      while (node != nullptr && node->key != "") {
	rect = new Rectangle(x, y, 100, 25);
	rect->setFillColor("white");
	vis->addSymbol(rect);

	label = new Label(node->key + ": " + std::to_string(node->value));
	label->setLocation((float)(x+label_width/2.), (float)(y+label_height/2.));
	label->setFontSize(12);
	vis->addSymbol(label);

	line = new Polyline();
	line->addPoint(x + label_width, y+label_height/2.);
	line->addPoint(x + label_width+spacing_width, y+label_height/2.);
	line->addPoint(x + label_width+ 3./4.*spacing_width, y );
	line->addPoint(x + label_width+spacing_width, y+label_height/2.);
	line->addPoint(x + label_width+ 3./4.*spacing_width, y +label_height);
	line->setStrokeWidth(1);
	line->setStrokeColor("red");
	vis->addSymbol(line);

	x += 200;
	node = node->next;
      }

      if (x + 100 > xmax)
	xmax = x+100;
      
      rect = new Rectangle(x, y, 100, 20);
      rect->setFillColor("white");
      vis->addSymbol(rect);

      label = new Label("null");
      label->setLocation((float)(x+50.), (float)(y+10.));
      label->setFontSize(12);
      vis->addSymbol(label);
    }

    vis->setViewport(0,xmax, 0, this->capacity*30);
    
    bridges_inst.setDataStructure(vis);
    bridges_inst.visualize();
  }
  
  virtual std::unique_ptr<dict_iter> realBegin() {
    //TODO
  }
  
  virtual std::unique_ptr<dict_iter> realEnd() {
    //TODO
  }
};

#endif
