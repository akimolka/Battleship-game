# Battleship

### Description
This project implemets the well-known [Battleship game](https://en.wikipedia.org/wiki/Battleship_(game)).

**Already supported features:**
- [X] classic shipset 
- [X] adequate Artificial Intelligence player
- [X] arranging ships on the board
- [X] generation of grids for lazy ones
- [X] games vs AI and other human players
- [X] beautiful output (since part 2)

**To be implemented:**
- [ ] extraordinary shipsets and opportunity to choose a shipset for a game
- [ ] AI player that calculates the possibility of box to be occupied

### How to run the game
Simply execute run.sh file

### Patterns used
***Factory method*** is used in creation of players, means of input and output. It provides an interface for usage of objects in a superclass, but allows subclasses to alter the behavior

***Builder*** is used in filling the board. As a number of rules should be followed during ship arrangement, client does not have a straight access to the construction of the board and uses fill_board() method instead, which guides him through this intricate process

***Flyweight*** idea is applied in creation of class StandartShips. Real objects are created only this class, elsewhere pointers are used.

### Architecture
###### class Game
Метод ***play*** позволяет игроку выбрать желаемый режим (через метод интерфейса ***select_mode***), соответсвующе инициализирует внутренние поля класса (указатели на игроков и доски) и запускает игру через приватный метод ***run***.

Метод ***fill_board*** руководит заполнением доски: при каждом вводе корабля игроком 1) проверяет, что такую фигуру можно поставить, 2) с помощью метода доски ***add_ships*** не ставит корабли, соприкасающиемся с уже поставленными. 

Приватный метод ***run*** играет роль "судьи". Просит у игрока А сделать ход (***player->get_move()***), ходит в доску соперника B полученным ходом (***board->hit(shot)***), принимает от неё результат, сообщает этот результат ходящему игроку А (***player->report_success***). Дальше при промахе сообщает обо всех выстрелах сопернику В (***player->report_losses***) и передаёт ему ход, при попадании повторяет процедуру с тем же игроком А. Также класс ослеживает победу одного из игроков и завершает игру.

###### class Player
Абстрактный ***Player*** с конкретными реализациями ***LivePlayer***, ***RandomPlayer***, ***RectanglePlayer***. <br/>
В полях хранит const указатель на доску соперника и имя. <br/>
Имеет уже упомянутые виртуальные методы:
- ***get_move*** - по текущему состоянию доски противника возращает выстрел 
- ***report_success*** - принимает информацию об удачности своего выстрела 
- ***report_losses*** - принимает информацию о выстрелах противника в свою доски (по сути нужен только для LivePlayer, так как AI игроки не использует информацию о состоянии своей доски)

У ***LivePlayer*** все методы перенаправляют работу методам интерфейса <br/>
***RandomPlayer*** каждый раз равновероятно выбирает все клетки <br/>
***RectanglePlayer*** моделирует ходы среднестатистического человека. Не стреляет рядом с уже убитым кораблём. При попадании стреляет рядом, пытаясь добить корабль. Но не высчивает, поместится ли один из оставшихся кораблей в место выстрела. Работает только с кораблями 1 x n.

###### class Board
В полях хранит набор кораблей, картинку "подбитости" доски (то есть то, как она выглядит для другого игрока) и карту кораблей. <br/>
- ***add_ships*** - добавляет корабли на доску. Если корабль соприкасается с другими кораблями - не ставит его.
- ***hit*** - принимает удар в координату. Если на клетке не стоял корабль, возвращает MISS. Иначе передаёт удар кораблю (***ship->hit***) и возвращает его ответ.
- ***get_board*** - возвращает картинку "подбитости". Соперник пользуется только ей; владельцу она нужна в случае, если это LivePlayer, для вывода своей доски.
- ***get_ships*** - возвращает карту кораблей. Нужна для вывода своей доски у LivePlayer.

###### class Ship
В полях хранит свои координаты и "подбитость". <br/>
Имеет методы
- ***hit*** - принимает удар, возвращает NONE/ HIT/ KILL
- ***get_coords*** -  возвращает координты корабля

###### class Figure
Используется: 1) набор коралей для игры - это массив фигур, 2) при заполенении доски, 3) потенциально может испоьзоваться AI player'ом. То есть там, где важна именно форма, а не координаты. <br/>
Имеет методы для удобной работы с фигурой: ***rotate***, ***shift_to***, ***reflect***, ***operator==***, ***get_proportions*** - возвращает длину и ширину, ***standardize*** - вписывает фигуру в координатную четверть, ***get_coords*** - получить координты фигуры.

###### class Interface
Абстрактный класс с реализованной конкретной реализацией ConsoleInterface. Отвечает за весь input и output.

