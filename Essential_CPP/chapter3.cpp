/**************************************************
 * Essential C++ -- Stanley Lippman
 * ���İ�
 * ���� GB2312
 * dongdongmingming 
 * email: domingfan@163.com
 *************************************************/
#include <iostream>
#include <vector>
#include <string>

#include <algorithm>    //find_if()

using namespace std;




// from Section 3.6: How to Design a Generic Algorithm*********************************************************************************************
// �� 3.6 �ڿ�ʼ��������һ�������㷨




const int int_size = 12;
int    ia[int_size]    = { 1, 1, 2, 3, 5, 11, 13, 21, 34, 55, 89, 144 };
vector<int> ivec( ia, ia+int_size );


// �������� function object
// �Ƚ�����������С����һ���������ڵڶ�����������true,���߷���false
class UAverage
{
public:
    bool operator()(int a1, int a2)
    {  //����()�����
        return a1 < a2 ? true : false;
    }
};



// P83
// ��vector vec��С��10������Ԫ�����һ���µ�vector nvec����
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
// filter_value ���뱻�Ƚ�ֵ��pred������� �ȽϺ���ָ��
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
// ʹ����bind2nd()  function object adapter
vector<int> filter_ver2( const vector<int> &vec, int val, const less<int> &lt )     // less<int> �������󣨿���less<int>���ͣ� ǰ��Ҫ����const�����߻ᱨ���ǳ������õĳ�ʼֵ����Ϊ��ֵ
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



// filter_ver2 ��Ϊ����ģ�壬����Ԫ�����ͼ���template�������У����������Զ���Ԫ������
// ͬʱ�����ٽ�vector�����ô�����Ǵ���ʼ����������ֹ�����������ҷ���һ�������������������Զ�������������
template <typename InputIterator, typename OutputIterator, typename ElemType, typename Comp>    // ����ģ�� ������������ͣ����� Comp �Ǻ�����������
OutputIterator      // ��������
filter_ver3(InputIterator first, InputIterator last, OutputIterator at, const ElemType &val, Comp pred) // pred �Ǻ�������
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

    // ������չʾless���÷����������������������һ��ֵС�ڵڶ���ֵ�ͷ���true��
    cout << "less return: " << less<int>()(12, 10) << endl;


    vector<int> local_vec = less_than_10(ivec);
    cerr << "less_than_10() less than 10 >" << local_vec.size() << endl;

	const int partition_value = 10;
    local_vec = filter_ver1(ivec, partition_value, greater_than);   // ֧��ָ���Ƚ�ֵ���ȽϺ���ָ��
    cerr << "filter_ver1() greater than 10 <" << local_vec.size() << endl;

    
    local_vec = filter_ver2( ivec, partition_value, less<int>() );
    cerr << "filter_ver2() less than 10 <" << local_vec.size() << endl;

    cout << "filter_ver3 for array---" << endl;
    // unless we use an iserter, must provide a sized container
	// within which filter can assign the values ...
	int ia2[ solution_size ];   // ������������洢���˽��
	filter_ver3( ia, ia+int_size, ia2, partition_value, less<int>() );


    cout << "filter_ver3 for vector---" << endl;
    vector<int> ivec2( solution_size );   // ������������洢���˽��
	filter_ver3( ivec.begin(), ivec.end(), ivec2.begin(), 
                 partition_value, greater<int>() );


    system("pause");
    return 0;
}