#pragma once
#include "../game.hpp"

#include <filesystem>

class game::Song {
private:
    std::string name;
    std::string coverPath;
    std::string songPath;
    std::string mapPath;

public:
    std::string getName() {
        return name;
    }

    std::string getCoverPath() {
        return coverPath;
    }

    std::string getSongPath() {
        return songPath;
    }

    std::string getMapPath() {
        return mapPath;
    }

    Song(const std::string name) {
        this->name = name;

        for (auto file : std::filesystem::directory_iterator("maps/" + name)) {
            if (file.is_directory()) {
                continue;
            }

            if (file.path().filename().replace_extension("").string() == "song") {
                songPath = file.path().string();
            }
            else if (file.path().filename().replace_extension("").string() == "cover") {
                coverPath = file.path().string();
            }
            else if (file.path().filename().replace_extension("").string() == "map") {
                mapPath = file.path().string();
            }
        }
    }
};

std::vector<game::Song> game::getSongs() {
    std::vector<Song> songs;

    for (auto file : std::filesystem::directory_iterator("maps")) {
        if (file.is_directory() && file.path().filename() != "." && file.path().filename() != "..") {
            songs.push_back(file.path().filename().string());
        }
    }

    return songs;
}

namespace game { Song *mapToLoad; }