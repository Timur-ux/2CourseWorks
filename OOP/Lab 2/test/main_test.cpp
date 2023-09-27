#include "Octal.hpp"
#include <gtest/gtest.h>
#include <fstream>

string readFromIFStream(ifstream & iFileStream);

TEST(test_toString, basic_metods_set) {

    Octal octal("12345670");
    string sOctal = "12345670";

    bool cmp = (octal.toString() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_copy, basic_metods_set) {

    string sOctal = "12345670";
    Octal octal(sOctal);

    bool cmp = (octal.toString() == Octal(octal).toString());

    ASSERT_TRUE(cmp);
}

TEST(test_equal, relations_test_set) {

    string sOctal = "12345670";
    Octal firstOctal(sOctal);
    Octal secondOctal(sOctal);

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_greater, relations_test_set) {

    string sFirstOctal = "123";
    string sSecondOctal = "13";
    Octal firstOctal(sFirstOctal);
    Octal secondOctal(sSecondOctal);

    bool cmp = (firstOctal > secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_lesser, relations_test_set) {

    string sFirstOctal = "123";
    string sSecondOctal = "13";
    Octal firstOctal(sFirstOctal);
    Octal secondOctal(sSecondOctal);

    bool cmp = (firstOctal < secondOctal);

    ASSERT_FALSE(cmp);
}

TEST(test_initializer_list, basic_creating_set) {

    Octal firstOctal("123");
    Octal secondOctal{'1', '2', '3'};

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_string, assingn_test_set) {

    string sOctal = "12345670";
    Octal octal = sOctal;

    bool cmp = (octal.toString() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_LinkOctal, assingn_test_set) {

    string sOctal = "12345670";
    Octal firstOctal(sOctal);
    Octal secondOctal = firstOctal;

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_DoubleLinkOctal, assingn_test_set) {

    string sOctal = "12345670";
    Octal octal = Octal(sOctal);

    bool cmp = (octal.toString() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_addition, operations_test_set) {

    Octal firstOctal("123");
    Octal secondOctal("17");
    Octal resultOctal("142");

    bool cmp = (firstOctal + secondOctal == resultOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_substraction, operations_test_set) {

    Octal firstOctal("142");
    Octal secondOctal("17");
    Octal resultOctal("123");

    bool cmp = (firstOctal - secondOctal == resultOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_serialize, serializer_test_set) {
    const int OCTALS_QUANTITY = 3;
    ofstream oFileStream;
    ifstream iFileStream;
    Octal octals[OCTALS_QUANTITY];
    string nums[OCTALS_QUANTITY] = {"123", "321", "444"};
    bool check = true;

    oFileStream.open("buffer.bin", ios::out | ios::binary);
    for(int i = 0; i < OCTALS_QUANTITY; ++i){
        octals[i] = nums[i];
        octals[i].serialize(oFileStream);
    }
    
    oFileStream.close();
    // next we read from file using ifstream(not Octal.deserialize
    // because it isn't tested yet)
    iFileStream.open("buffer.bin", ios::in | ios::binary);
    
    for(int i = 0; i < OCTALS_QUANTITY; ++i) {
        string readedNum = readFromIFStream(iFileStream);
        cout << "Serealization's test: " << readedNum << endl;
        reverse(readedNum.begin(), readedNum.end()); //Octal stores reversed num
        check = check and (readedNum == nums[i]);
    }

    iFileStream.close();

    ASSERT_TRUE(check);
}

TEST(test_deserialize, serializer_test_set) {
    const int OCTALS_QUANTITY = 3;
    ofstream oFileStream;
    ifstream iFileStream;
    Octal octals[2*OCTALS_QUANTITY];
    string nums[OCTALS_QUANTITY] = {"123", "321", "444"};
    bool check = true;

    oFileStream.open("buffer.bin", ios::out | ios::binary);
    for(int i = 0; i < OCTALS_QUANTITY; ++i) {
        octals[i] = nums[i];
        octals[i].serialize(oFileStream);
    }
    oFileStream.close();
    // next we read from file using Octal.deserialize
    iFileStream.open("buffer.bin", ios::in | ios::binary);
    for(int i = OCTALS_QUANTITY; i < 2*OCTALS_QUANTITY; ++i) {
        octals[i].deserialize(iFileStream);
        check = check and (octals[i] == octals[i - OCTALS_QUANTITY]);
    }
    iFileStream.close();

    ASSERT_TRUE(check);
}

TEST(test_print, print_test_set) {
    ofstream oFileStream;
    ifstream iFileStream;
    string strOctal;
    Octal octal;

    octal = "12345";
    oFileStream.open("buffer.txt");
    oFileStream << octal << endl;
    oFileStream.close();

    iFileStream.open("buffer.txt");
    iFileStream >> strOctal;
    iFileStream.close();

    bool check = (strOctal == octal.toString());

    ASSERT_TRUE(check);
}

int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}

string readFromIFStream(ifstream & iFileStream) {
    size_t len;
    iFileStream.read(reinterpret_cast<char *>(&len), sizeof(size_t));
    char readedNum[len+1]{'\0'};
    iFileStream.read(readedNum, len);
    return string(readedNum);
}