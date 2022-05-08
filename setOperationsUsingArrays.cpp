#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

// Used template just to show how to use it but implementation of only integer set is done.
template <typename T>
class Set // Class containing a set (with or without duplicates accordingly as we see in the program), its size (with or without duplicates accordingly as we see in the program) and its associated functions.
{
    public:

    int setSize;
    T* set;

    void setCardinality(); // 1
    Set<T> setUnion(Set s2); // 2
    Set<T> setIntersection(Set s2); // 3
    Set<T> setDifference(Set s2); // 4
    void setSymmetricDifference(Set s2); // 5
    void setComplement(Set s2); // 6
    void numOfSubsets(); // 7
    void setSubsets(); // 8
    bool checkSetSubset(); // 9
    bool checkSetSuperset(); // 10
    void checkElementBelongsTo(); // 11
    void checkSetEqual(); // 12
    void checkSetEquivalent(Set s2); // 13
    void setPowerSet(); // 14
    void removeDuplicates();
    void setDisplay();
    // The last two unnumbered functions (in the comments) aren't used directly by the user. They're used by other functions. Also, later we have defined three functions which are also not used directly by the user but are used by other functions. They're not members of the class as they aren't related to Sets' operations that closely.
};

template <typename T>
void Set<T> :: removeDuplicates() // Removes duplicate elements in the entered set if any are there. // Always used after inputting the sets' elements so that functions get the set(s) without duplicate elements.
{
    int cur;
    for(int i = 0; i < setSize ; i++)
    {
        cur = set[i]; // variable 'cur' holds the current element that is checked for duplicates with the remaining elements in front of it till the last element in the set.
        for(int j =  i + 1; j < setSize ; j++)
        {
            if(set[j] == cur) // If a duplicate element is found, 
            {
                for(int k = j; k < setSize - 1; k++)
                    set[k] = set[k+1]; // then all the elements from the position next to it are shifted backwards to delete the duplicate element (by overwriting it by the next element that is shifted 1 position backward to the place of the duplicate element). 
                
                setSize--; // After the deletion of 1 duplicate element, we decrement the set size by 1. All the elements after deleting the duplicate element are preserved(except of course the duplicate element as it is deleted). The elements from after the duplicate's element position till the last element were shifted once backward and then the size was decremented by one which decrements the array size by 1. So, shifting the elements (in this way as done) preserved the elements and deleted the duplicate element too. As we deleted one element and we already have all the elements till size-1 due to shifting (we shifted to delete the duplicate), we decrement the set size by 1 as after shifting we have one extra space in the array due to an element's deletion. Decrement of size takes place from the last location. We shifted the elements backwards, so, the last space is the extra one itself which we remove from the array/set by decrementing the size.
            }
        }
    }
}

template <typename T>
void Set<T> :: setDisplay() // Displays all the set elements.
{
    cout<<"\n{ ";
    for(int i = 0; i < setSize; i++)
    {
        cout<<set[i]<<" ";
    }
    cout<<"}\n";
}

template <typename T>
void Set<T> :: setCardinality() // 1 // Displays the number of elements present in the set. (After removing duplicates if any are there.)
{
    cout<<"\nThe cardinality of the entered set is: "<<setSize;
}

template <typename T>
Set<T> Set<T> :: setUnion(Set s2) // 2 // This function performs the union of the set in the object which called this function with the set in the object passed as its argument.
{
    Set setUnionObj; // This Set object will contain the set union of the two sets.
    setUnionObj.setSize = setSize + s2.setSize; // Maximum size of the union of two sets is taken as default.
    
    //The two for loops below put all the elements of the both sets with or without repeition in the union set (that's why we used the maximum size above as the default size). After the loops, we remove duplicates from the union set if there are any. The size of the union set is reduced if it is needed (if duplicates exist) in the removeDuplicates() itself. The size of the union set remains the max size itself if both the sets are disjoint sets.
    for(int i = 0; i < setSize; i++)
        setUnionObj.set[i] = set[i];
    for(int i = setSize, j = 0; j < s2.setSize; i++, j++)
        setUnionObj.set[i] = s2.set[j];
    
    setUnionObj.removeDuplicates();

    cout<<"\nThe union of the two sets is: ";
    setUnionObj.setDisplay();

    return setUnionObj; // Returning the Set object containing the union set.
}

