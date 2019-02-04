//
//  MergeSortEngine.cpp
//  Merge Sort
//
//  Created by vlad on 05.02.2019.
//  Copyright © 2019 vlad. All rights reserved.
//
#ifndef MergeSortEngine_cpp
#define MergeSortEngine_cpp

#include "MergeSortEngine.hpp"
#include <memory>
#include <vector>
#include <queue>
#include <set>

template<typename Iterator>
void  MergeSort<Iterator>::mergeSort(Iterator from,Iterator to){
    Range range(from,to);
    dividingAndMergening(range);
}


template<typename Iterator>
void MergeSort<Iterator>::dividingAndMergening(Range& range){
    const auto size = std::distance(range.left,range.right);
    if(size <= 1) return;
    const auto middle = size/2;
    auto rightFirstIterator = range.left;               // #1 ...) c
    std::advance(rightFirstIterator, middle);
    
    auto leftSecondIterator = rightFirstIterator;       // #2 (... c
    
    Range firstRange(range.left,rightFirstIterator),
    secondRange(leftSecondIterator,range.right);
    
    dividingAndMergening(firstRange);
    dividingAndMergening(secondRange);
    
    merge(firstRange, secondRange,size);
}



template<typename Iterator>
void  MergeSort<Iterator>::merge(Range& firstRange,Range& secondRange,Difference sizeOfArray){
    auto headIterator = firstRange.left;
    auto tempArray = std::make_unique<Element[]>(sizeOfArray);
    
    auto tempArrayIterator = tempArray.get();
    
    while(firstRange.left != firstRange.right &&
          secondRange.left != secondRange.right) {
        if (*firstRange.left < *secondRange.left) {
            *tempArrayIterator = std::move(*firstRange.left);
            ++firstRange.left;
            ++tempArrayIterator;
            
        }else if(*firstRange.left > *secondRange.left){
            *tempArrayIterator = std::move(*secondRange.left);
            ++secondRange.left;
            ++tempArrayIterator;
        }else{
            *tempArrayIterator = std::move(*secondRange.left);
            ++secondRange.left;
            ++firstRange.left;
            ++tempArrayIterator;
        }
    }
    
    if (firstRange.left == firstRange.right) {
        std::copy(std::make_move_iterator(secondRange.left),
                  std::make_move_iterator(secondRange.right),
                  tempArrayIterator);
    }else{
        std::copy(std::make_move_iterator(firstRange.left),
                  std::make_move_iterator(firstRange.right),
                  tempArrayIterator);
    }
    
    std::copy(std::make_move_iterator(tempArray.get()),
              std::make_move_iterator(&tempArray[sizeOfArray]),
              headIterator);
    
}

#endif /* MergeSortEngine_cpp */
