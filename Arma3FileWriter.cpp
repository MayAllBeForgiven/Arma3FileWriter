// Arma3FileWriter.cpp
#include "pch.h"
#include <windows.h>
#include <fstream>
#include <string>

// The exported function that Arma 3 calls
extern "C" __declspec(dllexport) void __stdcall RVExtension(char* output, int outputSize, const char* function);

// Implementation of the exported function
void __stdcall RVExtension(char* output, int outputSize, const char* function)
{
    // Clear the output buffer
    memset(output, 0, outputSize);

    // Convert the input to a std::string
    std::string input(function);

    // Parse the command and arguments
    size_t spacePos = input.find(' ');
    std::string command = input.substr(0, spacePos);
    std::string arguments = (spacePos != std::string::npos) ? input.substr(spacePos + 1) : "";

    if (command == "write" || command == "append")
    {
        // Split arguments into file path and data
        size_t delimiterPos = arguments.find(' ');
        std::string filePath = arguments.substr(0, delimiterPos);
        std::string data = (delimiterPos != std::string::npos) ? arguments.substr(delimiterPos + 1) : "";

        // Remove surrounding quotes from file path if present
        if (!filePath.empty() && filePath.front() == '"' && filePath.back() == '"')
        {
            filePath = filePath.substr(1, filePath.length() - 2);
        }

        // Determine the file open mode
        std::ios_base::openmode mode = std::ios::out;
        if (command == "append")
        {
            mode |= std::ios::app;
        }
        else
        {
            mode |= std::ios::trunc; // Overwrite the file
        }

        // Open the file
        std::ofstream outFile(filePath, mode);
        if (outFile.is_open())
        {
            outFile << data << std::endl;
            outFile.close();
            strncpy_s(output, outputSize, "SUCCESS", _TRUNCATE);
        }
        else
        {
            std::string errorMsg = "ERROR: Unable to open file " + filePath;
            strncpy_s(output, outputSize, errorMsg.c_str(), _TRUNCATE);
        }
    }
    else
    {
        strncpy_s(output, outputSize, "ERROR: Unknown command", _TRUNCATE);
    }
}
