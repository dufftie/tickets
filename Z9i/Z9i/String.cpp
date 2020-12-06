#include <iostream>
#include "String.h"

String::String() 
{
    length = 0;
	string = new char[1];
	string[length] = '\0';
}

String::String(const char* newString)
{
    string = new char[30];
    USInt i;
    for (i = 0; newString[i] != '\0'; ++i)
    {
        string[i] = newString[i];
    }
    string[i] = '\0';
    length = i;
}

String::String(const String &newString)
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

String::~String()
{
    if (length != 0)
    {
        delete[] string;
    }
}

USInt String::size()
{
	return length;
}

char& String::operator[](USInt pos)
{
    if (pos < 0 || pos > length)
    {
        throw("Позиция элемента за пределами массива...");
    }
    return string[pos];
}

void String::set(char* newString) 
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

String& String::operator=(String& text) 
{
    text.set(string);
    return *this;
}

bool operator<(String& string1, String& string2) 
{
    if (string1.length == 0)
    {
        return true;
    }
    int lim = string1.length < string2.length ? string1.length : string2.length;
    for (int i = 0; i < lim; ++i) 
    {
        if (tolower(string1.string[i]) < tolower(string2.string[i]))
        {
            return true;
        }
        else if (tolower(string1.string[i]) > tolower(string2.string[i]))
        {
            return false;
        }
    }
    return false;
}

bool operator>(String& string1, String& string2)
{
    if (string1.length == 0)
    {
        return true;
    }
    int lim = string1.length < string2.length ? string1.length : string2.length;
    for (int i = 0; i < lim; ++i)
    {
        if (tolower(string1.string[i]) > tolower(string2.string[i]))
            return true;
        else if (tolower(string1.string[i]) < tolower(string2.string[i]))
            return false;
    }
    return false;
}

bool operator==(String& string1, String& string2)
{
    if (string1.length != string2.length)
    {
        return false;
    }
    for (int i = 0; i < string1.length; ++i)
    {
        if (string1.string[i] != string2.string[i])
        {
            return false;
        }
    }
    return true;
}

bool operator==(String& string1, char char2)
{
    if (string1.length != 0)
    {
        return false;
    }
    if (string1[0] == char2)
    {
        return true;
    }
    else return false;
}

bool operator!=(String& string1, String& string2) 
{
    return !(string1 == string2);
}

bool operator!=(String& newString, char char2)
{
    return !(newString == char2);
}

String& String::operator++()
{
    int i;
    for (i = 0; string[i] != '\0'; i++)
        string[i] = string[i + 1];
    length = i - 1;
    return *this;
}

String& String::operator--()
{
    int i;
    for (i = 0; string[i] != '\0'; i++)
        string[i] = string[i - 1];
    length = i - 1;
    return *this;
}

String& String::operator++(int)
{
    String prev = *this;
    ++*this;
    return *this;
}
String& String::operator--(int)
{
    String prev = *this;
    --*this;
    return *this;
}

std::ostream& operator<<(std::ostream& output, String& text)
{
    output << text.string;
    return output;
}

std::istream& operator>>(std::istream& input, String& text)
{
    input >> text.string;
    return input;
}

void getline(std::istream& in, String& text)
{
    char* temp = new char[30];
    in.getline(temp, 30, '\n');
    text.set(temp);
    delete[] temp;
}