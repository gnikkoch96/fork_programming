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
    int choice;             //(Parent) For text-based menu
    int arrSize;            //Determine the size of the array
    int occurences;         //(Child) Count the # of times a letter has appeared

    char input;             //Can only be accessed in Parent Process
    char *arr;              //Can only be accessed in Child Process

    srand(time(NULL));      //Used for Randomizing Array

    if(childPID > 0)        //Parent Process
    {
        //Text Based Menu
        cout << "====MENU====\n1.Run Program\n2.Exit Program\nChoice: ";
        cin >> choice;
        cout << endl;
        if(choice == 1){//Run Program
            //Array Size
            cout << "Enter size: ";
            cin >> arrSize;
            cout << endl << endl;

            //Character to be searched
            cout << "Enter a Character: ";
            cin >> input;;
            cout << endl;

            if(childPID == 0) //Child Process
            {
                arr = new arr[arrSize];

                //Populates Array with Upper Case Letters (Randomly)
                for(int i = 0 ; i < arrSize; i++){
                    arr[i] = rand() % 90 + 65;

                    //Search and Count # of occurences of letter in the array
                    if(arr[i] == input)
                        ++occurences;
                }

                //Delete array after job is completed (De-allocate memory space to prevent memory leak)
                delete[] arr;

                //(Debug) Output # of Occurences
                cout << input << " appeared " << occurences << " times" << endl;
            }else //Parent Process - Error: Child Process could not be created
            {
                cout << "Error: " << getpid() << " couldn't spawn a child" << endl;
            }
        }else{
            cout << "Exiting Program..." << endl;
        }
    }
    return 0;
}
