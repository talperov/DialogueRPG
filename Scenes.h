#pragma once
#include "Dialogue.h"
#include <vector>

// Struct for a game scene with dialogue.
struct Scene {
    std::vector<Dialogue::DialogueLine> dialogueLines;  // Lines of dialogue.
    bool showCharacters;                                // Whether to show characters after dialogue.
};

// Intro scene for left character.
extern Scene animeIntroLeft;

// Intro scene for right character.
extern Scene animeIntroRight;

// Battle start scene.
extern Scene sceneBattleStart;

// Example scene.
extern Scene sceneExample;