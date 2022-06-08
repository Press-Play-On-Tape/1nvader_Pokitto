#pragma once

#define _SOUNDS
#define COOKIE_INITIALISED 39

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}

enum class TitleScreenMode : uint8_t {
    NewGame,
    LevelSelect,
    SoundEffects
};

inline TitleScreenMode &operator++(TitleScreenMode &c ) {
    c = static_cast<TitleScreenMode>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline TitleScreenMode operator++(TitleScreenMode &c, int ) {
    TitleScreenMode result = c;
    ++c;
    return result;
}

inline TitleScreenMode &operator--(TitleScreenMode &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<TitleScreenMode>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<TitleScreenMode>( 3 );
    }
    return c;
}

inline TitleScreenMode operator--(TitleScreenMode &c, int ) {
    TitleScreenMode result = c;
    --c;
    return result;
}

enum class SoundEffect : uint8_t {
    Tone_00,
    Tone_01,
    Tone_02,
    Tone_03,
    Tone_04,
    Tone_05,
    Tone_06,
    Tone_07,
    Tone_08,
    Tone_09,
};
