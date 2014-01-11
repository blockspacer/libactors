#pragma once

#include <vector>
#include <memory>

#include <threadpool/pool.h>

namespace libactors {

class ActionTask: public threadpool::ITask {
public:
    virtual void run() {
        std::cout << "hello from action" << std::endl;
    }
};

class Actor {
public:
    virtual ~Actor() {}

    bool hasJobs() const {
        return true; // FIXME
    }

    void work(threadpool::ThreadPool* const threadPool) {
        threadpool::ITask* task = new ActionTask;
        threadPool->add(task);
    }
};

typedef std::shared_ptr<Actor> ActorPtr;

}
