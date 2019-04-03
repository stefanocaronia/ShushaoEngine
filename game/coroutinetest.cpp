#include "coroutinetest.h"

using namespace se;

void CoroutineTest::Start() {
    StartCoroutine(coroutineA());
}

Routine CoroutineTest::coroutineA() {
    return [=](RoutinePush& yield_return) {
        Debug::Log(WARNING) << "coroutineA created" << endl;
        yield_return(new WaitForSeconds(2.0f));
        yield_return(StartCoroutine(coroutineB()));
        Debug::Log(WARNING) << "coroutineA running again" << endl;
    };
}

Routine CoroutineTest::coroutineB() {
    return [=](RoutinePush& yield_return) {
        Debug::Log(WARNING) << "coroutineB created" << endl;
        yield_return(new WaitForSeconds(4.5f));
        Debug::Log(WARNING) << "coroutineB enables coroutineA to run" << endl;
    };
}