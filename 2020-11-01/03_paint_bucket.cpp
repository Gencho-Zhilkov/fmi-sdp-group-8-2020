#include <cassert>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <ios>
#include <iostream>


template <typename Color=int>
class Image {
private:
    Color* pixels;
    size_t width, height;

public:
    Image(size_t width, size_t height):
        width(width), height(height) {
        pixels = new Color[width * height]();
    }

    Color& color(int x, int y) {
        assert(isValid(x, y));
        return pixels[y * width + x];
    }

    bool isValid(int x, int y) {
        return (x >= 0 && x < width) && (y >= 0 && y < height);
    }

    void bucket(int x, int y, Color newColor) {
        if (!isValid(x, y)) {
            throw std::out_of_range("Start pixel out of range!");
        }
        if (color(x, y) == newColor) {
            return;
        }


        const Color oldColor = color(x, y);
        const std::tuple<int, int> offsets[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

        typedef std::tuple<int, int> Pixel;
        std::queue<Pixel> toPaint;

        color(x, y) = newColor;
        toPaint.push({x, y});

        while(!toPaint.empty()) {
            auto [x, y] = toPaint.front();
            toPaint.pop();

            for(auto [dx, dy]: offsets) {
                auto x1 = x+dx, y1 = y+dy;
                if(isValid(x1, y1) && color(x1, y1) == oldColor) {
                    color(x1, y1) = newColor;
                    toPaint.push({x1, y1});
                }
            }
        }
    }
};


int main() {
    using namespace std;

    auto width = 15, height = 10;
    Image img(width, height);

    for(auto y = 0; y < height; ++y) {
        img.color(width / 2, y) = 0x10;
    }

    img.bucket(3, 5, 0xff);

    for(auto y = 0; y < height; ++y) {
        for(auto x = 0; x < width; ++x) {
            cout << hex << img.color(x, y) << ' ';
        }
        cout << endl;
    }

    return 0;
}
