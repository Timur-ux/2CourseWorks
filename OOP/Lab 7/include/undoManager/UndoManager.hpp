#ifndef UNDO_MANAGER_H_
#define UNDO_MANAGER_H_

#include <string>
#include <stack>
#include <type_traits>
#include <memory>
#include <vector>

#include "Location.hpp"
#include "Observer.hpp"
#include "mob/MobFabric.hpp"
#include "UndoVisitor.hpp"

enum class StateType {
    fullCopy,
    base,
    offset
};

class IState;
class IUndoManager {
public:
    virtual IUndoManager & addState(std::shared_ptr<IState> state) = 0;
    virtual IUndoManager & undo() = 0;
};

class DangeonUndoManager : public IUndoManager {
private:
    std::stack<std::shared_ptr<IState>> states;
    std::shared_ptr<LogObserver> logObserver;
    std::weak_ptr<ILocation> location;
    UndoVisitor visitor;
    bool isNowUndoTime = false;
public:
    DangeonUndoManager(std::weak_ptr<ILocation> _location, std::shared_ptr<LogObserver> _logObserver) :
        location(_location), logObserver(_logObserver), visitor(_location) {};
    IUndoManager & undo() override;
    IUndoManager & addState(std::shared_ptr<IState> state) override;

    void onAdd(const MobData & mob);
    void onMove(const MobData & mob, Position from, Position to);
    void onRemove(const MobData & mob);
};


class IState {
public:
    virtual std::string toString() = 0;
    virtual void accept(UndoVisitor & visitor) = 0;
};

class StateAdd;
class StateBase : public IState {
private:
    std::vector<StateAdd> mobAdds;
public:
    friend UndoVisitor;

    StateBase(std::vector<StateAdd> & _mobsAdds) : mobAdds(_mobsAdds) {}

    std::string toString() override;

    void accept(UndoVisitor & visitor) override;

};

class StateAdd : public IState {
private:
    std::shared_ptr<MobData> mobToAdd;
    StateAdd() = default;
public:
    friend UndoVisitor;
    friend StateBase;

    StateAdd(std::shared_ptr<MobData> _mobToAdd) : mobToAdd(_mobToAdd) {}

    std::string toString() override;

    void accept(UndoVisitor & visitor) override;
};

class StateRemove : public IState {
private:
    std::shared_ptr<MobData> mobToRemove;
public:
    friend UndoVisitor;

    StateRemove(std::shared_ptr<MobData> _mobToRemove) : mobToRemove(_mobToRemove) {};

    std::string toString() override;

    void accept(UndoVisitor & visitor) override;
};

class UndoUpdateData : public IUpdateData {
private:
    IState & state;
    std::string undoType;
public:
    UndoUpdateData(IState & _state, bool isSave = true);
    std::string asString() override;
};

#endif // UNDO_MANAGER_H_