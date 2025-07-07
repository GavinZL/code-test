
#include <type_traits>
/*
///SFINAE 模板
// 1. Substitution Failure Is Not An Error, 编译器规则，在模板参数替换失败时，这些错误不会导致整个编译失败
// 2. 条件编译，通过控制模板参数替换的失败，实现编译期的选择逻辑，如使用std::enable_if和SFINA，根据类型特点选择不同的模板特化或函数重载
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    add(T a, T b) {
        return a + b;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    add(T a, T b) {
        return a + b + 0.1;
    }
// 2. 实现类型特征类：std::is_arithmetic、std::is_pointer等
    template <class _Tp>
    struct __libcpp_is_pointer : public false_type {};
    template <class _Tp>
    struct __libcpp_is_pointer<_Tp*> : public true_type {};

// 3. 模板特化和重载 (可以帮助选择最合适的模板特化或函数重载)
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    print(const T& x) {
        std::cout << "Arithmetic: " << x << std::endl;
    }

    template <typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value>::type
    print(const T& x) {
        std::cout << "Non-Arithmetic: " << x << std::endl;
    }

// 4. noexcept 和 SFINAE
    template <typename T, typename U>
    struct is_nothrow_addable {
        //如果 T 和 U的加法不抛出异常，is_nothrow_addable<T, U>::value的值为true
        static const bool value = noexcept(std::declval<T>() + std::declval<U>());
    };
*/

// 模板
// c++11
/*
 *1. 模板别名， using
    template <typename T>
    using Vector = std::vector<T, std::allocator<T>>;
 *2. 可变参数模板
    template <typename... Args>
    void print(Args... args) {
        //...
    }
 *3. std::enable_if条件编译
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    add(T a, T b) {
        return a + b;
    }
 *4. decltype和auto， 编译器推导表达式类型
    template <typename T>
    auto add(T a, T b) -> decltype(a + b) {
        return a + b;
    }
 *
*/

// c++14
/*
 *1. 可变参数模板扩展 (允许在模板参数列表中使用可变参数模板)

*/


enum class Color : uint32_t {
    Red = 601,
    Green = 709,
    Blue = 2020
};

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <optional>
#include <variant>

template <typename T>
std::string toStr(const T& value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

inline std::string toStr(unsigned char ch)
{
    return std::to_string(ch);
}


void test(int&& v)
{
    std::cout << "rvalue" << std::endl;
}
void test(int& v)
{
    std::cout << "lvalue" << std::endl;
}

struct Cmp
{
    bool operator()(const int& a, const int& b) const
    {
        return a >= b;
    }
};

template <typename T>
void forword(T&& v)
{
    test(std::forward<T>(v));
}

int main(int argc, char** argv)
{
    // int a = 90;

    // Color color = static_cast<Color>(a);

    // std::cout << "color: " << (uint32_t)color << std::endl;


    // uint8_t a = 10;
    // printf("%s\n", toStr(a).c_str());

    // int a = 10;
    // test(a);
    // test(std::move(a));

    std::map<int, int, Cmp> m;
    m[1] = 1;
    m[1] = 2;

    std::cout << m.size() << std::endl;

    // auto ptr = std::make_shared<Cmp>();

    // std::optional<int> opt;
    // std::variant<int, std::string> var;

    // std::forword<int>(a);
}