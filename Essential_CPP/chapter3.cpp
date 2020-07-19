/**************************************************
 * Essential C++ -- Stanley Lippman
 * 中文版
 * 编码 GB2312
 * dongdongmingming 
 * email: domingfan@163.com
 *************************************************/
#include <iostream>
#include <vector>
#include <string>

#include <algorithm>    //find_if()

using namespace std;




// from Section 3.6: How to Design a Generic Algorithm*********************************************************************************************
// 从 3.6 节开始，如何设计一个泛型算法




const int int_size = 12;
int    ia[int_size]    = { 1, 1, 2, 3, 5, 11, 13, 21, 34, 55, 89, 144 };
vector<int> ivec( ia, ia+int_size );


// 函数对象 function object
// 比较两个变量大小，第一个参数大于第二个参数返回true,否者返回false
class UAverage
{
public:
    bool operator()(int a1, int a2)
    {  //重载()运算符
        return a1 < a2 ? true : false;
    }
};



// P83
// 将vector vec中小于10的所有元素组成一个新的vector nvec返回
vector<int> less_than_10( const vector<int> &vec )
{
    vector<int> nvec;
    for ( int ix = 0; ix < vec.size(); ++ix )
          if ( vec[ ix ] < 10 )
               nvec.push_back( vec[ ix ] );
    return nvec;
}







bool less_than( int v1, int v2 ) 
     { return v1 < v2 ? true : false; }

bool greater_than( int v1, int v2 ) 
     { return v1 > v2 ? true : false; }


// P84
// filter() P83
// filter_value 传入被比较值，pred传入调用 比较函数指针
vector<int> filter_ver1( const vector<int> &vec, int filter_value, bool (*pred)( int, int ))
{
    vector<int> nvec;

    for ( int ix = 0; ix < vec.size(); ++ix )
          // invokes the function addressed by pred
          // tests element vec[ix] against filter_value
          if ( pred( vec[ ix ], filter_value ))
               nvec.push_back( vec[ ix ] );

    return nvec;
}


// P87
// 使用了bind2nd()  function object adapter
vector<int> filter_ver2( const vector<int> &vec, int val, const less<int> &lt )     // less<int> 函数对象（看做less<int>类型） 前需要加上const，否者会报错：非常量引用的初始值必须为左值
{
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();
    
    // bind2nd( less<int>, val )
    // binds val to the second value of less<int>
    // less<int> now compares each value against val

    while (( iter = find_if( iter, vec.end(), bind2nd( lt, val ))) != vec.end() )
    {
             // each time iter != vec.end(), 
             // iter addresses an element less than val
             nvec.push_back( *iter );
             iter++;
    }
    return nvec;
}



// filter_ver2 改为函数模板，即将元素类型加入template的声明中，这样可以自定义元素类型
// 同时，不再将vector的引用传入而是传入始迭代器和终止迭代器，并且返回一个迭代器，这样可以自定义变更容器类型
template <typename InputIterator, typename OutputIterator, typename ElemType, typename Comp>    // 函数模板 ，定义多种类型，其中 Comp 是函数对象类型
OutputIterator      // 返回类型
filter_ver3(InputIterator first, InputIterator last, OutputIterator at, const ElemType &val, Comp pred) // pred 是函数对象
{
    while (( first = find_if( first, last, bind2nd( pred, val ))) != last )
        {
             cout << "found value: " << *first  << endl;
             // assign value, then advance both iterators
             *at++ = *first++;
        }
    return at;
}




int main()
{

    const int solution_size = 6;

    // 这里先展示less的用法，传入两个参数，如果第一个值小于第二个值就返回true。
    cout << "less return: " << less<int>()(12, 10) << endl;


    vector<int> local_vec = less_than_10(ivec);
    cerr << "less_than_10() less than 10 >" << local_vec.size() << endl;

	const int partition_value = 10;
    local_vec = filter_ver1(ivec, partition_value, greater_than);   // 支持指定比较值，比较函数指针
    cerr << "filter_ver1() greater than 10 <" << local_vec.size() << endl;

    
    local_vec = filter_ver2( ivec, partition_value, less<int>() );
    cerr << "filter_ver2() less than 10 <" << local_vec.size() << endl;

    cout << "filter_ver3 for array---" << endl;
    // unless we use an iserter, must provide a sized container
	// within which filter can assign the values ...
	int ia2[ solution_size ];   // 这个容器用来存储过滤结果
	filter_ver3( ia, ia+int_size, ia2, partition_value, less<int>() );


    cout << "filter_ver3 for vector---" << endl;
    vector<int> ivec2( solution_size );   // 这个容器用来存储过滤结果
	filter_ver3( ivec.begin(), ivec.end(), ivec2.begin(), 
                 partition_value, greater<int>() );


    system("pause");
    return 0;
}