//i want to create same system as in hospitals.for instance,what you do when you
//> come to hosputal.you come to reception and tell about your illness or type of
//> illness.then they reccommend you the doctor who is specified in this field and
//> tell you about his room number and time table.
//> we can create class patient who has name id and illness and we can also have
//> nationality so that respong will be in appropriate language .
//> then we can have base class doctor which has name,specifieed field, and time
//> table;
//> and there will be other derived classes of doctor who will inherit the
//> properties of base class and will have as a polymorpism different methods of
//> treatment.we could have vector of doctors class which will store the name and
//> specifed field and whatever illness is   program will recommend doctor and his
//> time or will reject and tell that there is no doctors.
#include<iostream>
#include<vector>
using str = std::string;

class Patient {
    str name;
    int id;
    str illness_type;
    str nationality;

};