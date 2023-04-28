#include <iostream>
#include <cstring>
using namespace std;

class Animal {
	public:
		Animal();
		Animal(string n, string s);
        Animal(string n, string s, int hp);
		virtual ~Animal();
		
		virtual string get_name();
		virtual string get_species();
		virtual int get_HP();
		virtual void update_HP(int x);
		virtual void turn_HP_into_zero();
		
		virtual void Talk();
		virtual void Sleep(int x);
		virtual void Work(int x);
		virtual void Eat(Animal *animal);
		virtual void Eaten(Animal *animal);
        virtual void Eat(int x);
        virtual void Killed(Animal *animal);
        virtual void Information();
		
	private:
		string name;
		string species;
		int HP;
};

class Cat : public virtual Animal {
	public:
		Cat(string n);
        Cat(string n, int hp);
		virtual ~Cat();
		void Talk();
		void Eat(Animal *animal);
		void Eaten(Animal *animal);
};

class Fish : public virtual Animal {
	public:
		Fish(string n);
        Fish(string n, int hp);
		virtual ~Fish();
		void Talk();
		void Eat(Animal *animal);
		void Eaten(Animal *animal);
};

class Bird : public virtual Animal {
	public:
		Bird(string n);
        Bird(string n, int hp);
		virtual ~Bird();
		void Talk();
		void Eat(Animal *animal);
		void Eaten(Animal *animal);
};

class Human : public virtual Animal {
	public:
		Human(string n);
        Human(string n, int hp);
		virtual ~Human();
		void Talk();
		void Eat(Animal *animal);
};
