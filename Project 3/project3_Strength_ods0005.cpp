/* project3_Strength_ods0005.cpp
 * Owen Strength
 *
 * compile:  g++ -std=c++11 project3_Strength_ods0005.cpp
 *
 * 10/11/2023
 * This program reads in two files of integers, sorts them, merges them, and writes the merged list to a new file.
 * The program prompts the user for the names of the input files and the output file.
 * The program then prints the sorted lists and the merged list to the screen.
 * The program also prints a message to the screen indicating the name of the output file.
 * The program uses dynamic arrays to store the integers from the input files.
 *
 * References:
 * Hints from the project description by Dr. Li on canvas
 *
 */
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/*
 * sorts an array of integers in ascending order using selection sort
 */
void sort(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/*
 * reads integers from a file into an array
 */
void readFromFile(int arr[], int size, string fileName)
{
    ifstream fin;
    fin.open(fileName);
    string temp;
    if (fin.fail())
    {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        fin >> temp;
        arr[i] = stoi(temp);
    }
    fin.close();
}

/*
 * gets the length of a file, so we can define the size of the array
 */
void getFileLength(int &size, string fileName)
{
    ifstream fin;
    fin.open(fileName);
    if (fin.fail())
    {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    int temp;
    while (fin >> temp)
    {
        size++;
    }
    fin.close();
}

/*
 * prints an array of integers
 */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }
}

/*
 * prints an array of integers in a single line
 */
void printArrayInLine(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

/*
 * merges two sorted arrays into a third sorted array
 */
void mergeArrays(int arr1[], int arr2[], int arr3[], int size1, int size2)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < size1 && j < size2)
    {
        if (arr1[i] < arr2[j])
        {
            arr3[k] = arr1[i];
            i++;
        }
        else
        {
            arr3[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < size1)
    {
        arr3[k] = arr1[i];
        i++;
        k++;
    }
    while (j < size2)
    {
        arr3[k] = arr2[j];
        j++;
        k++;
    }
}

/*
 * writes an array of integers to a file
 */
void writeToFileOut(int arr[], int size, string fileName)
{
    ofstream fout(fileName);
    for (int i = 0; i < size; i++)
    {
        fout << arr[i] << endl;
    }
    fout.close();
}

/*
 * main function
 */
int main()
{
    // declare variables
    string fileName1;
    string fileName2;
    string fileName3;
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;

    // get file names and read files into arrays
    cout << "***Welcome to Owen's sorting program***\nEnter the first input file name: ";
    cin >> fileName1;
    getFileLength(size1, fileName1);
    int *arr1 = new int[size1];
    readFromFile(arr1, size1, fileName1);
    sort(arr1, size1);
    cout << "The list of " << size1 << " numbers in file " << fileName1 << " is:" << endl;
    printArray(arr1, size1);

    // get file names and read files into arrays
    cout << "\nEnter the second input file name: ";
    cin >> fileName2;
    getFileLength(size2, fileName2);
    int *arr2 = new int[size2];
    readFromFile(arr2, size2, fileName2);
    sort(arr2, size2);
    cout << "The list of " << size2 << " numbers in file " << fileName2 << " is:" << endl;
    printArray(arr2, size2);

    // merge arrays and print merged array
    size3 = size1 + size2;
    int *arr3 = new int[size3];
    mergeArrays(arr1, arr2, arr3, size1, size2);
    sort(arr3, size3);
    cout << "\nThe sorted list of " << size3 << " numbers is: ";
    printArrayInLine(arr3, size3);

    // write merged array to file
    cout << "\nEnter the output file name: ";
    cin >> fileName3;
    writeToFileOut(arr3, size3, fileName3);
    cout << "***Please check the new file - " << fileName3 << "***" << endl;
    cout << "***Goodbye.***" << endl;
}
