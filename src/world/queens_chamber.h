#ifndef Queen_Chamber_h
#define Queen_Chamber_h

#include <mutex>
#include <condition_variable>
#include <queue>

using std::mutex;
using std::deque;
using std::condition_variable;
using std::unique_ptr;

namespace world{

    class QueensChamber{
    public:
        QueensChamber();
        bool checkIfBusy();
        void showAvailable();
        void showBusy();
        deque<int> chamber;
        mutex queue_accessor_;
        mutex resource_mutex;
        mutex queen_accesor_;
        condition_variable qcond_;
        condition_variable rcond_;
    private:
        bool isBusy_;
    };
}
#endif