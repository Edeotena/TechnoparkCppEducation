#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include "player.h"
#include "enemy.h"
#include "armor.h"

#define WRONG_INPUT (-1)

namespace map {
class map {
 private:
    int size_of_x;
    int size_of_y;
    player::player our_player;
    std::vector <enemy::enemy> enemies;
    std::vector <armor::armor> armors_on_map;
    int current_enemy = -1;
    int current_armor = -1;

 public:
    explicit map(const std::string& filename);

    ~map() = default;

    int get_x() const;

    int get_y() const;

    void show_actions(bool is_empty, bool is_armor);

    void make_actions(const std::string& action);

    int get_player_health() const;
};
}  // namespace map
