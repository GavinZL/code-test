
// 1. RVO(Return Value Optimization) / NRVO (Named Return Value Optimization)
    // 直接将返回值的内存申请在调用者堆栈上
    class BigObject
    {
    };

    BigObject foo() 
    {
        return BigObject(); // RVO
    }

    BigObject bar()
    {
        BigObject localObj;
        return localObj;    // NRVO
    }

// 2. 移动语义使用地方
    // 将临时对象移动插入容器
    // 当使用 std::move() 表示不再需要该值时，用于将对象移动插入容器 
    // 临时 vector 及其元素的分配方式

    // note:
    // std::move 不能移动const修饰的变量
    // const 返回值也不能应用移动语义
    // 未实现移动构造的变量，显示使用std::move会退化使用 const T& 类型的copy方式

// 3. 右值引用
    // 右值引用只能引用没有名称的临时对象，或通过std::move的对象
    // 注意，用 std::move() 标记马上会销毁的对象是没有意义的。事实上，这甚至会对优化产生反 效果。
    // 类中，任何形式的复制构造函数、复制赋值操作符或析构函数的显式声明都 禁用移动操作的自动生成

// 4. 
// a.请注意，手动实现移动构造函数和移动赋值操作符时，通常都应该有 noexcept 声明 （避免移动中赋值错误）
// b.移动将一个对象赋值给它自己之后，该对象处于一个有效但未定义的状态。

// 5.    
// std::string 小字符串优化 （SSO) , cap + size + pointer = 24bit, 就用这24bit存储小字符串



// ADL原则，参数依赖查询， 根据参数的命名空间，推断函数的命名空间
// namespace adl
// {
//     class ADLClass{};
//     void func(ADLClass& cls){}
// }

// int main(int argc, char* argv[])
// {
//     adl::ADLClass adl;
//     func(adl);          //adl, 通过参数的命名空间，推导函数的命名空间

//     adl::func(adl);     //正常的调用逻辑
//     return 0;
// }


// std::move && std::forward 测试
#include <stdio.h>
#include <utility>
#include <vector>
#include <type_traits>
#include <array>
#include <cstddef>
#include <memory>
#include <iostream>
#include <unordered_map>


class MFclass
{
public:
    MFclass(){printf("MFclass()\n");}
    MFclass(const MFclass& cls) {printf("MFclass(const MFclass&)\n");}
    MFclass(MFclass&& cls){printf("MFclass(MFclass&&)\n");}
    void operator = (const MFclass& cls){printf("operator = (const MFclass&)\n");}
    void operator = (MFclass&& cls){printf("operator = (MFclass&&)\n");}
    ~MFclass(){printf("~MFclass()\n");}
};

class MFclass2
{
public:
    MFclass2(){printf("MFclass2()\n");}
    MFclass2(const MFclass2& cls) {printf("MFclass2(const MFclass&)\n");}
    void operator = (const MFclass2& cls){printf("operator = (const MFclass2&)\n");}
    ~MFclass2(){printf("~MFclass2()\n");}
};

template<typename T>
void transform(T&& cls)
{
    decltype(auto) tem = std::move(cls);
    // 此处需要采用decltype(auto) 原始类型，如果类型不同，可能导致隐式转换
    // decltype(auto) tem = std::forward<T>(cls);
    // printf("transform-type: %d\n", std::is_same<MFclass&, decltype(tem)>::value);
}

template<typename T, bool b>
class MFTest
{
public:
    T _cls;
    //函数模板只有全特化，没有偏特化
    T createClassNRVO()
    {
        T cls;
        return b ? std::move(cls) : cls;
    }

    std::vector<T> createVector()
    {
        std::vector<T> ve;
        ve.emplace_back();
        return b ? std::move(ve) : ve;
    }
};

