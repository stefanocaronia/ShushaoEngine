# Shushao Engine

## How to build

* make
* make run
* make rebuild
* make clean
* make BUILD=Release

## Resources


## Components

### Sprite Renderer
### Mesh Renderer
### Light
### Transform
### Canvas
### Text

```c++
// componente text su una normale entity
Entity* label = AddEntity("Label");
Text* text = label->AddComponent<Text>();
text->sortingLayerID = Config::SortingLayers["UI"];
text->alignToGeometry = true;
text->SetFont(f)->SetText("Hello game engine!")->SetColor(Color::blue)->SetSize(0.5f);
text->transform->SetPivot(PivotPosition::TOPLEFT);
text->transform->rectTransform->SetRectSize({8,3});
text->transform->SetLocalPosition({5, -1, 0});

// Componente text in una canvas
Text* text1 = canvas->AddComponent<Text>();
text1->alignToGeometry = true;
text1->sortingLayerID = Config::SortingLayers["Background"];
text1->SetFont(f)->SetText("Hello game engine!")->SetColor(Color::red)->SetSize(0.5f);
text1->SetAlign(Align::TOPLEFT);
```

### Raw Image
### Image

## UI

### Canvas

```c++
Entity* canvas = AddEntity<ui::Canvas>("Canvas");
canvas->GetComponent<Canvas>()->SetRenderMode(RenderMode::WORLD);
canvas->transform->rectTransform->SetRectSize({10,4});
canvas->transform->SetLocalPosition({-1, 0, 0});
canvas->transform->SetPivot(PivotPosition::CENTER);
```

### Text

```c++
// Label in una canvas ancorata a un singolo punto
ui::Text* uiText = AddEntity<ui::Text>("Label su canvas");
uiText->setParent(canvas);
uiText->transform->SetPivot(PivotPosition::BOTTOMLEFT);
uiText->transform->rectTransform->SetAnchor({0.5f, 0.5f});
uiText->transform->rectTransform->SetRectSize({4, 1});
uiText->transform->SetLocalPosition({-2, -2, 0});
uiText->transform->SetPivot(PivotPosition::BOTTOMRIGHT);
auto tComp = uiText->GetComponent<Text>();
tComp->SetFont(f)->SetText("Label su canvas")->SetColor(Color::green)->SetSize(0.5f)->SetAlign(Align::CENTER);

// Text label in una child entity - ancorata diversamente
ui::Text* anchoredText = AddEntity<ui::Text>("Label 2");
anchoredText->setParent(canvas);
anchoredText->transform->SetPivot(PivotPosition::CENTER);
anchoredText->transform->rectTransform->SetAnchorMax({1, 1});
anchoredText->transform->rectTransform->SetAnchorMin({0, 1});
anchoredText->transform->rectTransform->RegisterPositionLRYH(1.0f, 1.0f, -1.0f, 1.0f);

```

### Raw Image
### Image


https://guides.github.com/features/mastering-markdown/
alt + 96