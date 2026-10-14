# PrismSabers

Quest (Scotland2) mod for Beat Saber 1.45.2. It replaces the stock saber trail with three spline trail layers you can configure separately, adds speed-based motion blur, and lets you customise saber colours, glow, the saber model and hit effects.

## Features
- **Main trail / Aura / Motion Blur**: three layers you configure separately. Each has its own length, smoothness, start/end position along the blade, opacity, fade curve, white-hot head, and colour source (Saber, Custom, Rainbow, or a Saber > Custom gradient).
- **Motion blur**: a short, dense trail that only shows up when the blade moves fast. It starts appearing at *Blur Start Speed* and reaches full opacity at *Blur Full Speed* (tip speed in m/s).
- **Saber colours**: use the game's colours, set your own per hand, or cycle a rainbow (speed, saturation, and hue offset between hands). Blade glow intensity is adjustable.
- **Saber model (visual only)**: position and rotation offsets, plus blade length and thickness scale. Hitboxes are not changed.
- **Effects**: multipliers for cut sparkle count, explosion count and particle lifetime; cut particle colour (Saber, White or Rainbow); toggles for the clash effect, floor burn marks and burn sparkles.
- **Presets**: Prism, Neon, Silk, Inferno, Vanilla+, Potato.
- Settings save to JSON and take effect right away. Open them from *Mod Settings → PrismSabers*.

## Performance
- Each layer is a single dynamic mesh using the game's own trail material, so there are no extra shaders or render passes.
- Mesh buffers are only reallocated when you change a layer's smoothness. Normal frames do not allocate.
- Saber positions are stored in a fixed 256-sample ring buffer and smoothed with Catmull-Rom splines, so trails stay smooth even at low sample rates.
- Hidden layers are skipped completely. Turning off burn marks, sparkles or clash skips their update code.
- *Performance Mode* caps smoothness at 12 segments and turns off motion blur.

## Build
```
qpm restore
cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -B build && cmake --build build
qpm qmod zip
```
