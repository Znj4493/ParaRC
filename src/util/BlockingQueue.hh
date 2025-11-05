#ifndef _BLOCKINGQUEUE_HH_
#define _BLOCKINGQUEUE_HH_

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>

using namespace std;

template <class T>
class BlockingQueue {
  private:
    mutex _mutex;
    condition_variable _cv;
    deque<T> _queue;
  public:
    void push(T value) {
      {
        unique_lock<mutex> lock(_mutex); //* 线程进入该代码块后，尝试获得mutex，若成功获得，就继续执行
                                         //* 若失败，则阻塞等待，直到获得mutex
                                         //* 获得锁后，其他线程无法进入该代码块
	      _queue.push_back(value);
      } //* unique_lock对象再离开其作用域时，会自动调用析构函数，自动释放锁（RAII）
      _cv.notify_one();
    };

    T pop(){
      unique_lock<mutex> lock(_mutex); //* 线程进入该代码块后，尝试获得mutex，若成功获得，就继续执行
      _cv.wait(lock, [=]{ return !_queue.empty(); }); //* 如果队列为空，则释放mutex并阻塞等待，直到队列中有元素
                                                      //* 如果队列不为空，则继续执行
      T toret(_queue.front());
      _queue.pop_front();

      return toret;
    };

    int getSize() {
      return _queue.size();
    }
};

#endif
