#include <cassert>
#include <iostream>
#include <fstream>
#include <initializer_list>


/* XXX: copy-paste */
struct Domino {
    int left;
    int right;
};

struct Player {
    char name[100];
    int money;
};

template<typename T>
void write(const std::string& filename, std::initializer_list<T> l) {
    std::ofstream f(filename, std::ios::binary);
    assert(f.is_open());

    for(auto x: l) {
        f.write((char *)&x, sizeof(x));
    }
    f.close();
}

int main() {

    write("domino_tiles.dat", {
        Domino{ .left = 1, .right = 2 },
        Domino{ .left = 2, .right = 3 },
        Domino{ .left = 3, .right = 5 },
        Domino{ .left = 4, .right = 4 },
        Domino{ .left = 5, .right = 2 },
        Domino{ .left = 6, .right = 1 },
        Domino{ .left = 7, .right = 2 },
        Domino{ .left = 8, .right = 6 }
    });

    write("players.dat", {
        Player{ {.name = "Player 1"}, .money = 1100 },
        Player{ {.name = "Player 2"}, .money = 1200 },
        Player{ {.name = "Player 3"}, .money = 1300 }
    });
}
