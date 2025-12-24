#include "Scenes.h"

// Intro scene – Left character speaks first.
Scene animeIntroLeft = {
    {
        { "What is THIS!?!?\nWho are you standing beside me?", Dialogue::DialogueLine::Speaker::LEFT }
    },
    true  // Reveal left character after dialogue.
};

// Right character (Greek) introduction.
Scene animeIntroRight = {
    {
        { "Ah! I see you finally arrived!\nI am Greek, your ally!", Dialogue::DialogueLine::Speaker::RIGHT }
    },
    true  // Reveal right character after dialogue.
};

// Battle start dialogue.
Scene sceneBattleStart = {
    {
        { "We must fight together!\nChoose your move wisely.", Dialogue::DialogueLine::Speaker::LEFT },
        { "I’ve got your back!\nLet’s do this!", Dialogue::DialogueLine::Speaker::RIGHT }
    },
    true  // Both characters visible.
};

// Example scene.
Scene sceneExample = {
    {
        { "This is a test scene for the dialogue system.", Dialogue::DialogueLine::Speaker::LEFT },
        { "Right character response goes here.", Dialogue::DialogueLine::Speaker::RIGHT }
    },
    true
};