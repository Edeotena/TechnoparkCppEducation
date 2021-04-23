#include "armor.h"

namespace armor {
    armor::armor(std::string armor_name, int x, int y) : x(x), y(y), armor_name(armor_name) {}

    int armor::get_x() const {
        return x;
    }

    int armor::get_y() const {
        return y;
    }

    std::string armor::get_name() const {
        return armor_name;
    }

    int armor::transport() const {
        if (armor_name == "armor") {
            return ARMOR;
        }
        if (armor_name == "helmet") {
            return HELMET;
        }
        if (armor_name == "shield") {
            return SHIELD;
        }
        if (armor_name == "pants") {
            return PANTS;
        }
        return TSHIRT;
    }

    int armor::transport_weight() const {
        if (armor_name == "armor") {
            return ARMOR_WEIGHT;
        }
        if (armor_name == "helmet") {
            return HELMET_WEIGHT;
        }
        if (armor_name == "shield") {
            return SHIELD_WEIGHT;
        }
        if (armor_name == "pants") {
            return PANTS_WEIGHT;
        }
        return TSHIRT_WEIGHT;
    }

    int armor::transport_armor() const {
        if (armor_name == "armor") {
            return ARMOR_ARMOR;
        }
        if (armor_name == "helmet") {
            return HELMET_ARMOR;
        }
        if (armor_name == "shield") {
            return SHIELD_ARMOR;
        }
        if (armor_name == "pants") {
            return PANTS_ARMOR;
        }
        return TSHIRT_ARMOR;
    }

    void armor::armor_delete() {
        x = -1;
        y = -1;
    }

    std::string armor_name(const int armor_number) {
        if (armor_number == ARMOR) {
            return "armor";
        }
        if (armor_number == HELMET) {
            return "helmet";
        }
        if (armor_number == PANTS) {
            return "pants";
        }
        if (armor_number == SHIELD) {
            return "shield";
        }
        return "T-Shirt";
    }
}  // namespace armor
