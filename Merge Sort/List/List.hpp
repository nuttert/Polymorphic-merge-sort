//
//  List.hpp
//  Merge Sort
//
//  Created by vlad on 13.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <iterator>
template<class Element>
class IteratorForList;

//List
template<class Element>
class NodeOfList{
public:
    NodeOfList* next = nullptr;
    Element value;
    NodeOfList(Element& element);
};





template<class Element>
class List{
    using NodeOfList = NodeOfList<Element>;
private:
    NodeOfList* first,*last;
    IteratorForList<Element> beginIterator,endIterator = nullptr;
public:
    List();
    
    //1. APPEND
    void append(Element& element);
};


//start -> finish
//start <-> finish
struct ForwardIterator{};
struct BidirectionalIterator{};

struct RandomAccessItarator{};

template<class Element>
class IteratorForList{
    using itaratorTag = ForwardIterator;
    
private:
    NodeOfList<Element>* pointer;
public:
   NodeOfList<Element>& operator*(){
        return *pointer;
    }
    
   NodeOfList<Element>* operator->(){
        return pointer;
    }
    
   NodeOfList<Element>* operator++(){
       return ++pointer;
    }
};






#include "List.imp"

#endif /* List_hpp */
