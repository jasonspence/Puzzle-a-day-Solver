#include <iostream>
#include <array>
#include <unordered_set>
#include <string_view>
#include <optional>
#include <vector>

struct Point {
    int x;
    int y;

    constexpr Point() : x(0), y(0) {};
    constexpr Point(int x, int y) : x(x), y(y) {};

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// hash function for Point, assuming 7x7 grid
template<>
struct std::hash<Point> {
    size_t operator()(const Point& p) const {
        return (7 * std::hash<int>()(p.x)) + std::hash<int>()(p.y);
    }
};

constexpr std::array<std::pair<std::string_view, Point>, 43> dateMap = {{
    {"Jan", Point(0,0)},
    {"Feb", Point(0,1)},
    {"Mar", Point(0,2)},
    {"Apr", Point(0,3)},
    {"May", Point(0,4)},
    {"Jun", Point(0,5)},
    {"Jul", Point(1,0)},
    {"Aug", Point(1,1)},
    {"Sep", Point(1,2)},
    {"Oct", Point(1,3)},
    {"Nov", Point(1,4)},
    {"Dec", Point(1,5)},
    {"1", Point(2,0)},
    {"2", Point(2,1)},
    {"3", Point(2,2)},
    {"4", Point(2,3)},
    {"5", Point(2,4)},
    {"6", Point(2,5)},
    {"7", Point(2,6)},
    {"8", Point(3,0)},
    {"9", Point(3,1)},
    {"10", Point(3,2)},
    {"11", Point(3,3)},
    {"12", Point(3,4)},
    {"13", Point(3,5)},
    {"14", Point(3,6)},
    {"15", Point(4,0)},
    {"16", Point(4,1)},
    {"17", Point(4,2)},
    {"18", Point(4,3)},
    {"19", Point(4,4)},
    {"20", Point(4,5)},
    {"21", Point(4,6)},
    {"22", Point(5,0)},
    {"23", Point(5,1)},
    {"24", Point(5,2)},
    {"25", Point(5,3)},
    {"26", Point(5,4)},
    {"27", Point(5,5)},
    {"28", Point(5,6)},
    {"29", Point(6,0)},
    {"30", Point(6,1)},
    {"31", Point(6,2)}
}};

constexpr std::optional<Point> findPoint(std::string_view date) {
    for (const auto& [key, value] : dateMap) {
        if (key == date) {
            return value;
        }
    }
    return {};
}

enum class Orientation {
    Normal0,
    Normal90, 
    Normal180, 
    Normal270,
    Flipped0,
    Flipped90,
    Flipped180,
    Flipped270
};

struct Tetronimo {
    std::string_view name;
    std::array<Point, 6> coordinates;
    int num_orientations;
    std::array<Orientation, 8> orientations;

    constexpr Tetronimo(
        std::string_view name,
        std::array<Point, 6> coordinates,
        int num_orientations,
        std::array<Orientation, 8> orientations
    ) : name(name), coordinates(coordinates), num_orientations(num_orientations), orientations(orientations) {}

