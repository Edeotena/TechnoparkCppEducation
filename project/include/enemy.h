#pragma  once

#include <string>

namespace enemy {
#define MAX_ENEMY_COUNT 3

enum ENEMY_NUMBER_ENUM {
    WOLF = 0,
    DOG = 1,
    RAT = 2
};

enum ENEMY_HEALTH_ENUM {
    RAT_HEALTH = 2,
    DOG_HEALTH = 3,
    WOLF_HEALTH = 6
};

enum ENEMY_DAMAGE_ENUM {
    RAT_DAMAGE = 4,
    DOG_DAMAGE  = 6,
    WOLF_DAMAGE = 11
};

class enemy {
 private:
    int x, y;
    int health;
    int damage;
    std::string enemy_name;
    std::string ENEMY_NAME_ARRAY[MAX_ENEMY_COUNT] = {"wolf", "dog", "rat"};

 public:
    enemy();

    enemy(const std::string& enemy_name, const int x, const int y);

    ~enemy() = default;

    int get_x() const;

    int get_y() const;

    void set_damage(const int damage);

    void set_health(const int health);

    std::string get_name() const;

    int get_health() const;

    int get_damage() const;

    void take_damage();
};
}  // namespace enemy