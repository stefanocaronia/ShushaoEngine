#include "debuginfo.h"
#include "color.h"
#include "utility.h"
#include "resources.h"
#include "ui/text.h"

namespace se {

void DebugInfo::Awake() {
    Font* consolas = Resources::Get<Font>("consolas");

    ui::Text* uiText = entity->AddChild<ui::Text>("time measures");
    uiText->transform->SetPivot(PivotPosition::TOPLEFT);
    uiText->transform->rectTransform->SetAnchor(AnchorPreset::TOPLEFT);
    uiText->transform->rectTransform->SetRectSize({3, 4});

    times = uiText->GetComponent<Text>();
	times->sortingLayerID = Config::SortingLayers.over();
	times->SetFont(consolas)->SetColor(color::white)->SetSize(0.2f);
    times->SetText("ciao consolas");
    times->SetLinespace(6);
}

void DebugInfo::Update() {
    std::string fr = std::string("Frame Rate: ") + util::toString(Time::frameRate);
    std::string ut = std::string("Update Time: ") + util::toString(Time::deltaTime);
    std::string ft = std::string("Fixed Time: ") + util::toString(Time::fixedDeltaTime);
    std::string rt = std::string("Render Time: ") + util::toString(Time::renderDeltaTime);
    std::vector<Text::Line> lines = {
		{fr, color::white},
        {ut, color::green},
        {ft, color::magenta},
        {rt, color::yellow}
	};
    times->SetLines(lines);

}

}  // namespace se