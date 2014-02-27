#!/usr/bin/env python
from __future__ import print_function
import itertools


class End(Exception):

    def __init__(self, why=" ", winner=0):
        self.why = why
        self.winner = winner

    def __setitem__(self, why=" ", winner="0"):
        self.why = why
        self.winner = winner


class Error(Exception):

    def __init__(self, espressione, messaggio):
        self.expr = espressione
        self.str = messaggio

    def __str__(self):
        return repr(self.messaggio)


class partita(object):

    def __init__(self, p1="X", p2="O"):
        self.field = field(p1, p2)
        self.player1 = human(player=1, symbol=p1)
        self.player2 = human(player=2, symbol=p2)
        self.p = {1: self.player1, 2: self.player2}
        self.turno = [1, 0]
        self.End = End()
        self.History = []

    def __main__(self):
        partita = True
        while partita is not False:
            partita = self.__turno()

    def __cambia_turno(self):
        self.turno[0] = self.turno[0] % 2 + 1
        self.turno[1] += 1
        if self.turno[1] is 8:
            raise End("end_of_game", "partita finita")

    def __gioca(self, x, y):
        self.field[(x, y)] = self.p[self.turno[0]]
        self.History[self.turno[1]] = (x, y)

    def __check(self, player):
        move_to_control = player.symbol
        counter = {"diag": [0, 0], "col": [0, 0, 0], "row": [0, 0, 0]}
        for key, val in self.field:
            if val is move_to_control:
                x, y = key
                counter["col"][y] += 1
                counter["row"][x] += 1
                if x == y:
                    counter["diag"][0] += 1
                if y == x - 3:
                    counter["diag"][1] += 1
        for val in counter.values():
            for i in val:
                if i is 3 and self.End.winner is 0:
                    raise End["win", player]

    def __turno(self):
        self.field.visualizza()
        player = self.p[self.turno[0]]
        player.ask_move()
        self.__gioca(player.move)
        try:
            self.__check(player.ask)
            self.__cambia_turno()
        except End:
            self.__store_history()
            if player.__ask_to_play():
                self.__reset_game()
            else:
                return False
        return True

    def __store_history(self):
        self.History.append((self.End[:], self.history[:]))

    def __reset_game(self):
        self.field = field()
        self.End = End()
        self.turno = [1, 0]


class AI(object):
    pass


class human(object):

    def __init__(self, player=1, symbol="X"):
        self.player = player
        self.symbol = symbol
        self.move = ()
        self.History = []

    def __ask_to_play(self):
        return raw_input("Do you want to play again? Yes/No").startswith("y")

    def ask_move(self):
        try:
            x, y = raw_input("Where do you want play? (x,y) \n").split(",")
            print(x, y, max(x, y) > 3, min(x, y) < 0, max(x, y) > 3 or min(x, y) < 1)
            if max(x, y) > 3 or min(x, y) < 1:
                print("occhio 1")
                raise Error("Out_of_field", "coordinate non esistenti")
            elif self.field[(x, y)] is not " ":
                print("occhio")
                raise Error("Coord_used", "coordinate gia' usate")
            else:
                self.move = (x, y)
                self.history.append(self.move)
        except ValueError:
            print(
                "Remember to write only the two coordinates, \
                        separated by a comma.\n\
                    Like that: x,y")
            self.ask_move()
        except Error:
            print("The coordinates you have passed are wrong")
            self.ask_move()


class field(object):

    def __init__(self, p1="X", p2="O"):
        self.field = {}
        # self.coord = [(x, y) for x in xrange(3) for y in xrange(3)]
        self.coord = list(itertools.product(xrange(3), repeat=2))
        for coord in self.coord:
            self.field[coord] = " "

    def __iter__(self):
        for coord in self.coord:
            yield self.field[coord]

    def __getitem__(self, key):
            return self.field[key]

    def __setitem__(self, key, val):
        self.field[key] = val

    def visualizza(self):
        for y in range(len(self.coord)/3):
            print("  ------------- ")
            for x in range(len(self.coord)/3):
                print(self.field[(x, y)], end=" || ")
            else:
                print("")
        else:
            print("  ------------- ")
