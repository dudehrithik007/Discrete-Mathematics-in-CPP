#include <iostream>
#include <math.h> // Used only for power function.
using namespace std;

// Elements of each set are separated by a blank space.

void cartesianProduct();
void inverseRelation();
int** ioRelation(int &m);
bool reflexiveCheck(int** relation, int m);
bool symmetricCheck(int** relation, int m);
bool transitiveCheck(int** relation, int m);
void equivalenceCheck(int** relation, int m);
void emptyCheck(int** relation, int m);
void universalCheck(int** relation, int m);
void identityCheck(int** relation, int m);
void irreflexiveCheck(int** relation, int m);
void asymmetricCheck(int** relation, int m);
void antisymmetricCheck(int** relation, int m);

int main()
{
    cout<<"\n\nProgram to find the Cartesian Product of two sets entered by the user, the inverse of a relation entered by the user, and to check and display the name of the type of the relation entered by the user.\n\n";

    char outerChoice;
    do
    {
        cout<<"\n\n-----------RELATIONS V1-----------\n";

        cout<<"\n1. Finding Cartesian Product. \n2. Finding the inverse of a relation. \n3. Reflexive check. \n4. Symmetric check. \n5. Transitive check. \n6. Equivalence check. \n7. Empty/Null/Void check. \n8. Full/Universal check. \n9. Identity check. \n10. Irreflexive check. \n11. Asymmetric check. \n12. Anti-Symmetric check.\n";

        cout<<"\nAll relations are inputted in terms of a 0-1 2D-Matrix.\n";

        cout<<"\n\nEnter choice here: ";
        int innerChoice;
        do // Input validation for variable 'innerChoice'.
        {
            cin >> innerChoice; 
            if(innerChoice < 1 || innerChoice > 12)
                cout<<"\nInvalid entry. Enter again: ";
        } while(innerChoice < 1 || innerChoice > 12);

        if(innerChoice == 1 || innerChoice == 2) // 
        {
            switch(innerChoice)
            {
                case 1: cartesianProduct(); break;
                case 2: inverseRelation(); break;
            }
        }
        else // For choices other than choice 2 and choice 1 (choice 1 is only taking two sets and finding their cartesian product, so no talk of a relation exists for it), the relation is on a set (same set) rather than two distinct sets. As for choice 2, we input the sets from which the relation is made and the relation and display the inverse of it inside the function itself. For choices other than 1 and 2, we need the following first two statements of this else block.
        {
            // The following two statements are used here itself for initialisation of the relation to avoid calling them separately in each function as each function requires the following same first two statements. We use pointers here (can also use return by reference) to get the array (the relation entered by the user) returned by ioRelation() and then pass that array (relation) to each of the functions. Each function checks on that relation, that's why we don't initialise the array (the relation) separately in each function as each function needs a relation entered by the user.
            int m; // The size of the set from which the relation which is to be entered by the user has been formed.
            int** relation = ioRelation(m); 
            switch(innerChoice)
            {
                case 3: reflexiveCheck(relation, m); break;
                case 4: symmetricCheck(relation, m); break;
                case 5: transitiveCheck(relation, m); break;
                case 6: equivalenceCheck(relation, m); break;
                case 7: emptyCheck(relation, m); break;
                case 8: universalCheck(relation, m); break;
                case 9: identityCheck(relation, m); break;
                case 10: irreflexiveCheck(relation, m); break;
                case 11: asymmetricCheck(relation, m); break;
                case 12: antisymmetricCheck(relation, m); break;
            }
        }
        cout<<"\nDo you wish to re-run? Enter any key to exit except 'y' or 'Y' to re-run: ";
        cin >> outerChoice;
    } while (outerChoice == 'y' || outerChoice == 'Y');

    cout<<"\n\n";
}