    Tetronimo(const Tetronimo& other) 
        : name(other.name), coordinates(other.coordinates), num_orientations(other.num_orientations), orientations(other.orientations) {}
};

constexpr std::array<Tetronimo, 8> tetronimos = {
    Tetronimo("Rectangle",    {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,1}, Point{1,2}}, 2, {Orientation::Normal0, Orientation::Normal90}),
    Tetronimo("S-shape",      {Point{0,0}, Point{0,1}, Point{1,1}, Point{2,1}, Point{2,2}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Flipped0, Orientation::Flipped90}),
    Tetronimo("AngleBracket", {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{2,0}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270}),
    Tetronimo("U-shape",      {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,2}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270}),
    Tetronimo("L-shape",      {Point{0,0}, Point{0,1}, Point{0,2}, Point{0,3}, Point{1,0}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("F-shape",      {Point{0,0}, Point{0,1}, Point{0,2}, Point{0,3}, Point{1,1}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("Snake",        {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,2}, Point{1,3}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("Blob",         {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,1}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270})
};

Tetronimo orient(const Tetronimo& piece, Orientation orientation, Point offset) {
    Tetronimo oriented(piece);
    for (size_t i=0; i < size(piece.coordinates); i++) {
        switch (orientation) {
            case Orientation::Normal0:
                oriented.coordinates[i] = piece.coordinates[i];
                break;
            case Orientation::Normal90:
                oriented.coordinates[i] = {piece.coordinates[i].y, -piece.coordinates[i].x};
                break;
            case Orientation::Normal180:
                oriented.coordinates[i] = {-piece.coordinates[i].x, -piece.coordinates[i].y};
                break;
            case Orientation::Normal270:
                oriented.coordinates[i] = {-piece.coordinates[i].y, piece.coordinates[i].x};
                break;
            case Orientation::Flipped0:
                oriented.coordinates[i] = {-piece.coordinates[i].x, piece.coordinates[i].y};
                break;
            case Orientation::Flipped90:
                oriented.coordinates[i] = {piece.coordinates[i].y, piece.coordinates[i].x};
                break;
            case Orientation::Flipped180:
                oriented.coordinates[i] = {piece.coordinates[i].x, -piece.coordinates[i].y};
                break;
            case Orientation::Flipped270:
                oriented.coordinates[i] = {-piece.coordinates[i].y, -piece.coordinates[i].x};
                break;
        }
    }
    for (Point& point : oriented.coordinates) {
        point.x += offset.x;
        point.y += offset.y;
    }
    return oriented;
}

struct Board {
    std::unordered_set<Point> coordinates;

    Board() {
        // 7x7 grid
        for (size_t i=0; i < 7; i++) {
            for (size_t j=0; j < 7; j++) {
                coordinates.insert(Point(i,j));
            }
        }
        coordinates.erase(Point(0,6));
        coordinates.erase(Point(1,6));
        coordinates.erase(Point(6,3));
        coordinates.erase(Point(6,4));
        coordinates.erase(Point(6,5));
        coordinates.erase(Point(6,6));
    }

    Board(Point month, Point day) : Board() {
        coordinates.erase(month);
        coordinates.erase(day);
    }

    void place_tet(const Tetronimo& tet, Orientation orientation, Point offset) {
        for (Point point : orient(tet, orientation, offset).coordinates) {
            coordinates.erase(point);
        }
    }
    void remove_tet(const Tetronimo& tet, Orientation orientation, Point offset) {
        for (Point point : orient(tet, orientation, offset).coordinates) {
            coordinates.insert(point);
        }
    }
};

bool fitsOnBoard(const Tetronimo& piece, const Board& board, Point location, Orientation orientation) {
    Tetronimo oriented = orient(piece, orientation, location);
    for (Point candidate : oriented.coordinates) {
        if (auto iter = board.coordinates.find(candidate); iter == board.coordinates.end()) {
            return false;
        }
    }
    return true;
}

struct LocatedTetronimo {
    std::string_view name;
    Orientation orientation;
    Point offset;
};

struct Solution {
    std::array<LocatedTetronimo, 8> locations;
};

void depthFirstSolver(Board& board, Solution& data, int depth, std::vector<Solution>& solutions) {
    if (depth >= 2) { //DEBUG: should be 8
        std::cout << "Found solution #" << size(solutions) << std::endl;
        solutions.push_back(data);
        return;
    }
    std::cout << "Beginning solver depth " << depth << ", Tetronimo: " << tetronimos[depth].name << std::endl;

    // test the next tetronimo on all available locations
    for (size_t ori_ind=0; ori_ind < tetronimos[depth].num_orientations; ori_ind++) {
        Orientation orientation = tetronimos[depth].orientations[ori_ind];
        std::cout << "  orientation: " << ori_ind << std::endl;
        Board copyForIterating(board);
        for (Point offset : copyForIterating.coordinates) {
            std::cout << "    offset: (" << offset.x << ", " << offset.y << ")" << std::endl;
            if (fitsOnBoard(tetronimos[depth], board, offset, orientation)) {
                std::cout << "    It FITS!" << std::endl;
                data.locations[depth].name = tetronimos[depth].name;
                data.locations[depth].offset = offset;
                data.locations[depth].orientation = orientation;
                board.place_tet(tetronimos[depth], orientation, offset);
                depthFirstSolver(board, data, depth + 1, solutions);
                board.remove_tet(tetronimos[depth], orientation, offset);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " month day" << std::endl;
        return 1;
    }
    std::optional<Point> opt_month = findPoint(argv[1]);
    std::optional<Point> opt_day   = findPoint(argv[2]);
    if (!opt_month || ! opt_day) {
        std::cout << "Couldn't parse the date! Aborting... " << std::endl;
        return 1;
    }
    Point month = opt_month.value();
    Point day   = opt_day.value();

    // for (size_t i=0; i < 7; i++) {
    //     for (size_t j=0; j < 7; j++) {
    //         //int ans = i ^ (j << 1);
    //         int ans = i * 7 + j;
    //         std::cout << "v0: " << i << ", v1: " << j << ", hash: " << ans << std::endl;
    //     }
    // }
    

    Board board(month, day);
    std::cout << fitsOnBoard(tetronimos[0], board, Point(0,1), Orientation::Normal0) << std::endl;

    Solution data;
    std::vector<Solution> solutions;
    depthFirstSolver(board, data, 0, solutions);

    return 0;
}
