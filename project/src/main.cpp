#include "map.h"


int main(int argc, const char** argv) {
    if (argc != 3 || strcmp(argv[1], "--map") != 0) {
        return WRONG_INPUT;
    }

    map::map new_map(argv[2]);
    std::string action;

    do {
        if (new_map.show_actions() && getline(std::cin, action)) {
            std::cout << std::endl;
        } else {
            break;
        }
        new_map.make_actions(action);
        if (new_map.get_player_health() <= 0) {
            std::cout << "player died\n";
            break;
        }
    } while (true);

    return 0;
}
