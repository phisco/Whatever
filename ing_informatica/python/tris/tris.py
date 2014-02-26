from __future__ import print_function
class Error(Exception):
    def __init__(self,espressione,messaggio):
        self.espressione=espressione
        self.messaggio=messaggio
    def __str__(self):
        return repr(self.messaggio)

class field:
    def __init__(self,p1="X",p2="O"):
        self.p={1:p1,2:p2}
        self.field={}
        for x in range(3):
            for y in range(3):
                self.field[(x,y)]=" "
        self.turno=[1,0]
        self.vittoria=0
    
    def cambia_turno(self):
        self.turno[0]=self.turno[0]%2+1
        self.turno[1]+=1
        if self.turno[1] is 9:
            raise Error("end_of_game","partita finita")

    def gioca(self,*coordinate):
        if len(tuple(coordinate))!=2 or max(coordinate)>3:
            raise Error("coord_wrong", "le cordinate sono sbagliate")
        coordinate_reali=[]
        for coord in coordinate:
            coordinate_reali.append(coord-1)
        coordinate_reali=tuple(coordinate_reali)
        if self.field[coordinate_reali] is " ":
            self.field[coordinate_reali]=self.p.get(self.turno[0])
        else:
            raise Error("coord_used" , "coordinate gia' usate")
        self.visualizza()
        self.check()
        if self.vittoria!=0:
            print ("vittoria per il giocatore "+str(self.vittoria[0]))
        self.turno[0]=self.turno[0]%2+1
        self.turno[1]+=1

    def visualizza(self):
        def splitta_campo(self):
            tmp=[]
            for keys in sorted(self.field.keys()):
                tmp.append(self.field[keys])
            groups=[tmp[i:i+3] for i in range(0,len(tmp),3)]
            return groups
        print("\n---------------\n",end="")
        for groups in splitta_campo(self):
            print(" | ",end="")
            for el in groups:
                print(el,end=" | ")
            else:
                print("\n---------------\n",end="")


    def check(self):
        move_to_control=self.p[self.turno[0]]
        print( move_to_control)
        counter={"diagonal":[0,0],"col":[0,0,0],"row":[0,0,0]}
        print( counter)
        for x in range(3):
            if self.field[x,x] is move_to_control:
                counter["diagonal"][0]+=1
            if self.field[2-x,x] is move_to_control:
                counter["diagonal"][1]+=1
            for y in range(3):
                print("row " ,str( x) ,self.field[x,y])
                print("col " ,str( y) ,self.field[x,y])
                if self.field[y,x] is move_to_control:
                    counter["col"][x]+=1
                if self.field[x,y] is move_to_control:
                    counter["row"][x]+=1
        for val in counter.values():
            print(val)
            for i in val:
                if i is 3:
                    self.vittoria=self.turno
