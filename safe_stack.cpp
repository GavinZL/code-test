#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception
{
  const char* what() const throw() {
    return "empty stack!";
  };
};
template<typename T>
class threadsafe_stack{
private:
  std::stack<T> data;
  mutable std::mutex m;
public:
  threadsafe_stack()
    : data(std::stack<T>()){}
  threadsafe_stack(const threadsafe_stack& other){
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data; // 1 在构造函数体中的执行拷贝
  }
  threadsafe_stack& operator=(const threadsafe_stack&) = delete;
  void push(T new_value){
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }
  std::shared_ptr<T> pop(){
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack(); // 在调用pop前，检查栈是否为空
    std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改堆栈前，分配出返回值
    data.pop();
    return res;
  }
  void pop(T& value){
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    value=data.top();
    data.pop();
  }
  bool empty() const{
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};



//层级锁
class hierarchical_mutex{
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_value;
  static thread_local unsigned long this_thread_hierarchy_value;  // 1
  void check_for_hierarchy_violation(){
    if(this_thread_hierarchy_value <= hierarchy_value)  // 2{
      throw std::logic_error(“mutex hierarchy violated”);
    }
  }
  void update_hierarchy_value(){
    previous_hierarchy_value=this_thread_hierarchy_value;  // 3
    this_thread_hierarchy_value=hierarchy_value;
  }
public:
  explicit hierarchical_mutex(unsigned long value):
      hierarchy_value(value),
      previous_hierarchy_value(0){}
  void lock(){
    check_for_hierarchy_violation();
    internal_mutex.lock();  // 4
    update_hierarchy_value();  // 5
  }
  void unlock(){
    this_thread_hierarchy_value=previous_hierarchy_value;  // 6
    internal_mutex.unlock();
  }
  bool try_lock(){
    check_for_hierarchy_violation();
    if(!internal_mutex.try_lock())  // 7
      return false;
    update_hierarchy_value();
    return true;
  }
};
thread_local unsigned long
     hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);  // 8