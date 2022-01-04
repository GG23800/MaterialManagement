#include<iostream>

#include"material.hpp"

int main (int argc, char *argv[])
{
    std::cout << "Bazinga!" << std::endl;

    material ma(0), mb(3,"lulu"), mc(51);
    mc = mb;
    nlohmann::json ja,jb,jc;
    ja = ma.get_json();
    jb = mb.get_json();
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mb.edit_ID(23);
    mb.edit_name("toto");
    jb = mb.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mc.edit_from_json(jb);
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    heat_material hm1(42);
    heat_material hm2(2,"lala",2.f,1.5f,6.f);
    heat_material hm3(mc,4.6f,0.23f,9.87f);
    heat_material cchm(hm2);
    cchm = hm3;

    hm3.edit_ID(199);
    hm3.edit_name("tralala");

    return 0;
}
