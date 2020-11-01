#include "logger.h"

using std::endl;
using std::mutex;
using std::lock_guard;
using util::logger;

logger::logger(std::ostream &os) :
    os_{os},
    print_mutex_{} {
}

void logger::log(const std::string& message) {
    lock_guard<mutex> print_lock{print_mutex_};
    os_ << message << endl;
}
