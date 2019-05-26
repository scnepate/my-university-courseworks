import random

def design(x,y,fnum):
    #x: length of the string, y: extra lines
    allow="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    durum=False
    while durum == False :
        liste=[]
        for i in range(0,x):
            v=''
            for j in range(0,x):
                rand=random.randint(0,25)
                v+=allow[rand]
            liste.append(v)
        satir=tuple(liste)
        liste2=[]
        for j in range(0,x):
            v=''
            for i in range(0,x):
                v+=liste[i][j]
            liste2.append(v)
        sutun=tuple(liste2)
        liste3=[]
        for i in range(0,y):
            v=''
            for j in range(0,x):
                rand=random.randint(0,25)
                v+=allow[rand]
            liste3.append(v)
        ekstra=tuple(liste3)
        say1=len(satir)
        say2=len(sutun)
        say3=len(ekstra)
        if(say1+say2+say3 == len(set(satir+sutun+ekstra))) :
            durum=True
            lists=liste+liste2+liste3
            random.shuffle(lists)

            # input
            f = open ( "i"+str(fnum), "w" )
            f.write ( str ( lists ) )
            f.close ()
            
            # result (as rows)
            f = open ( "o"+str(fnum)+"r", "w" )
            f.write ( str ( liste ) )
            f.close ()
            
            # result (as columns)
            f = open ( "o"+str(fnum)+"c", "w" )
            f.write ( str ( liste2 ) )
            f.close ()
