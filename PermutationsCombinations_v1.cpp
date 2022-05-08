#include <iostream>
#include <math.h>
using namespace std;

void nonNegValid(int* n);
int factorial(int n);
// In the following functions, all the respective formulae are implemented. NCERT Class 11 P & C Chapter is attached for more info.
int P(int n, int r);
int C(int n, int r);
int P_Rep(int n, int r);
int P_ith(int n, int *p, int pSize);
int P_CircularFixed(int n);
int P_CircularFree(int n);

// As we are using integer data type. Entering a float value will automatically be type-casted to the corresponding int value discarding the value after the point.
int main()
{
    cout<<"\n\nProgram to implement various algorithms of the Number of Permutations and Combinations.\n\n";

    char outerChoice;

    do
    {
        cout<<"\n\n----------Permutations & Combinations----------\n\n";

        cout<<"Enter 1, 2, 3, 4, 5, 6 or 7 respectively for \n\n1. Factorial. \n2. Number of Permutations of n different objects taken r at a time where repetition isn't allowed. \n3. Number of Combinations of n different objects taken r at a time where repetition isn't allowed. \n4. Number of Permutations of n different objects taken r at a time where repetition is allowed. \n5. Number of Permutations of n objects (when all the objects are not distinct/different objects; p[i] objects are of ith(same) kind) taken all n at a time where repetition isn't allowed. \n6. Permutations of n different objects taken all at a time (without repetition) in a circular fashion along a fixed (i.e., cannot be picked up out of the plane and turned over) circle. \n7. Permutations of n different objects taken all at a time (without repetition) in a circular fashion along a free (i.e., can be picked up out of the plane and turned over) circle.\n\n";
        int innerChoice;
        cout<<"Enter here: ";
        do // Input validation for 'innerChoice'.
        {
            cin>>innerChoice;
            if(innerChoice < 1 || innerChoice > 7)
                cout<<"\nInvalid entry. Enter again: ";
        } while(innerChoice < 1 || innerChoice > 7);
        
        if(innerChoice == 1)
        {
            cout<<"\n\nEnter a number to find it's factorial: ";
            int n;
            nonNegValid(&n); // Non-negative input validation for 'n'.

            cout << endl << n << "! = " << factorial(n);

            break;
        }
        else
        {
            // The following three statements are common to all remaining innerChoice values. Therefore used an else block first instead of initialising them in each of the following if blocks (if not using the else block) (or in each of the switch blocks - another way to implement). // One way to reduce lines of code.
            int n, r;
            int *p = NULL;
            int pSize;
            if(innerChoice >= 2 && innerChoice <= 4) // Common code for switch case values 2,3, and 4 this reduces lines of code here. Similarly below for 6 and 7 switch case values.
            {
                cout<<"\n\nEnter the values of n and r respectively:\n";
                do // Input validation for 'n' and 'r'.
                {
                    cout<<"\nn = ";
                    nonNegValid(&n); // Non-negative input validation for 'n'.
                    cout<<"r = ";
                    nonNegValid(&r); // Non-negative input validation for 'r'.
                    if(n < r) // 'n' >= 'r' validation.
                        cout<<"\nInvalid entry. Enter again (n >= r only):\n";
                } while(n < r);
            }
            else if(innerChoice == 5)
            {
                cout<<"\n\nEnter the value of n: ";
                cout<<"\nn = ";
                nonNegValid(&n); // Non-negative input validation for 'n'.

                cout<<"\nEnter the number of distinct characters that are repeated (more than once of course) in the given permutation: ";
                nonNegValid(&pSize); // Non-negative validation for 'pSize'.

                p = new int[pSize]; // Dynamic allocation of array p according to the size entered above.
                
                cout<<"\nEnter the count of each distinct character's repetition:\n";
                for(int i = 0; i < pSize; i++)
                {
                    do // Input validation for each of the array p's values (one iteration for one value's validation).
                    {
                        cin>>p[i];
                        if(p[i] < 2)
                            cout<<"\nRepeated character means a character that has been repeated more than once. Enter again: ";
                    } while (p[i] < 2);
                }
            }
            else // if(innerChoice == 6 || innerChoice == 7)
            {   
                cout<<"\n\nEnter the value of n: ";
                cout<<"\nn = ";
                nonNegValid(&n); // Non-negative input validation for 'n'.
            }

            switch(innerChoice) // Can also do the above things of the if, else-if, and else blocks below. But I didn't to not complicate the switch case (to avoid repetition of code also) and also to keep it neat.
            {
                case 2: cout << "\nP(" << n << ", " << r << ") = " << P(n,r); break;
                case 3: cout << "\nC(" << n << ", " << r << ") = " << C(n,r); break;
                case 4: cout << "\nP_Rep(" << n << ", " << r << ") = " << P_Rep(n,r); break;
                case 5: cout << "\nP_ith(" << n << ") = " << P_ith(n, p, pSize); break;
                case 6: cout << "\nP_CircularFixed(" << n << ") = " << P_CircularFixed(n); break; 
                case 7: cout << "\nP_CircularFree(" << n << ") = " << P_CircularFree(n); break; 
            }
        }

        cout<<"\n\nDo you wish to run the program again: (Enter 'Y' or 'y'). Else, press any key to exit: ";
        cin>>outerChoice;

    } while(outerChoice == 'Y' || outerChoice == 'y');

    cout<<endl<<endl;
    return 0;
}

void nonNegValid(int* num) // This function is used for all non-negative input validations. Uses a pointer in the parameter. Could have also used a return value instead.
{
    do
    {
        cin>>*num;
        if(*num < 0)
            cout<<"Invalid input. Enter again (Only non-negative integral values): ";
    } while (*num < 0);
}

int factorial(int n) // 1
{
    int  f = 1;

    for(int i = 1 ; i <= n; i++)
        f *= i;

    return f;
}

int P(int n, int r) // 2
{
    return factorial(n) / factorial(n-r);
}

int C(int n, int r) // 3
{
    return P(n,r) / factorial(r);
}

int P_Rep(int n, int r) // 4
{
    return pow(n,r);
}

int P_ith(int n, int *p, int pSize) // 5
{
    int ans;
    ans = factorial(n);
    for(int i = 0; i < pSize; i++)
        ans = ans/factorial(p[i]);

    return ans;
}

int P_CircularFixed(int n) // 6
{
    if(n >= 3)
        return factorial(n-1); // When clockwise and anticlockwise orders are different. // Not n! because the circle can be rotated. // Also, as there are no corner values or no start/end values (each value lies in between another two values), of course as values are arranged in the form of a circle.
    else
        return 1;
}

int P_CircularFree(int n) // 7
{
    if(n >= 3)
        return factorial(n-1) / 2; // When clockwise and anticlockwise orders are the same. // Half of the fixed circle's one as the circle can be picked up out of the plane and turned over. So, due to an object being left or right of another object - 2 cases in the fixed one are now only one case here. in the free one: same object on the right as well as left of another object by looking from one side or another accordingly. // Left or right means immediate left or immediate right.
    else
        return 1;
}

// For fixed circular ones, think of a meeting of people sitting on a round table.
// For free circular ones, think of a necklace with different colored beads.

// For n < 3, there are same number of permutations for both the fixed and free circle ones.