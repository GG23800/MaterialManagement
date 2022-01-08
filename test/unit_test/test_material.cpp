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
    // move assignement operator
    m4 = std::move(m1);
    EXPECT_EQ( m4.get_ID(), 0 );
    EXPECT_EQ( m4.get_name(), "unknowed");
    // move constructor
    material m5(std::move(m2));
    EXPECT_EQ( m5.get_ID(), lID );
    EXPECT_EQ( m5.get_name(), lName);
}

TEST( Material_class, edit_functions)
{
    material m1(0);
    int lID = 942;
    std::string lName = "Az5_i)~%";
    // full material edition
    m1.edit_material(lID, lName);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // full material edition with material
    lID = 56;
    lName = "adsxio";
    material m2(lID, lName);
    m1.edit_material(m2);    
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // ID edition
    lID = 974;
    m1.edit_ID(lID);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // Name edition
    lName = "&fdqçodcé";
    m1.edit_name(lName);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // edition from json
    lID = 8520;
    lName = "01:?=$";
    nlohmann::json ijson{};
    ijson["ID"] = lID;
    ijson["Name"] = lName;
    m1.edit_from_json(ijson);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // getting json
    int nID = 12;
    std::string nName = "tutu";
    ijson["ID"] = nID;
    ijson["Name"] = nName;
    nlohmann::json ojson = m1.get_json();
    // create a json different thant expected output and verify fields are present in output json
    EXPECT_NE( ojson["ID"], ijson["ID"] );
    EXPECT_NE( ojson["Name"], ijson["Name"] );
    EXPECT_EQ( ojson["ID"], lID );
    EXPECT_EQ( ojson["Name"], lName );
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
