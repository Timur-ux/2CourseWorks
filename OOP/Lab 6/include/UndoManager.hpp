#ifndef UNDO_MANAGER_H_
#define UNDO_MANAGER_H_

#include <string>
#include <stack>
#include <type_traits>
#include <memory>
#include <vector>

#include "Location.hpp"
#include "Observer.hpp"
#include "MobFabric.hpp"

enum class StateType {
	fullCopy,
	base,
	offset
};

class IState;
class IUndoManager {
public:
	virtual IUndoManager & addState(IState IState) = 0;
	virtual IState & undo() = 0;
};

class DangeonUndoManager : public IUndoManager {
private:
	std::stack<IState> states;
	std::shared_ptr<LogObserver> logObserver;
	std::shared_ptr<ILocation> location;
public:
	IState & undo() override;
	IUndoManager & addState(IState IState) override;

	void onAdd(const MobData & mob);
	void onMove(const MobData & mob, Position to);
	void onAttack(const MobData & idAttacker, const MobData & idDefender);
};


class IState {
public:
	virtual std::string toString() = 0;
	virtual IState & fromString(std::string _data) = 0;
};

class StateAdd;
class StateBase : public IState {
private:
	std::vector<StateAdd> mobsAdds;
public:
	StateBase(std::vector<StateAdd> & _mobsAdds) : mobsAdds(_mobsAdds) {}
	std::string toString() override;
	IState & fromString(std::string _data) override;
};

class StateAdd : public IState {
private:
	std::shared_ptr<MobData> mobToAdd;
public:
	StateAdd(std::shared_ptr<MobData> _mobToAdd) : mobToAdd(_mobToAdd) {}
	std::string toString() override;
	IState & fromString(std::string _data) override;
};

class StateMove : public IState {
private:
	std::shared_ptr<MobData> mobToMove;
	Position from;
	Position to;
public:
	StateMove(std::shared_ptr<MobData> _mobToMove, Position & _from, Position & _to)
		: mobToMove(_mobToMove)
		, from(_from)
		, to(_to) {}

	std::string toString() override;
	IState & fromString(std::string _data) override;

};

class StateRemove : public IState {
private:
	std::shared_ptr<MobData> mobToRemve;
public:
	StateRemove(std::shared_ptr<MobData> _mobToRemove) : mobToRemve(_mobToRemove) {};

	std::string toString() override;
	IState & fromString(std::string _data) override;
};

class StateValidator {
public:
	template<class TState>
		requires std::derived_from <TState, IState>
	static bool isDataValid(std::string _data);
};

#endif // UNDO_MANAGER_H_