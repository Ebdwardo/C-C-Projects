//
// Created by Eduardo Teodosio on 7/5/2020.
//

#include "Zombie.h"

Zombie::Zombie(){
    type;
}
Zombie::Zombie(char letter) {
    type = letter;
}

char Zombie::getType() {
    return this->type;
}
void Zombie::setType(char letter) {
    type = letter;
}

bool Zombie::operator==(const Zombie& other) {
    if (this->type == other.type){
        return true;
    } else{
        return false;
    }
}