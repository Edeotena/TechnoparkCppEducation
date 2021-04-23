#pragma once

#include <string>

#define ARMOR 1
#define HELMET 2
#define SHIELD 4
#define PANTS 3
#define TSHIRT 0

#define ARMOR_WEIGHT 3
#define HELMET_WEIGHT 2
#define SHIELD_WEIGHT 7
#define PANTS_WEIGHT 1
#define TSHIRT_WEIGHT 1

#define ARMOR_ARMOR 3
#define HELMET_ARMOR 3
#define SHIELD_ARMOR 5
#define PANTS_ARMOR 1
#define TSHIRT_ARMOR 1

namespace armor {
class armor {
 private:
    int x, y;
    std::string armor_name;
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
