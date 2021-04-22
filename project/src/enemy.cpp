#include "map.h"

namespace map {
    map::map(const std::string& filename) {
        try {
            std::ifstream map_file(filename);
            map_file >> size_of_x >> size_of_y;
            int x, y;
            std::string ivent;
            while (map_file >> x >> y >> ivent) {
                if (ivent == "wolf" || ivent == "dog" || ivent == "rat") {
                    enemy::enemy new_enemy(ivent, x, y);
                    enemies.push_back(new_enemy);
                }
            }
        }
        catch (const std::ifstream::failure& ex) {
            throw(std::ifstream::failure("file reading error"));
        }
    }

    bool map::show_actions() {
        int supported_actions = 0;

        if (current_enemy != -1) {
            ++supported_actions;
            std::cout << "Supported actions:\n * kick enemy\n";
        } else {
            std::cout << "Supported actions:\n";
            if (our_player.get_x() > 0) {
                std::cout << " * move left\n";
                ++supported_actions;
            }
            if (our_player.get_x() != size_of_x - 1) {
                std::cout << " * move right\n";
                ++supported_actions;
            }
            if (our_player.get_y() > 0) {
                std::cout << " * move down\n";
                ++supported_actions;
            }
            if (our_player.get_y() != size_of_y - 1) {
                std::cout << " * move up\n";
                ++supported_actions;
            }
        }

        if (!supported_actions) {
            std::cout << std::endl;
        }

        std::cout << our_player.get_x() << " x " << our_player.get_y() << ", hp: " << our_player.get_health() << " > ";
        if (supported_actions) {
            return true;
        }
        return false;
    }

    void map::make_actions(const std::string& action) {
    	size_t size = enemies.size();
        if (action == "move left") {
            our_player.move_x(-1);
        }
        if (action == "move right") {
            our_player.move_x(1);
        }
        if (action == "move down") {
            our_player.move_y(-1);
        }
        if (action == "move up") {
            our_player.move_y(1);
        }

        if (current_enemy == -1) {
            for (size_t i = 0; i < size; ++i) {
                if (enemies[i].get_health() > 0 && enemies[i].get_x() == our_player.get_x() && enemies[i].get_y() == our_player.get_y()) {
                    current_enemy = i;
                    std::cout << enemies[current_enemy].get_name() << " found, " << enemies[current_enemy].get_health() << " hp\n";
                }
            }
        }

        if (current_enemy == -1) {
               std::cout << "moved\n";
        }

        if (action == "kick enemy") {
            enemies[current_enemy].take_damage();
            if (enemies[current_enemy].get_health() > 0) {
                our_player.take_damage(enemies[current_enemy].get_damage());
                if (our_player.get_health() > 0) {
                    std::cout << "enemy kicked. Enemy hp: " << enemies[current_enemy].get_health() << std::endl;
                }
            } else {
                std::cout << "enemy killed\n";
                current_enemy = -1;
            }
        }
    }

    int map::get_player_health() const {
            return our_player.get_health();
        }

}  // namespace map
