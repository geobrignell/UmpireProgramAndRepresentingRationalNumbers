#include <iostream>

class Fraction{
 
    private:

    // Variables
    long long numerator; long long denominator; //Long ints to get larger range of fractions.

    public: 

    //Constructor
    constexpr Fraction(long long _numerator,long long _denominator):
    numerator(_numerator),
    denominator(_denominator){
        if (_denominator==0){//Check to make sure not dividing by zero.
            throw std::logic_error("Divided by 0. You cannot have a denominator of 0.");
        }
        simplify(); // Simplify the fraction on initialisation.
    };

    //Functions

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction){ //Print to console (cout)
        std::cout << fraction.numerator << "/" << fraction.denominator << std::endl;
        return os;
    }

    long long gcf(const long long &a,const long long &b){ //Get common factor
        long long c = a % b;
        if (c == 0){
            return b;
        }

    return gcf(b,c);
    }
    
    void simplify(){//Simplifies to fraction as much as possible
        long long bcf = gcf(numerator, denominator);

        numerator /= bcf;
        denominator /= bcf;

        if (denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }
    }

    Fraction operator +(Fraction const &other){ //Addition
        long long newNum = numerator*other.denominator + other.numerator*denominator;
        long long newDen = denominator*other.denominator;

        Fraction sum(newNum,newDen);

        return sum;
    }

    Fraction operator -(Fraction const &other){ // Subtraction
        long long newNum = numerator*other.denominator - other.numerator*denominator;
        long long newDen = denominator*other.denominator;

        Fraction sum(newNum,newDen);

        return sum;
    }
     
    Fraction operator *(Fraction const &other){ // Mulitplication
        long long newNum = numerator*other.numerator;
        long long newDen = denominator*other.denominator;

        Fraction product(newNum,newDen);

        return product;
    }

    Fraction operator /(Fraction const &other){ // Division
        long long newNum = numerator*other.denominator;
        long long newDen = denominator*other.numerator;

        Fraction product(newNum,newDen);

        return product;
    }

    Fraction& operator +=(Fraction const &other){
        *this = *this + other;
        return *this;
    }

    Fraction& operator -=(Fraction const &other){
        *this = *this - other;
        return *this;
    }

    Fraction& operator /=(Fraction const &other){
        *this = *this / other;
        return *this;
    }

    Fraction& operator *=(Fraction const &other){
        *this = *this * other;
        return *this;
    }

    constexpr Fraction& operator++(){ //Prefix ++
        numerator = numerator + denominator;
        
        return *this;
   }

    constexpr Fraction operator++(int){ //Postfix ++
        Fraction holder = *this;
        ++(*this);
        return holder;
   }

    constexpr Fraction& operator--(){ //Prefix --
        numerator = numerator - denominator;
        return *this;
   } 

    constexpr Fraction operator--(int){ //Postfix ++
        Fraction holder = *this;
        --(*this);
        return holder;
   }
    
    bool operator==(const Fraction &other){
        if (numerator == other.numerator && denominator == other.denominator){
            return true;
        }
        return false;
   }

    bool operator!=(const Fraction &other){

        if (numerator != other.numerator || denominator != other.denominator){
            return true;
        }
        return false;
   }

    bool operator>(const Fraction &other){
        double forigin = (long double)numerator/(long double)denominator;
        double fother  = (long double)other.numerator/(long double)other.denominator;

        if (forigin > fother){
            return true;
        }
        return false;

   }

    bool operator<(const Fraction &other){
        double forigin = (long double)numerator/(long double)denominator;
        double fother  = (long double)other.numerator/(long double)other.denominator;

        if (forigin < fother){
            return true;
        }
        return false;
   }

   bool operator>=(const Fraction &other){
        double forigin = (long double)numerator/(long double)denominator;
        double fother  = (long double)other.numerator/(long double)other.denominator;

        if (forigin >= fother){
            return true;
        }
        return false;
   }

   bool operator<=(const Fraction &other){
        double forigin = (long double)numerator/(long double)denominator;
        double fother  = (long double)other.numerator/(long double)other.denominator;

        if (forigin <= fother){
            return true;
        }
        return false;
   }
    
    Fraction abs(){//Absolute of the fraction
        simplify();
        long long store = numerator;
        if (store < 0){
            store *=-1;
        }
        Fraction absolute(store, denominator);
        return absolute;

    };

    constexpr Fraction pow(int x){ //To the power of
        Fraction result(1,1);
        
        for (unsigned i = 0;  i < x;  ++i){
            result *= *this;
        }

        return result;
    }
};

//Now outside of class

//Regular falsi implementation
Fraction findRootFalsi(Fraction (*f)(Fraction),Fraction x1, Fraction x2){
    Fraction tolerance(1ll,100000000ll); //Tolerance of 10^-8
    Fraction zero(0ll,1ll);              // Just a 0 fraction 0/1
    
    Fraction middle = (x1*(*f)(x2)  -  x2*(*f)(x1)) / ((*f)(x2) - (*f)(x1));
    
    while( ((*f)(middle)).abs() > tolerance){// While the absolute value at middle is greater than the tolerance away from 0.

        if ( (*f)(middle) <= zero){ //If the value at middle is below 0. Set x1 to middle.
            x1 = middle;
        }
        else{                       //If the value at middle is above 0. Set x2 to middle.
            x2 = middle;
        }
        middle = (x1 * (*f)(x2)  -  x2*(*f)(x1)) / ((*f)(x2) - (*f)(x1));
        std::cout << " " <<  (middle) << std::endl;
        }
    //}
    return middle;
    }

Fraction myQuadratic(Fraction x){ // Simple quadratic to show off regular falsi y = x^2 - 2
    return (x * x) -Fraction(2,1);
}


int main(){
    
    Fraction root = findRootFalsi(myQuadratic, Fraction(0,1), Fraction(2,1));
    std::cout << "\n Root of x^2 -2 : " << root << std::endl; 

    return 0;
}





