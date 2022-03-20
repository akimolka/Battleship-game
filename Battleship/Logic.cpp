#include "BattleshipEntities.h"
#include "Output.cpp"
#include "Input.cpp"
#include <ctime>
#include <cstdlib>
#include <queue>
#include <utility>

class ShipSet {
public:
    virtual std::vector<const Figure*> get() const = 0;
};



class StandardShips: public ShipSet {
    const Figure patrol_boat;  // ◊
    const Figure submarine;    // ◊◊
    const Figure destroyer;   // ◊◊◊
    const Figure carrier;      // ◊◊◊◊

public:
    StandardShips()
        : patrol_boat({0, 0}, {0, 0}), submarine({0, 0}, {0, 1}),
          destroyer({0, 0}, {0, 2}), carrier({0, 0}, {0, 3}) {};

    std::vector<const Figure*> get() const override {
        return {&patrol_boat, &patrol_boat, &patrol_boat, &patrol_boat,
                      &submarine, &submarine, &submarine,
                      &destroyer, &destroyer,
                      &carrier};
    }
};




class BoardGenerator {
protected:
    static const int size = 10;
public:
    virtual Board* get(const ShipSet* shipset) const = 0;
};

class RandomBoardGenerator: public BoardGenerator {
    static const int max_fill_board_tries = 3;
    static const int max_place_figure_tries = 3;
    static const int max_random_times = 7;

    static bool check_figure_coords(const Figure& figure) {
        for (const Coord& coord : figure.get_coords())
            if (coord.x < 0 || coord.y < 0 || coord.x >= size || coord.y >= size)
                return false;
        return true;
    }

    static bool place_figure(Figure& figure, Board* board) {
        for (int random_time = 0; random_time < max_random_times; random_time++) {
            int x = rand() % size;
            int y = rand() % size;
            figure.shift_to({x, y});
            if (check_figure_coords(figure) && board->add_ships(figure.get_coords()))
                return true;
        }
        for (int x = 0; x < size; x++)
            for (int y = 0; y < size; y++) {
                figure.shift_to({x, y});
                if (check_figure_coords(figure) && board->add_ships(figure.get_coords()))
                    return true;
            }
        return false;
    }

public:
    Board* get(const ShipSet* shipset) const override {
        std::srand(std::time(nullptr));
        Board* board;
        for (int fill_board_try = 0; fill_board_try < max_fill_board_tries; fill_board_try++) {
            board = new Board();
            std::vector<const Figure*> ships_to_place = shipset->get();
            bool board_filled = true;
            while (!ships_to_place.empty()) {
                bool figure_placed = false;

                for (int place_figure_try = 0; place_figure_try < max_place_figure_tries; place_figure_try++) {
                    Figure figure(*ships_to_place.back());
                    int turn = rand() % 3;
                    int reflect = rand() % 2;
                    for (int i = 0; i < turn; i++)
                        figure.rotate();
                    for (int i = 0; i < reflect; i++)
                        figure.reflect();
                    if (place_figure(figure, board)) {
                        figure_placed = true;
                        ships_to_place.pop_back();
                        break;
                    }
                }

                if (!figure_placed) {
                    board_filled = false;
                    break;
                }
            }

            if (board_filled)
                return board;
            else
                board->~Board();
        }
        throw std::exception();
    }
};


class Player {
protected:
    const Board* opponent_board;
    static const std::vector<const std::pair<int, int>> moves;

    static bool is_valid(const Coord& coord) {
        return coord.x >= 0 && coord.y >= 0 && coord.x < Board::size && coord.y < Board::size;
    }

    void mark_unineteresting_rec(const Coord& coord, std::vector<std::vector<bool>>& interesting,
                             std::vector<std::vector<bool>>& used) {
        used[coord.x][coord.y] = true;
        interesting[coord.x][coord.y] = false;
        for (auto move : moves) {
            int x = coord.x + move.first;
            int y = coord.y + move.second;
            if (!is_valid({x, y}))
                continue;
            interesting[x][y] = false;
            if (!used[x][y] && opponent_board->get_board()[x][y] == HitResult::KILL)
                mark_unineteresting_rec({x, y}, interesting, used);
        }
    }

