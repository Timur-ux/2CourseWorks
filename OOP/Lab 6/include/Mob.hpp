#ifndef MOB_H_
#define MOB_H_

namespace Mob {
	enum class Status {
		alive = 0,
		died = 1
	};
}


class IMob {
protected:
	Mob::Status status;
	double health;
	double damage;
	double attackRange;
public:
	virtual void attack(IMob & other);
};



#endif // MOB_H_