void cartesianProduct() // 1
{
    cout<<"\nEnter the size of the first set: ";
    int size1;
    do // Input validation for variable 'size1'.
    {
        cin >> size1;
        if(size1 < 0)
            cout<<"\nSize of a set cannot be negative. Enter again: ";
    } while (size1 < 0);

    cout<<"Enter the elements in the first set:\n";
    int* set1 = new int[size1]; // Dynamically allocating an array of size as entered above by the user.
    for(int i = 0; i < size1; i++)
        cin >> set1[i];

    cout<<"\nEnter the size of the second set: ";
    int size2;
    do // Input validation for variable 'size2'.
    {
        cin >> size2;
        if(size2 < 0)
            cout<<"\nSize of a set cannot be negative. Enter again: ";
    } while (size2 < 0);

    cout<<"Enter the elements in the second set:\n";
    int* set2 = new int[size2]; // Dynamically allocating an array of size as entered above by the user.
    for(int i = 0; i < size2; i++)
        cin >> set2[i];
    
    // Displaying the first set and the second set in the format: "{first} x {second}": 
    cout<<"\n{ ";
    for(int i = 0; i < size1; i++)
        cout << set1[i] << " ";
    cout<<"} x { ";
    for(int i = 0; i < size2; i++)
        cout << set2[i] << " ";
    cout<<"} = ";


    // Performing and displaying the cartesian product:
    cout<<"{   ";
    for(int i = 0; i < size1; i++) // Each element (set1[i]) of the first set (which comes at the first position in the ordered pairs).
    {
        for(int j = 0; j < size2; j++) // with each element (set2[j]) of the second set (which comes at the second position in the ordered pairs).
        {
            cout << "( " << set1[i] << " " << set2[j] << " )   "; // Printing the ordered pairs accordingly as explained above in the comments.
        }
    }
    cout<<"} \n\n";

    cout<<"Number of elements in the Cartesian Product = "<<(size1*size2)<<endl<<endl; 
}

