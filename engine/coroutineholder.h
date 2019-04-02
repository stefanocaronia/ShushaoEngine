#pragma once

/*
    Credits: https://github.com/exawon/CoroBehaviour
*/

#include <set>
#include "coroutine.h"

namespace se {

class CoroutineHolder {
  public:
    virtual ~CoroutineHolder();

  private:
    std::set<Coroutine*> Coroutines;

  public:
    Coroutine* StartCoroutine(Routine InRoutine);
    void StopCoroutine(Coroutine* CoroutinePtr);
    void StopAllCoroutines();
    bool HasCoroutines();

  private:
    Coroutine* CastAsCoroutine(YieldInstruction* YieldInstructionPtr);
    bool YieldCoroutine(Coroutine* CoroutinePtr);
    Coroutine* PushCoroutine(Coroutine* CoroutinePtr);
    Coroutine* PopCoroutine(Coroutine* CoroutinePtr);

  protected:
    void ResumeCoroutines();
};

}  // namespace se

/* EXAMPLE

class ExampleClass : public Component
{
    void Start() {
        StartCoroutine(coroutineA());
    }

    Routine coroutineA()
    {
        return [=](RoutinePush& yield_return)
        {
            // wait for 1 second
            std::cout << "coroutineA created";
            yield_return(new WaitForSeconds(1.0f));
            yield_return(StartCoroutine(coroutineB()));
            std::cout << "coroutineA running again";
        };
    }

    Routine coroutineB()
    {
        return [=](RoutinePush& yield_return)
        {
            std::cout << "coroutineB created";
            yield_return(new WaitForSeconds(2.5f));
            std::cout << "coroutineB enables coroutineA to run";
        };
    }
}
*/