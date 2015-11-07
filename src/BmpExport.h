#include <fstream>
#include <iostream>

#include "Color.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

using namespace std;

short padding = 0x0000;
short BM = 0x4d42;	//"BM"

//BMP header struct
struct bmp_header
{
    int32_t size_of_file;
    int32_t reserve;
    int32_t offset_of_pixle_data;
    int32_t size_of_header;
    int32_t width;
    int32_t height;
    short num_of_colour_plane;
    short num_of_bit_per_pix;
    int32_t compression;
    int32_t size_of_pix_data;
    int32_t h_resolution;
    int32_t v_resolution;
    int32_t num_of_colour_in_palette;
    int32_t important_colours;
} HEADER;


void exportBmp(Color** res)
{
  //init header
  int size = SCR_WIDTH*SCR_HEIGHT*3*sizeof(char);
	HEADER.size_of_file = sizeof(HEADER) + size + sizeof(padding) * SCR_HEIGHT + 2;
	HEADER.reserve = 0000;
	HEADER.offset_of_pixle_data = 54;
	HEADER.size_of_header = 40;
	HEADER.width = SCR_WIDTH;
	HEADER.height = SCR_HEIGHT;
	HEADER.num_of_colour_plane = 1;
	HEADER.num_of_bit_per_pix = 24;
	HEADER.compression = 0;
	HEADER.size_of_pix_data = size + sizeof(padding) * SCR_HEIGHT;
	HEADER.h_resolution = 2835;
	HEADER.v_resolution = 2835;
	HEADER.num_of_colour_in_palette = 0;
	HEADER.important_colours = 0;

	//write bmp headers
	ofstream file;
	file.open ("result.bmp", ios::out | ios::trunc | ios::binary);
	file.write ((char*)(&BM), 2);
	file.write ((char*)(&HEADER), sizeof(HEADER));

  //write bmp data
  char blue;
  char green;
  char red;
	for(int y = SCR_HEIGHT-1; y >= 0; y--)
	{
	  for(int x = 0; x < SCR_WIDTH; x++)
	  {
	    blue = res[y][x].b*255;
	    green = res[y][x].g*255;
	    red = res[y][x].r*255;
	    file.write((char*)(&blue), 1);
	    file.write((char*)(&green), 1);
	    file.write((char*)(&red), 1);
	  }
	}
}
