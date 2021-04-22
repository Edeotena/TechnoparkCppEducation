#pragma  once

#include <string>

namespace enemy {
class enemy {
 private:
    int x, y;
    int health;
    int damage;
    std::string enemy_name;

 public:
    enemy();

    enemy(const std::string& enemy_name, const int x, const int y);

    int get_x() const;

    int get_y() const;

    std::string get_name() const;

    int get_health() const;

    int get_damage() const;

    void take_damage();
};
}  // namespace enemy
