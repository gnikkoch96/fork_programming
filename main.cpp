#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

/*
    1. Parent Process - Handles User Input
    2. Child Process - Handles one Search process (Remember to deallocate)
*/

int main()
{
    int childPID = fork();
    int arrSize;            //Determine the size of the array
    char input;             //Can only be accessed in Parent Process
    char *arr;              //Can only be accessed in Child Process
    srand(time(NULL));      //Used for Randomizing Array

    if(childPID > 0)        //Parent Process
    {
        //Array Size
        cout << "Enter size: ";
        cin >> arrSize;
        cout << endl << endl;

        //Character to be searched
        cout << "Enter a Character: ";
        cin >> input;;
        cout << endl;

    }else if(childPID == 0) //Child Process
    {
        arr = new arr[arrSize];
        for(int i = 0 ; i < arrSize; i++){
            arr[i] = rand() +
        }
    }else                   //Parent Process - Error: Child Process could not be created
    {

    }
    return 0;
}
