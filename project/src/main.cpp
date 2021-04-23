#include "map.h"


int main(int argc, const char** argv) {
    int number = 0;
    bool armor = false;

    if (argc == 4) {
    	armor = true;
    }

    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '.') {
            number = i;
        }
    }

    map::map new_map(argv[number]);

    std::string action;

    do {
        std::cout << "Supported actions:";
        if (getline(std::cin, action)) {
            new_map.show_actions(false, armor);
        } else {
            new_map.show_actions(true, armor);
            return 0;
        }
        new_map.make_actions(action);
        if (new_map.get_player_health() <= 0) {
            std::cout << "player died\n";
            return 0;
        }
    } while (true);
}
