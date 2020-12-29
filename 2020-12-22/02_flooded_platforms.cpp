#include <algorithm>
#include <vector>
#include <set>

struct Platform {
    int start, end;
    int y;

    bool operator <(const Platform &that) {
        return this->y <= that.y;
    }
};

std::vector<Platform> flood(std::vector<Platform> platforms, int x0) {
    std::set<int> streams({x0});
    std::vector<Platform> res;

    std::sort(platforms.begin(), platforms.end());
    for(auto platform: platforms) {
        auto it = streams.lower_bound(platform.start);

        bool flooded = it != streams.end() && *it <= platform.end;
        while(it != streams.end() && *it <= platform.end) {
            streams.erase(it);
            ++it;
        }

        if(flooded) {
            streams.insert(platform.start);
            streams.insert(platform.end);
            res.push_back(platform);
        }
    }

    return res;
}

int main() {
    return 0;
}
