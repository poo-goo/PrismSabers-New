#pragma once

#include "config-utils/shared/config-utils.hpp"

namespace PrismSabers {
    enum ColorSource { SaberColor = 0, CustomColor = 1, Rainbow = 2, SaberToCustom = 3 };
    inline std::vector<std::string> const ColorSourceNames = {"Saber", "Custom", "Rainbow", "Saber > Custom"};
    inline std::vector<std::string> const SaberColorModeNames = {"Game", "Custom", "Rainbow"};
    inline std::vector<std::string> const CutColorModeNames = {"Saber", "White", "Rainbow"};
}

#define TRAIL_LAYER(p, label, en, dur, gran, base, tip, op, fade, white, src, ...)                                                             \
    CONFIG_VALUE(p##Enabled, bool, label " Enabled", en);                                                                                     \
    CONFIG_VALUE(p##Duration, float, label " Length (s)", dur, "How long the layer persists behind the blade");                              \
    CONFIG_VALUE(p##Granularity, int, label " Smoothness", gran, "Number of spline segments. Higher = smoother, slightly more GPU work");   \
    CONFIG_VALUE(p##BaseOffset, float, label " Start", base, "Where the layer starts along the blade (0 = hilt, 1 = tip)");                 \
    CONFIG_VALUE(p##TipOffset, float, label " End", tip, "Where the layer ends along the blade (1 = tip, >1 extends past it)");              \
    CONFIG_VALUE(p##Opacity, float, label " Opacity", op);                                                                                    \
    CONFIG_VALUE(p##Fade, float, label " Fade Curve", fade, "Falloff exponent. 1 = linear, higher = faster fade");                          \
    CONFIG_VALUE(p##WhiteHead, float, label " White Head", white, "Fraction of the layer near the blade that blends to white-hot");         \
    CONFIG_VALUE(p##ColorSource, int, label " Color", src);                                                                                   \
    CONFIG_VALUE(p##CustomColor, UnityEngine::Color, label " Custom Color", UnityEngine::Color(__VA_ARGS__));

DECLARE_CONFIG(Config) {
    CONFIG_VALUE(Enabled, bool, "Enable PrismSabers", true);
    CONFIG_VALUE(HideVanillaTrail, bool, "Hide Vanilla Trail", true, "Replace the stock trail with PrismSabers layers");
    CONFIG_VALUE(PerformanceMode, bool, "Performance Mode", false, "Caps smoothness at 12 and disables motion blur");

    // Saber colors
    CONFIG_VALUE(SaberColorMode, int, "Saber Color Mode", 0);
    CONFIG_VALUE(LeftColor, UnityEngine::Color, "Left Saber Color", UnityEngine::Color(1.0f, 0.1f, 0.35f, 1.0f));
    CONFIG_VALUE(RightColor, UnityEngine::Color, "Right Saber Color", UnityEngine::Color(0.1f, 0.6f, 1.0f, 1.0f));
    CONFIG_VALUE(RainbowSpeed, float, "Rainbow Speed", 0.35f, "Hue cycles per second");
    CONFIG_VALUE(RainbowSaturation, float, "Rainbow Saturation", 0.9f);
    CONFIG_VALUE(RainbowOffset, float, "Rainbow Hand Offset", 0.5f, "Hue offset between left and right saber");
    CONFIG_VALUE(GlowIntensity, float, "Blade Glow Intensity", 1.0f);

    // Layers
    TRAIL_LAYER(Main, "Trail", true, 0.30f, 40, 0.0f, 1.0f, 0.9f, 1.6f, 0.06f, 0, 1.0f, 1.0f, 1.0f, 1.0f)
    TRAIL_LAYER(Glow, "Aura", true, 0.18f, 24, 0.55f, 1.06f, 0.35f, 2.4f, 0.0f, 0, 1.0f, 0.85f, 0.4f, 1.0f)
    TRAIL_LAYER(Blur, "Motion Blur", true, 0.045f, 16, 0.0f, 1.0f, 0.55f, 1.2f, 0.25f, 0, 1.0f, 1.0f, 1.0f, 1.0f)
    CONFIG_VALUE(BlurMinSpeed, float, "Blur Start Speed", 2.0f, "Tip speed (m/s) where blur starts to appear");
    CONFIG_VALUE(BlurFullSpeed, float, "Blur Full Speed", 9.0f, "Tip speed (m/s) where blur reaches full opacity");

    // Saber model
    CONFIG_VALUE(PositionOffset, UnityEngine::Vector3, "Position Offset (cm)", UnityEngine::Vector3(0, 0, 0));
    CONFIG_VALUE(RotationOffset, UnityEngine::Vector3, "Rotation Offset (deg)", UnityEngine::Vector3(0, 0, 0));
    CONFIG_VALUE(LengthScale, float, "Blade Length", 1.0f, "Visual only, hitboxes are unchanged");
    CONFIG_VALUE(ThicknessScale, float, "Blade Thickness", 1.0f, "Visual only, hitboxes are unchanged");

    // Effects
    CONFIG_VALUE(CutSparkles, float, "Cut Sparkles", 1.0f, "Multiplier for sparkle particles on note cuts");
    CONFIG_VALUE(CutExplosion, float, "Cut Explosion", 1.0f, "Multiplier for explosion particles on note cuts");
    CONFIG_VALUE(CutLifetime, float, "Cut Particle Lifetime", 1.0f);
    CONFIG_VALUE(CutColorMode, int, "Cut Particle Color", 0);
    CONFIG_VALUE(ClashEffect, bool, "Saber Clash Effect", true);
    CONFIG_VALUE(BurnMarks, bool, "Floor Burn Marks", true);
    CONFIG_VALUE(BurnSparkles, bool, "Floor Burn Sparkles", true);
};

#undef TRAIL_LAYER

namespace PrismSabers {
    void ApplyPreset(int preset);
    inline std::vector<std::string> const PresetNames = {"Prism (default)", "Neon", "Silk", "Inferno", "Vanilla+", "Potato (max FPS)"};
}
