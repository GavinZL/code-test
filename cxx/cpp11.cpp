// features

#include <cstdio>
#include <memory>
#include <utility>
#include <array>
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <complex>

int main(int argc, char* argv[])
{


//  1.移动语义
    //  1.1 减少拷贝
    //  1.2 使noncopyable类型可以进行move

//  2.右值引用 【Rvalue references only bind to rvalues】
    //  2.1 右值、左值、左值引用、右值引用
            // 左值：赋值'='的左侧，通常是一个变量
            // 右值：赋值‘=’的右侧，通常是一个常量、表达式、函数， 不能绑定到非const变量，避免修改临时值的值
            // 左值引用：
            // 右值引用：
    //  2.2 int&& xr2 = 0; // `xr2` is an lvalue of type `int&&` -- binds to the rvalue temporary, `0`

//  3.万能引用
    //  3.1 T&& 
    //  3.2 引用折叠
    //      T& & becomes T&
    //      T& && becomes T&
    //      T&& & becomes T&
    //      T&& && becomes T&&
    int x = 0;      // `x` is an lvalue of type `int`
    auto&& al = x;  // `al` is an lvalue of type `int&` -- binds to the lvalue, `x`
    auto&& ar = 0;  // `ar` is an lvalue of type `int&&` -- binds to the rvalue temporary, `0`

    // // Since C++14 or later:
    // void f(auto&& t) {
    // // ...
    // }

    // // Since C++11 or later:
    // template <typename T>
    // void f(T&& t) {
    // // ...
    // }

    // int x = 0;
    // f(0);       // T is int, deduces as f(int &&) => f(int&&)
    // f(x);       // T is int&, deduces as f(int& &&) => f(int&)

    // int& y = x;
    // f(y);       // T is int&, deduces as f(int& &&) => f(int&)

    // int&& z = 0;// NOTE: `z` is an lvalue with type `int&&`.
    // f(z);       // T is int&, deduces as f(int& &&) => f(int&)
    // f(std::move(z)); // T is int, deduces as f(int &&) => f(int&&)    

//  4.变参模板
    // 怎么创建一个拥有1个、2个或者更多的初始化器的类？
    // 怎么避免创建一个实例而只拷贝部分的结果？
    // 怎么创建一个元组
    // template <typename... T>
    // struct arity {
    // constexpr static int value = sizeof...(T);
    // };
    // static_assert(arity<>::value == 0);
    // static_assert(arity<char, short, int>::value == 3);

    //eg.
    // template <typename First, typename... Args>
    // auto sum(const First first, const Args... args) -> decltype(first) {
    // const auto values = {first, args...};
    // return std::accumulate(values.begin(), values.end(), First{0});
    // }

    // sum(1, 2, 3, 4, 5); // 15
    // sum(1, 2, 3);       // 6
    // sum(1.5, 2.0, 3.7); // 7.2

//  5.初始化列表 std::initializer_list
    // int sum(const std::initializer_list<int>& list) {
    //     int total = 0;
    //     for (auto& e : list) {
    //         total += e;
    //     }
    //     return total;
    // }

    // auto list = {1, 2, 3};
    // sum(list); // == 6
    // sum({1, 2, 3}); // == 6
    // sum({}); // == 0

//  6. static_assert 编译器
    // static_assert(expression, string);
    // expression在编译期进行求值，当结果为false（即：断言失败）时，将string作为错误消息输出

//  7. auto 推断
    // 应用到一个变量

//  8. lambda 表达式
    // [] - captures nothing.
    // [=] - capture local objects (local variables, parameters) in scope by value.
    // [&] - capture local objects (local variables, parameters) in scope by reference.
    // [this] - capture this by reference.
    // [a, &b] - capture objects a by value, b by reference.

//  9. decltype 表达式类型推断，保留引用 、cv
    // 应用到一个表达式

//  10. 类型别名 using
    // template <typename T>
    // using Vec = std::vector<T>;
    // Vec<int> v; // std::vector<int>

    // using String = std::string;
    // String s {"foo"};

//  11. nullptr 替换NULL

//  12. 枚举强类型
    // // Specifying underlying type as `unsigned int`
    // enum class Color : unsigned int {
    //  Red = 0xff0000, 
    //  Green = 0xff00, 
    //  Blue = 0xff };
    // // `Red`/`Green` in `Alert` don't conflict with `Color`
    // enum class Alert : bool { Red, Green };
    // Color c = Color::Red;

//  13. attribute 提供统一的语法相对于__attribute__(..), __declspec
    // // `noreturn` attribute indicates `f` doesn't return.
    // [[ noreturn ]] void f() {
    //      throw "error";
    // }

//  14. constexpr 常量表达式
    // 注意：constexpr函数有如下限制：
    // 函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new delete等，不能虚函数。
    // constexpr int square(int x) {
    //     return x * x;
    // }
    // int square2(int x) {
    //     return x * x;
    // }
    // int a = square(2);  // 注意此处传递的是常量，故可以在编译阶段进行优化
    //                     // mov DWORD PTR [rbp-4], 4
    // int b = square2(2); // mov edi, 2
    //                     // call square2(int)
    //                     // mov DWORD PTR [rbp-8], eax
    
    // const int x = 123;
    // constexpr const int& y = x; // error -- constexpr variable `y` must be initialized by a constant expression
    
    // const:主要用于表达“对接口的写权限控制”，即“对于被const修饰的量名(例如const指针变量)，
    // 不得通过它对所指对象作任何修改”。(但是可以通过其他接口修改该对象)。
    // 另外，把对象声明为const也为编译器提供了潜在的优化可能。具体来说就是，
    // 如果把一个量声明为const，并且没有其他地方对该量作取址运算，
    // 那么编译器通常(取决于编译期实现)会用该量的实际常量值直接替换掉代码中所有引用该量的地方，
    // 而不用在最终编译结果中生成对该量的存取指令。

    // constexpr:的主要功能则是让更多的运算可以在编译期完成，并能保证表达式在语义上是类型安全的。
    // (译注：相比之下，C语言中#define只能提供简单的文本替换，而不具任何类型检查能力)。与const相比，
    // 被constexpr修饰的对象则强制要求其初始化表达式能够在编译期完成计算。之后所有引用该常量对象的地方，
    // 若非必要，一律用计算出来的常量值替换。

//  15. 委托构造
    // struct Foo {
    //  int foo;
    //  Foo(int foo) : foo{foo} {}
    //  Foo() : Foo(0) {}   //委托构造
    // };
    
//  16. 用户自定义常量字符 User-defined literals
    // eg
    // `unsigned long long` parameter required for integer literal.
    // long long operator "" _celsius(unsigned long long tempCelsius) {
    //     return std::llround(tempCelsius * 1.8 + 32);
    // }
    // 24_celsius; // == 75
    // `const char*` and `std::size_t` required as parameters.
    // int operator "" _int(const char* str, std::size_t) {
    //     return std::stoi(str);
    // }

    // "123"_int; // == 123, with type `int`

//  17. override、final关键字

//  18. default 、delete function 默认、删除函数

//  19. 冒号循环遍历
    std::array<int, 5> a {1, 2, 3, 4, 5};
    for (int& x : a){
        x *= 2;
    }

//  20. 移动构造函数

//  21. 构造函数初始化 Converting constructors
    // struct A {
    //     A(int) {}
    //     A(int, int) {}
    //     A(int, int, int) {}
    // };

    // A a {0, 0}; // calls A::A(int, int)
    // A b(0, 0); // calls A::A(int, int)
    // A c = {0, 0}; // calls A::A(int, int)
    // A d {0, 0, 0}; // calls A::A(int, int, int)

    // struct A {
    //     A(int) {}
    //     A(int, int) {}
    //     A(int, int, int) {}
    //     A(std::initializer_list<int>) {}
    // };

    // A a {0, 0}; // calls A::A(std::initializer_list<int>)
    // A b(0, 0); // calls A::A(int, int)
    // A c = {0, 0}; // calls A::A(std::initializer_list<int>)
    // A d {0, 0, 0}; // calls A::A(std::initializer_list<int>)

//  22. explicit关键字

//  23. inline namespace ，使用了inline就称为默认调用对象，如果要调用Version1需要显示指定
    // namespace Program {
    //     namespace Version1 {
    //         int getVersion() { return 1; }
    //         bool isFirstVersion() { return true; }
    //     }
    //     inline namespace Version2 {
    //         int getVersion() { return 2; }
    //     }
    // }

    // int version {Program::getVersion()};              // Uses getVersion() from Version2
    // int oldVersion {Program::Version1::getVersion()}; // Uses getVersion() from Version1
    // bool firstVersion {Program::isFirstVersion()};    // Does not compile when Version2 is added

//  24. 非静态数据初始化
    // Default initialization prior to C++11
    // class Human {
    //     Human() : age{0} {}
    // private:
    //     unsigned age;
    // };
    // // Default initialization on C++11
    // class Human {
    // private:
    //     unsigned age {0};
    // };
    // c++98: 只要static const int 类型的变量可在类内部初始化
    // c++11: 允许非静态成员在类内部初始化 - 主要减少多个构造函数初始化 ，且构造函数初始化覆盖类内部初始化值

//  25. 根据*this是左值or右值，限制成员函数 【&、const&、&&...】
    // struct Bar {
    // // ...
    // };

    // struct Foo {
    //     Bar getBar() & { return bar; }
    //     Bar getBar() const& { return bar; }
    //     Bar getBar() && { return std::move(bar); }
    // private:
    //     Bar bar;
    // };

    // Foo foo{};
    // Bar bar = foo.getBar(); // calls `Bar getBar() &`

    // const Foo foo2{};
    // Bar bar2 = foo2.getBar(); // calls `Bar Foo::getBar() const&`

    // Foo{}.getBar(); // calls `Bar Foo::getBar() &&`
    // std::move(foo).getBar(); // calls `Bar Foo::getBar() &&`

    // std::move(foo2).getBar(); // calls `Bar Foo::getBar() const&&`

//  26. Trailing return types 
    // 主要解决作用域问题
    // int f() {
    //     return 123;
    // }
    // // vs.
    // auto f() -> int {
    //     return 123;
    // }
    // auto g = []() -> int {
    //     return 123;
    // };
    // NOTE: This does not compile!
    // template <typename T, typename U>
    // decltype(a + b) add(T a, U b) {
    //     return a + b;
    // }

    // // Trailing return types allows this:
    // template <typename T, typename U>
    // auto add(T a, U b) -> decltype(a + b) {
    //     return a + b;
    // }

//  27. char32_t and char16_t
    char32_t utf8_str32[] = U"\u0123";
    char16_t utf8_str16[] = u"\u0123";

//  28. Raw string literals
    //格式： R"delimiter(raw_characters)delimiter"
    // msg1 and msg2 are equivalent.
    const char* msg1 = "\nHello,\n\tworld!\n";
    const char* msg2 = R"(
    Hello,
        world!
    )";