/* 

A relation is represented here in terms of a 0-1 matrix. Each row represents an element of the first set (in the order in which the
elements were entered in the array representing the first set) and each column represents an element of the second set ("). An entry of
1 in the array/matrix at (i,j)th position means that an ordered pair is present in the relation consisting of the elements represented
by that row and that column. Similarly, an entry of 0 means that that ordered pair isn't present in the relation.

*/
void inverseRelation() // 2
{
    cout<<"\n\nEnter the number of elements in the first set of the relation to be entered: "; // Size of the first set from which the relation is formed equals the number of rows of the relation-matrix as each row represents an element of the first set, i.e., the first element of an ordered pair of the relation.
    int m;
    do // Input validation for variable 'm'.
    {
        cin >> m;
        if(m < 0)
            cout<<"\nNumber of elements cannot be negative. Enter again: ";
    } while (m < 0);

    int* set1 = new int[m]; // First Set from which the relation is formed. // Dynamically allocating an array of size as entered by the user above.
    cout<<"\nEnter the first set: \n";
    cout<<"{\n";
    for(int i = 0; i < m; i++)
        cin>>set1[i];
    cout<<"}\n";

    cout<<"\nEnter the number of elements in the second set of the relation to be entered: "; // Size of the Second set from which the relation is formed equals the number of columns of the relation-matrix as each column represents an element of the second set, i.e., the second element of an ordered pair of the relation.
    int n;
    do // Input validation for variable 'n'.
    {
        cin >> n;
        if(n < 0)
            cout<<"\nNumber of elements cannot be negative. Enter again: ";
    } while (n < 0);

    int* set2 = new int[n]; // Second Set from which the relation is formed. // Dynamically allocating an array of size as entered by the user above.
    cout<<"\nEnter the second set: \n";
    cout<<"{\n";
    for(int i = 0; i < n; i++)
        cin>>set2[i];
    cout<<"}\n";

    cout<<"\nEnter the relation in the 0-1 matrix:\n"; // The following three lines dynamically allocates a 2D array of size as entered by the user above.
    int** relation = (int**) new int*[m]; // 'relation' is a pointer to the first pointer of 'm' pointers to integers.
    for(int i = 0; i < m; i++)
        relation[i] = (int*) new int[n]; // 'relation[i]' (each of the 'm' pointers) is a pointer to the first element of an array of 'n' integer values.

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            do
            { // Input validation for each element of the array (due to 0-1 matrix representation of a relation).
                cout<<"\n["<<i<<"]["<<j<<"] = ";
                cin>>relation[i][j];
                if(relation[i][j] != 0 && relation[i][j] != 1)
                    cout<<"\n\nInvalid entry. Enter again:\n\n";
            } while(relation[i][j] != 0 && relation[i][j] != 1);
        }
    }

    cout<<"\nThe entered relation in matrix form is:\n\n";
    cout<<"    ";
    for(int i = 0; i < n; i++)
        cout<<set2[i]<<" "; // Each column corresponding to an element of the second set. // This statement in the for loop is used only to show in the output what each column represents for helping the user see the (second element in) ordered pairs at a glance.
    cout<<endl<<"  ";
    for(int i = 0; i < n; i++)
        cout<<"---";
    cout<<endl;
    for(int i = 0; i < m; i++)
    {
        cout<<set1[i]<<" | "; // Each row corresponding to an element of the first set. // This statement in the for loop is used only to show in the output what each row represents for helping the user see the (first element in) ordered pairs at a glance.
        for(int j = 0; j < n; j++)
        {
            cout<<relation[i][j]<<" ";  // This statement prints the elements of the 0-1 relation matrix. Except this statement in this block (separated by two empty lines one above and one below), all are for formatting the display for an easy comprehension of the printed elements' values.
        }
        cout<<endl;
    }

    cout<<"\nThe entered relation in set form is:\n\n";
    cout<<"{"; // Set bracket opened.
    for(int i = 0; i < m; i++) // For traversing the rows of the relation-matrix.
    {
        for(int j = 0; j < n; j++) // For traversing the columns of the relation-matrix.
        {
            if(relation[i][j] == 1) // According to the explanation in the comment block above this function's definition, wherever we have an entry of 1 in the relation-matrix, (we print:) the corresponding row represents the first element (belongs to the first set) of the ordered pair and the corresponding column represents the second element (belongs to the second set) of the ordered pair. The rows' and columns' values respectively are represented by the first set and the second set from which the relation was formed.
            {
                cout<<" ( "<<set1[i]<<" "<<set2[j]<<" ) "; // Each element of the matrix represents an ordered pair.
            }
        }
    }
    cout<<"}\n"; // Set bracket closed.

    /* 
    
    Finding and displaying the inverse: // Inverse of a relation is found by interchanging the first element and the second element of 
    each of the ordered pairs in the original relation. In this implementation, for the matrix-form: as in the original relation each row
    represents an element of the first set of the ordered pairs and each column represent an element of the second set of the ordered
    pairs, we find the transpose of the matrix, i.e., interchanging all the rows and columns of the matrix which means interchanging the
    first and the second elements of all the ordered pairs. The resulting transposed matrix now represents the inverse relation of the 
    original relation. In implementation: a X entry at, ith row representing an element e (belonging to the first set) and jth column
    representing and element f (belonging to the second set) after the transpose becomes a X entry at jth row representing an element f
    (belonging to the second set) and ith column representing an element e (belonging to the first set) thereby interchanging the first
    and the second elements of all the ordered pairs (which are present in the relation when X = 1). X = {0,1}. Now, we read the inverse
    relation in the usual way as we read any relation: for any entry 1 in it, the corresponinding row value(in the original relation it is
    the column value) will be the first element(in the original relation it is the second element) of an ordered pair and the 
    corresponding column value(in the original relation it is the row value) will be the second element(in the original relation it is the
    first element) of the ordered pair. Hence we interchanged the first and second elements of all ordered pairs and found the inverse 
    relation.

    */
    cout<<"\nThe inverse relation in matrix form is:\n\n";
    cout<<"    ";
    for(int i = 0; i < m; i++)
        cout<<set1[i]<<" "; // As explained in the comment above while printing the relation in the matrix form.
    cout<<endl<<"  ";
    for(int i = 0; i < m; i++)
        cout<<"---";
    cout<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<set2[i]<<" | "; // As explained in the comment above while printing the relation in the matrix form.
        for(int j = 0; j < m; j++)
        {
            cout<<relation[j][i]<<" "; // As explained in the comment above while printing the relation in the matrix form.
        }
        cout<<endl;
    }

    cout<<"\nThe inverse relation in set form is:\n\n";
    cout<<"{"; // Set bracket opened.
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(relation[i][j] == 1) // Here instead of using the inverse relation, in this implementation, from the original relation itself, if the entry is 1, we are just printing the corresponding column value (representing the second element of the ordered pair) first and then the corresponding row value (representing the first element of the ordered pair) instead of the opposite as we did in printing the original relation in the set form above.
            {
                cout<<" ( "<<set2[j]<<" "<<set1[i]<<" ) "; // Each ordered pair of the inverse relation. // As explained in the comment above while printing the relation in the set form.
            }
        }
    }
    cout<<"}"; // Set bracket closed.

    cout<<endl<<endl;
}

