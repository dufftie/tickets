#pragma once
#include <iostream>
typedef unsigned short int USInt;

class String
{
private:
	char* string;
	USInt length;
public:
	USInt size();
	char& operator[](USInt pos);
	void set(char*);

	String& operator=(String&);
	String& operator++();
	String& operator--();
	String& operator++(int);
	String& operator--(int);

	friend bool operator<(String&, String&);
	friend bool operator>(String&, String&);
	friend bool operator==(String&, String&);
	friend bool operator==(String&, char);
	friend bool operator!=(String&, String&);
	friend bool operator!=(String&, char);

	friend std::ostream& operator<<(std::ostream&, String&);
	friend std::istream& operator>>(std::istream&, String&);

	String();
	String(const char*);
	String(const String&);
	~String();
};

void getline(std::istream&, String&);