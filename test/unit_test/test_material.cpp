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
    Material m1(0);
    EXPECT_EQ( m1.get_name(), lName );
    // full constructor
    int lID = 23;
    lName = "Rename";
    Material m2(lID, lName);
    EXPECT_EQ( m2.get_ID(), lID );
    EXPECT_EQ( m2.get_name(), lName);
    // copy constructor
    Material m3(m2);    
    EXPECT_EQ( m3.get_ID(), lID );
    EXPECT_EQ( m3.get_name(), lName);
    // copy assignement
    lID = 42;
    lName = "NewName";
    Material m4(lID, lName);
    m2 = m4;
    EXPECT_EQ( m2.get_ID(), lID );
    EXPECT_EQ( m2.get_name(), lName);
    // move assignement operator
    m4 = std::move(m1);
    EXPECT_EQ( m4.get_ID(), 0 );
    EXPECT_EQ( m4.get_name(), "unknowed");
    // move constructor
    Material m5(std::move(m2));
    EXPECT_EQ( m5.get_ID(), lID );
    EXPECT_EQ( m5.get_name(), lName);
}

TEST( Material_class, edit_functions)
{
    Material m1(0);
    int lID = 942;
    std::string lName = "Az5_i)~%";
    // full material edition
    m1.edit_material(lID, lName);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // full material edition with material
    lID = 56;
    lName = "adsxio";
    Material m2(lID, lName);
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

    // verify nothing is done if json is not complete
    ijson = nlohmann::json{};
    ijson["ID"] = 123;
    m1.edit_from_json(ijson);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    ijson = nlohmann::json{};
    ijson["Name"] = "bob";
    m1.edit_from_json(ijson);
    EXPECT_EQ( m1.get_ID(), lID );
    EXPECT_EQ( m1.get_name(), lName);
    // if type of variable is not respected if ID is a string for example nlohmann json has an assert to verifiy that
    // if need of a special test to show function where the assert apply one can use typeid of <typeinfo>
}

TEST( HeatMaterial_class, constructor )
{
    // default name "unknowed", density 1, specific heat 1, thermal conductivity 1
    // verify default value
    std::string lName = "unknowed";
    float lDensity = 1.f;
    float lSpecificHeat = 1.f;
    float lThermalConductivity = 1.f;
    HeatMaterial hm1(0);
    EXPECT_EQ( hm1.get_name(), lName );
    EXPECT_FLOAT_EQ( hm1.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), lThermalConductivity );
    int lID = 87;
    lName = "bazinga";
    Material m1(lID, lName);
    HeatMaterial hm2(m1);
    EXPECT_EQ( hm2.get_ID(), lID );
    EXPECT_EQ( hm2.get_name(), lName );
    EXPECT_FLOAT_EQ( hm2.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), lThermalConductivity );
    
    // full constructor
    lID = 23;
    lName = "Rename";
    lDensity = 2.98f;
    lSpecificHeat = 3.14f;
    lThermalConductivity = 93.78;
    HeatMaterial hm3(lID, lName, lDensity, lSpecificHeat, lThermalConductivity);
    EXPECT_EQ( hm3.get_ID(), lID );
    EXPECT_EQ( hm3.get_name(), lName );
    EXPECT_FLOAT_EQ( hm3.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm3.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm3.get_thermal_conductivity(), lThermalConductivity );
    lID = 10001;
    lName = "#_o:!§ac";
    m1.edit_material(lID, lName);
    lDensity = 98.321f;
    lSpecificHeat = 23458.121f;
    lThermalConductivity = 743.81f;
    HeatMaterial hm4(m1, lDensity, lSpecificHeat, lThermalConductivity);
    EXPECT_EQ( hm4.get_ID(), lID );
    EXPECT_EQ( hm4.get_name(), lName );
    EXPECT_FLOAT_EQ( hm4.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm4.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm4.get_thermal_conductivity(), lThermalConductivity );

    // copy constructor
    HeatMaterial hm5(hm4);
    EXPECT_EQ( hm5.get_ID(), lID );
    EXPECT_EQ( hm5.get_name(), lName );
    EXPECT_FLOAT_EQ( hm5.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm5.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm5.get_thermal_conductivity(), lThermalConductivity );
    
    // copy assignement
    hm1 = hm5;
    EXPECT_EQ( hm1.get_ID(), lID );
    EXPECT_EQ( hm1.get_name(), lName );
    EXPECT_FLOAT_EQ( hm1.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), lThermalConductivity );   
    
    // move assignement operator
    hm2 = std::move(hm4);
    EXPECT_EQ( hm2.get_ID(), lID );
    EXPECT_EQ( hm2.get_name(), lName );
    EXPECT_FLOAT_EQ( hm2.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), lThermalConductivity );
    
    // move constructor
    HeatMaterial hm6(std::move(hm5));
    EXPECT_EQ( hm6.get_ID(), lID );
    EXPECT_EQ( hm6.get_name(), lName );
    EXPECT_FLOAT_EQ( hm6.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm6.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm6.get_thermal_conductivity(), lThermalConductivity );
}

