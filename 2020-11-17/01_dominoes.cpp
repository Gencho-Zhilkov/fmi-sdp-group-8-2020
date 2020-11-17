/*
Задача 3. Имате двоичен файл с пряк достъп players.dat (в който се пази информация за най-много 10 играчи на
домино като за всеки играч се пази име до 100 символа и начална сума пари, която играчът притежава) и двоичен файл
с пряк достъп domino_tiles.dat, в който се пази информация за уникални плочки за домино като за всяка плочка се пази
стойността на лявата й страна и стойността на дясната й страна.
Реализирайте програма, която:

(1 т) а) Прочита, извлича информацията от двата файла и разпределя последователно плочките от dominos.dat на
играчите като първата плочка дава на играч номер едно от първия файл, втората плочка дава на втория играч и т.н. Ако
в players.dat са изброени 4 играча, то петата плочка ще се даде на първия играч, шестата на втория и така нататък до
края на плочките от domino_tiles.dat.
* За целта можете да реализирате допълнителни структури от данни.

(1 т) б) След получаването на плочките, играчите започват игра. Във всеки ход на играта, всеки играч поставя на
масата първата получена плочка и играчът с най-висока сума, на двете страни на плочката, печели всичките плочки в
рамките на хода (при равенство на сумата на две плочки, печели човекът с най-висока страна от плочката). При
прибиране на спечелените плочки играчът може да ги използва отново, но не преди да е изиграл всички останали
плочки. Освен че печели плочките, този играч взима и по 100 пари от всеки от другите играчи. Ако даден играч изгуби
всичките си пари или плочките му свършат, то той излиза от играта. Напишете програма, която реализира 15 хода от
тази игра и като резултат извежда на стандартния изход името на играча с най-много пари и сумата пари, която има
след изиграването на играта.
* Ако даден играч има сума между 0 и 100 пари, той може да изиграе още един ход.
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>


struct Domino {
    int left;
    int right;

    int value() const {
        return left + right;
    }

    int max() const {
        return std::max(left, right);
    }

    bool operator>(const Domino& that) const {
        return value() > that.value() || (value() == that.value() && max() > that.max());
    }
};

std::vector<Domino> readDominos(const std::string& filename) {
    std::vector<Domino> dominos;
    std::ifstream f(filename, std::ios::binary);
    assert(f.is_open());

    Domino domino;
    while(f.read((char *)&domino, sizeof(domino))) {
        dominos.push_back(domino);
    }
    f.close();
    return dominos;
}


struct Player {
    char name[100];
    int money;
    std::queue<Domino> dominos;

    bool canPlay() {
        return money > 0 && !dominos.empty();
    }
};


std::vector<Player> readPlayers(const std::string& filename) {
    std::vector<Player> players;
    std::ifstream f(filename, std::ios::binary);
    assert(f.is_open());

    Player player;
    while(f.read((char *)&player, sizeof(player.name) + sizeof(player.money))) {
        players.push_back(player);
    }
    f.close();
    return players;
}

class Game {
private:
    std::vector<Player> players;

    void distribute(std::vector<Domino> dominos) {
        const auto numPlayers = players.size();
        for(auto i = 0; i < dominos.size(); i++) {
            players[i % numPlayers].dominos.push(dominos[i]);
        }
    }

public:
    Game(const std::vector<Player>& players, const std::vector<Domino>& dominos): players(players) {
        distribute(dominos);
    }

    void playTurn() {
        assert(!players.empty());

        auto moneyOnTheTable = 0;
        std::vector<Domino> dominosOnTheTable;

        auto winner = players.begin();
        Domino bestDomino {.left = 0, .right = 0};

        for(auto player = players.begin(); player != players.end(); ++player) {
            if(!player->canPlay()) {
                continue;
            }

            const auto bet = std::min(player->money, 100);
            player->money -= bet;
            moneyOnTheTable += bet;

            const auto domino = player->dominos.front();
            player->dominos.pop();
            dominosOnTheTable.push_back(domino);

            if (domino > bestDomino) {
                winner = player;
                bestDomino = domino;
            }
        }

        winner->money += moneyOnTheTable;
        for(auto domino: dominosOnTheTable) {
            winner->dominos.push(domino);
        }
    }

    const Player& maxPlayer() const {
        assert(!players.empty());
        auto bestPlayer = players.begin();
        for(auto player = players.begin()+1; player != players.end(); ++player) {
            if (player->money > bestPlayer->money) {
                bestPlayer = player;
            }
        }
        return *bestPlayer;
    }
};


int main() {
    auto dominos = readDominos("domino_tiles.dat");
    auto players = readPlayers("players.dat");

    auto game = Game(players, dominos);
    for(auto i = 0; i < 15; i++) {
        game.playTurn();
    }
    auto maxPlayer = game.maxPlayer();

    std::cout << maxPlayer.name << std::endl;
    std::cout << maxPlayer.money << std::endl;
    return 0;
}
