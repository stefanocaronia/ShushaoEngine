#pragma once

#define BOOST_COROUTINES2_NO_LIB

/*
    Credits: https://github.com/exawon/CoroBehaviour
*/

#include <boost/coroutine2/all.hpp>
#include <ctime>
#include <functional>

namespace se {

// typeid without rtti
using TYPE_INFO = void*;

template <typename T>
TYPE_INFO _TYPEID_() {
    return reinterpret_cast<TYPE_INFO>(&_TYPEID_<T>);
}

#define TYPEID(T) _TYPEID_<T>()

class YieldInstruction {
    friend class Component;

public:
    YieldInstruction(TYPE_INFO InType) : Type(InType) {}
    virtual ~YieldInstruction() {}
    virtual void End() {}
    virtual bool IsEnded() {
        return true;
    }
    TYPE_INFO Type;
};

class WaitForSeconds : public YieldInstruction {
private:
    float Time;

    float Now() {
        return std::clock() / static_cast<float>(CLOCKS_PER_SEC);
    }

public:
    WaitForSeconds(float Seconds) : YieldInstruction(TYPEID(WaitForSeconds)), Time(Now() + Seconds) {}

protected:
    virtual void End() override {
        Time = Now();
    }

    virtual bool IsEnded() override {
        return Time <= Now();
    }
};

class WaitWhile : public YieldInstruction {
private:
    std::function<bool()> Condition;

public:
    WaitWhile(std::function<bool()> InCondition) : YieldInstruction(TYPEID(WaitWhile)), Condition(InCondition) {}

protected:
    virtual void End() override {
        Condition = []() {
            return false;
        };
    }

    virtual bool IsEnded() override {
        return !Condition();
    }
};

class WaitUntil : public YieldInstruction {
private:
    std::function<bool()> Condition;

public:
    WaitUntil(std::function<bool()> InCondition) : YieldInstruction(TYPEID(WaitWhile)), Condition(InCondition) {}

protected:
    virtual void End() override {
        Condition = []() {
            return true;
        };
    }

    virtual bool IsEnded() override {
        return Condition();
    }
};

using BoostCoroutine = boost::coroutines2::coroutine<class YieldInstruction*>;
using RoutinePull = BoostCoroutine::pull_type;
using RoutinePush = BoostCoroutine::push_type;
using Routine = std::function<void(RoutinePush&)>;

class Coroutine : public YieldInstruction {
    friend class Component;

public:
    Coroutine(RoutinePull& InPull) : YieldInstruction(TYPEID(Coroutine)), Pull(std::move(InPull)), NextPtr(nullptr) {}

    RoutinePull Pull;
    Coroutine* NextPtr;

    YieldInstruction* GetYieldReturn() {
        return Pull.get();
    }

    virtual void End() override {
        Pull = RoutinePull(Routine());
    }
    virtual bool IsEnded() override {
        return !Pull;
    }

    void Resume() {
        Pull();
    }
};

}  // namespace se
