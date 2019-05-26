#include <iostream>

#include "tpbst.hpp"

int main() {
    TwoPhaseBST<int> tpbst;

    // tpbst.print()
    //         // .print("ceng213")
    //         // .print("ceng213", "sec1")
    //         .insert("ceng213", "sec50", 50)
    //         .insert("ceng213", "sec25", 25)
    //         .insert("ceng213", "sec80", 80)
    //         .insert("ceng213", "sec100", 100)
    //         .insert("ceng213", "sec90", 90)
    //         .insert("ceng213", "sec95", 95)
    //         .insert("ceng213", "sec105", 105)
    //         .insert("ceng213", "sec49", 49)
    //         .insert("ceng213", "sec13", 13)
    //         .insert("ceng477", "sec50", 50)
    //         .insert("ceng477", "sec49", 49)
    //         .print("ceng213")
    //         .print("ceng477")
    //         .print()
    //         // .print("ceng213", "")
    //         // .print("ceng477", "sec1")
    //         .remove("ceng213", "sec100")
    //         .remove("ceng213", "sec2")
    //         .remove("ceng213", "sec50")
    //         .remove("ceng213", "sec49")
    //         .remove("ceng213", "sec95")
    //         .remove("ceng213", "sec95")
    //         .remove("ceng213", "sec105")
    //         .remove("ceng213", "sec25")
    //         .remove("ceng213", "sec80")
    //         // .remove("ceng213", "sec13")
    //         .remove("ceng213", "sec90")
    //         .remove("ceng477", "sec50")
    //         .print();



            tpbst.insert("ceng100","sec05",5)
            .insert("ceng213", "sec1", 1)
          .insert("ceng100","sec86",86)
          .insert("ceng100","sec41",41)
          .insert("ceng100","sec22",22)
          .insert("ceng100","sec14",14)
          .insert("ceng100","sec67",67)
          .insert("ceng100","sec96",96)
          .remove("ceng100","sec41")
          .insert("ceng100","sec04",4)
          .insert("ceng100","sec01",1)
          .insert("ceng100","sec55",55)
          .insert("ceng100","sec42",42)
          .insert("ceng100","sec41",41)
          .insert("ceng100","sec39",39)
          .insert("ceng100","sec63",63)
          .insert("ceng100","sec02",2)
          .remove("ceng100","sec55")
          .insert("ceng100","sec40",40)
          .insert("ceng100","sec68",68)
          .insert("ceng100","sec75",75)
          .insert("ceng100","sec99",99)
          .insert("ceng100","sec95",95)
          .insert("ceng100","sec03",3)
          .insert("ceng100","sec06",6)
          .insert("ceng100","sec17",17)
          .remove("ceng100","sec41")
          .remove("ceng100","sec40")
          .remove("ceng100","sec42")
          .insert("ceng100","sec08",8)
          .insert("ceng100","sec15",15)
          .insert("ceng100","sec97",97)
          .insert("ceng100","sec72",72)
          .insert("ceng100","sec77",77)
          .insert("ceng100","sec79",79)
          .print ()
          .remove("ceng100","sec05")
          .remove("ceng100","sec06")
          .print ();

    // std::cout << "Number of enrolled students in ceng213 - sec13 is " << *(tpbst.find("ceng213", "sec13")) << std::endl;

    return 0;
}