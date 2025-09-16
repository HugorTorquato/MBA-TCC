// Example.cpp
class Animal {
public:
    void speak();
};

class Cachorro : private Animal {
public:
    void wagTail();
};

class Gato : public Animal {
public:
    void purr();
};

class Rato : protected Animal {
public:
    void squeak();
};