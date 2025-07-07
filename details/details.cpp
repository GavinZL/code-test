
#include <iostream>

// 隐式类型转换
struct S1 {
  short a, b;
};
// 小端模式
//00000000 00000001 00000000 00000010
struct S2 {
  int a;
};

void demo() {
  S2 s2;
  S1 *p = reinterpret_cast<S1 *>(&s2);
  p->a = 2;
  p->b = 1;

  std::cout << s2.a << std::endl; // 猜猜这里会输出多少？
}

// 私有继承 （EBO，压缩存储空间）
class Empty{};

class ETest
{
private:
    Empty e;
    int  a;
};
class ATest : private Empty
{
private:
  int a;
};
class BTest : public Empty
{
private:
  int a;
};

// 虚表指针位置
class AVurtal
{
public:
  AVurtal(int i):a(i)
  {
    std::cout << "AVurtal" << std::endl;
  }

  ~AVurtal()
  {
    std::cout << "~AVurtal" << std::endl;
  }

  AVurtal(const AVurtal& )
  {
    std::cout << "const AVurtal&" << std::endl;
  }

  AVurtal(AVurtal&& )
  {
    std::cout << "AVurtal&&" << std::endl;
  }

  AVurtal* operator = (const AVurtal&)
  {
    std::cout << "operator = const AVurtal&" << std::endl;
    return this;
  }

  AVurtal* operator = (AVurtal&&)
  {
    std::cout << "operator =  AVurtal&&" << std::endl;
    return this;
  }

  void funA()
  {
    std::cout << "funA: " << a << std::endl;
  }

private:
  int a = 10;
};


class AccessC
{
public:
  int a;
  char b;
  float c;
};

class AccessD
{
public:
  int a;
protected:
  char b;
private:
  float c;
};


#include <vector>
void funV()
{


  AccessC *c = new AccessC;
  int bb = 0;
  int a[10] = {0};
  std::vector<int> v = {1, 1, 1, 1, 1, 1, 1};

  printf("cc: %p\n", c);
  printf("bb: %p\n", &bb);
  printf("a: %p, v: %p \n", &a, &a[1]);
  printf("v: %p, vv: %p\n", &v, &v[1]);
}

#include <forward_list> 
#include <memory>


std::shared_ptr<AVurtal> getA()
{
   std::shared_ptr<AVurtal> a = std::make_shared<AVurtal>(100);
   return std::move(a);
}


std::shared_ptr<AVurtal> getB()
{
   return std::move(getA());
}

std::shared_ptr<AVurtal> getC()
{
   return std::move(getB());
}


#include <type_traits>
template<typename T, typename = typename std::enable_if<std::is_class<T>::value>::type>
struct UserData
{
    int                           _type;
    std::shared_ptr<T>            _data;

    UserData(int type, std::shared_ptr<T> data)
        : _type(type)
        , _data(data) {}

    ~UserData()
    {
        printf("~UserData : %d\n", _type);
        // if (_data)
        // {
        //     delete _data;
        // }
    }
};



template <typename F, typename... Args>
struct is_invocable : std::is_constructible<std::function<void(Args ...)>,
                      std::reference_wrapper<typename std::remove_reference<F>::type>>
{
};

//typename = typename std::enable_if<std::is_invocable<F>::value>::type>    //c++17
template <typename F, 
typename = typename std::enable_if<std::is_constructible<std::function<void()>, F>::value>::type>
void funT(F f)
{
   f();
}           

int main(int argc, char* argv[])
{

  auto fun = []() -> bool{
    std::cout << ",,,";
    return true;
  };

  funT(fun);

  std::cout << " --- " << std::is_invocable<decltype(fun)>::value << std::endl;

  // AVurtal a(0);   //&a
  // AVurtal *b = new AVurtal(10); //b
  //   //std::shared_ptr<UserData<AVurtal>> ud = std::make_shared<UserData<AVurtal>>()

  // auto uus = std::make_shared<UserData<AVurtal>>(0, std::shared_ptr<AVurtal>(b));

    // auto aa = std::move(getC());
    // aa->funA();
    // std::cout << "use_count: " << aa.use_count() << std::endl;

    // demo();
    // std::cout << "s1: " << sizeof(S1) << ", s2: " << sizeof(S2) << std::endl;

    // std::cout << "et: " << sizeof(ETest) << std::endl;
    // std::cout << "at: " << sizeof(ATest) << std::endl;
    // std::cout << "bt: " << sizeof(BTest) << std::endl;

    //AVurtal *av = new AVurtal;
    // std::cout << "addr: " << *(av + 4) << std::endl;


    // std::forward_list<std::unique_ptr<AVurtal>> list;
    // for(int i=0; i<5; ++i)
    // {
    //   // list.emplace_front(std::make_unique<AVurtal>());
    //   // list.emplace_front(std::unique_ptr<AVurtal>(new AVurtal));
    //   // list.push_front(std::make_unique<AVurtal>());
    //   list.push_front(std::unique_ptr<AVurtal>(new AVurtal(i)));
    // }

    // std::for_each(list.cbegin(), list.cend(), [](auto& item)
    // {
    //     item->funA();
    // });

    //vector 中的内容放在堆上
    // funV();

    return 0;
}