//
// Created by Ceren Duru Cinar on 13.04.2023.
//

#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include <string>
#include <iostream>
using namespace std;

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
private:
    int time_slots;
    string ** data;

public:
    Schedule(); // default constructor
    Schedule(int c); // parametric constructor
    ~Schedule(); // destructor
    Schedule(const Schedule &); // deep copy constructor
    int getTimeSlots() const;
    string * getRow(int row) const;
    string ** getData() const;
    //string ** clone() const;
    string *& operator[](Days) const;
    const Schedule & operator=(const Schedule &);
    Schedule operator+(const Days & rhs);
    Schedule operator+ (int);
    Schedule operator+ (const Schedule & rhs);
};

ostream & operator<<(ostream & os, const Schedule & sch);
ostream & operator<<(ostream & os, const Days &);
bool operator<(const Schedule & lhs, const Schedule & rhs);
Schedule operator* (const Schedule & lhs, const Schedule & rhs);
#endif
