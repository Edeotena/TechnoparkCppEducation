#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include "player.h"
#include "enemy.h"

#define WRONG_INPUT (-1)

namespace map {
class map {
 private:
    int size_of_x;
    int size_of_y;
    player::player our_player;
    std::vector <enemy::enemy> enemies;
    int current_enemy = -1;

 public:
    explicit map(const std::string& filename);

    bool show_actions();

    void make_actions(const std::string& action);

    int get_player_health() const;
};
}  // namespace map
