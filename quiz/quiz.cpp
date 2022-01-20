//number 7

#include <iostream> 
#include <vector> 
 
class complex {
    public:
        complex() : real(0), imagine(0) { }
        complex(double r) : real(r), imagine(0) { }
        complex(double r, double i) : real(r), imagine(i) { }
        // ...
        void setReal(double inR) { real = inR; }
        double getReal() { return real; }
        double getI() { return imagine; }
        complex& operator+=(const complex& a)
            { real+=a.real; imagine+=a.imagine; return *this; }
        //friend complex operator+(const complex &a, const complex &b);

        complex operator+(complex b) {
            return complex(real + b.real, imagine+b.imagine);
        }

        // ...
    private:
        double real, imagine;
}; 

//zero out the real component
void stripReal(complex *comNum) {
    comNum->setReal(0);
}


int main() { 
    complex numA(12, -1);
    complex numB(0, -1);
    complex numC = numA+numB;
    std::cout << "complex C real: " << numC.getReal() << " imaginary: " <<numC.getI() << std::endl;

    std::cout << "strip Real component of numA: " << numA.getReal() << " imaginary: " <<numA.getI() << std::endl;
    stripReal(&numA);
    std::cout << "strip Real component of numA: " << numA.getReal() << " imaginary: " <<numA.getI() << std::endl;

}