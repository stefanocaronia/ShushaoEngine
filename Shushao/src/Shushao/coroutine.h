#pragma once

#define COROUTINE [=](RoutinePush & yield_return)

/*
    Credits: https://github.com/exawon/CoroBehaviour
*/

#include "Shushao/Core.h"
#include "sepch.h"

namespace se {

class SHUSHAO_API YieldInstruction {
    friend class Component;

public:
    YieldInstruction(TypeInfo InType) : Type(InType) {}
    virtual ~YieldInstruction() {}
    virtual void End() {}
    virtual bool IsEnded() {
        return true;
    }
    TypeInfo Type;
};

class SHUSHAO_API WaitForSeconds : public YieldInstruction {
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

class SHUSHAO_API WaitWhile : public YieldInstruction {
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

class SHUSHAO_API WaitUntil : public YieldInstruction {
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

class SHUSHAO_API Coroutine : public YieldInstruction {
    friend class Component;
    friend class Program;

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
