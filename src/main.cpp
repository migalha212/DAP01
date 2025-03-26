#include "CLInterface.h"

// * This exists basically just to control the project, the aim is to mimic the class structure we used in ldts


int main(int argc, char* argv []) {
    CLInterface interface;
    // ./app locations.csv distances.csv input.txt output.txt
    switch (argc) {
        /* Run program with default files straight away */
    case 1:
        interface.defaultRun();
        break;

        /* With the correct argument, the program will open in the interactive mode*/
    case 2:
        interface.presentUI();
        if (argv[1] == "-i") {
            std::cout << "interactive" << std::endl;
        }
        else {
            //! error, but run with default files
        }
        break;
        /* In this case the program will open straight to the interactive menu */
    case 3:
        break;
        // In this case the program will skip to the output step as all arguments are present
    case 4:
        break;
        // Same as case 4, but the default will be to output to a file, which should be the final argument
    case 5:
        break;
        // Can either End the program right away with an error message
        // or send the error message and send the user to the interactive menu
    default:
        //interface.printArgumentError();
        return 1;
    }


    return 0;
}