template <typename T>
Set<T> Set<T> :: setIntersection(Set s2) // 3 // This function performs the intersection of the set in the object which called this function with the set in the object passed as its argument.
{
    Set setInterObj; // This Set object will contain the set with the intersection of the two sets.
    setInterObj.setSize = 1; // Initially the size of the intersection set is 1.
    setInterObj.set = new int[setInterObj.setSize]; // 'new' operator is used to dynamically allocate an array, i.e., an array of the specified size at the run-time. In C++, the static arrays' syntax in some compilers work as dynamic array itself. So by using any of the syntax here along with operators such as ++ or --, we can change the size of an array at run-time according to the current instance of the program. Working is shown below as well:
    for(int i = 0; i < setSize; i++)
        for(int j = 0; j < s2.setSize; j++)
            if(set[i] == s2.set[j]) // if the current element in first set equals the current element in the second set.
            {
                setInterObj.set[setInterObj.setSize - 1] = set[i]; // Then put that element in the intersection set. The index here is one less than the size of the intersection set. Initially it was set to 1. So, we put the first element in it at position 0, and increment the size for the second element (This technique works as we start with an initial intersection set size of 1 for the first element and whenever we get to know that an element exists to be put intersection set, at that time itself after putting that element in the set, we are incrementing the size for the next element. If the next element doesn't exist we decrement the one unused space in the array after the loops. So successively incrementing the set size (creating space) for the next element (to be put at size - 1 in the next iteration) according to the currently available element dynamically makes this technique of indexing the array with the its size work). If there is not a second element then we decrement the size once after all the loops as the second element doesn't exist to be put. Also, if the first element (no element) also does not exist to be put in the intersection set. Then after we exit the loops we decrement the initial default size by 1 to get a size of 0 to imply an empty set as the intersection set. Similarly for any number of elements for the intersection set if they exist. 
                setInterObj.setSize++; // Incrementing the size of the array dynamically.
                break; 
            }
    
    setInterObj.setSize--; // Decrementing the size of the array dynamically.
    cout<<"\nThe intersection of the two sets is: ";
    setInterObj.setDisplay();

    return setInterObj; // Returning the Set object containing the intersection set.
}

template <typename T>
Set<T> Set<T> :: setDifference(Set s2) // 4 // This function performs the set difference of the set in the object which called this function minus the set in the object passed as its argument.
{
    Set setDiffObj; // This object will contain the set containing the set difference A - B.
    setDiffObj.setSize = 1; // Same as explained in the setIntersection().
    setDiffObj.set = new int[setDiffObj.setSize]; // Same as explained in the setIntersection().
    int flag; // flag is used to check whether A and B have a common element or not.
    for(int i = 0; i < setSize; i++) // Iterating through each element of the first set.
    {
        flag  = 0; // for each element we initially set flag to 0 to indicate it doesn't lie in A intersection B, i.e., there is no element in the second set which is same as the current element.

        for(int j = 0; j < s2.setSize; j++) // // Iterating through each element of the second set and checking:
            if(set[i] == s2.set[j]) // if we have a common element then we don't put that in the set difference's set. Each element of the first set is compared with each element of the second set.
            {
                flag = 1; // flag is set to 1 to indicate that the current element is exists in both the sets, i.e., it is common to both the sets. So, we won't put it in the set difference's set.
                break; // As soon as we find a match/common element, we indicate this by setting flag to 1 and breaking out of the j-for loop as we don't need to check further as we have got the only one match that exists if it exists and there are no duplicates in either of the sets.
            }
        // for the flag = 1 case, we ignore (don't do anything) that element of the first according to the definition of set difference.
        if(flag == 0) // If we don't have the current element as the common element (flag remains 0) then we put that element(of the first set - according to the definition of set difference) in the set difference's set.
        {
            setDiffObj.set[setDiffObj.setSize - 1] = set[i]; // Same as explained in the setIntersection().
            setDiffObj.setSize++; // Same as explained in the setIntersection().
        }    
    }

    setDiffObj.setSize--; // As explained in the setIntersection().
    cout<<"\nThe set difference A - B = ";
    setDiffObj.setDisplay();

    return setDiffObj; // Returning the Set object containing the set difference set.
}

