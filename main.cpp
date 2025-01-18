#include <iostream>
#include <fstream>
#include <filesystem>
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

constexpr std::optional<Point> getPointByDate(std::string_view date) {
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

std::string toString(Orientation o) {
    switch (o) {
        case Orientation::Normal0: return "Normal0";
        case Orientation::Normal90: return "Normal90";
        case Orientation::Normal180: return "Normal180";
        case Orientation::Normal270: return "Normal270";
        case Orientation::Flipped0: return "Flipped0";
        case Orientation::Flipped90: return "Flipped90";
        case Orientation::Flipped180: return "Flipped180";
        case Orientation::Flipped270: return "Flipped270";
    }
    return "Unknown";
}

struct Tetronimo {
    std::string_view name;
    char symbol;
    std::array<Point, 6> coordinates;
    int num_orientations;
    std::array<Orientation, 8> orientations;

    constexpr Tetronimo(
        std::string_view name,
        char symbol,
        std::array<Point, 6> coordinates,
        int num_orientations,
        std::array<Orientation, 8> orientations
    ) : name(name), symbol(symbol), coordinates(coordinates), num_orientations(num_orientations), orientations(orientations) {}

    Tetronimo(const Tetronimo& other) 
        : name(other.name), coordinates(other.coordinates), num_orientations(other.num_orientations), orientations(other.orientations) {}
};

constexpr std::array<Tetronimo, 8> tetronimos = {
    Tetronimo("Rectangle",    'O', {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,1}, Point{1,2}}, 2, {Orientation::Normal0, Orientation::Normal90}),
    Tetronimo("S-shape",      'S', {Point{0,0}, Point{0,1}, Point{1,1}, Point{2,1}, Point{2,2}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Flipped0, Orientation::Flipped90}),
    Tetronimo("AngleBracket", 'A', {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{2,0}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270}),
    Tetronimo("U-shape",      'U', {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,2}}, 4, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270}),
    Tetronimo("L-shape",      'L', {Point{0,0}, Point{0,1}, Point{0,2}, Point{0,3}, Point{1,0}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("F-shape",      'F', {Point{0,0}, Point{0,1}, Point{0,2}, Point{0,3}, Point{1,1}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("Snake",        'r', {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,2}, Point{1,3}}, 
                8, {Orientation::Normal0, Orientation::Normal90, Orientation::Normal180, Orientation::Normal270, Orientation::Flipped0, Orientation::Flipped90, Orientation::Flipped180, Orientation::Flipped270}),
    Tetronimo("Blob",         'b', {Point{0,0}, Point{0,1}, Point{0,2}, Point{1,0}, Point{1,1}}, 
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

std::array<Point, 6> doRotation(const std::array<Point, 6>& coordinates, Orientation orientation) {
    std::array<Point, 6> out;
    for (size_t i=0; i < size(coordinates); i++) {
        switch (orientation) {
            case Orientation::Normal0:
                out[i] = coordinates[i];
                break;
            case Orientation::Normal90:
                out[i] = {coordinates[i].y, -coordinates[i].x};
                break;
            case Orientation::Normal180:
                out[i] = {-coordinates[i].x, -coordinates[i].y};
                break;
            case Orientation::Normal270:
                out[i] = {-coordinates[i].y, coordinates[i].x};
                break;
            case Orientation::Flipped0:
                out[i] = {-coordinates[i].x, coordinates[i].y};
                break;
            case Orientation::Flipped90:
                out[i] = {coordinates[i].y, coordinates[i].x};
                break;
            case Orientation::Flipped180:
                out[i] = {coordinates[i].x, -coordinates[i].y};
                break;
            case Orientation::Flipped270:
                out[i] = {-coordinates[i].y, -coordinates[i].x};
                break;
        }
    }
    return out;
}

std::array<Point, 6> doTranslation(const std::array<Point, 6>& coordinates, Point offset) {
    std::array<Point, 6> out;
    for (size_t i=0; i < size(coordinates); i++) {
        out[i] = {coordinates[i].x + offset.x, coordinates[i].y + offset.y};
    }
    return out;
}


struct Board {
    std::array<std::pair<Point, char>, 43> coordinates;
    static constexpr char blank = ' ';

    Board() {
        size_t pos = 0;
        for (size_t i=0; i < 2; i++) {
            for (size_t j=0; j < 6; j++) {
                coordinates[pos] = {Point(i,j), blank};
                pos++;
            }
        }
        for (size_t i=2; i < 6; i++) {
            for (size_t j=0; j < 7; j++) {
                coordinates[pos] = {Point(i,j), blank};
                pos++;
            }
        }
        for (size_t i=6; i < 7; i++) {
            for (size_t j=0; j < 3; j++) {
                coordinates[pos] = {Point(i,j), blank};
                pos++;
            }
        }
    }

    Board(Point month, Point day) : Board() {
        auto m = findPosition(month);
        if (m) {
            coordinates[m.value()].second = 'X';
        }
        auto d = findPosition(day);
        if (d) {
            coordinates[d.value()].second = 'X';
        }
    }

    constexpr std::optional<size_t> findPosition(Point p) const {
        for (size_t i=0; i <= size(coordinates); i++) {
            if (coordinates[i].first == p) {
                return i;
            }
        }
        return {};
    }

    bool isBlank(Point point) const {
        auto p = findPosition(point);
        if (p) {
            return (coordinates[p.value()].second == blank);
        }
        return false;
    }

    std::vector<Point> getAllBlanks() const {
        std::vector<Point> out;
        for (auto val : coordinates) {
            if (val.second == blank || val.second == 'X') {
                out.push_back(val.first);
            }
        }
        return out;
    }

    void place_tet(const std::array<Point, 6>& tet, char symbol) {
        for (Point point : tet) {
            auto p = findPosition(point);
            if (p) {
                coordinates[p.value()].second = symbol;
            }
        }
    }
    void remove_tet(const std::array<Point, 6>& tet) {
        for (Point point : tet) {
            auto p = findPosition(point);
            if (p) {
                coordinates[p.value()].second = blank;
            }
        }
    }

    std::string toString() const {
        std::string out = "________\n|";
        int cur_row = 0;
        for (auto& pos : coordinates) {
            if (pos.first.x != cur_row) {
                cur_row = pos.first.x;
                out.append("|\n|");
            }
            out.push_back(pos.second);
        }
        out.append("_____\n___");
        return out;
    }
};

bool fitsOnBoard(const std::array<Point, 6>& piece, const Board& board) {
    for (Point candidate : piece) {
        if (!board.isBlank(candidate)) {
            return false;
        }
    }
    return true;
}

struct LocatedTetronimo {
    std::string_view name;
    Orientation orientation;
    Point offset;

    std::string toCSV() {
        return toString(orientation) + ", " + std::to_string(offset.x) + ", " + std::to_string(offset.y);
    }
};

struct Solution {
    std::array<LocatedTetronimo, 8> locations;
    Board board;

    std::string toCSVRow() {
        std::string out = "";
        auto blanks = board.getAllBlanks();
        for (auto blank : blanks) {
            out.append(std::to_string(blank.x) + "," + std::to_string(blank.y) + ",");
        }
        for (auto loc : locations) {
            out.append(loc.toCSV());
            out.append(", "); // TODO: fix trailing comma
        }
        return out;
    }
};

void depthFirstSolver(Board& board, Solution& data, int depth, std::vector<Solution>& solutions) {
    // if (size(solutions) > 10) { // debug limiter
    //     return;
    // }
    if (depth >= 8) {
        std::cout << "Found solution #" << size(solutions)+1 << std::endl;
        std::cout << board.toString() << std::endl;
        data.board = board;
        solutions.push_back(data);
        return;
    }
    //std::cout << "Beginning solver depth " << depth << ", Tetronimo: " << tetronimos[depth].name << std::endl;

    // test the next tetronimo on all locations
    for (size_t ori_ind=0; ori_ind < tetronimos[depth].num_orientations; ori_ind++) {
        Orientation orientation = tetronimos[depth].orientations[ori_ind];
        std::array<Point, 6> tet = doRotation(tetronimos[depth].coordinates, orientation);
        //std::cout << "  orientation: " << ori_ind << std::endl;
        for (auto& offset : board.coordinates) {
            // TODO: Test adding an early exit if the offset block is not free
            std::array<Point, 6> orientedTetronimo = doTranslation(tet, offset.first);
            if (fitsOnBoard(orientedTetronimo, board)) {
                //std::cout << "    It FITS!" << " offset: (" << offset.first.x << ", " << offset.first.y << ")" << std::endl;
                data.locations[depth].name = tetronimos[depth].name;
                data.locations[depth].offset = offset.first;
                data.locations[depth].orientation = orientation;
                board.place_tet(orientedTetronimo, tetronimos[depth].symbol);
                depthFirstSolver(board, data, depth + 1, solutions);
                board.remove_tet(orientedTetronimo);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc > 3) {
        std::cerr << "Usage: " << argv[0] << std::endl;
        std::cerr << "Usage: " << argv[0] << " month day" << std::endl;
        return 1;
    }

    Board board;

    if (argc == 3) {
        std::optional<Point> opt_month = getPointByDate(argv[1]);
        std::optional<Point> opt_day   = getPointByDate(argv[2]);
        if (!opt_month || ! opt_day) {
            std::cout << "Couldn't parse the date! Aborting... " << std::endl;
            return 1;
        }
        Point month = opt_month.value();
        Point day   = opt_day.value();
        board = Board(month, day);
    }

    Solution data;
    std::vector<Solution> solutions;
    depthFirstSolver(board, data, 0, solutions);

    std::cout << "Saving solutions" << std::endl;
    {
        std::filesystem::create_directories("output");

        const std::string csv_filename = "output/data.csv";
        std::ofstream outFile(csv_filename);
        if (!outFile) {
            std::cerr << "Error opening file: " << csv_filename << std::endl;
            return 1;
        }

        outFile << "First blank x,First blank y,Second blank x,Second blank y," <<
                        "Rectangle Orientation,Rectangle x,Rectangle y," << 
                        "S-shape Orientation,S-shape x,S-shape y," <<
                        "AngleBracket Orientation,AngleBracket x,AngleBracket y," <<
                        "U-shape Orientation,U-shape x,U-shape y," <<
                        "L-shape Orientation,L-shape x,L-shape y," <<
                        "F-shape Orientation,F-shape x,F-shape y," <<
                        "Snake Orientation,Snake x,Snake y," <<
                        "Blob Orientation,Blob x,Blob y,blank\n"; // TODO: fix trailing comma due to "toCSVRow()"
        for (auto solution : solutions) {
            outFile << solution.toCSVRow() << "\n";
        }
    }
    std::cout << "Finished saving" << std::endl;

    return 0;
}
