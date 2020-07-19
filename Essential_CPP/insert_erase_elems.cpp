#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <algorithm>    // std::find

using namespace std;

// 使用find()寻找元素返回iterator
// list使用insert()和erase()插入和删除元素


int main(){
    list<int>::iterator aaa,bbb;

    int ial[7] = {1,1,2,3,5,55,89};
    int ia2[4] = {8,13,21,34};
    list<int> elems(ial, ial+7);    // 使用现有数组初始化list


  
    list<int>::iterator  it = find(elems.begin(), elems.end(), 55);

    elems.insert(it, ia2, ia2+3);   // 在位置it处插入元素

    list<int>::iterator itit = find(elems.begin(), elems.end(), 13);

    aaa = elems.erase(itit);   // 删除13元素，返回iterator指向删除元素的后一个位置。

    // 便利输出list所有元素
    for(list<int>::iterator iter = elems.begin();iter != elems.end(); ++iter)
    cout << *iter << endl;

    list<int>::iterator it1 = find(elems.begin(), elems.end(), 5);  //其所指元素将是第一个被删除的元素
    list<int>::iterator it2 = find(elems.begin(), elems.end(), 21); //其所指元素将是最后一个呗删除元素的下一位置（即删除此之前的元素）
    bbb = elems.erase(it1, it2); //删除it1和it2位置之间的所有元素，返回iterator指向删除元素的后一个位置。


    
    system("pause");
    return 0;
}


 