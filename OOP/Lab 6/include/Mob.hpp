#ifndef MOB_H_
#define MOB_H_

class IMob {
protected:
	double health;
	double damage;
	double attackRange;
public:
	virtual void attack(IMob & other);
};

#endif // MOB_H_