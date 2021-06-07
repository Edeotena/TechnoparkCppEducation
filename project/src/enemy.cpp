#include "enemy.h"

namespace enemy {
    enemy::enemy() : x(0), y(0), health(0), damage(0) {}

    enemy::enemy(const std::string& enemy_name, const int x, const int y) : x(x), y(y), enemy_name(enemy_name) {
        if (enemy_name == ENEMY_NAME_ARRAY[WOLF]) {
            health = WOLF_HEALTH;
            damage = WOLF_DAMAGE;
        }
        if (enemy_name == ENEMY_NAME_ARRAY[DOG]) {
            health = DOG_HEALTH;
            damage = DOG_DAMAGE;
        }
        if (enemy_name == ENEMY_NAME_ARRAY[RAT]) {
            health = RAT_HEALTH;
            damage = RAT_DAMAGE;
        }
    }

    int enemy::get_x() const {
        return x;
    }

    int enemy::get_y() const {
        return y;
    }

    void enemy::set_damage(const int damage) {
        this->damage = damage;
    }

    void enemy::set_health(const int health) {
        this->health = health;
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