template <typename T>
void Set<T> :: setSymmetricDifference(Set s2) // 5
{
    Set symDiffObj = ((*this).setDifference(s2)).setUnion(((s2).setDifference(*this))); // Here we use A sym Diff B = (A - B) union (B-A). We do this here by first getting the set difference A-B and using the returned object which contains A-B, we call the union function to get its union with the passed object. The passed object here is again the returned object containing set difference B-A. // 'this' pointer points to the current object (The object which was used to call this function).
    cout<<"\nThe symmetric set difference is ";
    symDiffObj.setDisplay();
}

template <typename T>
void Set<T> :: setComplement(Set s2) // 6
{
    Set setCompObj = s2.setDifference(*this);
    cout<<"\nThe complement of the set with respect to the universal set entered is: ";
    setCompObj.setDisplay();
}

template <typename T>
void Set<T> :: numOfSubsets() // 7
{
    cout<<"\nNumber of subsets possible of the entered set = "<<pow(2, setSize);
}

template <typename T>
void Set<T> :: setSubsets() // 8
{
    int powerSetSize = pow(2, setSize); // Number of subsets = Number of elements in the powerset.
    for(int j = 0; j < powerSetSize; j++) // Comment - 1 at the end of the whole Program.
    {
        int eachBinVal[setSize] = {0}; // Initially this array has all zereos for all its elements. This array will contain each binary digit of a number in decimal converted to binary. 
        int k = j; // k is assigned the current decimal number in the counting as we need to manipulate j to convert it to binary, and j is also the counter, therefore we assign it to a temporary variable k and do the manipulation on k instead of j such that for the next iteration the counter value remains preserved which will be incremented in the next iteration.
        int b = 0; // variable 'b' is used to insert the values to the array eachBinVal[setSize].
        while(k != 0) // converting the current j value from decimal to binary and inserting each bit to the array. (order of insertion of the bits isn't important as we're not trying to convert the decimal number to it's binary equivalent instead our aim is to get that binary (permutation) corresponding to the decimal number. For eg in 3-bits: 3 is 011 in binary but we store 110 (in the opposite order) instead and from 5 (which is 110 in binary) we get 011, so we got both the permutations of the bits. Similarly for all possible permutations of 3 bits. And so on for n bits). Permutation is not used for the element itself but for the bits in the binary number array, where 1 and 0 represent respectively whether an element will be present or not.
        {
            eachBinVal[b] = k % 2;
            k = k / 2;
            b++;
        }

        // In the code below till the end of this outer for-loop iteration, we are printing the current subset.
        cout<<"\n{ "; // Current subset brace open.
        for(int q = 0; q < setSize; q++)  // Each iteration of this for loop prints each element of the current subset as this for loop is inside the outer-for loop.
        {
            if(eachBinVal[q] == 1) // For the current permutation of bits obtained from the above while loop we print the corresponding elements accordingly(as explained in the above comments).
                cout<<set[q]<<" ";
        }  
        cout<<"}   "; // Current subset brace closed. // Elements of a subset are separated by a single white space and the subsets are separated by three white-spaces.
    }
}

