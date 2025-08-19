#pragma once


class ContainersInterface
{
private:
    // Private constructor to prevent direct instantiation
    ContainersInterface() {}

    // Deleted copy constructor and assignment operator
    ContainersInterface(const ContainersInterface&) = delete;
    ContainersInterface& operator=(const ContainersInterface&) = delete;

public:
    virtual ~ContainersInterface() = default;

    static ContainersInterface& getInstance()
    {
        // Creates a static local variable inside the getInstance() method.
        // This ensures that the instance is created only once and persists for the lifetime of the program.
        // The first time getInstance() is called, instance is constructed.
        // On every subsequent call, the same instance object is returned.
        // This is a thread-safe way to implement a singleton in C++11 and later.
        // Note: The static variable is initialized the first time this function is called.
        // It is destroyed when the program exits.

        static ContainersInterface instance;
        return instance;
    }

    private:
    

    
};