template<typename T>
class MFTest<T, true>
{
public:
    T _cls;
    //函数模板只有全特化，没有偏特化
    T createClassNRVO()
    {
        T cls;
        return std::move(cls);
    }
    std::vector<T> createVector()
    {
        std::vector<T> ve;
        ve.emplace_back();
        return std::move(ve);
    }
};

template<typename T>
class MFTest<T, false>
{
public:
    // T _cls;
    //函数模板只有全特化，没有偏特化
    T createClassNRVO()
    {
        T cls;
        return cls;
    }

    std::vector<T> createVector()
    {
        std::vector<T> ve;
        ve.emplace_back();
        return ve;
    }
};

template<typename T>
class MFTest2
{
public:
    T _cls;
};



void testForward(MFclass&& cls)
{
    auto _cls = std::forward<MFclass>(cls);
    auto _cls2 = std::move(cls);
}

// 构造赋值
class MFTest3
{
public:
    MFTest3(MFclass&& cls) :_cls(std::move(cls)) //这样赋值 只会有一次移动构造调用
    {
        // 如果赋值一个右值，存在一个_cls的构造 + 移动赋值
        // _cls = std::move(cls);
    }
private:
    MFclass _cls;
};

int main(int argc, char* argv[])
{

    // 1.临时对象应用初始化
    // 此种类型，不建议在返回值前添加std::move,
    // a. 调用std::move 会将返回值类型改变 MFclass --> MFclass&&, 阻止了编译器的RVO优化
    // b. 此种情况会多调用一次移动构造函数，如果返回类型没有移动构造退化调用copy构造函数
    // auto cls1 = MFTest<MFclass,false>().createClassNRVO();       //对象一次构造析构
    // auto cls2 = MFTest<MFclass,true>().createClassNRVO();        //两次构造一次移动构造
    // auto cls3 = MFTest<MFclass2,false>().createClassNRVO();      //对象一次构造析构
    // auto cls4 = MFTest<MFclass2,true>().createClassNRVO();       //
    // auto func = []()->decltype(auto) { return std::move(MFclass2());};
    // auto cls5 = func();

    // auto cls6 = MFTest<MFclass, false>().createVector();
    // auto cls7 = MFTest<MFclass, true>().createVector();             // ???为啥会有两次构造
                                                                    // 测试结果：使用move-vector时，默认会构造一个对象

    // 2. 临时对象赋值
    // a. 无具名对象(临时对象赋值)
    // MFTest2<MFclass>()._cls = MFTest<MFclass,false>().createClassNRVO();            //调用赋值移动
    // MFTest2<MFclass2>()._cls = MFTest<MFclass2,false>().createClassNRVO();            //调用赋值移动2
    // MFTest2<MFclass>()._cls = std::move(MFTest<MFclass,false>().createClassNRVO());    //调用赋值移动, std::move多余调用
    // MFTest2<MFclass2>()._cls = std::move(MFTest<MFclass2,false>().createClassNRVO());    //调用赋值移动, std::move多余调用
    
    // b. 具名赋值 & 参数传递
    // decltype(auto) tmp = MFTest<MFclass,false>().createClassNRVO();
    // MFTest2<MFclass>()._cls = tmp;               //拷贝赋值， 左值
    // MFTest2<MFclass>()._cls = std::move(tmp);    //移动赋值， 右值
    // transform(tmp);                              //拷贝构造， 左值
    // transform(std::move(tmp));                   //移动构造， 右值
    // transform(MFTest<MFclass,false>().createClassNRVO());//同上

    // decltype(auto) tmp2 = MFTest<MFclass2,false>().createClassNRVO();
    // MFTest2<MFclass2>()._cls = tmp2;               //拷贝赋值， 左值
    // MFTest2<MFclass2>()._cls = std::move(tmp2);    //移动赋值， 右值
    // transform(tmp2);                              //拷贝构造， 左值
    // transform(std::move(tmp2));                   //移动构造， 右值
    // transform(MFTest<MFclass2,false>().createClassNRVO());//同上

    // decltype(auto) tmp = MFTest<MFclass2,false>().createClassNRVO();
    // MFTest2<MFclass2>()._cls = tmp;

    // 3.内存对齐
    // a.以最大bit字段为整体内存对齐位数，以下最大为4bit，整数需以4的倍数对齐(16bit)
    // b.以当前字段类型大小对齐offset ,以下对齐方式 1x11111111xx1111
    // struct A
    // {
    //     uint8_t a1;                     // 1bit
    //     std::array<uint16_t,4> a2;      // 2*4 = 8bit
    //     uint32_t a3;                    // 4bit
    // };
    // printf("size: %ld\n", sizeof(A));

    // 4. move static变量
    // static std::vector<int32_t> sv{1,2,3,4,5,6,7,8};
    // std::vector<int32_t> sv1 = std::move(sv);
    // printf("--> sv: %ld, sv1: %ld\n", sv.size(), sv1.size());

    // 5. struct var move
    // struct SM
    // {
    //     std::array<int32_t, 5> arr{1, 2, 3, 4, 5};
    // };

    // SM sm1{10, 20, 30, 40, 50};
    // SM sm2 = std::move(sm1);
    // printf("--> sm1: %ld, sm2: %ld\n", sm1.arr.size(), sm2.arr.size());
    // for(int i=0; i<5; i++)
    // {
    //     printf("[%d] - %d-%d\n", i, sm1.arr[i], sm2.arr[i]);
    // }

    // 6. 值传递
    // a.值传递时，通过移动来创建并初始化一个新值时，收益比较大
    // b.如果已经存在一个值，给这个值赋值场景，采用值传递就适得其反，此时建议采用const 左值引用

    // 7. 成员变量初始化测试
    // MFTest3 tst3(MFTest<MFclass,false>().createClassNRVO());

    // 8. 智能指针赋值&析构
    // MFclass *a = new MFclass();
    // auto aa = std::shared_ptr<MFclass>(a);
    // auto bb = std::shared_ptr<MFclass>(aa.get());
    // printf("a: %ld, b: %ld\n", aa.use_count(), bb.use_count());


    // 9.测试编译默认生成特殊函数
    // // 继承类没有move构造，导致基类的数据也不能move
    // class S1
    // {
    // public:
    //     std::vector<int> v{1,2,3,4};

    //     // virtual ~S1() = default;
    // };

    // class S2 : public S1
    // {
    // public:
    //     std::vector<int> v2{2,3,4,5};

    //     virtual ~S2() = default;
    // };

    // S1 s1;
    // S1 s2 = s1;
    // printf("s1: %ld, s2: %ld\n", s1.v.size(), s2.v.size());
    // S1 s3 = std::move(s1);
    // printf("s1: %ld, s3: %ld\n", s1.v.size(), s3.v.size());

    // S2 a2;
    // S2 a3 = a2;
    // printf("a2: v:%ld,v2:%ld, a3: v:%ld, v2:%ld\n", a2.v.size(),a2.v2.size(), a3.v.size(), a3.v2.size());
    // S2 a4 = std::move(a2);
    // printf("a2: v:%ld,v2:%ld, a4: v:%ld, v2:%ld\n", a2.v.size(),a2.v2.size(), a4.v.size(), a4.v2.size());


    // 10.
    // std::string &&st = "hello"; //complile error , "hello" 是一个lvalue
    // "hello" = "world";           //error: read-only variable is not assignable
    // printf("%d\n", std::is_same<const char[6], decltype("hello")>::value);
    // std::cout << "type: " << typeid("hello").name() << std::endl;


    // 11. 非模板函数的 forward操作
    // testForward(MFTest<MFclass,false>().createClassNRVO());

    // 12. 强制类型转换
    // a. reinterpret_cast 用于进行各种不同类型的指针之间、不同类型的引用之间以及指针和能容纳指针的整数类型之间的转换
    // b. static_cast 用于进行比较“自然”和低风险的转换，如整型和浮点型、字符型之间的互相转换
    // c. const_cast 运算符仅用于进行去除 const 属性的转换，它也是四个强制类型转换运算符中唯一能够去除 const 属性的运算符
    // d. 用 reinterpret_cast 可以将多态基类（包含虚函数的基类）的指针强制转换为派生类的指针，但是这种转换不检查安全性，即不检查转换后的指针是否确实指向一个派生类对象。dynamic_cast专门用于将多态基类的指针或引用强制转换为派生类的指针或引用，而且能够检查转换的安全性。
    //    dynamic_cast 是通过“运行时类型检查”来保证安全性的。dynamic_cast 不能用于将非多态基类的指针或引用强制转换为派生类的指针或引用——这种转换没法保证安全性，只好用 reinterpret_cast 来完成。

    // 13. decltype类型
    // auto decf = [](std::string&& str){
    //     // 区别decltype(str) 与 decltype((str)) ,一个圆括号&两个圆括号
    //     // decltype检测名称类型
    //     std::cout << std::is_same<decltype(str), std::string&&>::value << std::endl; // true
    //     std::cout << std::is_reference<decltype(str)>::value << std::endl; // true
    //     std::cout << std::is_rvalue_reference<decltype(str)>::value << std::endl; // true
    //     // decltype检测值类型
    //     std::cout << std::is_same<decltype((str)), std::string&>::value << std::endl; // true
    //     std::cout << std::is_reference<decltype((str))>::value << std::endl; // true
    //     std::cout << std::is_lvalue_reference<decltype((str))>::value << std::endl; // true
    // };

    // decf("hello");

    // 14. 迭代器失效处理
    // std::unordered_map<int, int> _map{
    //     {1,1},
    //     {2,2},
    //     {3,3},
    //     {4,4},
    //     {5,5},
    //     {6,6},
    //     {7,7}
    // };

    // for(auto it = _map.begin(); it !=  _map.end(); )
    // {
    //     printf("key: %d, value: %d\n", it->first, it->second);
    //     if(it->first == 3)
    //     {
    //         it = _map.erase(it);
    //     }else{
    //         ++it;
    //     }
    // }

    // 15. std::forward
    // 1. 将调用形参作为纯 rvalue 引用 (使用 && 声明，但不使用 const 或 volatile)。
    // 2. 形参的类型必须是函数模板的形参。
    // 3. 将形参转发给另一个函数时，可以使用 std::forward<>() 的辅助函数，该函数在 <utility>
    // 头文件中声明。

    // 通用引用\转发引用 [模板中]
    // • 可以统一绑定到所有类型的对象 (const 和非 const) 和值类别。
    // • 通常用来转发参数，但这并不是唯一的用法

    // • 带有两个 & 符 (&&) 的声明可以是两个不同的类型:
    //     - 如果不是函数模板形参，它是一个普通的 ravlue 引用，只绑定到 ravlue。 
    //     - 如果是函数模板参数，它是一个通用引用，可以绑定到所有值类别。
    // • 通用引用 (在 C++ 标准中称为转发引用) 是一种可以通用地引用任何类型和值类别对象的引 用。类型是:
    //     - lvalue引用(类型&):绑定到lvalue
    //     - rvalue引用(类型&&):绑定到rvalue
    // • 要完美地传递传递的实参，请使用 std::forward<>()，并将该形参声明为函数模板形参的通 用引用。
    // • std::forward<>() 是一个条件 std::move()。如果参数是 rvalue，则扩展为 std::move()。
    // • 使用 std::forward<>() 标记对象可能是有意义的，即使在调用成员函数时也是如此。
    // • 通用引用是所有重载解析的次优选择。
    // • 不要为通用引用实现泛型构造函数 (或为特定类型进行约束)。

    return 0;
}