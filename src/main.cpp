#include "CLInterface.h"

// * This exists basically just to control the project, the aim is to mimic the class structure we used in ldts


int main(int argc, char* argv []) {
    CLInterface interface;
    // ./app locations.csv distances.csv input.txt output.txt
    switch (argc) {
        /* Run program with default files straight away */
    case 1:
        interface.defaultRun("", "", "", "");
        break;

        /* With the correct argument, the program will open in the interactive mode*/
    case 2: {
        if (std::string(argv[1]) == "-i") {
            interface.presentUI("", "", std::cout);
        }
        else if (std::string(argv[1]) == "-h") {
            std::cout << "Usage:" << std::endl;
            std::cout << "./app -i\n   \033[90m- for interface with predefined files\033[0m" << std::endl;
            std::cout << "./app locations.csv distances.csv\n   \033[90m- for interface with custom files\033[0m" << std::endl;
            std::cout << "./app locations.csv distances.csv output.txt\n   \033[90m- for interface with custom files and output to file\033[0m" << std::endl;
            std::cout << "./app locations.csv distances.csv input.txt output.txt\n   \033[90m- for execution without interface of custom files, input file and output to file\033[0m" << std::endl;
            return 0;
        }
        else {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: ./app -h - for help" << std::endl;
            return 1;
        }
        break;
    }
          /* In this case the program will open straight to the interactive menu */
    case 3: {
        std::string locatinsFileName = argv[1];
        std::string distancesFileName = argv[2];

        if (interface.presentUI(locatinsFileName, distancesFileName, std::cout)) {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: ./app -i" << std::endl;
            return 1;
        }
        break;
    }
    case 4: {
        std::string locatinsFileName = argv[1];
        std::string distancesFileName = argv[2];
        std::string outputFileName = argv[3];

        std::ofstream outFile(outputFileName);

        if (interface.presentUI(locatinsFileName, distancesFileName, outFile)) {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: ./app -i" << std::endl;
            return 1;
        }
        break;
    }
          // Same as case 4, but the default will be to output to a file, which should be the final argument
    case 5: {
        std::string locatinsFileName = argv[1];
        std::string distancesFileName = argv[2];
        std::string inputFileName = argv[3];
        std::string outputFileName = argv[4];

        interface.defaultRun(locatinsFileName, distancesFileName, inputFileName, outputFileName);
        std::cout << "Result written to " << outputFileName << std::endl;
        break;
    }
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



