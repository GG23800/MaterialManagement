# MaterialManagement
A small librairy for material management used in simulation tool. This librairy can save material list under json file.

## Author

Jérôme Dubois: jerome.dubois23800@gmail.com

## Tests

Tests are made using gtest. If gtest is not installed on your computer comment line 29 in CMakeList.txt:
'''bash
 #add_subdirectory(test)
'''

## Used library

Json part of the librairy is made using [nlohmann/json](https://github.com/nlohmann/json.git).

## License

This librairy is licensed under [GNU General Public License V3.0](LICENSE).

It can be used for free for open source user, academic user, hobby project. For commercial use please contact the author.

## To do

Make correct tests via gtest

Make doxigen documentation?

Utility of material ID? Automatically managed by MaterialList

Material list as a template? No need for multiple class with inheritance? Or take benefit from polymorphismon material list template?
