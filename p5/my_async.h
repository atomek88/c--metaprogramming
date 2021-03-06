#ifndef MY_ASYNC_H
#define MY_ASYNC_H
#include<future>
#include<type_traits>
#include<thread>
#include<utility>
#include<cmath>
using std::forward;
using std::result_of_t;
using std::decay_t;
using std::move;
using std::packaged_task;
using std::thread;
template<typename T> int f(T) { return 2; }

namespace mpcs {
  template<typename Func, typename ...Args>
  auto my_async(Func f, Args&&... args)
//  std::future<result_of_t<decay_t<Func>(decay_t<Args>()...)>> my_async(Func f, Args&&... args)
//  auto my_async(Func f, Args&&... args) -> std::future<decltype(f(forward<Args>(args)...)>
  {
    using RetType = decltype(f(args...));
    packaged_task<RetType(Args...)> pt(f);
    auto result = pt.get_future();
    thread(std::move(pt), args...).detach();
    return result;
  }
}
#endif