#include "bee.h"
#include "worker.h"
#include "drone.h"
#include "queen.h"

using bees::Bee;
using bees::Worker;
using bees::Drone;
using bees::Queen;

std::ostream& operator <<(const std::ostream& os, const bees::Bee& b);

Bee::Bee(){}

Bee::Bee(int id, string role, int nectar_units, int pollen_units) :
        id_(id), role_(role), nectar_units_(nectar_units), pollen_units_(pollen_units) {}

Bee::~Bee() {}

Bee *Bee::create_a_bee(int id, string role, int nectar_units, int pollen_units) {
    if (role == "Nectar Worker" || role == "Pollen Worker") {
        return new Worker(id, role, nectar_units, pollen_units);
    }else if(role == "Drone"){
        return new Drone(id, role);
    }else if(role == "Queen"){
        return new Queen(id, role);
    }
    else {
        cout << "Invalid role." << endl;
        return nullptr;
    }
}

int Bee::get_id() const{
    return id_;
}

string Bee::get_role() const {
    return role_;
}

int bees::Bee::getNectar_units_() const {
    return nectar_units_;
}

int bees::Bee::getPollen_units_() const {
    return pollen_units_;
}

std::ostream& bees::operator<<(std::ostream& os, const Bee& b){
    if(b.get_role() == "Drone")
        os<<"DRONE #"<<b.get_id()<<std::endl;
    else if(b.get_role() == "Nectar Worker")
        os<<"NECTAR("<<b.getNectar_units_()<<") WORKER #"<<b.get_id()<<std::endl;
    else if(b.get_role() == "Pollen Worker")
        os<<"POLLEN("<<b.getPollen_units_()<<") WORKER #"<<b.get_id()<<std::endl;
    return os;
}