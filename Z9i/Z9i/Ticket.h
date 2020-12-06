#pragma once
#include <iostream>
#include "String.h"
class Ticket
{
private:
    char* destination;
    char* maxDestination;
    char* string;
    int flightNo;
    char* passengerName;
    char* flightDate;
    USInt length;
public:
    USInt size();
    void setSize(int);
    void set(char*);
    void setDestinations(std::istream&);

    char* getDestinations();
    char* getPassengerName();
    char* getFlightDate();
    int getFlightNo();

    char& operator[](USInt pos);
    Ticket& operator=(Ticket&);
    char* c_str();
    /*String& T2S(Ticket&);*/

    Ticket();
    Ticket(const Ticket&);

    friend std::ostream& operator<<(std::ostream&, Ticket&);
    friend bool operator!=(Ticket&, Ticket&);
    friend bool operator==(Ticket&, Ticket&);
};

