
#include <thread>
#include <libactors/actor.h>
#include <libactors/dispatcher.h>

using namespace libactors;

int main() {
    const size_t threadsCount = 4;
    Dispatcher dispatcher(threadsCount);
    dispatcher.addActor(std::make_shared<Actor>());

    std::thread dispatcherThread(dispatcher);
    std::cout << "dispatcher started" << std::endl;

    dispatcherThread.join();
    std::cout << "dispatcher stopped" << std::endl;
    return 0;
}
