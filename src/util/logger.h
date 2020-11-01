#ifndef BEEHIVE_LOGGER_H
#define BEEHIVE_LOGGER_H

#include <iostream>
#include <mutex>

namespace util {

    /**
     * A thread safe logging utility used to print out messages in the
     * simulation.
     *
     * @author Sean Strout @ RIT CS
     */
    class logger {
    public:
        /**
         * Create the logger.
         *
         * @param os the output stream, e.g. cout
         */
        logger(std::ostream &os);

        /**
         * Log a message to the output stream.
         *
         * @param message the message
         */
        void log(const std::string &message);

    private:
        /** the output stream to log to */
        std::ostream &os_;
        /** a mutex to prevent threaded message from stomping on each other */
        std::mutex print_mutex_;
    }; // logger

} // util

#endif // BEEHIVE_LOGGER_H
