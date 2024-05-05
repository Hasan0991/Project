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
    Patient(str _name,int _id,str _illness,str _nationality) : name(_name),illness_type(_illness),nationality(_nationality) {
        if(_id<0){
            throw std::invalid_argument("invalid data");
        }
        id = _id;
    }

    str get_illness()const{return illness_type;}
    str get_name()const{return name;}
    int get_id() const{return id;}
    str get_nationality()const{return nationality;}
};

class Illness_Types{
public:
    std::vector<str> illness_types;
    str field;

    Illness_Types(std::vector<str> _illnes_types,str _field) : illness_types(_illnes_types),field(_field) {}

    Illness_Types() {}

    bool has_illness(const str& illness)const{
        for(const str& type: illness_types){
            if(type==illness){
                return true;
            }
        }
        return false;
    }

};
class Prescription {
public:
    void add_pill(const str& new_pill){
        med_pill.push_back(new_pill);
    }

    std::vector<str> med_pill;
};
class Doctor{
public:
    str name;
    str field;
    str time_table;
public:
    Doctor(str _name,str _field,str _time_table) : name(_name),field(_field),time_table(_time_table)  {}

    virtual Prescription treat() const = 0;
    virtual ~Doctor()= default;
};

class Surgery : public Doctor{
public:
    Surgery(str name,str time_table) : Doctor(name,"Surgery",time_table) {}

    Prescription treat() const override{
        Prescription prescription;
        prescription.add_pill("painkillers");
        return prescription;
    }
};
class Physician: public Doctor{
public:
    Physician(str name,str time_table): Doctor(name,"Physician", time_table) {}
    Prescription treat() const override{
        Prescription prescription;
        prescription.add_pill("antibiotics");
        return prescription;
    }
};

class Ophthalmologist: public Doctor{
public:
    Ophthalmologist(str name,str time_table): Doctor(name,"Ophthalmologist", time_table) {}
    Prescription treat() const override{
        Prescription prescription;
        prescription.add_pill("eye drops");
        return prescription;
    }
};


