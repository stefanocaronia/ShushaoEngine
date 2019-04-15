#include "debuginfo.h"
#include "color.h"
#include "resources.h"
#include "ui/text.h"
#include "utility.h"

namespace se {

void DebugInfo::Awake() {
    Font* font = Resources::Get<Font>("consolas");

    ui::Text* uiText = entity->AddChild<ui::Text>("Benchmark");
    uiText->transform->SetPivot(PivotPosition::TOPLEFT);
    uiText->transform->rectTransform->SetAnchor(AnchorPreset::TOPLEFT);
    uiText->transform->rectTransform->SetRectSize({4, 6});

    times = uiText->GetComponent<Text>();
    times->sortingLayerID = Config::SortingLayers.over();
    times->SetFont(font)->SetColor(color::white)->SetSize(22)->SetWordWrap(true)->SetAlign(Align::RIGHT);
    times->SetLineHeight(1.2f);
    times->SetText(L"Questa è una prova di\nQuesta è una  di scrittura\nQuesta è una prova scrittura\nQuesta è una prova di scrittura\n");
}

void DebugInfo::Update() {
    return;
    std::wstring fr = std::wstring(L"Frame Rate: ") + util::toWstring(Time::frameRate) + std::wstring(L"\n");
    std::wstring ut = std::wstring(L"Update Time: ") + util::toWstring(Time::deltaTime) + std::wstring(L"\n");
    std::wstring ft = std::wstring(L"Fixed Time: ") + util::toWstring(Time::fixedDeltaTime) + std::wstring(L"\n");
    std::wstring rt = std::wstring(L"Render Time: ") + util::toWstring(Time::renderDeltaTime) + std::wstring(L"\n");

    times->SetText(fr + ut + ft + rt);
}

}  // namespace se