// The following function inputs the set and its size from which a relation on it is formed and the relation in a 0-1 matrix form. It also displays the relation both in the 0-1 matrix form and in the set form.
int** ioRelation(int &m)
{
    cout<<"\nEnter the number of elements in the set from which the relation to be entered is formed: ";
    do // Input validation for variable 'm'.
    {
        cin >> m;
        if(m < 0)
            cout<<"\nNumber of elements cannot be negative. Enter again: ";
    } while (m < 0);

    int* set = new int[m];
    cout<<"\nEnter the set: \n";
    cout<<"{\n"; // Open Brace.
    for(int i = 0; i < m; i++)
        cin>>set[i];
    cout<<"}"; // Close Brace.

    cout<<"\n\nEnter the relation in the 0-1 matrix:\n"; // Following three statements dynamically allocating a 2D array as explained in the inverseRelation().
    int** relation = (int**) new int*[m];
    for(int i = 0; i < m; i++)
        relation[i] = (int*) new int[m];

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            do // Input validation for each element of the array (due to 0-1 matrix representation of a relation).
            {
                cout<<"\n["<<i<<"]["<<j<<"] = ";
                cin>>relation[i][j];
                if(relation[i][j] != 0 && relation[i][j] != 1)
                    cout<<"\n\nInvalid entry. Enter again:\n\n";
            } while(relation[i][j] != 0 && relation[i][j] != 1);
        }
    }

    // Remaining explanation are comments as in inverseRelation(). Here both the sets are same as the relation is on the same set.
    cout<<"\nThe entered relation in matrix form is:\n";
    for(int i = 0; i < m; i++)
        cout<<set[i]<<" ";
    cout<<endl<<"  ";
    for(int i = 0; i < m; i++)
        cout<<"---";
    cout<<endl;
    for(int i = 0; i < m; i++)
    {
        cout<<set[i]<<" | ";
        for(int j = 0; j < m; j++)
        {
            cout<<relation[i][j]<<" "; 
        }
        cout<<endl;
    }    

    cout<<"\nThe entered relation in set form is:\n\n    ";
    cout<<"\n\n{";
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][j] == 1)
            {
                cout<<" ( "<<set[i]<<" "<<set[j]<<" ) ";
            }
        }
    }
    cout<<"}";

    cout<<"\n\n";

    return relation; // returns the pointer to the first pointer to integers of the relation. In essence, returns the relation.
}

bool reflexiveCheck(int** relation, int m) // 3
{
    int flag = 0;
    for(int i = 0; i < m; i++) // Only one for loop is used as we need to check only the diagonal elements.
    { 
        if(relation[i][i] == 0) // All the diagonal elements of a matrix represent ordered pairs of the form (a,a) for all a belongs to the set.
        {
            flag = 1; // If any (a,a) doesn't belong to the relation, then we set flag to 1 to indicate that due to this element at least, the relation isn't reflexive. We don't need to check further so we use break as we have found one condition which makes the relation non-reflexive. Otherwise, if all the diagonal elements are 1, i.e., all ordered pairs of the form (a,a) belong to the relation (for all a belongs to the set), then the flag remains 0 and we conclude that the relation is reflexive.
            break;
        }
    }

    if(flag == 0)
    {
        cout<<"\nIt is a reflexive relation.\n\n\n";
        return true;
    }    
    else
    {
        cout<<"\nIt isn't a reflexive relation.\n\n\n";
        return false;
    }    
}

