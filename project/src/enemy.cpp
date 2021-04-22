#include "enemy.h"

namespace enemy {
    enemy::enemy() : x(0), y(0), health(0), damage(0) {}

    enemy::enemy(const std::string& enemy_name, const int x, const int y) : x(x), y(y), enemy_name(enemy_name) {
        if (enemy_name == "wolf") {
            health = 6;
            damage = 11;
        }
        if (enemy_name == "dog") {
            health = 3;
            damage = 6;
        }
        if (enemy_name == "rat") {
            health = 2;
            damage = 4;
        }
    }

    int enemy::get_x() const {
        return x;
    }

    int enemy::get_y() const {
        return y;
    }

    std::string enemy::get_name() const {
        return enemy_name;
    }

    int enemy::get_health() const {
        return health;
    }

    int enemy::get_damage() const {
        return damage;
    }

    void enemy::take_damage() {
        --health;
    }
}  // namespace enemy
