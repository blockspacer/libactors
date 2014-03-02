#pragma once

#include <queue>
#include <mutex>
#include <atomic>

namespace libactors {

class SpinLock {
public:
    SpinLock()
        : flag_(ATOMIC_FLAG_INIT)
    {}

    void lock() {
        while (!try_lock()) {
        }
    }

    bool try_lock() {
        return !flag_.test_and_set();
    }

    void unlock() {
        flag_.clear();
    }

private:
    std::atomic_flag flag_;
};

template <typename T>
class LockedQueue {
public:
    void push(const T& t) {
        std::lock_guard<SpinLock> guard(lock_);
        queue_.push(t);
    }

    void pop() {
        std::lock_guard<SpinLock> guard(lock_);
        queue_.pop();
    }

    const T& front() const {
        std::lock_guard<SpinLock> guard(lock_);
        return queue_.front();
    }

    bool empty() const {
        std::lock_guard<SpinLock> guard(lock_);
        return queue_.empty();
    }

private:
    mutable SpinLock lock_;
    std::queue<T> queue_;
};

} // namespace libactors