template <typename T>
bool Set<T> :: checkSetSubset() // 9
{
    cout<<"\nEnter the size of the set to be checked: ";
    int subSize;
    do // Input validation for variable 'subSize'. Here we don't check whether the size is greater than the main set itself as the user can enter duplicate elements which we later remove. This is one implementation.
    {
        cin >> subSize;
        if(subSize < 0)
            cout<<"\nSize of any set >= 0. Enter again: ";
    } while (subSize < 0);

    if(subSize == 0)
        cout<<"\nThe entered set contains no elements as it's size is 0. Entered set = { } is a subset of every set.\n";
    else // If the size of the subset to be checked is > 0.
    {
        Set subCheckObj; // Object containing the subset that is to be entered below and checked.
        subCheckObj.setSize = subSize;
        subCheckObj.set = (int*) new int[subCheckObj.setSize];
        // the above two lines or subCheckObj.set[subCheckObj.setSize]; // Explained above in setIntersection() regarding the static and dynamic array syntax. 
        cout<<"\nEnter set elements (with or without repetition):\n";
        for(int i = 0; i < subSize; i++)
            cin >> subCheckObj.set[i];
        
        subCheckObj.removeDuplicates();

        int flag[subSize] = {0}; // flag array is used to check whether each of the elements in the subset are in the set or not. Initially all its elements are 0 to indicate no element of the subset is also in the set (of course as we haven't started checking).
        for(int i = 0; i < subCheckObj.setSize; i++)
        { // Outer loop is iterating on the subset's elements and the inner on the set's elements as we need to check each subset's element with all of the set's elements and not vice versa.
            for(int j = 0; j < setSize; j++)
            {
                if(subCheckObj.set[i] == set[j]) // If the subset's current element is also in the main set. Then we set flag[subset's current element position(i.e., the corresponding location to the current subset element in the flag array)] as 1 to indicate that the current element of the subset is in the set too. // Here the term corresponding is explained in the above function.
                {
                    flag[i] = 1;
                    break;
                }
            }
        }

        int flagFinal = 0; // To check if ALL the elements of the subsets are in the set or not.
        for(int i = 0; i < subCheckObj.setSize; i++)
        {
            if(flag[i] == 0) // If ith flag array's value is 0, that means, that the corresponding element of the subset at position i is not in the set. Then we set the flagFinal variable to 1 to indicate that we've got atleast one element which is in the subset but not in the set, so no need to check further (we use break), and we deduce that the set in the subset object is not a subset of the main set. Else if all the elements of the subset are in the set, then all the flag array's values will be 1 from the above code itself, and flagFinal value would also remain as 0 (due to this if condition being false everytime) as it was initialised. And hence we can then say that the subset is a subset of the set.
            {
                flagFinal = 1; 
                break;
            }
        }

        if(flagFinal == 1)
        {
            cout<<"\nNot a subset.\n";
            return false;
        }
        else
        {
            cout<<"\nIt's a subset.\n";        
            return true;
        }
    }
}

template <typename T>
bool Set<T> :: checkSetSuperset() // 10 // Identical to the above function except here we check whether all the elements of the first set are in the second set, i.e., if second set is a superset of the first set or not. // Comments - As explained in the above function - analogous to that.
{
    cout<<"\nEnter the size of the set to be checked: ";
    int supSize;
    do
    {
        cin >> supSize;
        if(supSize < 0)
            cout<<"\nSize of any set >= 0. Enter again: ";
    } while (supSize < 0);

    Set supCheckObj;
    supCheckObj.setSize = supSize;
    // or subCheckObj.set[subCheckObj.setSize];
    supCheckObj.set = (int*) new int[supCheckObj.setSize];
    cout<<"\nEnter set elements (with or without repetition):\n";
    for(int i = 0; i < supSize; i++)
        cin >> supCheckObj.set[i];
    
    supCheckObj.removeDuplicates();

    int flag[setSize] = {0};
    for(int i = 0; i < setSize; i++) 
    {
        for(int j = 0; j < supCheckObj.setSize; j++)
        {
            if(set[i] == supCheckObj.set[i])
            {
                flag[i] = 1;
                break;
            }
        }
    }

    int flagFinal = 0;
    for(int i = 0; i < setSize; i++)
    {
        if(flag[i] == 0)
        {
            flagFinal = 1;
            break;
        }
    }

    if(flagFinal == 1)
    {
        cout<<"\nNot a superset.\n";
        return false;
    }
    else
    {
        cout<<"\nIt's a superset.\n";        
        return true;
    }
}

template <typename T>
void Set<T> :: checkElementBelongsTo() // 11 // Checks if an element belongs to the entered set or not.
{
    cout<<"\n\nEnter the element to be checked whether it is in the entered set or not: ";
    int ele;
    cin>>ele;

    int flag = 0; // Flag is used to track whether we have found that element in the set or not. // Initially it is set to 0 to indicate we have not found the element in the set 'yet' (of course as we haven't checked yet).
    for(int i = 0; i < setSize; i++)
    {
        if(set[i] == ele) // If we find that element in the set, then we set flag to 1 to indicate that element exists in the set and we exit checking further using the break statement. (Extra info: Set doesn't contain duplicates so only one instance of that element exists)
        {
            flag = 1; // We only set flag to 1 if we have found the element's match in the set. Otherwise, flag remains 0 to indicate no match found.
            break;
        }
    }

    if(flag == 1)
        cout<<"\nElement belongs to the entered set.\n";
    else // flag == 0 // When no element's match in the set is found the flag as it was initially 0 remains 0 as we don't enter the if statement in the for loop above.
        cout<<"\nElement does not belong to the entered set.\n";
}

