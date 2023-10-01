#include "Octal.hpp"
#include <gtest/gtest.h>
#include <fstream>

class SerializableTest : public testing::Test {
public:
    static const int OCTALS_COUNT = 3;

    Octal octals[OCTALS_COUNT];
    string nums[OCTALS_COUNT] = {"123", "456", "70123"};
    string bufferName = "buffer.bin";

    void SetUp() {
        ofstream oFileStream(bufferName);
        
        for(int i = 0; i < OCTALS_COUNT; ++i) {
            octals[i] = nums[i];
            octals[i].serialize(oFileStream);
        }
        oFileStream.close();
    }

    string readNum(istream &is) {
        string readedNum;
        
        is >> readedNum;

        return readedNum;
    }

    void TearDown() {};

};

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

TEST_F(SerializableTest, serialize_test) {
    bool check = true;
    ifstream iFileStream(bufferName);
    for(int i = 0; i < OCTALS_COUNT; ++i) {
        check = check and (readNum(iFileStream) == nums[i]);
    }
    iFileStream.close();

    ASSERT_TRUE(check);
}

TEST_F(SerializableTest, deserialize_test) {
    bool check = true;
    Octal scanOctals[OCTALS_COUNT];
    ifstream iFileStream("buffer.bin");
    
    for(int i = 0; i < OCTALS_COUNT; ++i) {
        scanOctals[i].deserialize(iFileStream);
        check = check and (scanOctals[i] == octals[i]);
    }
    iFileStream.close();

    ASSERT_TRUE(check);
}

TEST(test_print, io_test_set) {
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

TEST(test_read, io_test_set) {
    ofstream oFileStream;
    ifstream iFileStream;
    string strOctal;
    Octal octals[2];

    octals[0] = "12345";
    oFileStream.open("buffer.txt");
    oFileStream << octals[0] << endl;
    oFileStream.close();

    iFileStream.open("buffer.txt");
    iFileStream >> octals[1];
    iFileStream.close();

    ASSERT_TRUE(octals[0] == octals[1]);
}

int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}
