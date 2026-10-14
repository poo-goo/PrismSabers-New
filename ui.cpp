#include "ui.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "bsml/shared/BSML-Lite.hpp"
#include "config.hpp"

using namespace UnityEngine;

namespace PrismSabers {
    namespace {
        void Header(Transform* parent, std::string_view text) {
            BSML::Lite::CreateText(parent, fmt::format("<b><color=#7fdcff>{}</color></b>", text), TMPro::FontStyles::Normal, 5.0f);
        }

#define LAYER_UI(p)                                                         \
    AddConfigValueToggle(parent, c.p##Enabled);                             \
    AddConfigValueIncrementEnum(parent, c.p##ColorSource, ColorSourceNames); \
    AddConfigValueColorPicker(parent, c.p##CustomColor);                    \
    AddConfigValueSliderIncrement(parent, c.p##Duration, 0.005f, 0.005f, 1.5f); \
    AddConfigValueSliderIncrement(parent, c.p##Opacity, 0.05f, 0.0f, 1.0f); \
    AddConfigValueIncrementInt(parent, c.p##Granularity, 2, 2, 96);         \
    AddConfigValueSliderIncrement(parent, c.p##BaseOffset, 0.01f, 0.0f, 1.0f); \
    AddConfigValueSliderIncrement(parent, c.p##TipOffset, 0.01f, 0.0f, 1.5f); \
    AddConfigValueSliderIncrement(parent, c.p##Fade, 0.1f, 0.1f, 6.0f);     \
    AddConfigValueSliderIncrement(parent, c.p##WhiteHead, 0.01f, 0.0f, 1.0f);

        void Build(Transform* host);

        void Rebuild(Transform* host) {
            for (int i = host->get_childCount() - 1; i >= 0; i--)
                Object::Destroy(host->GetChild(i)->get_gameObject());
            Build(host);
        }

        void Build(Transform* host) {
            auto& c = getConfig();
            auto scroll = BSML::Lite::CreateScrollableSettingsContainer(host);
            auto parent = scroll->get_transform();

            Header(parent, "PrismSabers");
            AddConfigValueToggle(parent, c.Enabled);
            AddConfigValueToggle(parent, c.HideVanillaTrail);
            AddConfigValueToggle(parent, c.PerformanceMode);

            Header(parent, "Presets");
            for (int i = 0; i < (int) PresetNames.size(); i++) {
                BSML::Lite::CreateUIButton(parent, PresetNames[i], [i, host]() {
                    ApplyPreset(i);
                    Rebuild(host);
                });
            }

            Header(parent, "Saber Colors");
            AddConfigValueIncrementEnum(parent, c.SaberColorMode, SaberColorModeNames);
            AddConfigValueColorPicker(parent, c.LeftColor);
            AddConfigValueColorPicker(parent, c.RightColor);
            AddConfigValueSliderIncrement(parent, c.RainbowSpeed, 0.05f, 0.0f, 3.0f);
            AddConfigValueSliderIncrement(parent, c.RainbowSaturation, 0.05f, 0.0f, 1.0f);
            AddConfigValueSliderIncrement(parent, c.RainbowOffset, 0.05f, 0.0f, 1.0f);
            AddConfigValueSliderIncrement(parent, c.GlowIntensity, 0.05f, 0.0f, 3.0f);

            Header(parent, "Main Trail");
            LAYER_UI(Main)
            Header(parent, "Aura Trail");
            LAYER_UI(Glow)
            Header(parent, "Motion Blur");
            LAYER_UI(Blur)
            AddConfigValueSliderIncrement(parent, c.BlurMinSpeed, 0.5f, 0.0f, 20.0f);
            AddConfigValueSliderIncrement(parent, c.BlurFullSpeed, 0.5f, 0.5f, 30.0f);

            Header(parent, "Saber Model (visual only)");
            AddConfigValueIncrementVector3(parent, c.PositionOffset, 1, 0.5);
            AddConfigValueIncrementVector3(parent, c.RotationOffset, 0, 5.0);
            AddConfigValueSliderIncrement(parent, c.LengthScale, 0.05f, 0.25f, 2.0f);
            AddConfigValueSliderIncrement(parent, c.ThicknessScale, 0.05f, 0.25f, 3.0f);

            Header(parent, "Effects");
            AddConfigValueSliderIncrement(parent, c.CutSparkles, 0.1f, 0.0f, 4.0f);
            AddConfigValueSliderIncrement(parent, c.CutExplosion, 0.1f, 0.0f, 4.0f);
            AddConfigValueSliderIncrement(parent, c.CutLifetime, 0.1f, 0.1f, 3.0f);
            AddConfigValueIncrementEnum(parent, c.CutColorMode, CutColorModeNames);
            AddConfigValueToggle(parent, c.ClashEffect);
            AddConfigValueToggle(parent, c.BurnMarks);
            AddConfigValueToggle(parent, c.BurnSparkles);
        }
    }

    void SettingsDidActivate(HMUI::ViewController* self, bool firstActivation, bool, bool) {
        if (firstActivation)
            Build(self->get_transform());
    }
}
