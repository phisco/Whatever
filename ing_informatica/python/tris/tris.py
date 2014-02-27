#!/usr/bin/env python
from __future__ import print_function
import itertools

class End(object,exception):
    def __init__(self,why=" ",winner=0):
        self.why=why
        self.winner=winner

    def __setitem__(self,why=" ",winner="0"):
        self.why=why
        self.winner=winner
        
class Error(Exception):
    def __init__(self,espressione,messaggio):
        self.expr=espressione
        self.str=messaggio
    def __str__(self):
        return repr(self.messaggio)

class partita(object):
    def __init__(self,p1="X",p2="O"):
        self.field=field(p1,p2)
        self.player1=human(player=1,symbol=p1)
        self.player2=human(player=2,symbol=p2)
        self.p={1:self.player1,2:self.player2}
        self.turno=[1,0]
        self.End=End()
    def __cambia_turno(self):
        self.turno[0]=self.turno[0]%2+1
        self.turno[1]+=1
        if self.turno[1] is 9:
            raise Error("end_of_game","partita finita")

    def __gioca(self,x,y):
        self.field[(x,y)]=self.p[ self.turno[0] ]
    
    def __check(self,player):
        move_to_control=player.symbol
        counter={"diag":[0,0],"col":[0,0,0],"row":[0,0,0]}
        for key,val in self.field:
            if val is move_to_control:
                x,y=key
                counter["col"][y]+=1
                counter["row"][x]+=1
                if x == y:
                    counter["diag"][0]+=1
                if y == x-3:
                    counter["diag"][1]+=1
        for val in counter.values():
            for i in val:
                if i is 3 and self.End.winner is 0:
                    self.End["win",player]

    def __turno(self):
        self.__gioca(self.p[self.turno])
        if self.check() is not 0:
            raise

class human(object):
    def __init__(self,player=1,symbol="X"):
        self.player=player
        self.symbol=symbol
        self.move=()
        
    def ask_move():
        try:
            x,y=raw_input("Where do you want play? (x,y) \n").split(",")
            if max(x,y)>3 or min(x,y)<0:
                raise Error("out_of_field")
            elif self.field[(x,y)] is not " ":
                raise Error("coord_used" , "coordinate gia' usate")
            else:
                self.move=(x,y)
        except ValueError:
            print("Remembre to write only the two coordinates, separated by a comma.\n\
                    Like that: x,y")
            ask_move()
        except Error:
            if Error.expr.startswith("o"):
                print("The coordinates you have passed are wrong")
            else:
                print("The coordinates you have passed have been already used")
            ask_move()
        return self.move

class field(object):
    def __init__(self,p1="X",p2="O"):
        self.field={}
        for x,y in itertools.combinations(range(3),2):
            self.field[(x,y)]=" "

    def reinit(self):
        self.field={}
        for x,y in itertools.combinations(range(3),2):
            self.field[(x,y)]=" "

    def __iter__(self):
        for square in sorted(self.field.iteritems()):
            yield square

    def __getitem__(self,key):
        return self.field[key]
    
    def __setitem__(self,key,val):
        self.field[key]=val

    def visualizza(self):
        def splitta_campo(self):
            groups=[sorted(self.field.keys())[i:i+3] for i in range(0,len(self.field.keys()),3)]
            return groups
        print("\n ------------- \n",end="")
        for groups in splitta_campo(self):
            print(" | ",end="")
            for el in groups:
                print(self.field[ el ],end=" | ")
            else:
                print("\n ------------- \n",end="")

