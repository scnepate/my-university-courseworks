   ######       ####     ###     ###     ######        ####        #####    ###     ###   ##### 
 ##      ##    ##  ##    ###     ###   ##      ##     ##  ##      ##   ##   ###     ###  ##   ##
##        #    ##  ##    ###     ###  ##        #     ##  ##      ##        ###     ###  ##     
##             ######    ###     ###  ##              ##  ##        ##      ###     ###    ##   
##        #   ########   ###     ###  ##        #    ########         ##    ###     ###      ## 
 ##      ##  ##      ##   ###   ###    ##      ##   ##      ##    ##   ##    ###   ###   ##   ##
   ######   ##        ##    #####        ######    ##        ##    #####       #####      ##### 

##### ##### ##### ##### ####  ##### #   # ##### ##### #   #
#   #     #     # #   # #   # #   # #   # #     #   # ##  #
#   #    #  ##### ####  ####  #   #  ###  #     #   # # # #
#####  #    #   # #   # #   # #####   #   #     ##### #  ##
#   # ##### ##### #   # ####  #   #   #   ##### #   # #   #

##### ##### ##### ##### ##### #     #####
#   # #   # #   #   #   #   # #       #  
#   # #   # ####    #   #   # #       #  
#  #  ##### #   #   #   ##### #       #  
### # #   # #   #   #   #   # ##### ##### 

import the3
import sys
import rr

s = input ( "Enter lower bound for N:" )
e = input ( "Enter upper bound for N:" )

number_of_correct = 0
fnum = 0

for i in range ( s, e+1 ):
    rr.design ( i, max ( 50, 5 ), fnum )
    
    # read and evaluate input
    f = open ( "i"+str(fnum), "r" )
    inp = eval ( f.read () )
    #print "N =", len ( inp[0] ), ": overall =", len ( inp    )
    o = the3.place_words ( inp )
    f.close ()

    # read first output
    f = open ( "o"+str(fnum)+"r", "r" )
    c0 = eval ( f.read () )
    f.close ()

    # read second output
    f = open ( "o"+str(fnum)+"c", "r" )
    c1 = eval ( f.read () )
    f.close ()

    #if you want to see input/output uncomment next four lines
    #print inp
    #print o
    #print c0
    #print c1

    # compare both outputs to given output
    if c0 == o or c1 == o:
        print "test "+str(fnum)+": Correct!"
        number_of_correct += 1
    else:  print "test "+str(fnum)+": Wrong Answer!"

    fnum += 1

print "Result: "+str(100.0*number_of_correct/fnum)+"%"