/*

    In all the following functions' comments, "(i,j)" means the ordered pair formed by the corresponding row value (representing the
    first element of that ordered pair) and the corresponding column value (representing the second element of that ordered pair).

    (all 4 possible outcomes: 11,00,10,01, are taken into consideration to find the condition for symmetricity in terms of matrics).
    If (a,b) belongs to R, then if (b,a) belongs to R then the relation is symmetric if the said condition is true for all such ordered
    pairs. A 1 entry at (i,j)th position and a 1 entry at (j,i)th position means that the relation is symmetric for all the ordered pairs
    (i,j) (as well as (j,i); if it is symmetric for any one of the pairs: (i,j) or (j,i) then it is symmetric for both of them). 
    An entry of 0 at (i,j)th position means that the ordered pair (i,j) doesn't exists so (j,i) also must not exist and therefore its
    entry must be 0 for the relation to be symmetric for (i,j). If any one of the ordered pairs is 1 and the other one is 0, then the
    symmetric condition would be false for that ordered pair whose entry is 1 as when checking for the ordered pair whose entry is 1, the
    entry at corresponding symmetric making ordered pair would be 0 and hence it'd not be symmetric for the ordered pair whose entry is 1.
    When checking for the ordered pair with the corresponding entry as 0, as that ordered pair doesn't exist, we need not check further
    according to the definition of symmetricity and it'd be symmetric for the ordered pair whose entry is 0. But, in this last case,
    when we'll check for the corresponing ordered pair whose entry is 1, it'd not be symmetric, so, different entries implies non-symmetric
    relation as we need at least one such pair of ordered pairs to prove that relation is non-symmetric. So, we observe that when both the 
    corresponding entries are same then the relation is symmetric w.r.t. that ordered pair, and when they're different, then it isn't
    w.r.t. that ordered pair and whenever we find one such ordered pair, then the relation isn't symmetric and we have no need to check
    any further (there may or may not exist more such ordered pairs).

    Implementation:

*/

bool symmetricCheck(int** relation, int m) // 4
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][j] != relation[j][i]) // When we find "such" pair of ordered pairs, then we set the flag to 1 to indicate the non-symmetricity and break free from the loop as we need not check further. If we don't find any "such" pair of ordered pairs, then flag remains 0 and it means that the relation is symmetric w.r.t. all the ordered pairs and hence we say the relation is symmetric.
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
    {
        cout<<"\nIt is a symmetric relation.\n\n\n";
        return true;
    }    
    else
    {
        cout<<"\nIt isn't a symmetric relation.\n\n\n";
        return false;
    }    
}

/*

    Similar deductions in the following functions as the above function instead in each of the following, we of course go by the
    definition of that type of the check we are performing.

*/

/*

    If (a,b) belongs to R, and if (b,c) belongs to R, then if (a,c) belongs to R, the relation is transitive w.r.t. (a,b).
    If (a,b) belongs to R and (b,c) doesn't belong to R, then also according to the above definition, the relation is transitive
    w.r.t. (a,b).

    If (i,j)'s entry is 0 then this ordered pair doesn't exist. If it is 1, and ALL (j,k)s' entries is 0, then it is transitive for (i,j).
    If (i,j)'s entry is 1 and if (j,k)'s entry is 1, then if ALL (i,k)s' entries must be 1 for the relation to be transitive. If >= 1
    of the (i,k)s' entries is not 1, then the relation would not be transitive for (i,j) and hence the relation wouldn't be transitive.
    So, we use the contradiction approach to check. If (i,j) entry is 0, then no problem, as the ordered pair doesn't exist in the relation
    we of course cannot check it. If (i,j) is 1 and ALL (j,k)s is 0, then also no problem as explained above. But if (i,j) is 1 and any 
    (j,k) is also 1 and then if (i,k) is 1 then no problem as explained above but if it is 0 then it isn't transitive for (i,j) as we have
    found one condition that violates the definition of transitivity for (i,j) and therefore for the relation.

    1: true and 0: false and X: Don't Care. (in the if condition below:)
    In the implementation: All possible 8 permutations of 0s and 1s fit well with the above explanation. Starting with 0, cannot check.
    We are left with 4 pairs of 0s and 1s with 1 for 1st operand. 1 && 0 && X would be transitive as explained above in the second case.
    So, we're left with the last case as explained above: 1 && 1 && X, this would only be transitive if X is 0 (relation[i][k] == 1) and
    the only case left for the non-transitivity is if X = 1 (relation[i][k] == 0) when all three operands are true. All these cases
    are deduced and pertain to the definition of the transitivity of a relation.

*/
bool transitiveCheck(int** relation, int m) // 5
{
    int flag = 0;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            for(int k = 0; k < m; k++)
            {
                if(relation[i][j] == 1 && relation[j][k] == 1 && relation[i][k] != 1)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1)
                break;
        }
        if(flag == 1)
            break;        
    }

    if(flag == 0)
    {
        cout<<"\nIt is a transitive relation.\n\n\n";
        return true;
    }    
    else
    {
        cout<<"\nIt isn't a transitive relation.\n\n\n";
        return false;
    }  
}