    void mark_uninteresting(const Coord& coord, std::vector<std::vector<bool>>& interesting) {
        std::vector<std::vector<bool>> used(Board::size, std::vector<bool> (Board::size));
        mark_unineteresting_rec(coord, interesting, used);
    }

public:
    explicit Player(const Board* board): opponent_board(board) {}
    virtual Coord get_move() = 0;
    virtual void report_success(HitResult result) = 0;
    virtual void report_losses(const Coord& shot, HitResult result, const Board* board) = 0;
};

const std::vector<const std::pair<int, int>>Player::moves = {{-1, -1}, {-1, 0}, {-1, 1},
                                                            {0, -1}, {0, 1},
                                                            {1, -1}, {1, 0}, {1, 1}};

class LivePlayer: public Player {
    const std::string name;
    Input* input;
    Output* output;
public:
    LivePlayer(std::string  name, const Board* board, Input* input, Output* output)
        : Player(board), name(std::move(name)), input(input), output(output) {}

    Coord get_move() override {
        output->move(name, opponent_board);
        while (true) {
            std::vector<Coord> shot = input->read();
            if (shot.size() == 1)
                return shot[0];
        }
    }

    void report_success(HitResult result) override {
        output->report_success(result);
    }

    void report_losses(const Coord& shot, HitResult result, const Board* board) override {
        output->report_losses(name, shot, result, board);
    }
};

class RandomPlayer: public Player {
public:
    explicit RandomPlayer(const Board* board): Player(board) {}

    Coord get_move() override {
        std::srand(std::time(nullptr));
        int x = rand() % Board::size;
        int y = rand() % Board::size;
        return {x, y};
    }
    void report_success(HitResult result) override {}
    void report_losses(const Coord& shot, HitResult result, const Board* board) override {}
};


class DummyRectanglePlayer: public Player {
    std::vector<std::vector<bool>> interesting;
    std::queue<Coord> potential_moves;

    Coord find_interesting(int x, int y) {
        for (int i = x; true; i = (i + 1) % Board::size)
            for (int j = y; true; j = (j + 1) % Board::size)
                if (interesting[i][j])
                    return {i, j};
    }

    Coord find_another_hit(const Coord& coord) {
        std::vector<std::pair<int, int>> straight_moves =
                {{-1, 0},{0, -1}, {0, 1}, {1, 0}};
        for (auto move : moves) {
            int x = coord.x + move.first;
            int y = coord.y + move.second;
            if (is_valid({x, y}) && opponent_board->get_board()[x][y] == HitResult::HIT)
                return {x, y};
        }
        return {-1, -1};
    }

    void make_neighbours_potential(const Coord& coord) {
        std::vector<std::pair<int, int>> straight_moves =
                {{-1, 0},{0, -1}, {0, 1}, {1, 0}};
        for (auto move : moves) {
            int x = coord.x + move.first;
            int y = coord.y + move.second;
            if (is_valid({x, y}))
                potential_moves.push({x, y});
        }
    }

public:
    DummyRectanglePlayer(const Board* board): Player(board) {
        interesting.resize(Board::size, std::vector<bool> (Board::size, true));
    }

    Coord get_move() override {
        int n = Board::size;
        while (!potential_moves.empty()) {
            Coord coord = potential_moves.front();
            if (interesting[coord.x][coord.y])
                return coord;
            potential_moves.pop();
        }

        std::srand(std::time(nullptr));
        int starting_x = rand() % Board::size;
        int starting_y = rand() % Board::size;
        potential_moves.push(find_interesting(starting_x, starting_y));
        return potential_moves.front();
    }

