#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <thread>

namespace util {
    /**
     * An abstract class that simulates a Java thread.
     *
     * @author Sean Strout @ RIT CS
     */
    class my_thread {
    public:
        /**
         * Create the thread.
         */
        my_thread();

        /**
         * Destruct the thread.  The behavior is if the thread has not been
         * joined on yet it will when this is run.
         */
        virtual ~my_thread();

        /**
         * Schedule the thread's run method to be run in a separate thread at
         * some point after this is called.  This is a non-blocking call.
         */
        void start();

        /**
         * Detach from the thread and make it a background thread that does not
         * need to be joined on and will be abruptly terminated when the main()
         * ends.
         */
        void detach();

        /**
         * The method the thread will execute when it is running.  Returning from
         * this method means the thread has terminated normally.
         */
        virtual void run() = 0;

        /**
         * Wait for this thread to terminate, normally or by exception.
         *
         * @throws exception if the thread terminated abnormally
         */
        void join();

    private:
        /** the thread */
        std::thread thread_;
    }; // my_thread

} // util

#endif // MY_THREAD_H
