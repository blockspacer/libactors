#pragma once

#include <queue>
#include <threadpool/pool.h>
#include <libactors/actor.h>

namespace libactors {

class Dispatcher {
public:
    Dispatcher(size_t threadsCount)
        : threadPool_(new threadpool::ThreadPool)
        , threadsCount_(threadsCount)
    {}

    void addActor(ActorPtr actor) {
        actors_.push(actor);
    }

    void operator()() {
        threadPool_->start(threadsCount_);
        for (size_t i = 0; i < 1000; ++i) {
            ActorPtr actor = actors_.front();
            actors_.pop();
            if (actor->hasJobs()) {
                actor->work(threadPool_.get());
            }
            actors_.push(actor);
        }
        threadPool_->stop();
    }
private:
    std::queue<ActorPtr> actors_;
    std::shared_ptr<threadpool::ThreadPool> threadPool_;
    size_t threadsCount_;
};


} // namespace libactors
