⚠ Make sure the file path and data does not contain any spaces (I may or may not fix this in the future)

# Arma3FileWriter

An Arma 3 extension that allows SQF scripts to write or append data to external files. It's currently has no linux support, just windows.

## Installation
Copy the @Arma3FileWriter folder into the Arma 3 root folder. 

ℹ - I've not submitted this extention to Battleye so you will have to disable battleye off in the arma 3 launcher in order to use this extention.

## Usage

Here in an example on how to write to a file in a .sqf script:
```
private _filePath = "C:\your_path\file.txt"; 
private _data = "This will overwrite the file content.";

// Enclose the file path in double quotes
private _escapedFilePath = format ['"%1"', _filePath];

// Prepare the command string
private _commandString = format ["write %1 %2", _escapedFilePath, _data];

// Call the extension
private _result = "Arma3FileWriter" callExtension _commandString;

// Display the result
systemChat _result; // Should display "SUCCESS" or an error message
```
If you want to append you can change the command string to say append instead of write:
```
private _commandString = format ["append %1 %2", _escapedFilePath, _data];
```

## Source code
I've aded the source code as a .cpp file if you want to make modifications or compile it yourself.
