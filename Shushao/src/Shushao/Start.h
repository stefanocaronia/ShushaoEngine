#pragma once

#include "Shushao/Application.h"
#include "Shushao/debug.h"

extern se::Application* se::CreateApplication();

int main(int argc, char** argv) {
    auto app = se::CreateApplication();
    app->Init();

    DEBUG_INFO("Test");

    app->Run();

    delete app;
}
