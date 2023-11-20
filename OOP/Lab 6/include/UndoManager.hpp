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
class DangeonUndoManager : public IUndoManager {
private:
	std::stack<State> states;
	std::shared_ptr<LogObserver> logObserver;
	std::shared_ptr<ILocation> location;
public:
	State & undo() override;
	IUndoManager & addState(State state) override;

	void on_addMob(int id);
	void on_move(int id, Position from, Position to);
	void on_attack(int idAttacker, int idDefender);
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

#endif // UNDO_MANAGER_H_