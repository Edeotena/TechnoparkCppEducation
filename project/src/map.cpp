#include "map.h"

namespace map {
    int map::get_x() const {
        return size_of_x;
    }

    int map::get_y() const {
        return size_of_y;
    }

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
                } else {
                    armor::armor new_armor(ivent, x, y);
                    armors_on_map.push_back(new_armor);
                }
            }
        }
        catch (const std::ifstream::failure& ex) {
            throw(std::ifstream::failure("file reading error"));
        }
    }

    void map::show_actions(bool is_empty) {
        bool action_made = false;
        bool enemy_fight = false;

        std::cout << std::endl;

        if (current_enemy != -1) {
            std::cout << " * kick enemy\n";
            action_made = true;
            enemy_fight = true;
        }

        if (our_player.get_x() > 0 && !enemy_fight) {
            std::cout << " * move left\n";
            action_made = true;
        }
        if (our_player.get_x() != size_of_x - 1 && !enemy_fight) {
            std::cout << " * move right\n";
            action_made = true;
        }
        if (our_player.get_y() > 0 && !enemy_fight) {
            std::cout << " * move down\n";
            action_made = true;
        }
        if (our_player.get_y() != size_of_y - 1 && !enemy_fight) {
            std::cout << " * move up\n";
            action_made = true;
        }

        if (is_empty && !action_made) std::cout << std::endl;


        if (current_armor != -1 && !our_player.have_armor(armors_on_map[current_armor].transport())) {
            std::cout << " * pick " << armors_on_map[current_armor].get_name() << std::endl;
        }
        if (current_armor != -1) {
            for (int i = 0; i < 5; ++i) {
                if (our_player.have_armor(i)) {
                    std::cout << " * throw " << armor::armor_name(i) << std::endl;
                }
            }
        }

        std::cout << our_player.get_x() << " x " << our_player.get_y() << ", hp: " << our_player.get_health() << ", armor: " << our_player.get_armor() << " > ";

        if (!is_empty) {
            std::cout << std::endl;
        }
    }

    void map::make_actions(const std::string& action) {
        if (action == "move left") {
            if (current_armor != -1) {
                armors_on_map[current_armor].armor_delete();
                current_armor = -1;
            }
            our_player.move_x(-1);
        }
        if (action == "move right") {
            if (current_armor != -1) {
                armors_on_map[current_armor].armor_delete();
                current_armor = -1;
            }
            our_player.move_x(1);
        }
        if (action == "move down") {
            if (current_armor != -1) {
                armors_on_map[current_armor].armor_delete();
                current_armor = -1;
            }
            our_player.move_y(-1);
        }
        if (action == "move up") {
            if (current_armor != -1) {
                armors_on_map[current_armor].armor_delete();
                current_armor = -1;
            }
            our_player.move_y(1);
        }

        if (current_enemy == -1 && current_armor == -1) {
            for (size_t i = 0; i < enemies.size(); ++i) {
                if (enemies[i].get_health() > 0 && enemies[i].get_x() == our_player.get_x() && enemies[i].get_y() == our_player.get_y()) {
                    current_enemy = i;
                    std::cout << enemies[current_enemy].get_name() << " found, " << enemies[current_enemy].get_health() << " hp\n";
                }
            }
               for (size_t i = 0; i < armors_on_map.size(); ++i) {
                if (armors_on_map[i].get_x() == our_player.get_x() && armors_on_map[i].get_y() == our_player.get_y()) {
                    current_armor = i;
                    std::cout << armors_on_map[current_armor].get_name() << " found\n";
                }
             }
        }

        if (current_enemy == -1 && current_armor == -1) {
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

        if (action.find("pick") == 0) {
            if (our_player.add_armor(armors_on_map[current_armor].transport(), armors_on_map[current_armor].transport_armor(), armors_on_map[current_armor].transport_weight())) {
                std::cout << "clothes worn\n";
                armors_on_map[current_armor].armor_delete();
                current_armor = -1;
            } else {
                std::cout << "you can't pick this up\n";
            }
        }
        if (action.find("throw") == 0) {
            std::string item = action.substr(6);
            armor::armor new_armor(item, -1, -1);
            if (our_player.throw_armor(new_armor.transport(), new_armor.transport_armor(), new_armor.transport_weight())) {
                std::cout << "the " << item << " is thrown out\n";
            } else {
                std::cout << "you haven't this item\n";
            }
        }
    }

    int map::get_player_health() const {
            return our_player.get_health();
        }

}  // namespace map
