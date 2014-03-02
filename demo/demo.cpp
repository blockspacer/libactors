
#include <libactors/actor.h>
#include <libactors/dispatcher.h>

using namespace libactors;

int main() {
    const size_t threadsCount = 4;
    Dispatcher dispatcher(threadsCount);
    dispatcher.addActor(std::make_shared<Actor>());

    std::cerr << "dispatcher start" << std::endl;
    dispatcher.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    dispatcher.stop();
    std::cerr << "dispatcher stopped" << std::endl;

    return 0;
}
