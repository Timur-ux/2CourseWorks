#ifndef UNDO_MANAGER_H_
#define UNDO_MANAGER_H_

#include <string>
#include <stack>
#include <memory>

#include "Observer.hpp"

enum class StateType {
	fullCopy,
	base,
	offset
};

class State;
class IUndoManager {
public:
	virtual IUndoManager & addState(State state) = 0;
	virtual State & undo() = 0;
};

struct Position;
class ILocation;
class MobData;
class DangeonUndoManager : public IUndoManager {
private:
	std::stack<State> states;
	std::shared_ptr<LogObserver> logObserver;
	std::shared_ptr<ILocation> location;
public:
	State & undo() override;
	IUndoManager & addState(State state) override;

	void on_addMob(const MobData & mob);
	void on_move(const MobData & mob, Position from, Position to);
	void on_attack(const MobData & idAttacker, const MobData & idDefender);
};


class State {
protected:
	StateType type;
	std::string state;

	State(StateType _type, std::string _state) : type(_type), state(_state) {}
public:
	virtual std::string & getState() {
		return state;
	}

	virtual StateType getType() {
		return type;
	}
};

/*
	State Formats:
	1. base -- <type> <name> <id>; <type> <name> <id>;...
	2. offset -- <action*> <type> <name> <id>
	3. fullCopy -- same as base
*/


#endif // UNDO_MANAGER_H_