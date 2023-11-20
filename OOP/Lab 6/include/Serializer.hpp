#ifndef SERIALIZER_H_
#define SERIALIZER_H_
#include <map>
#include <iostream>
#include <fstream>

class ISerializer {
public:
	virtual ISerializer & serialize(std::ostream & os) = 0;
	virtual ISerializer & deserialize(std::istream & is) = 0;
};

class ILocation;
struct MobData;

class LocationSerializer : ISerializer {
private:
	std::map <int, MobData> data;
public:
	ISerializer & serialize(std::ostream & os) override;
	ISerializer & deserialize(std::istream & is) override;
	ISerializer & setDataToSerialize(std::map<int, MobData> & _data);
};

#endif