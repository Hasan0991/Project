#include <gtest/gtest.h>
#include "main.h"
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
    Patient patient("John Doe", 123456, "Flu", "English");
    EXPECT_FALSE(hospital.appointment(&patient));
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