//so i have patient who has illness and in order to find appropriate doctor i need to create a function which will look through that illness in vector of illness
class Hospital{
    std::vector<Doctor*> doctors;
    std::vector<Illness_Types> illnes_types;
public:
    Hospital()= default;
    void add_doctor(Doctor* doctor){
        doctors.push_back(doctor);
    }
    void add_field(const Illness_Types& illness_type){
        illnes_types.push_back(illness_type);
    }
    Prescription appointment(Patient* patient){
        Prescription prescription;
        for(Doctor* D:doctors){
            for(const auto& types: illnes_types) {
                if(types.has_illness(patient->get_illness()) && D->field==types.field){
                    std::cout<<"yes there is a doctor  "<<D->name<<std::endl;
                    std::cout<<"He is specified in the field of  "<<D->field<<std::endl;
                    std::cout<<"time table  "<<D->time_table<<std::endl;
                    Prescription doctor_prescription = D->treat();
                    std::cout << "Prescribed Medication: ";
                    for(const auto& pill: doctor_prescription.med_pill){
                        prescription.add_pill(pill);
                    }
                    for(const auto& pill: doctor_prescription.med_pill){
                        std::cout<<pill<<std::endl;
                    }

                }

            }
        }
        return prescription;
        std::cout<<"there are no doctors who can help you"<<std::endl;
    }
    ~Hospital(){
        for(Doctor* d:doctors){
            delete d;
        }
    }
    Hospital(const Hospital&)= delete;
    Hospital &operator=(const Hospital&)= delete;
};
// i have vector of medical pills i need to get for the outpur which pills must patient take
//illness type is vector where i  store all illness types ofcertain field#include
TEST(SURGERYPRESCTRIPTIONTEST,SATISFIEDOUTPUT){
    Surgery surgery("HASAN","18:00 - 19:00");
    Prescription prescription = surgery.treat();
    EXPECT_EQ(prescription.med_pill[0],"painkillers");
}
TEST(PHYSICANPRESCTRIPTIONTEST,SATISFIEDOUTPUT){
    Physician physician("HASAN","18:00 - 19:00");
    Prescription prescription = physician.treat();
    EXPECT_EQ(prescription.med_pill[0],"antibiotics");
}
TEST(OphthalmologistPRESCTRIPTIONTEST,SATISFIEDOUTPUT){
    Ophthalmologist ophthalmologist("HASAN","18:00 - 19:00");
    Prescription prescription = ophthalmologist.treat();
    EXPECT_EQ(prescription.med_pill[0],"eye drops");
}
TEST(HOSPITALTEST,SATISFIEDOUTPUT){
    Patient patient("ALI",123451,"Cancer","azerbaijanian");
    Hospital hospital;
    hospital.add_doctor(new Surgery("HASAN","10:00 - 15:00 PM"));
    hospital.add_doctor(new Physician("JOHN","15:30 - 18:00 PM"));
    hospital.add_doctor(new Ophthalmologist("MARTA","8:00 - 12:00 PM"));

    hospital.add_field(Illness_Types( {"Appendicitis", "Fractures", "Cancer"},"Surgery"));
    hospital.add_field(Illness_Types( {"Flu", "Fever", "Cough"},"Physician"));
    hospital.add_field(Illness_Types( {"Myopia", "Hyperopia", "Astigmatism"},"Ophthalmologist"));
    Prescription prescription =hospital.appointment(&patient);
    EXPECT_EQ(prescription.med_pill[0],"painkillers");
}
TEST(HOSPITALTEST,SATISFIEDOUTPUTFORPHYSICIAN){
    Patient patient("ALI",123451,"Flu","azerbaijanian");
    Hospital hospital;
    hospital.add_doctor(new Surgery("HASAN","10:00 - 15:00 PM"));
    hospital.add_doctor(new Physician("JOHN","15:30 - 18:00 PM"));
    hospital.add_doctor(new Ophthalmologist("MARTA","8:00 - 12:00 PM"));

    hospital.add_field(Illness_Types( {"Appendicitis", "Fractures", "Cancer"},"Surgery"));
    hospital.add_field(Illness_Types( {"Flu", "Fever", "Cough"},"Physician"));
    hospital.add_field(Illness_Types( {"Myopia", "Hyperopia", "Astigmatism"},"Ophthalmologist"));
    Prescription prescription =hospital.appointment(&patient);
    EXPECT_EQ(prescription.med_pill[0],"antibiotics");
}
TEST(HOSPITALTEST,SATISFIEDOUTPUTFORPOPHTALMOLOGIST){
    Patient patient("ALI",123451,"Hyperopia","azerbaijanian");
    Hospital hospital;
    hospital.add_doctor(new Surgery("HASAN","10:00 - 15:00 PM"));
    hospital.add_doctor(new Physician("JOHN","15:30 - 18:00 PM"));
    hospital.add_doctor(new Ophthalmologist("MARTA","8:00 - 12:00 PM"));

    hospital.add_field(Illness_Types( {"Appendicitis", "Fractures", "Cancer"},"Surgery"));
    hospital.add_field(Illness_Types( {"Flu", "Fever", "Cough"},"Physician"));
    hospital.add_field(Illness_Types( {"Myopia", "Hyperopia", "Astigmatism"},"Ophthalmologist"));
    Prescription prescription =hospital.appointment(&patient);
    EXPECT_EQ(prescription.med_pill[0],"eye drops");
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    Patient patient("ALI",123451,"Fever","azerbaijanian");
    Hospital hospital;
    hospital.add_doctor(new Surgery("HASAN","10:00 - 15:00 PM"));
    hospital.add_doctor(new Physician("JOHN","15:30 - 18:00 PM"));
    hospital.add_doctor(new Ophthalmologist("MARTA","8:00 - 12:00 PM"));

    hospital.add_field(Illness_Types( {"Appendicitis", "Fractures", "Cancer"},"Surgery"));
    hospital.add_field(Illness_Types( {"Flu", "Fever", "Cough"},"Physician"));
    hospital.add_field(Illness_Types( {"Myopia", "Hyperopia", "Astigmatism"},"Ophthalmologist"));
    hospital.appointment(&patient);
}