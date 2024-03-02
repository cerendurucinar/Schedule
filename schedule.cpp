//
// Created by Ceren Duru Cinar on 13.04.2023.
//

#include "schedule.h"

Schedule::Schedule() // default constructor
{
    time_slots = 0;
    data = new string * [7]; // creating the rows
    for (int i = 0; i < 7; i++) // initializing all rows to point to NULL
    {
        data[i] = nullptr;
    }
}


Schedule::Schedule(int c)
// parametric constructor that takes an integer for column number
{
    time_slots = c;
    data = new string * [7]; // creating the rows
    for (int i = 0; i < 7; i++)
    {
        data[i] = new string[c]; // creating columns
        for (int j = 0; j < c; j++) // initializing all the columns to "free"
        {
            data[i][j] = "free";
        }
    }
}

Schedule::~Schedule() // destructor
{

    for (int i = 0; i < 7; i++) // first deleting columns
    {
        delete [] data[i];
    }
    delete [] data; // then deleting pointer to the pointer

}
/*
string ** Schedule::clone() const
// creates a clone of the object on which the function is called
{
    string ** data_ptr;
    data_ptr = new string * [7]; // creating rows
    if (time_slots == 0) // checking if it is empty
    {
        for (int i = 0; i < 7; i++) // initializing all to null
        {
            data_ptr[i] = nullptr;
        }
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            data_ptr[i] = new string[time_slots]; // creating columns
            for (int j = 0; j < time_slots; j++) // initializing all the elements of the object to the copied one
            {
                data_ptr[i][j] = data[i][j];
            }
        }
    }
    cout << "copy constructor invoked" << endl;
    return data_ptr;
}
*/
Schedule::Schedule(const Schedule & copy) // deep copy constructor
{
    time_slots = copy.time_slots;
    data = new string * [7]; // allocating new pointer to string pointer
    for (int i = 0; i < 7; i++)
    {
        data[i] = new string[time_slots]; // allocating new string pointers fpr the columns
        for (int j = 0; j < time_slots; j++)
        {
            data[i][j] = copy.getData()[i][j]; // copying row infos
        }
    }
}

// Getter functions
int Schedule::getTimeSlots() const
// returns time_slots
{
    return time_slots;
}

string * Schedule::getRow(int row) const
// returns the row pointer
{
    return data[row];
}

string ** Schedule::getData() const
{
    return data;
}

//Operators
string *& Schedule::operator[](Days day) const
// returns the row that corresponds to the day
{
    return data[day];
}

const Schedule & Schedule:: operator= (const Schedule & rhs)
        // assigns right hand side to left hand side(object itself) and returns the object
{
    if (this != &rhs) // checking self assignment
    {
        for (int i = 0; i < 7; i++) // first deleting columns
        {
            delete [] data[i];
        }
        delete [] data; // deleting rows
        data = new string *[7];  // allocating new matrix
        time_slots = rhs.time_slots;
        for (int i = 0; i < 7; i++)
        {
            data[i] = new string[time_slots];
            for (int j = 0; j < time_slots; j++)
            {
                data[i][j] = rhs.data[i][j]; // copying infos
            }
        }
    }
    return *this;
}

Schedule Schedule:: operator+(int rhs)
// set a particular time slot of all days to busy and return a brand new object
{
    Schedule result(*this); // copying left hand side
    if (result.time_slots != 0) // checking if there are any columns
    {
        for (int i = 0; i < 7; i++)
        {
            result.data[i][rhs] = "busy"; // setting it busy
        }
    }
    return result;
}

Schedule Schedule:: operator+(const Days & rhs)
// sets all columns of a particular day to busy and return a brand new object
{
    Schedule result(*this); // copying left hand side
    for (int i = 0; i < result.time_slots; i++)
    {
        result.data[rhs][i] = "busy"; // setting busy
    }
    return result;
}

Schedule Schedule:: operator+ (const Schedule & rhs)
// returns a schedule object which contains common free slots of the lhs and rhs
{
    Schedule result(rhs.getTimeSlots()); // creating new schedule object
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < rhs.getTimeSlots(); j++)
        {
            if (this->getData()[i][j] != "free" || rhs.getData()[i][j] != "free")
            {
                result.getData()[i][j] = "busy"; // setting busy
            }
        }
    }
    return result;
}

// free functions
ostream & operator<< (ostream & os, const Schedule & sch)
// outputs the schedule object on os and returns reference of os
{
    string d[7] = {"Mo:", "Tu:", "We:", "Th:", "Fr:", "Sa:", "Su:"}; // array for the day names
    for (int i = 0; i < 7; i++)
    {
        os << d[i] << " "; // outputting day names
        for (int j = 0; j < sch.getTimeSlots(); j++)
        {
            os << sch.getRow(i)[j] << " "; // outputting the contents
        }
        os << endl;
    }
    return os;
}

ostream & operator<< (ostream & os, const Days & day)
// outputs the enum type day name and returns the reference of os
{
    string d[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    os << d[day];
    return os;
}

bool operator<(const Schedule & lhs, const Schedule & rhs)
// returns true if lhs has less busy spots, false otherwise
{
    int countlhs= 0, countrhs = 0;
    for (int i = 0; i < 7; i++) // checking lhs
    {
        for (int j = 0; j < lhs.getTimeSlots(); j++)
        {
            if (lhs.getData()[i][j] == "busy")
            {
                countlhs++; // updating busy count
            }
        }
    }
    for (int i = 0; i < 7; i++) // checking rhs
    {
        for (int j = 0; j < rhs.getTimeSlots(); j++)
        {
            if (rhs.getData()[i][j] == "busy")
            {
                countrhs++; // updating busy count
            }
        }
    }
    return (countlhs < countrhs);
}

Schedule operator* (const Schedule & lhs, const Schedule & rhs)
// creates and returns a schedule object that contains common busy spots of lhs and rhs
{
    Schedule result(lhs.getTimeSlots()); // creating new schedule object
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < lhs.getTimeSlots(); j++)
        {
            if (lhs.getData()[i][j] == "busy" && rhs.getData()[i][j] == "busy") // if they are both equal to busy
            {
                result.getData()[i][j] = "busy"; // we update it as busy
            }
        }
    }
    return result;
}



