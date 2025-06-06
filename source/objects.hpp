#pragma once
#include "util.hpp"

namespace objects {
    class TitleLogo;
    class TitleText;
    class SongCover;
    class SongText;
    class BgFlash;
    class Cursor;
    class BlackFade;
    class Note;
    class EventTimer;
    class Player;

    namespace templates {
        class Rect;
        class Text;
        class Sprite;
    }
}

#include "objects/templates/rect.cpp"
#include "objects/templates/text.cpp"
#include "objects/templates/sprite.cpp"

#include "objects/titlelogo.cpp"
#include "objects/titletext.cpp"
#include "objects/songcover.cpp"
#include "objects/songtext.cpp"
#include "objects/blackfade.cpp"
#include "objects/bgflash.cpp"
#include "objects/note.cpp"
#include "objects/eventtimer.cpp"
#include "objects/player.cpp"