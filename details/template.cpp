// 
// 1. 函数模板
// 1.1 定义模板
// 在编译阶段，模板并不是被编译成一个可以支持多种类型的实体。而是对每一个用于该模板 的类型都会产生一个独立的实体。
template<typename T>
T max(T a, T b)
{
    return b < a ? a : b; //此处T类型 必须能支持 operator <运算符， 还应该支持copy&move支持返回类型
}
// 1.2 模板参数推断
// 1.3 多个模板参数
//  。作为返回类型的模板参数
template<typename T1, typename T2, typename RT> //显示调用::max<int, float ,double>(4, 2.1);
RT max(T1 a, T2 b)
{
    return a < b ? a : b;
}
//  。返回类型推断 
//  c++14 （auto返回）
template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return a<b ? a : b;
}
//  c++11 (尾返回，std::decay去掉引用)
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> typename std::decay<decltype(true?a:b)>::type
{
    return a < b ? a : b;
}
//  。将返回类型声明为公共类型(common type),也是进行萃取操作
//  c++14 std::common_type_t<T1, T2>
//  c++11 typename std::common_type<T1,T2>::type
template<typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b)
{
    return b < a ? a : b;
}


//  1.4 默认模板参数

//  1.5 函数模板的重载
// .一个非模板函数可以和一个与其同名的函数模板共存，并且这个同名的函数模 板可以被实例化为与非模板函数具有相同类型的调用参数。
// 在所有其它因素都相同的情况 下，模板解析过程将优先选择非模板函数，而不是从模板实例化出来的函数
// .由于在模板参数推断时不允许自动类型转换，而常规函数是允许的

// 1.6 按值传递还是按引用传递？
// 建议将按引用传递用于除简单类型(比如基础类型和 std::string_view)以外的类型
// 不过出于以下原因，按值传递通常更好一些: 
//  语法简单。
//  编译器能够更好地进行优化。
//  移动语义通常使拷贝成本比较低。
//  某些情况下可能没有拷贝或者移动。
// 再有就是，对于模板，还有一些特有情况:
//  模板既可以用于简单类型，也可以用于复杂类型，因此如果默认选择适合于复杂类型可能方式，可能会对简单类型产生不利影响。
//  作为调用者，你通常可以使用std::ref()和std::cref()(参见7.3节)来按引用传递参数。
//  虽然按值传递 string literal 和 raw array 经常会遇到问题，但是按照引用传递它们通常只会遇到更大的问题

// 2. 类模板
// .不同于非模板类，不可以在函数内部或者块作用域内({...})声明和定义模板。
// 通常 模板只能定义在 global/namespace 作用域，或者是其它类的声明里面
// .模板函数和模板成员函数只有在被调用的时候才会实例化
// .如果一个类模板有 static 成员，对每一个用到这个类模板 的类型，相应的静态成员也只会被实例化一次

// .类型别名
//  typedef 
//  using
//  alias templates 给一组类型取别名
template<typename T>
using DequeStack = Stack<T, std::deque<T>>;

template<typename T>
using MyTypeIterator = typename MyType<T>::iterator;

// std::add_const_t<T>              // since C++14
// typename std::add_const<T>::type // since C++11
// namespace std { 
//     template<typename T>
//     using add_const_t = typename add_const<T>::type; 
// }

// 3. 非类型模板参数
template<typename T, std::size_t Maxsize> 
class Stack {
private:
    std::array<T, Maxsize> elems; // elements 
    std::size_t numElems; // current number of elements
};
// .使用非类型模板参数是有限制的。通常它们只能是整形常量(包含枚举)，指向 objects/functions/members 的指针，
//  objects 或者 functions 的左值引用，或者是 std::nullptr_t (类型是 nullptr)。
// .浮点型数值或者 class 类型的对象都不能作为非类型模板参数使用
// .当传递对象的指针或者引用作为模板参数时，对象不能是字符串常量，临时变量或者数据成 员以及其它子对象
// template<char const* name> 
// class MyClass {};
// // MyClass<"hello"> x; //ERROR: string literal "hello" not allowed
// extern char const s03[] = "hi"; // external linkage 
// char const s11[] = "hi"; // internal linkage
// int main()
// {
//     MyClass<s03> m03; // OK (all versions) 
//     MyClass<s11> m11; // OK since C++11
//     static char const s17[] = "hi"; // no linkage 
//     MyClass<s17> m17; // OK since C++17
// }
// .用auto作为非类型模板参数的类型 （c++17）

// 4. 变参模板
// .c++11
    // #include <iostream>
    // void print ()
    // {}
    // template<typename T, typename... Types> 
    // void print (T firstArg, Types... args)
    // {
    // std::cout << firstArg << std::endl; //print first argument
    // print(args...); // call print() for remaining arguments }
// .sizeof... 运算符 [被扩展成参数包中所包含的 参数数目]
    // template<typename T, typename... Types> void print (T firstArg, Types... args)
    // {
    //     std::cout << firstArg << std::endl;
    //     if (sizeof...(args) > 0) {  //error if sizeof...(args)==0 ,通常函数模板中 if 语句的两个分支都会被实例化
    //         print(args...);         // and no print() for no arguments declared 
    //     }
    // }
// .折叠表达式  （c++17）


#include <iostream>
int main(int argc, char* argv[])
{

// 1. 函数模板

    return 0;
}


template <typename X>
struct Trans_ {
  using type = int64_t;
};
template <typename T>
using Trans = typename Trans_<T>::type;


template <typename Output, typename...Dummy>
struct BatchTrans_ {
  using type = Output;
};

template <typename...Processed, typename CurInput, typename...Remain>
struct BatchTrans_<std::tuple<Processed...>, CurInput, Remain...>{
  using CurOutput = Trans<CurInput>;
  using NewProcessed = std::tuple<Processed..., CurOutput>;
  using type = typename BatchTrans_<NewProcessed, Remain...>::type;
};

template <typename InputHead, typename...InputRemain>
using BatchTrans = typename BatchTrans_<std::tuple<>,
                                        InputHead, InputRemain...>::type;