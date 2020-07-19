// STL中的绑定器有类绑定器和函数绑定器两种，类绑定器有binder1st和binder2nd，而函数绑定器是bind1st和bind2nd，他们的基本目的都是用于构造一个一元的函数对象。
// 绑定器bind


// bind2nd( lt, val )     仿函数
// 使用仿函数配合绑定器 用于作为 find_if 的第三个参数

#include <iostream>
#include <vector>
#include <string>

#include <algorithm>    //find_if()

using namespace std;



string    str_camer[6]    = { "a365" ,"365d" ,"39de" ,"47fd" ,"2t73" ,"3g46" };
vector<string> vct_camer( str_camer, str_camer+6 );    // 使用已初始化的数组初始化list



/* -------------------------------------------------------------------------- */
/*                                     仿函数                                    */
/* -------------------------------------------------------------------------- */
class A {
  public:
  A(const std::string str,int id)
          {
            this->str=str; this->id=id;
          } 
  string GetStr()
      {
          return str;
      }
  private:
        std::string str; int id;

};


// 仿函数
struct compare: binary_function<A, string,bool> {       // 这里继承 binary_function
  bool operator()( A &value, string str) const          // value 是引用
  {
    if (value.GetStr()== str)
      return true;
    else
      return false;
  }
};


// 函数，两个参数
template<typename T> bool compare_no(const T* s1 , const T* s2)
{  
          return strcmp(s1->no, s2->no) == 0;   // strcmp() 函数用于对两个字符串进行比较（区分大小写）

}

/* ----------------------------------- 仿函数 ---------------------------------- */



int main(){
    vector<A> a;
    A b( "aa",4);

    A c( "bb",6);

    A d( "23",9);

    A e( "zz",7);

    a.push_back(b);

    a.push_back(c);

    a.push_back(d);

    a.push_back(e);


// bind2nd() 绑定仿函数 compare
    vector<A>::iterator t = find_if(a.begin(),a.end(),bind2nd(compare(), "33"));
    if (t != a.end()) // 找到了
    {
        cout << "Yes Found : " << t->GetStr() << endl;
    }
    else // 没找到
    {
        // do something
        cout << "con't find it" << endl;
    }











    system("pause");
    return 0;
}