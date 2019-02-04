//
//  MergeSortEngine.hpp
//  Merge Sort
//
//  Created by vlad on 05.02.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef MergeSortEngine_hpp
#define MergeSortEngine_hpp
#include <stdio.h>
#include <iterator>
template<class Iterator>
class MergeSort{
    using Difference = typename std::iterator_traits<Iterator>::difference_type;
    using Element = typename std::iterator_traits<Iterator>::value_type;
    struct Range{
    public:
        Iterator left,right;
        Range(Iterator left,Iterator right):left(left),right(right){}
    };
    //Main methods
public:
    static void mergeSort(Iterator from,Iterator to);
private:
    static void dividingAndMergening(Range& range);
    static void merge(Range& firstRange,Range& secondRange,Difference sizeOfArray);
};
    

#include "MergeSortEngine.cpp"
#endif /* MergeSortEngine_hpp */
