#pragma once
#include "util.hpp"

namespace objects {
    class TitleLogo;
    class TitleText;
    class SongCover;
    class SongText;
    class BgReact;

    namespace templates {
        class Rect;
        class Text;
    }
}

#include "objects/templates/rect.cpp"
#include "objects/templates/text.cpp"

#include "objects/titlelogo.cpp"
#include "objects/titletext.cpp"
#include "objects/songcover.cpp"
#include "objects/songtext.cpp"
#include "objects/bgreact.cpp"