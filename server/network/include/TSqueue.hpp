#ifndef TSQUEUE_HPP
#define TSQUEUE_HPP

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

template <typename T>
class TSQueue {
    std::queue<T> queue_;
    mutable std::mutex
        mutex_;  // Moved out of public interface to prevent races between this

    // and pop().
    bool empty() const {
        return queue_.empty();
    }

public:
    TSQueue() = default;
    TSQueue(const TSQueue<T> &) = delete;
    TSQueue &operator=(const TSQueue<T> &) = delete;

    TSQueue(TSQueue<T> &&other) noexcept {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_ = std::move(other.queue_);
    }

    virtual ~TSQueue() {
    }

    unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    T pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }

    void push(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }
};

#endif
