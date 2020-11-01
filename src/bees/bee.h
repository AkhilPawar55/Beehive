#ifndef Bee_h
#define Bee_h

#include <string>
#include <iostream>
#include "../util/my_thread.h"
#include "../world/beehive.h"

using std::cout;
using std::endl;
using std::ostream;

using std::string;
using util::my_thread;

namespace bees {
    class Bee : public my_thread {
    public:
        Bee();

        Bee(int id, string role, int nectar_units, int pollen_units);

        static Bee *create_a_bee(int id, string role, int nectar_units, int pollen_units);

        virtual void run()= 0;

        int get_id() const;

        string get_role() const;

    public:
        ~Bee();

    private:
        int id_;
        string role_;
        int nectar_units_;
    public:
        int getNectar_units_() const;

    private:
        int pollen_units_;
    public:
        int getPollen_units_() const;
    };

    ostream& operator<<(ostream& os, const Bee& b);
}

#endif