#include "player.h"

namespace player {
    player::player() {
        for (int i = 0; i < 5; ++i) {
            armor_equipment[i] = false;
        }
    }

    void player::move_x(const int x) {
        this->x += x;
    }

    void player::move_y(const int y) {
        this->y += y;
    }

    int player::get_x() const {
        return x;
    }

    int player::get_y() const {
        return y;
    }

    int player::get_health() const {
        return health;
    }

    void player::take_damage(const int damage) {
        if (armor_count >= damage) {
            --health;
            return;
        }
        health -= damage - armor_count;
    }

    int player::get_armor() const {
        return armor_count;
    }

    bool player::have_armor(const int armor_number) const {
        if (armor_equipment[armor_number]) {
            return true;
        }
        return false;
    }

    bool player::add_armor(const int armor_number, const int armor_count, const int armor_weight) {
        if (!armor_equipment[armor_number] && this->armor_count + armor_count <= 20) {
            armor_equipment[armor_number] = true;
            this->armor_count += armor_count;
            weight += armor_weight;
            return true;
        }
        return false;
    }

    bool player::throw_armor(const int armor_number, const int armor_count, const int armor_weight) {
        if (armor_equipment[armor_number]) {
            armor_equipment[armor_number] = false;
            this->armor_count -= armor_count;
            weight -= armor_weight;
            return true;
        }
        return false;
    }
}  // namespace player
