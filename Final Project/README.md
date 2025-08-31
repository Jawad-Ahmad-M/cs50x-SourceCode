# CS50x Final Project: Run-Length Encoding (RLE) Compression and Decompression

## Overview

This project implements a command-line tool for **Run-Length Encoding (RLE)**, a simple compression technique that reduces file sizes by representing consecutive identical elements as a single data value and count. The tool supports both compression and decompression of text files.

## Video Demo:
```url
https://youtu.be/D-EPfD-YsvI
```

### Features
- **Compression**: Converts a text file into its compressed form using RLE.
- **Decompression**: Restores an RLE-encoded file to its original form.
- **Single and Multiple File Support**: Compress or decompress a single file or process multiple files simultaneously.

## Table of Contents
1. [Project Files](#project-files)
2. [How to Compile and Run](#how-to-compile-and-run)
3. [Usage](#usage)
4. [Functions](#functions)
5. [Testing](#testing)

## Project Files

- **`test.c`**: The main program handling RLE operations, including command-line argument parsing and task delegation.
- **`rle.c`**: Contains the implementation of RLE compression and decompression functions.
- **`rle.h`**: Header file declaring functions used in `rle.c`.
- **`Makefile`**: Makefile for compiling the program with debugging and optimization flags.

### Description of Each File

#### `test.c`
The main entry point of the program. It parses command-line arguments and delegates compression or decompression tasks to `helperFunctionSingleFile` or `helperFunctionMultipleInputs`. It uses `rleCompress` and `rleDecompress` to process files and displays the compression ratio after processing.

#### `rle.c`
Contains the core RLE functions:
- `rleCompress`: Compresses text using RLE and writes it to the output file.
- `rleDecompress`: Decompresses RLE-encoded files and writes the result to the output file.
- `comparisonRatio`: Calculates the compression ratio between original and compressed files.
- `getFileSize`: Retrieves the size of a file.

#### `rle.h`
Declares the functions in `rle.c` for use in `test.c`.

#### `Makefile`
Simplifies compilation with necessary flags for debugging and optimization.

## How to Compile and Run

### Compilation
Navigate to the project directory and run:

```bash
make
```

This generates an executable named `test` based on the provided `Makefile`.

### Running the Program
The program supports two modes of operation:

#### For a Single File
- **Compression**:
  ```bash
  ./test -c inputfile.txt outputfile.txt
  ```
- **Decompression**:
  ```bash
  ./test -d inputfile.txt outputfile.txt
  ```

#### For Multiple Files
Use the `-m` flag to process multiple files. Output files are automatically named with an `output_` prefix:
- **Compression**:
  ```bash
  ./test -c -m file1.txt file2.txt file3.txt
  ```
- **Decompression**:
  ```bash
  ./test -d -m file1.txt file2.txt file3.txt
  ```

### Print Usage
To display usage instructions, run the program without arguments or with invalid arguments:

```bash
./test
```

This shows the available command-line options.

## Functions

### `rleCompress(const char* input, FILE* output)`
- **Purpose**: Compresses the input string using RLE and writes the compressed data to the output file.
- **Parameters**:
  - `input`: The string to be compressed.
  - `output`: File pointer for writing compressed data.

### `rleDecompress(FILE* input, FILE* output)`
- **Purpose**: Decompresses an RLE-encoded file and writes the result to the output file.
- **Parameters**:
  - `input`: File pointer to the RLE-encoded data.
  - `output`: File pointer for writing decompressed data.

### `comparisonRatio(FILE* original, FILE* compressed)`
- **Purpose**: Calculates the compression ratio between the original and compressed files.
- **Parameters**:
  - `original`: File pointer to the original uncompressed file.
  - `compressed`: File pointer to the compressed file.
- **Returns**: The ratio of the original file size to the compressed file size.

### `getFileSize(char* fileName)`
- **Purpose**: Retrieves the size of a file.
- **Parameters**:
  - `fileName`: Name of the file to measure.
- **Returns**: File size in bytes.

### `helperFunctionSingleFile(char* mode, char* inputFile, char* outputFile)`
- **Purpose**: Handles compression or decompression for a single file based on the mode (`-c` or `-d`).
- **Parameters**:
  - `mode`: Operation mode (`-c` for compression, `-d` for decompression).
  - `inputFile`: Input file to process.
  - `outputFile`: Output file for the result.

### `helperFunctionMultipleInputs(char* mode, char** files, int argc)`
- **Purpose**: Handles compression or decompression for multiple files.
- **Parameters**:
  - `mode`: Operation mode (`-c` or `-d`).
  - `files`: Array of file names to process.
  - `argc`: Number of arguments passed.

### `printUsage()`
- **Purpose**: Displays usage instructions for the program, detailing command-line options.

## Testing

### Test Cases for Compression
- Test with text files containing repeated characters (e.g., "aaaaaa") to verify effective compression.
- Test with files lacking repeated characters to evaluate minimal compression.

### Test Cases for Decompression
- Verify that decompressed files match their originals using tools like `diff` or by comparing file sizes.

### Edge Cases
- Test with empty files, very large files, and files containing special characters to ensure robustness.

### Example Output
```bash
$ ./test -c example.txt compressed_example.txt
The value by which size decreased is 35.14%
```
