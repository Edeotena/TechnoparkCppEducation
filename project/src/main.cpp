#include "map.h"


int main(int argc, const char** argv) {
    if (argc != 4) {
        return (-1);
    }

    int number = 0;

    for (int i = 0; i < 4; ++i) {
        if (argv[i][0] == '.') {
            number = i;
        }
    }

    map::map new_map(argv[number]);

    std::string action;

    do {
        std::cout << "Supported actions:";
        if (getline(std::cin, action)) {
            new_map.show_actions(false);
        } else {
            new_map.show_actions(true);
            return 0;
        }
        new_map.make_actions(action);
        if (new_map.get_player_health() <= 0) {
            std::cout << "player died\n";
            return 0;
        }
    } while (true);
}
