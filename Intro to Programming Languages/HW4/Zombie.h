//
// Created by Eduardo Teodosio on 7/5/2020.
//This is the Zombie class, each zombie contains a letter and thats about it

#ifndef ASSIGNMENT4_ZOMBIE_H
#define ASSIGNMENT4_ZOMBIE_H


class Zombie {
private:
    char type;
public:
    Zombie();
    Zombie(char);

    char getType();
    void setType(char type);
    bool operator==(const Zombie&);
};


#endif //ASSIGNMENT4_ZOMBIE_H
