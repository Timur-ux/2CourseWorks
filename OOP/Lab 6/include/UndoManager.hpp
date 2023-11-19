#ifndef UNDO_MANAGER_H_
#define UNDO_MANAGER_H_

#include <string>
#include <stack>
#include <memory>

#include "Observer.hpp"

enum class StateType;

class State;

class OffsetState;
class BaseState;

class IUndoManager {
public:
	virtual IUndoManager & addState(State state) = 0;
	virtual State & undo() = 0;
};

class DangeonUndoManager : public IUndoManager {
private:
	std::stack<State> states;
	std::shared_ptr<LogObserver> logObserver;
public:
	State & undo() override;
	IUndoManager & addState(State state) override;

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

enum class StateType {
	fullCopy,
	base,
	offset
};

class BaseState : public State {
public:
	BaseState(std::string _state) : State(StateType::base, _state) {};
};

class OffsetState : public State {
public:
	OffsetState(std::string _state) : State(StateType::offset, _state) {};
};

#endif // UNDO_MANAGER_H_