//  29. 继承的构造函数
    // class Derived : public Base {
    // public:
    //     // 提升Base类的f函数到Derived类的作用范围内
    //     // 这一特性已存在于C++98标准内
    //     using Base::f;
    //     void f(char);     // 提供一个新的f函数
    //     void f(int);  // 与Base类的f(int)函数相比更常用到这个f函数
    //     // 提升Base类的构造函数到Derived的作用范围内
    //     // 这一特性只存在于C++11标准内
    //     using Base::Base;
    //     Derived(char);    // 提供一个新的构造函数
    //     // 与Base类的构造函数Base(int)相比
    //     // 更常用到这个构造函数
    //     Derived(int);
    //     // …
    // };

//  30. 用做模板参数的局部类型
    // void f(vector<X>& v)
    // {
    //     struct Less {
    //         bool operator()(const X& a, const X& b)
    //         { return a.v<b.v; }
    //     };
    //     // C++98: 错误: Less是局部类
    //         // C++11: 正确
    //         sort(v.begin(), v.end(), Less());
    // }

    // template<typename T> void foo(T const& t){}
    // enum X { x };
    // enum { y };

    // int main()
    // {
    //     foo(x);     // C++98: ok; C++11: ok
    //     //（译注：y是未命名类型的值，C++98无法从这样的值中推断出函数模板参数）
    //     foo(y);     // C++98: error; C++11: ok
    //     enum Z { z };
    //     foo(z);     // C++98: error; C++11: ok
    //     //（译注：C++98不支持从局部类型值推导模板参数
    // }

