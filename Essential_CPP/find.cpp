#include <list>
#include <map>
#include <iostream>
#include <algorithm>    //find_if() find()

using namespace std;

// find() 和 find_if() 的使用
// 仿函数例子参考 cpp_bianchengnet\functionObject.cpp
// 仿函数是重载了()运算符的类，但是重载运算符()可以有一个或多个操作数
// find_if() 第三个参数只能使用只有一个操作数的函数对象，所以需要使用bind2nd()或bind1st()绑定一个操作数为固定值，使拥有两个操作数的函数对象（比如bless()等）变为单操作数函数对象


// 类
class CCPerson
{
public:
    CCPerson(void);
    ~CCPerson(void);

    bool operator==(const CCPerson &rhs) const      // 重载“==”操作符  自定义比较操作
    {
        return (age == rhs.age);
    }
public:
    int age;
};
CCPerson::CCPerson(){}
CCPerson::~CCPerson(){ cout<<"m_s"<<endl; }

// 仿函数
typedef struct finder_t
{
    finder_t(int n) : age(n) { }
    bool operator()(CCPerson *p)
    {
        return (age == p->age);
    }
    int age;
}finder_t;

int    ia[12]    = { 1, 10, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
list<int> lst( ia, ia+12 );    // 使用已初始化的数组初始化list


// 一个参数函数一个bool类型返回值的普通函数
bool less_than_15( int v1 ) 
     { return v1 < 15 ? true : false; }


// 仿函数例子一
// 单个操作数 unary function object
class less_than_25
{
public:
    bool operator()(float a1) const
    {   //重载()运算符
    return a1 < 25;
    }
};


// 仿函数例子二
// 两个操作数 binary function object
struct less_than_nn:binary_function<int, int, bool>{                //ff bind2nd 使用的函数对象需要继承自 binary_function
    bool operator()(const int &a , const int &b) const{
        return a<b;
    }
};



int main()
{

// 对int类型list使用 find()
    list<int>::iterator it = find(lst.begin(), lst.end(), 10); // 查找list中是否有元素“10”
    if (it != lst.end()) // 找到了
    {
        // do something 
        std::cout << "find it" << endl;
    }
    else // 没找到
    {
        // do something
        cout << "con't find it" << endl;
    }



// 那么，如果容器里的元素是一个类呢？例如，有list<CCPerson> ，其中CPerson类定义如上
list<CCPerson> gglst;
list<CCPerson*> cclst;
CCPerson aaa,bbb,ccc,ddd,eee,fff,ggg;
aaa.age=15;
bbb.age=16;
ccc.age=50;
eee.age=53;
fff.age=55;
ggg.age=73;

gglst.push_back(aaa);
gglst.push_back(bbb);
gglst.push_back(ccc);
gglst.push_back(ddd);
gglst.push_back(eee);
gglst.push_back(fff);
gglst.push_back(ggg);

cclst.push_back(&aaa);
cclst.push_back(&bbb);
cclst.push_back(&ccc);
cclst.push_back(&ddd);
cclst.push_back(&eee);
cclst.push_back(&fff);
cclst.push_back(&ggg);


// 对类对象使用 find()  即 查找“相等”的类对象
// 判断两个CPerson对象“相等”的定义，是通过类重载“==”操作符实现的
// 这里list存储的是类CCPerson的对象
CCPerson cp_to_find; // 要查找的对象
cp_to_find.age = 50;
list<CCPerson>::iterator cit = find(gglst.begin(), gglst.end(), cp_to_find); // 查找，在前两个参数指定的范围内查找和第三个参数相等的第一个对象

// 两个对象的比较通过重载的 "==" 操作符实现
if (cit != gglst.end()) // 找到了
{
    std::cout << "find() find the first!" << std::endl;
}
else // 没找到
{
    std::cout << "None#1" << std::endl;
}


/* ------------------------------ find_if 分割线 ------------------------------ */


// find()的第三个参数是元素（如对象，简单类型int类型，值等），find_if()的第三个参数可以指定判断方法（返回bool）
// 使用 find_if() 第三个参数使用结构体重载
// 但是当比较的两个元素已经有其自己的“相等”定义，即是说我们不能够给list元素重载“==”操作符，
// 比如下面的list中的每一个元素都是一个对象的指针，我们不能通过判断指针是否相等来实现我们想要的判断。
// 我们需要借助于结构体（函数对象） finder_t ，我们可以使用 find_if() 查找容器元素是CCPerson类的内容。
// 这里list存储的是类CCPerson的指针
list<CCPerson*>::iterator iit = find_if(cclst.begin(), cclst.end(), finder_t(50)); // 查找年龄为50的人
if (iit != cclst.end()) // 找到了
{
    cout << "Yes Found person with age : " << (*iit)->age << endl;
}
else // 没找到
{
    // do something
    cout << "con't find it" << endl;
}



// 使用 find_if() 第三个参数使用函数对象
    class map_value_finder
    {
    public:
        map_value_finder(const std::string &cmp_string):m_s_cmp_string(cmp_string){}
        bool operator ()(const std::map<int, std::string>::value_type &pair)
        {
            return pair.second == m_s_cmp_string;
        }
    private:
        const std::string &m_s_cmp_string;                    
    };

    std::map<int, std::string> my_map;
    my_map.insert(std::make_pair(10, "china"));
    my_map.insert(std::make_pair(20, "usa"));
    my_map.insert(std::make_pair(30, "english"));
    my_map.insert(std::make_pair(40, "hongkong"));    
    
    std::map<int, std::string>::iterator nit = my_map.end();
    nit = find_if(my_map.begin(), my_map.end(), map_value_finder("English"));
    if (nit == my_map.end())
       printf("not found\n");       
    else
       printf("found key:%d value:%s\n", nit->first, nit->second.c_str());


// 使用 find_if() 第三个参数使用单参数普通函数
    list<int>::const_iterator iter15 =  find_if( lst.begin(), lst.end(),   less_than_15); // 可以使用只有一个参数一个bool返回值的普通函数
    if (iter15 == lst.end())
       cerr << "not found\n"<< endl;       
    else
       cerr << "less_than_15 found \n"<< endl;



// 使用 find_if() 第三个参数使用unary(一元)functionobject
    list<int>::const_iterator iter25 =  find_if( lst.begin(), lst.end(),   less_than_25());
    if (iter25 == lst.end())
       cerr << "not found\n"<< endl;       
    else
       cerr << "less_than_25() found \n"<< endl;


    int val = 56;
// 使用 find_if() 第三个参数使用binary(二元)functionobject，使用function object adapter转化为一元再传入
    list<int>::const_iterator iternn =  find_if( lst.begin(), lst.end(),   bind2nd(less_than_nn(), val));
    if (iternn == lst.end())
       cerr << "not found\n"<< endl;       
    else
       cerr << "less_than_nn() found \n"<< endl;




    system("pause");
    return 0;
}

