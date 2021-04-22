#include "player.h"

namespace player {
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
        health -= damage;
    }
}  // namespace player
