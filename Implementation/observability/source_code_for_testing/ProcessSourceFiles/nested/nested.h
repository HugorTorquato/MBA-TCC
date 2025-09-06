// nested.h
#pragma once
class Outer {
public:
    class Inner;
};
class DerivedNested : public Outer::Inner;
