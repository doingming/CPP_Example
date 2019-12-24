#include <iostream>
#include <stdlib.h>
#include <vector>

/* vector 嵌套 vector */

int main()
{
    std::vector< std::vector<int> > ivec;
    int n=5,m=12;

    for(int i=0;i<m;++i)
    {
        std::vector<int> vec;
        for(int j=0;j<n;++j)
        {
            vec.push_back(j+10*i);
        }
        ivec.push_back(vec);
    }


    for(int i = 0; i < m; ++i)
    {
        std::cout<<"The "<<i + 1<<"th output is: ";
        for(int j = 0; j < n; ++j)
        {
            std::cout<<ivec[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    system("pause");
    return 0;
}