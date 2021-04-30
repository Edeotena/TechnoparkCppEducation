#pragma once

#include <string>

namespace armor {
#define MAX_ARMOR_COUNT 5

enum ARMOR_NUMBER_ENUM {
    TSHIRT = 0,
    ARMOR = 1,
    HELMET = 2,
    PANTS = 3,
    SHIELD = 4
};

enum ARMOR_WEIGHT_ENUM {
    ARMOR_WEIGHT = 3,
    HELMET_WEIGHT = 2,
    SHIELD_WEIGHT = 7,
    PANTS_WEIGHT = 1,
    TSHIRT_WEIGHT = 1
};

enum ARMOR_DEFENSE_ENUM {
    ARMOR_ARMOR = 3,
    HELMET_ARMOR = 3,
    SHIELD_ARMOR = 5,
    PANTS_ARMOR = 1,
    TSHIRT_ARMOR = 1
};

class armor {
 private:
    int x, y;
    std::string armor_name;
    std::string ARMOR_NAME_ARRAY[MAX_ARMOR_COUNT] = {"t-shirt", "armor", "helmet", "pants", "shield"};
 public:
    armor(std::string armor_name, int x, int y);

    ~armor() = default;

    int get_x() const;

    int get_y() const;

    std::string get_name() const;

    int transport() const;

    int transport_weight() const;

    int transport_armor() const;

    void armor_delete();
};

std::string armor_name(const int armor_number);
}  // namespace armor
