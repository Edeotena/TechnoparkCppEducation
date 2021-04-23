#pragma once

namespace player {
class player {
 private:
    int health = 100;
    int x = 0, y = 0;
    int armor_count = 0, weight = 0;
    bool armor_equipment[5];

 public:
    player();

    ~player() = default;

    void move_x(const int x);

    void move_y(const int y);

    int get_x() const;

    int get_y() const;

    int get_health() const;

    void take_damage(const int damage);

    int get_armor() const;

    bool have_armor(const int armor_number) const;

    bool add_armor(const int armor_number, const int armor_count, const int armor_weight);

    bool throw_armor(const int armor_number, const int armor_count, const int armor_weight);
};
}  // namespace player
