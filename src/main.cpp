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
        if (std::string(argv[1]) == "-i") {
            std::string outputFileName = "../output_interactive.txt";
            std::ofstream outFile(outputFileName);
            if (!outFile.is_open()) {
            std::cout << "Error opening output file." << std::endl;
            exit(1);
        }
            interface.presentUI("","", outFile);
        }
        else if (std::string(argv[1]) == "-h") {
            std::cout << "Usage: ./app -i" << std::endl;
            std::cout << "or ./app locations.csv distances.csv input.txt output.txt" << std::endl;
            return 0;
        }
        else {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: ./app -i" << std::endl;
            std::cerr << "or ./app locations.csv distances.csv input.txt output.txt" << std::endl;
            return 1;
        }
        break;
        /* In this case the program will open straight to the interactive menu */
    case 3:
        //interface.presentUI(argv[1], argv[2], outFile);
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
        std::cerr << "Invalid argument" << std::endl;
        std::cerr << "Usage: ./app -i" << std::endl;
        std::cerr << "or ./app locations.csv distances.csv input.txt output.txt" << std::endl;
        return 1;
    }
    return 0;
}



