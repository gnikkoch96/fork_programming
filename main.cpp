#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

/*
    1. Parent Process - Handles User Input
    2. Child Process - Handles one Search process (Remember to deallocate)
*/

void printArray(char *arr, int arrSize){
    for(int i = 0; i < arrSize; i++){
        cout << arr[i] << ", ";
    }

    cout << endl;
}

int main()
{
    int childPID = 10;      //Dummy Value
    int choice;             //(Parent) For text-based menu
    int arrSize;            //Determine the size of the array
    int occurences = 0;     //(Child) Count the # of times a letter has appeared

    char input;             //Can only be accessed in Parent Process
    char *arr;              //Can only be accessed in Child Process

    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O','P', 'Q', 'R', 'S', 'T', 'U','V', 'W', 'X',
        'Y', 'Z'
    };

    srand(time(NULL));      //Used for Randomizing Array
    do{
        if(childPID > 0)        //Parent Process
        {
            //Text Based Menu
            cout << "====MENU====\n1.Run Program\n2.Exit Program\nChoice: ";
            cin >> choice;
            cout << endl;

            if(choice == 1){//Run Program
                cout << "====Parent Process: " << getpid() << " | " << "ParentID: " << getppid() << "====" << endl;

                //Array Size
                cout << "Enter size: ";
                cin >> arrSize;
                cout << endl << endl;

                //Character to be searched
                cout << "Enter a Character: ";
                cin >> input;;
                cout << endl;


                if(childPID = fork())                   //Process is created where the child process knows the input and size of the array
                    pid_t cpid = wait(NULL);

                if(childPID == 0) //Child Process
                {
                    cout << "====Child Process: " << getpid() << " | " << "ParentID: " << getppid() << "====" << endl;

                    arr = new char[arrSize];

                    //Populates Array with Upper Case Letters (Randomly)
                    do{//Injected Bug Portion
                        for(int i = 0 ; i < arrSize; i++){
                            arr[i] = alphabet[rand() % 26];

                            //Search and Count # of occurences of letter in the array
                            if(arr[i] == input)
                                ++occurences;
                        }
                        if(occurences < 1)
                            cout << "Child Process: " << getpid() << " couldn't find any occurence of " << input << endl;
                    }while(occurences < 1);

                    //(Debug) Check
//                    printArray(arr, arrSize);

                    //Delete array after job is completed (De-allocate memory space to prevent memory leak)
                    delete[] arr;

                    //(Debug) Output # of Occurences
                    cout << input << " appeared " << occurences << " times" << endl;
                    cout << "(Debug) De-Allocating Array Space..." << endl;

                    //Child Process Exits and Returns back to Parent Process
                    exit(0);
                }else if (childPID < 0)//Parent Process - Error: Child Process could not be created
                {
                    cout << "Error: " << getpid() << " couldn't spawn a child" << endl;
                }
            }else{
                cout << "Exiting Program..." << endl;
            }
        }
    }while(choice == 1);

    return 0;
}
