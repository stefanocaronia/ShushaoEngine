#include "debuginfo.h"
#include "color.h"
#include "utility.h"
#include "resources.h"
#include "ui/text.h"

namespace se {

void DebugInfo::Awake() {
    Font* consolas = Resources::Get<Font>("Modenine");

    ui::Text* uiText = entity->AddChild<ui::Text>("time measures");
    uiText->transform->SetPivot(PivotPosition::TOPLEFT);
    uiText->transform->rectTransform->SetAnchor(AnchorPreset::TOPLEFT);
    uiText->transform->rectTransform->SetRectSize({3, 4});

    times = uiText->GetComponent<Text>();
	times->sortingLayerID = Config::SortingLayers.over();
	times->SetFont(consolas)->SetColor(color::white)->SetSize(0.3f);
    times->SetText("ciao consolas");
}

void DebugInfo::Update() {
    //#ifdef ASD
    std::string fr = "Frame Rate: " + util::toString(frameRate);
    std::string ut = "Update Time: " + util::toString(updateTime);
    std::string rt = "Render Time: " + util::toString(renderTime);
    std::vector<Text::Line> lines = {
		{fr, color::white},
        {ut, color::green},
        {rt, color::yellow}
	};
    times->SetLines(lines);
    //#endif
}

}  // namespace se