void equivalenceCheck(int** relation, int m) // 6
{
    if(reflexiveCheck(relation, m) == true && symmetricCheck(relation, m) == true && transitiveCheck(relation, m) == true)
        cout<<"It is an equivalence relation.\n\n\n";
    else
        cout<<"It isn't an equivalence relation\n\n\n";
}

// If the relation is doesn't contain any ordered pairs then it is called an empty relation, otherwise, it is not an empty relation.
void emptyCheck(int** relation, int m) // 7
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][j] == 1) // If at least one ordered pair is found then it is non-empty. Otherwise, it is empty.
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
        cout<<"\nIt is an empty relation.\n\n\n";
    else
        cout<<"\nIt isn't an empty relation.\n\n\n";
}

/*

    The relation matrix with all ones represent the cartesian product of the first set with the second set and a relation which is equal
    to the cartesian product is called a universal relation, i.e., it contains all possible ordered pairs from the two sets (in that order).
    Otherwise, it isn't a universal relation.

*/
void universalCheck(int** relation, int m) // 8
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][j] == 0) // If at least one 0 entry is found, that means that ordered pair isn't present from the cartesian product and hence the relation is non-universal, otherwise it is universal.
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
        cout<<"\nIt is a universal relation.\n\n\n";
    else
        cout<<"\nIt isn't a universal relation.\n\n\n";
}

/*

    If ONLY (a,a) belongs to R for all a belongs to the set.
    
    If any other ordered pair other than that of type (a,a) belongs to R, or, If at least one (a,a) type ordered pair doesn't belong to R
    or both, then it is not identity. Otherwise, the relation is an identity relation.

*/
void identityCheck(int** relation, int m) // 9
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][i] == 0 || i != j && relation[i][j] == 1)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
        cout<<"\nIt is an identity relation.\n\n\n";
    else
        cout<<"\nIt isn't an identity relation.\n\n\n";
}

/*

    if (a,a) doesn't belong to R for all a belongs to the set.

*/
void irreflexiveCheck(int** relation, int m) // 10
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        if(relation[i][i] == 1) // If at least one (a,a) found in the relation then it is non-irreflexive, otherwise it is irreflexive.
        {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
        cout<<"\nIt is an irreflexive relation.\n\n\n";
    else
        cout<<"\nIt isn't an irreflexive relation.\n\n\n";
}

/*

    Here along with the relation being antisymmetric, if for a == b, no (a,b) belong to R, then the relation is asymmetric. 

    Now, if any one or both of the above conditions is false, then the relation isn't asymmetric. 
    
    In the if condition below: The second condition is the same as in the antisymmetric case (as explained there). The first condition
    says that if any ordered pair of the type (a,a) exists or the second condition says if the relation is not antisymmetric or both are
    true, then the relation isn't asymmetric for that ordered pair and hence the relation is non-asymmetric. Otherwise, the relation
    is asymmetric for that ordered pair. If the relation is asymmetric for all the ordered pairs then the relation is said to be 
    asymmetric.

*/
void asymmetricCheck(int** relation, int m) // 11
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(relation[i][i] == 1 || i != j && relation[i][j] == 1 && relation[j][i] == 1)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
        cout<<"\nIt is an asymmetric relation.\n\n\n";
    else
        cout<<"\nIt isn't an asymmetric relation.\n\n\n";
}

/*

    If (a,b) belongs to R and if (b,a) doesn't belong to R for all a != b, then, the relation is antisymmetric.

    The above condition doesn't say anything about a == b, so that condition is irrelevent here (the relation is antisymmetric for the
    ordered pairs following a == b). Therefore, we only check for a != b. Now with this condition, if (a,b) belongs to R and (b,a) belongs
    to R, then only the relation would be non-antisymmetric. Otherwise, when either one of them or none of them belongs to R, then it 
    satisfies the defintion for antisymmetricity for that ordered pair. If the relation is antisymmetric for all ordered pairs, then it
    is said to be an antisymmetric relation.

*/
void antisymmetricCheck(int** relation, int m) // 12
{
    int flag = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(i != j && relation[i][j] == 1 && relation[j][i] == 1)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(flag == 0)
        cout<<"\nIt is an anti-symmetric relation.\n\n\n";
    else
        cout<<"\nIt isn't an anti-symmetric relation.\n\n\n";
}