//
//  main.cpp
//  Merge Sort
//
//  Created by vlad on 01.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "List/List.hpp"
#include <queue>
#include <set>
using std::vector;
using std::cout;
using std::endl;



template<class Iterator>
class MergeSort{
     using Difference = typename std::iterator_traits<Iterator>::difference_type;
     using Element = typename std::iterator_traits<Iterator>::value_type;
     struct Range;
   
    
   
public:
    
  static void mergeSort(Iterator from,Iterator to){
      Range range(from,to);
      dividingAndMergening(range);
    }
    
    
//  [a,b)
private:
    struct Range{
    public:
        Iterator left,right;
        Range(Iterator left,Iterator right):left(left),right(right){}
    };
    
   

    
    static void dividingAndMergening(Range& range){
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
    
    
    static void merge(Range& firstRange,Range& secondRange,Difference sizeOfArray){
        auto headIterator = firstRange.left;
        
        auto tempArray = std::make_unique<Element[]>(sizeOfArray);
    
        decltype(auto) tempArrayIterator = tempArray.get();
        
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
};


class Matrix{
private:
    vector<vector<bool>> data = {};
public:
    size_t size()const{
        return std::move(data.size());
    }
    bool operator()(size_t i,size_t j) const{
        return data[i][j];
    }
    Matrix(std::initializer_list<std::initializer_list<bool>> list){
        data.insert(data.begin(), list.begin(), list.end());
    }
};

class MinimumWay{
    using vector = std::vector<int>;
    using set = std::set<int>;
private:
    struct MainObjects{
        const Matrix& matrix;
        int X;
        int Y;
        size_t matrixSize;
        
    };
public:
static vector minimumWay(const Matrix& matrix,int X,int Y){
    MainObjects collection {matrix,
                        X,
                        Y,
                        matrix.size() };
    vector way = findingMinimum(collection,std::move(X));
    if(!way.empty())way.push_back(Y);
    return way;
}


private:
    
    static vector findingMinimum(MainObjects& mainObjects,
                                 const int&& currentRaw,
                                 vector way = {},
                                 set traversedPoints = {}
                                 ){
    way.push_back(currentRaw);
    traversedPoints.insert(currentRaw);
    if(mainObjects.matrix(currentRaw,mainObjects.Y))return way;
    if(way.size() == mainObjects.matrixSize)return {};
    size_t minLenght = mainObjects.matrixSize;
    vector minWay;
    for (int currentColumn = 0; currentColumn < mainObjects.matrixSize; ++currentColumn) {
        if(traversedPoints.find(currentColumn)!=traversedPoints.end()) continue;
        vector tempWay{findingMinimum(mainObjects,std::move(currentColumn),way,traversedPoints)};
        if (tempWay.size()<minLenght &&
            tempWay.size()!= 0) {
            minWay = tempWay;
            minLenght = tempWay.size();
        }
    }
        return minWay;
  }
    
};


int main(int argc, const char * argv[]) {
    Matrix matrix1 = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
    Matrix matrix2 = {{ 0, 0, 0, 0},
        { 0, 0, 0, 1},
        { 0, 0, 0, 0},
        { 0, 1, 0, 0}};
   auto way = MinimumWay::minimumWay(matrix2, 1, 2);
    
  
    return 0;
}
