#include "my_thread.h"

using util::my_thread;

using std::exception;
using std::thread;

my_thread::my_thread() :
    thread_{} {
}

my_thread::~my_thread() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

void my_thread::detach() {
    thread_.detach();
}

void my_thread::start() {
    thread_ = thread{&my_thread::run, this};
}

void my_thread::join() {
    thread_.join();
}