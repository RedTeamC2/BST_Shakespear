#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP


template<class K, class V>
class Dictionary {
protected:
  struct dict_iter {
    virtual bool operator==(dict_iter& it) = 0;
    virtual bool operator!=(dict_iter& it) = 0;
    virtual dict_iter& operator++() = 0;
    virtual std::pair<K,V> operator*() = 0;
  };

  
  virtual std::unique_ptr<dict_iter> realBegin() = 0;
  virtual std::unique_ptr<dict_iter> realEnd() = 0;
  
public:
  class iterator {
    std::unique_ptr<dict_iter> ptr;
  public:
    iterator(std::unique_ptr<dict_iter> pt) {
      this->ptr = std::move(pt);
    }      

    bool operator==(const iterator&i) {
      return this->ptr->operator==(*(i.ptr));
    }

    bool operator!=(const iterator&i) {
      return this->ptr->operator!=(*(i.ptr));
    }
    
    iterator& operator++() {
      this->ptr->operator++();
      return *this;
    }
    
    std::pair<K,V> operator*() {
      return ptr->operator*();
    }
  };
  
  /**
   * Returns the value stored for key
   * @param key key of node to get
   * @return value stored for key
   */
  virtual V get (const K& key) const = 0;

  /**
   * sets the value of node at key with value
   * @param key key of node to be set
   * @param value new value of node
   */
  virtual void set(const K& key, const V& value) = 0;

  /**
   * @return an iteration to any dictionary
   */
  iterator begin() {
    return iterator(realBegin());
  }

  /**
   * @return an iteration to any dictionary
   */
  iterator end() {
    return iterator(realEnd());
  }  
  
  virtual ~Dictionary() = default;
};

#include <map>

template<class K, class V>
class StandardDictionary : public Dictionary<K, V> {
protected:
  std::map<K, V> underlyingmap;

  typedef typename Dictionary<K, V>::dict_iter dict_iter;
  
  struct sd_iter : Dictionary<K, V>::dict_iter{
    typename std::map<K, V>::iterator it;

    sd_iter() = default;

    sd_iter(const sd_iter&) = default;
    
    sd_iter (typename std::map<K, V>::iterator i)
      :dict_iter(), it(i) {
    }

    
    virtual bool operator==(dict_iter& ite) {
      sd_iter& a = dynamic_cast<sd_iter&>(ite);
      return it == a.it;
    }
    virtual bool operator!=(dict_iter& ite) {
      sd_iter& a = dynamic_cast<sd_iter&>(ite);
      return it != a.it;
    }
    virtual dict_iter& operator++() {
      it++;
      return *this;
    }
    virtual std::pair<K,V> operator*() {
      return *it;
    }


  };

  virtual std::unique_ptr<dict_iter> realBegin() {
    return std::make_unique<sd_iter>(underlyingmap.begin());
  }

  virtual std::unique_ptr<dict_iter> realEnd() {
    return std::make_unique<sd_iter>(underlyingmap.end());
  }
  
public:
  virtual V get(const K& key) const {
    V ret;
    auto iter =  underlyingmap.find(key);
    if (iter != underlyingmap.end())
      ret = iter->second;
    return ret;
  }
  virtual void set (const K& key, const V& value) {
    underlyingmap[key] = value;    
  }
  virtual void deleteKey(const K& key) {
    std::cout<<"not implemented yet"<<std::endl;
  }
  
};


#endif
