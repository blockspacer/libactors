#pragma once

#include <queue>
#include <atomic>
#include <threadpool/pool.h>
#include <libactors/actor.h>
#include <libactors/locked_queue.h>

namespace libactors {

typedef LockedQueue<ActorPtr> ActorsQueue;

class DispatcherThread {
public:
    DispatcherThread(std::atomic_bool* const isStopped, ActorsQueue* const actors,
                     threadpool::ThreadPool* const threadPool)
        : isStopped_(isStopped)
        , actors_(actors)
        , threadPool_(threadPool)
    {}

    void operator()() {
        while (!*isStopped_) {
            if (actors_->empty()) {
                continue;
            }
            ActorPtr actor = actors_->front();
            actors_->pop();
            if (actor->hasJobs()) {
                actor->work(threadPool_);
            }
            actors_->push(actor);
        }
    }

private:
    std::atomic_bool* const isStopped_;
    ActorsQueue* const actors_;
    threadpool::ThreadPool* const threadPool_;
};

class Dispatcher {
public:
    Dispatcher(size_t threadsCount)
        : threadsCount_(threadsCount)
    {}

    void addActor(ActorPtr actor) {
        actors_.push(actor);
    }

    void start() {
        isStopped_ = false;
        threadPool_.start(threadsCount_);
        DispatcherThread dispThread(&isStopped_, &actors_, &threadPool_);
        dispatcherThread_.reset(new std::thread(dispThread));
    }

    void stop() {
        isStopped_ = true;
        threadPool_.stop();
        dispatcherThread_->join();
    }

private:
    ActorsQueue actors_;
    std::unique_ptr<std::thread> dispatcherThread_;
    threadpool::ThreadPool threadPool_;
    size_t threadsCount_;
    std::atomic_bool isStopped_;
};


} // namespace libactors