template <typename T>
void Set<T> :: checkSetEqual() // 12 // Here we have used the logic if A is a subset of B (or B is the superset of A using checkSetSuperset()) and B is a subset of A (checkSetSubset()), then A = B. // P is a subset of Q <=> Q is a superset of P.
{
    cout<<"\nBased on both ways subsets'/supersets' condition. Initially checks whether the entering set is a subset of the entered set or not and then checks whether the entering set is a superset of the entered set or not.\n";
    if(checkSetSubset() && checkSetSuperset())
        cout<<"\nEqual.";
    else
        cout<<"\nUnequal.";
}

template <typename T>
void Set<T> :: checkSetEquivalent(Set s2) // 13 // If number of elements (of course after removing duplicates as already we've done that in main()) of both the sets are same, they're said to be equivalent, else they're said to be not equivalent.
{
    if(setSize == s2.setSize)
        cout<<"\nThe sets are equivalent.\n";
    else   
        cout<<"The sets aren't equivalent.\n";
}

template <typename T>
void Set<T> :: setPowerSet() // 14 // Subsets separated by commas/spaces inside braces form the power set. A set of subsets of a set is called a power set.
{
    cout<<"\n{   ";
    setSubsets();
    cout<<"}   ";
}

int factorial(int n) // Returns the factorial of 'n'.
{
    int  f = 1; // initially it is 1 so that if n = 0, we don't enter the loop and we return 1 as 0! = 1. Also, if n != 0, then too in the loop, multiplications starts from initial value of i which is 1 itself till n. So, initially, we get 1*1 = 1 (if n >= 1), and so on (if n > 1).

    for(int i = 1 ; i <= n; i++)
        f *= i;

    return f;
}

int P(int n, int r) // Number of permutations of 'n' different objects taken 'r' at a time without repetition.
{
    return factorial(n) / factorial(n-r);
}

int C(int n, int r) // Number of combinations of 'n' different objects taken 'r' at a time without repetition. 
{
    return P(n,r) / factorial(r);
}

