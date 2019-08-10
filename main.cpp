#include <iostream>
#include "include/vector2.h"

int main(){
    Vector2 VecA = Vector2(2.0, 3.0);    
    Vector2 VecB = Vector2(2.0, 2.0);    
    Vector2 VecC = VecA + VecB;
    std::cout << " VecA + VecB = " << VecC.components[0] << "i + " << VecC.components[1] << "j\n";
}
