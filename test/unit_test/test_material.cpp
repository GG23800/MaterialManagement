#include<gtest/gtest.h>

#include"material.hpp"

// Author: Jérôme Dubois
// Date: 2021/01
//
// Comment: some unit on material librairy

TEST( Material_class, constructor )
{
    // verify default name
    std::string lName = "unknowed";
    material m1(0);
    EXPECT_EQ( m1.get_name(), lName );
    // full constructor
    int lID = 23;
    lName = "Rename";
    material m2(lID, lName);
    EXPECT_EQ( m2.get_ID(), lID );
    EXPECT_EQ( m2.get_name(), lName);
    // copy constructor
    material m3(m2);    
    EXPECT_EQ( m3.get_ID(), lID );
    EXPECT_EQ( m3.get_name(), lName);
    // copy assignement
    lID = 42;
    lName = "NewName";
    material m4(lID, lName);
    m2 = m4;
    EXPECT_EQ( m2.get_ID(), lID );
    EXPECT_EQ( m2.get_name(), lName);
}

TEST( Material_class, edit_functions)
{
    material m1(0);

}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