//  31. 窄类型转换
    // int x0 {7.3};    // 编译错误: 窄转换
    // int x1 = {7.3};    // 编译错误：窄转换
    // double d = 7;
    // int x2{d};    // 编译错误：窄转换（double类型转化为int类型）
    // char x3{7};  // OK：虽然7是一个int类型，但这不是窄转换
    // std::vector<int> vi = {1, 2.3, 4, 5.6};  //错误：double至int到窄转换

//  32. POD
    // struct S { int a; };    // S属于POD
    // struct SS { int a; SS(int aa) : a(aa) { } }; // SS不属于POD
    // struct SSS { virtual void f(); /* ... */ };
    // POD的(递归)定义如下：
    // 所有的成员类型和基类都是POD类型
    // 不含虚函数
    // 不含虚基类
    // 不含引用
    // 不含多种访问权限(译注：对所有non-static成员有相同的public/private/protected访问控制权限)
    // C++11中关于POD方面最重要的部分就是POD中允许存在不影响内存布局和性能的构造函数（译注：参见C++11中新引入的default构造函数语法）。

//  33. union
    // C++11中的对union的限制条件重新定义如下：
    // 不含虚函数（与C++98相同）
    // 不含引用成员（与C++98相同）
    // 没有基类（与C++98相同）
    // 若union的某个成员的类型含有自定义构造/拷贝/析构函数，那么该union的相应构造/拷贝/析构函数将会被自动“禁用”（译注：在C++11中我们可以使用delete关键字来“禁用”构造/析构函数），随之而来的后果是：该union不能被实例化成对象。
    
    struct Acomplex
    {
        int x;
        int y;
    };
    
    struct Bcomplex
    {
        Bcomplex() = delete;
        int x;
        int y;
    };

    union U1 {
        int m1;
        Acomplex m2;    // ok
    };

    union U2 {
        int m1;
        Bcomplex m3;    // ok , 构造、赋值、析构
    };
    // U1 u;            // ok
    // u.m2 = {1,2};    // ok：给complex成员赋值
    // U2 u2;           // 编译错误: string类含有析构函数，因而U2的析构函数已被自动禁用
    //                  //（译注：析构函数被禁用意味着不允许在栈上实例化U2对象，否则无法析构）
    // U2 u3 = u2;      // 编译错误：string类含有拷贝构造函数，
    //                  // 因而U2类型同样也不能被拷贝构造