int main()
{
    cout<<"\n\nProgram to implement set operations using arrays.\n\n";

    char outerChoice;
    int innerChoice;

    do
    {
        cout<<"\n\n\n\n-----------Set-Operations-----------";

        cout<<"\n\nEnter 1, 2 or 3 for an integer-valued set, a real-valued set or a character valued set: ";
        int typeChoice;
        do // Input validation for variable 'typeChoice'.
        {
            cin>>typeChoice;
            if(typeChoice < 1 || typeChoice > 3)
                cout<<"\nInvalid entry. Enter again: ";
        } while (typeChoice < 1 || typeChoice > 3);

        switch(typeChoice)
        {
            case 1: // Used template just to show how to use it but implementation of only integer set is done.

                    Set<int> setObj; 

                    cout<<"\nEnter the size (number of elements to be inputted in the set - with or without repetion) of the set (first): "; 
                    do // Input validation for variable 'setObj.setSize'.
                    {
                        cin>>setObj.setSize;
                        if(setObj.setSize < 0)
                            cout<<"\nInvalid entry. Size of a set cannot be negative. Enter again: ";
                    } while(setObj.setSize < 0);

                    setObj.set = (int*) new int[setObj.setSize]; // Dynamic Array Allocation to represent the set.

                    cout<<"\nEnter set elements:\n";
                    for(int i = 0; i < setObj.setSize; i++)
                        cin>>setObj.set[i];

                    setObj.removeDuplicates(); // Therefore, no function gets a set containing duplicate elements.

                    cout<<"\n\nThe first set is: ";
                    setObj.setDisplay();

                    cout<<"\nOperations: \n1. Cardinality \n2. Union \n3. Intersection \n4. Difference \n5. Symmetric-Difference \n6. Complement \n7. Find the number of subsets/Number of elements in the Power Set. \n8. Find all subsets \n9. Check whether an entered set is a subset of the entered set or not. \n10. Check whether an entered set is a superset of the entered set or not. \n11. Check whether an entered element belongs to the entered set or not. \n12. Check whether the entered two sets are equal or not. \n13. Check whether the entered two sets are equivalent or not. \n14. Find the Power Set. \n\n";

                    cout<<"Enter choice here: ";
                    do // Input validation for variable 'innerChoice'.
                    {
                        cin>>innerChoice;
                        if(innerChoice < 1 || innerChoice > 14)
                            cout<<"\nInvalid entry. Enter again: ";
                    } while(innerChoice < 1 || innerChoice > 14);
                    
                    if(innerChoice >= 2 && innerChoice <= 6 || innerChoice == 13) // For these values (operations) we need a second set too as they're binary operations.
                    {
                        Set<int> secSetObj;

                        if(innerChoice != 6) // Change in the cout statements only.
                            cout<<"\nEnter the size (number of elements to be inputted in the set - with or without repetion) of the set (second): "; 
                        else
                            cout<<"\nEnter the size (number of elements to be inputted in the set - with or without repetion) of the universal set: ";
                        do // Input validation for variable 'secSetObj.setSize'.
                        {
                            cin>>secSetObj.setSize;
                            if(secSetObj.setSize < 0)
                                cout<<"\nInvalid entry. Enter again: ";
                        } while(secSetObj.setSize < 0);

                        secSetObj.set = (int*) new int[secSetObj.setSize];

                        cout<<"\nEnter set elements:\n";
                        for(int i = 0; i < secSetObj.setSize; i++)
                            cin>>secSetObj.set[i];

                        secSetObj.removeDuplicates(); // Therefore, no function gets a set containing duplicate elements.

                        cout<<"\n\nThe second set is: ";
                        secSetObj.setDisplay();
                        cout<<"\n\n";

                        switch(innerChoice)
                        {
                            case 2: setObj.setUnion(secSetObj); break;
                            case 3: setObj.setIntersection(secSetObj); break;
                            case 4: setObj.setDifference(secSetObj); break;
                            case 5: setObj.setSymmetricDifference(secSetObj); break;
                            case 6: setObj.setComplement(secSetObj); break;
                            case 13: setObj.checkSetEquivalent(secSetObj); break;
                        }
                    }
                    else // These operations do not require a second operand. They're unary operations on a set.
                    {
                        switch(innerChoice)
                        {   
                            case 1: setObj.setCardinality(); break;
                            case 7: setObj.numOfSubsets(); break;
                            case 8: setObj.setSubsets(); break;
                            case 9: setObj.checkSetSubset(); break;
                            case 10: setObj.checkSetSuperset(); break;
                            case 11: setObj.checkElementBelongsTo(); break;
                            case 12: setObj.checkSetEqual(); break;
                            case 14: setObj.setPowerSet(); break;
                        }
                    }
        }
        cout<<"\n\nDo you wish to run the program again: (Enter 'Y' or 'y'). Else, press any key to exit: ";
        cin>>outerChoice;
    } while (outerChoice == 'Y' || outerChoice == 'y');
    cout<<"\n\n";
    return 0;
}

/* Comment 1:

// Each iteration corresponds to each subset/each element in the powerset. // As the number of subsets is "2" to the POWER of number of
elements in the set n, (Also, 2^n = nC0 + nC1 + nC2 + ... + nCn. So, 2^n represents the number of all the possible combinations of the n
elements in the set taken r at a time where 0 <= r <= n (without repetition). Combinations as order of elements is irrelevent in sets.
(Same elements in different orders in two or more sets are the same set.)), that's why, each subset correspond to a "binary" number
(counting from 0 to 2^n - 1 in decimal) (and each binary number represents a permuatation of n bits <=> combination of 'n' elements of 
the set taken 'r' at a time (of course without repetition). Eg: Set containing 3 elements say {1,2,3}, permutations of the following 3 
'BITS': 011 are 011,101,110, each correspond to a subset: {2,3}, {1,3}, {1,2}, inside each of these subsets the order is irrelevent of the
elements. That's why these 3 subsets are combination of 3 'ELEMENTS' taken 2 at a time. Permutation of bits (as we need all the bit 
patterns) as each bit pattern (is unique) in that order selects different different elements as the elements in the set are in order in
the array in which they were inputted.) of size n (n bits can represent binary numbers from 0 to 2^n - 1), where inside any subset a 0 
will indicate that that corresponding element from the set(whose subsets we are finding here) won't be present in the current subset and
a 1 indicates that it'll be present (Here order of the elements stays same in a set as they're inputted in an array. So, 'corresponding 
element' makes sense here - only to read (corresponding) elements from the set according to the current binary number).

*/