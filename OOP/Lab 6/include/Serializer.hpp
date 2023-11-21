#ifndef SERIALIZER_H_
#define SERIALIZER_H_
#include <memory>
#include <iostream>
#include <fstream>

#include "Location.hpp"

class ISerializer {
public:
	virtual ISerializer & serialize(std::ostream & os) = 0;
	virtual ISerializer & deserialize(std::istream & is) = 0;
};

class ILocation;
struct MobData;

class LocationSerializer : public ISerializer {
private:
	std::shared_ptr<ILocation> location;
public:
	ISerializer & serialize(std::ostream & os) override;
	ISerializer & deserialize(std::istream & is) override;
	ISerializer & setLocation(std::shared_ptr<ILocation> _location);
};

#endif