#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue{
public:
    ThreadSafeQueue() {
    }
    ~ThreadSafeQueue() {
    }
    void Push(const T& value);
    void Pop(T& value);
    bool Empty();

private:
    std::mutex m_;
    std::queue<T> q_;
    std::condition_variable cond_;
};

template <typename T>
void ThreadSafeQueue<T>::Push(const T& value) {
    std::lock_guard<std::mutex> lock(m_);
    q_.push_back(value);
    cond_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::Pop(T& value) {
    std::unique_lock<std::mutex> lock(m_);
    cond_.wait(lock, [this]{return !q_.empty();});
    value = q_.front();
    q_.pop();
    // unique_lock具备上锁和解锁的过程
    // 当为empty时，mutex为解锁，处于阻塞和等待过程
    // 不为空位上锁过程
}

template <typename T>
bool ThreadSafeQueue<T>::Empty() {
    std::lock_guard<std::mutex> lock(m_);
    return q_.empty();
}

int main() {
    return 0;
}