    void report_success(HitResult result) override {
        Coord curr = potential_moves.front();
        interesting[curr.x][curr.y] = false;

        if (result == HitResult::KILL)
            mark_uninteresting(potential_moves.front(), interesting);
        else if (result == HitResult::HIT) {
            Coord another_hit = find_another_hit(curr);

            if (another_hit.x == -1)
                make_neighbours_potential(potential_moves.front());
            else {
                Coord potential = {curr.x + 2 * (another_hit.x - curr.x), curr.y + 2 * (another_hit.y - curr.y)};
                if (is_valid(potential))
                    potential_moves.push(potential);
                interesting[another_hit.x + (another_hit.y - curr.y)][another_hit.y + (another_hit.x - curr.x)] = false;
                interesting[another_hit.x - (another_hit.y - curr.y)][another_hit.y - (another_hit.x - curr.x)] = false;
            }
        }

        potential_moves.pop();
    }

    void report_losses(const Coord& shot, HitResult result, const Board* board) override {}
};



enum Mode { TWO_PLAYERS, AGAINST_RANDOM, AGAINST_DUMMY, AGAINST_PROFI };

class Game {
    Input* input = new ConsoleInput();
    Output* output = new ConsoleOutput();
    BoardGenerator* board_gen = new RandomBoardGenerator();
    const ShipSet* shipset;
    Board* board_a;
    Board* board_b;
    Player* player_a;
    Player* player_b;

    void run(Player* player_a, Player* player_b, Board* board_a, Board* board_b) {
        std::vector<Player*> players = {player_a, player_b};
        std::vector<Board*> boards = {board_a, board_b};
        std::vector<int> count(2);
        count[0] = count[1] = shipset->get().size();
        int turn = 0;
        while (count[0] && count[1]) {
            Coord shot = players[turn]->get_move();
            HitResult result = boards[(turn + 1) % 2]->hit(shot);
            players[turn]->report_success(result);
            players[(turn + 1) % 2]->report_losses(shot, result, boards[(turn + 1) % 2]);
            if (result == HitResult::MISS)
                turn = (turn + 1) % 2;
        }
        if (count[0])
            cout << "player_a won";
        else
            cout << "player_b won";
    }

public:
    Game(const ShipSet* shipset): board_a(nullptr), board_b(nullptr), shipset(shipset) {};

    Board* fill_board() {
        Board* board = new Board();
        std::vector<const Figure*> ships_to_place = shipset->get();
        std::cout << "Enter ship coordinates\n"; // TODO place message into output
        while (!ships_to_place.empty()) {
            std::vector<Coord> input_figure = input->read();
            for (auto it = ships_to_place.begin(); it < ships_to_place.end(); it++) // TODO message about incorrect ship
                if (**it == input_figure && board->add_ships(input_figure)) {
                    ships_to_place.erase(it);
                    break;
                }
            output->board_creation(board, ships_to_place);
        }
        return board;
    }

    void add_board(Board* board) {
        board_a = board;
    };
    void add_boards(Board* first_board, Board* second_board) {
        board_a = first_board;
        board_b = second_board;
    }

    void play(Mode mode) {
        if (mode == Mode::TWO_PLAYERS && (board_a == nullptr || board_b == nullptr))
            std::cout << "Initialize two boards first with add_boards method!";
        else if (mode == Mode::TWO_PLAYERS) {
            std::cout << "Enter your names\n";
            std::string name_a, name_b;
            std::cin >> name_a >> name_b;
            player_a = new LivePlayer(name_a, board_b, input, output);
            player_b = new LivePlayer(name_b, board_a, input, output);
        }
//        else if (board_a == nullptr) {
//            std::cout << "Initialize two boards first with add_boards method!";
//            std::cout << "Board will be initialized for you";
//            board_a = board_gen->get(shipset);
//        }
        else {

            std::cout << "Enter your name\n";
            std::string name_a;
            std::cin >> name_a;
            board_a = board_gen->get(shipset);
            board_b = board_gen->get(shipset);
            player_a = new LivePlayer(name_a, board_b, input, output);
            switch (mode) {
                case Mode::AGAINST_RANDOM:
                    player_b = new RandomPlayer(board_a);
                    break;
                case Mode::AGAINST_DUMMY:
                    player_b = new DummyRectanglePlayer(board_a);
            }
        }

        run(player_a, player_b, board_a, board_b);
    }
};