TEST( HeatMaterial_class, edit_functions)
{
    HeatMaterial hm1(64);
    float lDensity = 12.873f;
    float lSpecificHeat = 0.00037461f;
    float lThermalConductivity = 1862538.5f;
    // density edition
    hm1.edit_density(lDensity);
    EXPECT_FLOAT_EQ( hm1.get_density(), lDensity );
    // specific heat
    hm1.edit_specific_heat(lSpecificHeat);
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), lSpecificHeat);
    // thermal conductivity
    hm1.edit_thermal_conductivity(lThermalConductivity);
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), lThermalConductivity);
    // full material edition
    hm1 = HeatMaterial(64);
    // check default value is set
    EXPECT_FLOAT_EQ( hm1.get_density(), 1.f );
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), 1.f );
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), 1.f );
    int lID = 39;
    std::string lName = "gdqfuoph";
    HeatMaterial nhm(lID, lName, lDensity, lSpecificHeat, lThermalConductivity);
    hm1.edit_material(nhm);
    EXPECT_EQ( hm1.get_ID(), lID );
    EXPECT_EQ( hm1.get_name(), lName);
    EXPECT_FLOAT_EQ( hm1.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), lThermalConductivity );   

    // edition from json
    lID = 623;
    lName = "apodicnrehumsqfjkdsfhu";
    lDensity = 0.0072635f;
    lSpecificHeat = 2.736645f;
    lThermalConductivity = 3726.473624f;
    nlohmann::json ijson{};
    ijson["ID"] = lID;
    ijson["Name"] = lName;
    ijson["Density"] = lDensity;
    ijson["SpecificHeat"] = lSpecificHeat;
    ijson["ThermalConductivity"] = lThermalConductivity;
    hm1.edit_from_json(ijson);
    EXPECT_EQ( hm1.get_ID(), lID );
    EXPECT_EQ( hm1.get_name(), lName);
    EXPECT_FLOAT_EQ( hm1.get_density(), lDensity );
    EXPECT_FLOAT_EQ( hm1.get_specific_heat(), lSpecificHeat );
    EXPECT_FLOAT_EQ( hm1.get_thermal_conductivity(), lThermalConductivity );
    //missing part of material
    //test was made on material, check heat material is not edited if material should not be edited
    int nID = 52;
    std::string nName = "idneabdo";
    float nDensity = 372.97f;
    float nSpecificHeat = 29.17263f;
    float nThermalConductivity = 82173.2726f;
    HeatMaterial hm2(nID, nName, nDensity, nSpecificHeat, nThermalConductivity);
    ijson = nlohmann::json{};
    ijson["ID"] = lID;
    //ijson["Name"] = lName;
    ijson["Density"] = lDensity;
    ijson["SpecificHeat"] = lSpecificHeat;
    ijson["ThermalConductivity"] = lThermalConductivity;
    hm2.edit_from_json(ijson);
    EXPECT_EQ( hm2.get_ID(), nID );
    EXPECT_EQ( hm2.get_name(), nName);
    EXPECT_FLOAT_EQ( hm2.get_density(), nDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), nSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), nThermalConductivity );
    //missing part of heat specificity
    ijson = nlohmann::json{};
    ijson["ID"] = lID;
    ijson["Name"] = lName;
    //ijson["Density"] = lDensity;
    ijson["SpecificHeat"] = lSpecificHeat;
    ijson["ThermalConductivity"] = lThermalConductivity;
    hm2.edit_from_json(ijson);
    EXPECT_EQ( hm2.get_ID(), nID );
    EXPECT_EQ( hm2.get_name(), nName);
    EXPECT_FLOAT_EQ( hm2.get_density(), nDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), nSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), nThermalConductivity );
    ijson = nlohmann::json{};
    ijson["ID"] = lID;
    ijson["Name"] = lName;
    ijson["Density"] = lDensity;
    //ijson["SpecificHeat"] = lSpecificHeat;
    ijson["ThermalConductivity"] = lThermalConductivity;
    hm2.edit_from_json(ijson);
    EXPECT_EQ( hm2.get_ID(), nID );
    EXPECT_EQ( hm2.get_name(), nName);
    EXPECT_FLOAT_EQ( hm2.get_density(), nDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), nSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), nThermalConductivity );
    ijson = nlohmann::json{};
    ijson["ID"] = lID;
    ijson["Name"] = lName;
    ijson["Density"] = lDensity;
    ijson["SpecificHeat"] = lSpecificHeat;
    //ijson["ThermalConductivity"] = lThermalConductivity;
    hm2.edit_from_json(ijson);
    EXPECT_EQ( hm2.get_ID(), nID );
    EXPECT_EQ( hm2.get_name(), nName);
    EXPECT_FLOAT_EQ( hm2.get_density(), nDensity );
    EXPECT_FLOAT_EQ( hm2.get_specific_heat(), nSpecificHeat );
    EXPECT_FLOAT_EQ( hm2.get_thermal_conductivity(), nThermalConductivity );

    // test output json
    nlohmann::json ojson = hm2.get_json();
    EXPECT_EQ( ojson["ID"], nID );
    EXPECT_EQ( ojson["Name"], nName);
    EXPECT_FLOAT_EQ( ojson["Density"], nDensity );
    EXPECT_FLOAT_EQ( ojson["SpecificHeat"], nSpecificHeat );
    EXPECT_FLOAT_EQ( ojson["ThermalConductivity"], nThermalConductivity );

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
