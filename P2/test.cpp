#include <iostream>

using namespace std;

//Create your 2D array
int main() {
int **array = new int[ 2 ];

for( int i = 0; i < 2; ++i )
{
    array[ i ]  = new int[ 2 ];
}

//Then set them to NULL

    for( int i = 0; i < 2; ++i )
    {
        for( int j = 0; j < 2; ++j )
        {
            array[ i ][ j ] = NULL;
        }
    }

//Now you can use it
}