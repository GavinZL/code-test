
#include <cstdio>
#include <memory>
#include <utility>

int main(int argc, char *argv[])
{

    //0.shared_from_this()
    //为什么我们不能在构造函数调用 shared_from_this() 的原因，因为其内部的 weak_ptr 并没有初始化。所以会产生错误。

    //1. 二进制常量
    int x = 0b101'0000;
    printf("%d\n", 0b101);


    //2. auto应用到lambda， 使lambda有多态性
    auto fun1 = [](auto x) {
        return x;
    };
    printf("%d\n", fun1(10));
    printf("%s\n", fun1("hello"));

    //3. lambda捕获列表变量初始化
    //3.1 捕获列表初始化变量
    auto fun2 = [](auto x) {return x * 100;};
    auto fun3 = [a=fun2(10)](){return a;};
    printf("func3:%d\n", fun3());

    //3.2 std::move移动
    auto p = std::make_unique<int>(1);
    auto fun4 = [p = std::move(p)](){
        *p = 10;
    };

    //3.3 引用别名
    auto b = 1;
    auto fun5 = [&r = b, b = b * 10] {
        ++r;
        return r + b; //此处的b是lambda内部的变量，和外部的b进行区分
    };
    printf("fun5: %d\n", fun5());

    //4. 返回类型推断
    // auto func6(){return 2.0f;};
    // decltype(auto) 推断返回类型，包含引用和cv修饰符， 比起auto更精确(auto可能改变类型修饰符)
    auto func6 = [](const int& i) -> auto 
    {
        return i;   //return int type
    };

    auto func7 = [](const int& i) -> decltype(auto)
    {
        return i;   //return const int& type
    };

    printf("%d\n", std::is_same<const int&, decltype(func6(8))>::value);
    printf("%d\n",std::is_same<const int&, decltype(func7(8))>::value);

    //5. constexpr body内松散限制
    // c++11 严格限制：只包含typedef、using、return等
    // c++14 增加操作：if、loops、mult-return
    // constexpr int factorial(int n) {
    //     if (n <= 1) {
    //         return 1;
    //     } else {
    //         return n * factorial(n - 1);
    //     }
    // }

    //6. 模板变量
    // template<class T>
    // constexpr T pi = T(3.1415926535897932385);
    // template<class T>
    // constexpr T e  = T(2.7182818284590452353);

    //7. [[deprecated]] attribute 标记一个方法或类即将遗弃
    // [[deprecated]]
    // void old_method();
    // [[deprecated("Use new_method instead")]]
    // void legacy_method();

    //Library features
    //7. std::integer_sequence 序列生成
    //8. std::make_unique<T>()
}
