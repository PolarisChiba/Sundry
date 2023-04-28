#include <iostream>
#include <cstring>
#include "function.h"
using namespace std;

Animal::Animal(string n, string s) {
	name = n;
	species = s;
	HP = 10;
	cout << name << " birth\n";
}
Animal::Animal(string n, string s, int hp) {
    name = n;
	species = s;
	HP = hp;
	cout << name << " birth\n";
}

void Animal::Information() {
    cout << this->name << " " << this->species << " " << this->HP << "\n";
}

string Animal::get_name() {
	return this->name;
}

string Animal::get_species() {
	return this->species;
}

int Animal::get_HP() {
	return this->HP;
}

void Animal::update_HP(int x) {
	this->HP += x;
}

void Animal::turn_HP_into_zero() {
	this->HP = 0;
}

void Animal::Eat(int x) {
	this->HP += x;
}

void Animal::Killed(Animal* animal) {
    if (this->species == animal->species) {
        this->turn_HP_into_zero();
    }
}

void Animal::Sleep(int x) {
	if (this->HP <= 100)
		this->HP *= x;
}

void Animal::Work(int x) {
	this->HP -= x;
}

Animal::~Animal() {
	cout << this->get_name() << " " << "dead\n";
}

Cat::Cat(string s) : Animal(s, "cat") {}
Cat::Cat(string s, int hp) : Animal(s, "cat", hp) {}

void Cat::Talk() {
	cout << "Meow\n";
}

void Cat::Eat(Animal *animal) {
	if (animal->get_species() == "fish")
		this->update_HP(animal->get_HP());
}

Fish::Fish(string s) : Animal(s, "fish") {}
Fish::Fish(string s, int hp) : Animal(s, "fish", hp) {}

void Fish::Talk() {
	cout << "?\n";
}

void Fish::Eaten(Animal *animal) {
	if (animal->get_species() != "fish") {
		this->turn_HP_into_zero();
	}
}

Bird::Bird(string s) : Animal(s, "bird") {}
Bird::Bird(string s, int hp) : Animal(s, "bird", hp) {}

void Bird::Talk() {
	cout << "Suba\n";
}

void Bird::Eat(Animal *animal) {
	if (animal->get_species() == "fish")
		this->update_HP(animal->get_HP());
}

void Bird::Eaten(Animal *animal) {
	if (animal->get_species() == "human") {
		this->turn_HP_into_zero();
	}
}

Human::Human(string s) : Animal(s, "human") {}
Human::Human(string s, int hp) : Animal(s, "human", hp) {}

void Human::Talk() {
	cout << "Hello, world\n";
}

void Human::Eat(Animal *animal) {
	if (animal->get_species() == "cat")
		this->turn_HP_into_zero();
	else if (animal->get_species() == "fish" || animal->get_species() == "bird") {
		this->update_HP(animal->get_HP());
	}
}

void Animal::Eaten(Animal* animal){}
void Fish::Eat(Animal* animal){}
void Cat::Eaten(Animal* animal){}
void Animal::Talk(){}
void Animal::Eat(Animal* animal){}

Cat::~Cat() {}
Fish::~Fish() {}
Bird::~Bird() {}
Human::~Human() {}