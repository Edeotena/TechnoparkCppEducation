#pragma once

namespace player {
class player {
 private:
    int health = 100;
    int x = 0, y = 0;

 public:
    void move_x(const int x);

    void move_y(const int y);

    int get_x() const;

    int get_y() const;

    int get_health() const;

    void take_damage(const int damage);
};

}  // namespace player
