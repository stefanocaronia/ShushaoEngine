#include "debuginfo.h"
#include "color.h"
#include "utility.h"
#include "resources.h"
#include "ui/text.h"

namespace se {

void DebugInfo::Awake() {
    Font* font = Resources::Get<Font>("consolas");

    ui::Text* uiText = entity->AddChild<ui::Text>("Benchmark");
    uiText->transform->SetPivot(PivotPosition::TOPLEFT);
    uiText->transform->rectTransform->SetAnchor(AnchorPreset::TOPLEFT);
    uiText->transform->rectTransform->SetRectSize({4, 1});

    times = uiText->GetComponent<Text>();
	times->sortingLayerID = Config::SortingLayers.over();
	times->SetFont(font)->SetColor(color::white)->SetSize(22);
    times->SetLineSpace(0.0f);
    //times->SetLineheight(24);

    /* std::string fr = "ABC 123456";
    std::string ut = "afa 123456";
    std::string ft = "agh 123456";
    std::string rt = "1df 123456";

    std::vector<Text::Line> lines = {
		{fr, color::white},
        {ut, color::green},
        {ft, color::magenta},
        {rt, color::yellow}
	};
    times->SetLines(lines); */
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
