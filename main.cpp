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
#include<gtest/gtest.h>

class Patient {
    str name;
    int id;
    str illness_type;
    str nationality;
public:
    Patient(str _name,int _id,str _illness,str _nationality) : name(_name),id(_id),illness_type(_illness),nationality(_nationality) {}

    str get_illness(){return illness_type;}
    str get_name(){return name;}
    int get_id(){return id;}
    str get_nationality(){return nationality;}
};
class Doctor{
public:
    str name;
    str field;
    str time_table;
public:
    Doctor(str _name,str _field,str _time_table) : name(_name),field(_field),time_table(_time_table)  {}

    virtual void treat() const = 0;
    virtual ~Doctor(){}
};
class Surgery : public Doctor{
public:
    Surgery(str name,str time_table) : Doctor(name,"Surgery",time_table) {}

    void treat() const override{
        std::cout<<"suggestion ->"<<std::endl;
        std::cout<<"Srgery works"<<std::endl;
    }
};
class Physician: public Doctor{
public:
    Physician(str name,str time_table): Doctor(name,"Physician", time_table) {}
    void treat() const override{
        std::cout<<"suggestion ->"<<std::endl;
        std::cout<<"Physycian works"<<std::endl;
    }
};

class Ophthalmologist: public Doctor{
public:
    Ophthalmologist(str name,str time_table): Doctor(name,"Ophthalmologist", time_table) {}
    void treat() const override{
        std::cout<<"suggestion ->"<<std::endl;
        std::cout<<"WEAR GLASSES "<<std::endl;
    }
};

class Illness_Types{
public:
    std::vector<str> illness_types;
    str field;

    Illness_Types(std::vector<str> _illnes_types,str _field) : illness_types(_illnes_types),field(_field) {}

    bool has_illness(const str illness){
        for(str type: illness_types){
            if(type==illness){
                return true;
            }
        }
        return false;
    }
};
//so i have patient who has illness and in order to find appropriate doctor i need to create a function which will look through that illness in vector of illness
class Hospital{
    std::vector<Doctor*> doctors;
    std::vector<Illness_Types> illnes_types;
public:
    Hospital(){}
    void add_doctor(Doctor* doctor){
        doctors.push_back(doctor);
    }
    void add_field(Illness_Types illness_type){
        illnes_types.push_back(illness_type);
    }
    bool appointment(Patient* patient){
        for(Doctor* D:doctors){
            for(Illness_Types types: illnes_types) {
                if(types.has_illness(patient->get_illness()) && D->field==types.field){
                    std::cout<<"yes there is a doctor "<<D->name<<std::endl;
                    std::cout<<"He is specified in the field of"<<D->field<<std::endl;
                    std::cout<<"time table"<<D->time_table<<std::endl;
                    D->treat();
                    return true;
                }
            }
        }
        std::cout<<"there are no doctors who can help you"<<std::endl;
        return false;
    }
    ~Hospital(){
        for(Doctor* d:doctors){
            delete d;
        }
    }
    Hospital(const Hospital&)= delete;
    Hospital &operator=(const Hospital&)= delete;
};
//illness type is vector where i  store all illness types ofcertain field#include <gtest/gtest.h>
TEST(HOSPITALTEST,SATISFIEDOUTPUT){
    Hospital hospital;
    hospital.add_doctor(new Physician("Dr. Smith", "9:00 - 17:00"));
    hospital.add_field(Illness_Types({"Flu", "Fever", "Cough"}, "Physician"));
    Patient patient("John Doe", 123456, "Flu", "English");
    EXPECT_TRUE(hospital.appointment(&patient));
}
TEST(HOSPITALTEST,UNSATISFIEDOUTPUT){
    Hospital hospital;
    hospital.add_doctor(new Physician("Dr. Smith", "9:00 - 17:00"));
    hospital.add_field(Illness_Types({"Flu", "Fever", "Cough"}, "Physician"));
    Patient patient("John Doe", 123456, "Astigmatism", "English");
    EXPECT_TRUE(hospital.appointment(&patient));
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    Patient patient("ALI",123451,"Astigmatism","azerbaijanian");
    Hospital hospital;
    hospital.add_doctor(new Surgery("HASAN","10:00 - 15:00 PM"));
    hospital.add_doctor(new Physician("JOHN","15:30 - 18:00 PM"));
    hospital.add_doctor(new Ophthalmologist("MARTA","8:00 - 12:00 PM"));

    hospital.add_field(Illness_Types( {"Appendicitis", "Fractures", "Cancer"},"Surgery"));
    hospital.add_field(Illness_Types( {"Flu", "Fever", "Cough"},"Physician"));
    hospital.add_field(Illness_Types( {"Myopia", "Hyperopia", "Astigmatism"},"Ophthalmologist"));
    hospital.appointment(&patient);
}