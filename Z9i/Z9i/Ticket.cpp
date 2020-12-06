#include "Ticket.h"
#include <iostream>

Ticket::Ticket()
{
    length = 30;
    string = new char[30];
    string[length] = '\0';
}

USInt Ticket::size()
{
    USInt i;
    for (i = 0; string[i] != '\0'; i++)
    {
        length = i;
    }
    return i;
}

void Ticket::setSize(int i)
{
    length = i;
    string[i] = '\0';
    Ticket* maxDestination = new Ticket[length];

}

Ticket::Ticket(const Ticket& newString)
{
    this->length = newString.length;
    this->string = new char[30];
    USInt i;
    for (i = 0; i < newString.length; i++)
    {
        this->string[i] = newString.string[i];
    }
    string[i] = '\0';
    /*length = newString.length;
    string = new char[newString.length + 1];
    USInt i;
    for (i = 0; newString.string[i] != '\0'; ++i)
    {
        string[i] = newString.string[i];
    }
    string[i] = '\0';*/
}

//String& Ticket::T2S(Ticket& news)
//{
//    return news;
//}

Ticket& Ticket::operator=(Ticket& newString)
{
    for (USInt i = 0; newString[i] != '\0'; i++)
    {
        string[i] = newString[i];
    }
    return *this;
}

char* Ticket::c_str()
{
    return destination;
}

bool operator!=(Ticket& string1, Ticket& string2)
{
    return !(string1 == string2);
}

bool operator==(Ticket& string1, Ticket& string2)
{
    if (string1.length != string2.length)
    {
        return false;
    }
    for (int i = 0; i < string1.length; ++i)
        if (string1.destination[i] != string2.destination[i])
        {
            return false;
        }
    return true;
}

void Ticket::set(char* newString)
{
    if (string == newString)
        return;
    if (string != nullptr)
    {
        delete[] string;
    }
    string = new char[30];
    USInt i;
    for (i = 0; newString[i] != '\0'; i++)
    {
        string[i] = newString[i];
    }
    length = i;
    string[i] = '\0';
    /*string = new char[length + 1];
    int i;
    for (i = 0; newstr[i] != '\0'; ++i)
    {
        string[i] = newstr[i];
    }
    string[i] = '\0';
    length = i;*/
}

void Ticket::setDestinations(std::istream& in)
{
    in.getline(string, 25, '\n');
    for  (USInt i = 0; i < 4; i++)
    {
        in.ignore(30, '\n');
    }
}

char* Ticket::getDestinations()
{
    return string;
}

int Ticket::getFlightNo()
{
    return flightNo;
}

char* Ticket::getPassengerName()
{
    return passengerName;
}

char& Ticket::operator[](USInt pos)
{
    if (pos < 0 || pos > 30)
    {
        throw("Позиция элемента за пределами массива...");
    }
    return string[pos];
}

char* Ticket::getFlightDate()
{
    return flightDate;
}

std::ostream& operator<<(std::ostream& output, Ticket& text)
{
    output << text.string;
    return output;
}
