#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

using namespace std;


void convert_utf16_utf8(string source, string destination){

    char const* s = source.data();

    FILE* fr = fopen(s, "r");

    fseek(fr, 0L, SEEK_END);
    size_t size = ftell(fr);
    fseek(fr, 0L, SEEK_SET);

    cout << "size = " << size << endl;

    unsigned char arr[size];

    fread(arr, 1, size, fr);

    fclose(fr);

    char const* d = destination.data();

    FILE* fw = fopen(d, "w");

    unsigned short ch;

    for(int i=3; i<size; i++){  // i is the first byte, but i-1 is the second byte

        cout << (unsigned short)arr[i-1] << endl;

        if(arr[i]!=0){    // connect 2 byte  
            bitset<8>  elem = arr[i];
            cout << "arr[i] " << elem << endl;  
            bitset<8>  selem = arr[i-1];
            cout << "arr[i-1] " << selem << endl;
            ch = arr[i] << 8;
            ch = ch | (unsigned short)arr[i-1];  // the result is equal the short variable which we write into utf16
            bitset<16>  celem = ch;
            cout << "ch= " << celem << endl;
        }

        if(arr[i] == 0 and arr[i-1] >= 0 and arr[i-1] <= 127){  // 1 byte
        
            cout << " 1 byte \n";
            bitset<8>  elem = arr[i];
            cout << "arr[i] " << elem << endl;
            bitset<8>  selem = arr[i-1];
            cout << "arr[i-1] " << selem << endl;
            fwrite(&arr[i-1], 1, 1, fw);
            
            cout << "----------------------------------- \n";

        }else if(ch >= 128 and ch <= 8191){   // 2^13    2 byte
           
            unsigned char first = ((ch << 2) >> 8) |  0b11000000;
            bitset<8>  felem = first;
            cout << "first " << felem << endl;
            fwrite(&first, 1, 1, fw);

            unsigned char second = (ch & 0b0000000000111111) | 0b10000000;
            bitset<8>  s_elem = second;
            cout << "second " << s_elem << endl;

            fwrite(&second, 1, 1, fw);
            
            cout << "----------------------------------- \n";
        }

        i++;

    }

    fclose(fw);
}