// Library features
//  1. std::move 
    // template <typename T>
    // typename remove_reference<T>::type&& move(T&& arg) {
    //  return static_cast<typename remove_reference<T>::type&&>(arg);
    // }

//  2. std::forward
    // template <typename T>
    // T&& forward(typename remove_reference<T>::type& arg) {
    //  return static_cast<T&&>(arg);
    // }

//  3. std::thread

//  4. std::to_string
    auto xx = std::to_string(1.2); // == "1.2"
    auto yx = std::to_string(123); // == "123"

//  5. Type traits
    static_assert(std::is_integral<int>::value, "");
    static_assert(std::is_same<int, int>::value, "");
    static_assert(std::is_same<std::conditional<true, int, double>::type, int>::value, "");

//  6. smart pointer 
    // std::unique_ptr
    // std::shared_ptr
    // std::weak_ptr

//  7. std::chrono 时间相关
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();
    // Some computations...
    end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    double t = elapsed_seconds.count(); // t number of seconds, represented as a `double`

//  8. std::tuple 不同类型的固定数量的集合
    // `playerProfile` has type `std::tuple<int, const char*, const char*>`.
    auto playerProfile = std::make_tuple(51, "Frans Nielsen", "NYI");
    std::get<0>(playerProfile); // 51
    std::get<1>(playerProfile); // "Frans Nielsen"
    std::get<2>(playerProfile); // "NYI"

//  9. std::tie
    // Creates a tuple of lvalue references. Useful for unpacking std::pair and std::tuple objects. Use std::ignore as a placeholder for ignored values. In C++17, structured bindings should be used instead.
    // With tuples...
    std::string playerName;
    std::tie(std::ignore, playerName, std::ignore) = std::make_tuple(91, "John Tavares", "NYI");

    // With pairs...
    std::string yes, no;
    std::tie(yes, no) = std::make_pair("yes", "no");


//  10. std::array、std::unordered_map、std::unordered_multimap、std::unordered_set、std::unordered_multiset

//  11. std::make_shared<>

//  12. std::ref
    // create a container to store reference of objects.
    auto val = 99;
    auto _ref = std::ref(val);
    _ref++;
    auto _cref = std::cref(val);
    //_cref++; does not compile
    std::vector<std::reference_wrapper<int>>vec; // vector<int&>vec does not compile
    vec.push_back(_ref); // vec.push_back(&i) does not compile
    std::cout << val << std::endl; // prints 100
    std::cout << vec[0] << std::endl; // prints 100
    std::cout << _cref; // prints 100

//  13. memory mode

//  14. std::async
    // a. std::launch::async | std::launch::deferred It is up to the implementation whether to perform asynchronous execution or lazy evaluation.
    // b. std::launch::async Run the callable object on a new thread.
    // c. std::launch::deferred Perform lazy evaluation on the current thread.
    auto foo = [](){
        /* Do something here, then return the result. */
        return 1000;
    };

    auto handle = std::async(std::launch::async, foo);  // create an async task
    auto result = handle.get();  // wait for the result

//  15. std::begin、std::end

    return 0;
}