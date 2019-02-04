//
//  main.cpp
//  Merge Sort
//
//  Created by vlad on 01.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include <iostream>

#include "Engine/MergeSortEngine.hpp"
using std::vector;
using std::cout;
using std::endl;





int main(int argc, const char * argv[]) {
 
    vector<int> collection{8,4,2000,15,256,512,32,64,0,128};
    using VIterator = decltype(collection.begin());
    MergeSort<VIterator>::mergeSort(collection.begin(),collection.end());
    for(const auto& element:collection)cout << element << endl;
    return 0;
}
