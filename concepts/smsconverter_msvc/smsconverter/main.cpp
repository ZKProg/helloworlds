// STDLIB
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstddef>

// SDL
#include <SDL.h>
#include <SDL_image.h>

// LINEAR ALGEBRA
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\io.hpp>

using namespace std;
using namespace boost::numeric::ublas;

// GLOBALS
ofstream output_file;


/****************************************************************************************
* ENTRY POINT
*****************************************************************************************/
int main(int argc, char **argv) {

	system("color c");
	cout << "Launching..." << endl;

	string image_file_path;

	if (argc > 1) {
		image_file_path = string(argv[1]);
	} else {
		cout << "You must provide an image file to open for conversion." << endl;
		return 1;
	}

	// --------------------------------------------------------------------------------
	// SDL AND IMG INIT

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL lib could not loaded: " << SDL_GetError() << endl;
		return 1;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;

	if (IMG_Init(flags) & flags != flags) {
		cout << "IMG lib vould not be loaded: " << IMG_GetError() << endl;
		return 1;
	}

	// --------------------------------------------------------------------------------
	// OUTPUT FILE
	output_file.open("output.data", ios_base::beg);

	if (!output_file.is_open()) {
		cout << "The output file could not be created. Check the rights." << endl;
		return 1;
	}

	

	// --------------------------------------------------------------------------------
	// LOAD IMAGE
	// --------------------------------------------------------------------------------

	SDL_Surface *image = nullptr;
	image = IMG_Load(image_file_path.c_str());

	if (image == nullptr) {
		cout << "The image could be loaded: " << IMG_GetError() << endl;
		return 1;
	}

	if (static_cast<unsigned short>(image->format->BitsPerPixel) > 8) {
		cout << "The image format is not accepted. The color depth MUST be of 8 bits per pixel." << endl;
		return 1;
	}

	if (image->w != 256 || image->h != 192) {
		cout << "Currently, only 256x192 resolution pictures are supported for convertion." << endl;
		return 1;
	}

	cout << "Image size: " << image->w << "x" << image->h << " pixels." << endl;
	cout << "Bytes per pixel: " << static_cast<int>(image->format->BytesPerPixel) << endl;
	cout << "Bits per pixel: " << static_cast<int>(image->format->BitsPerPixel) << endl;
	cout << "Image format accepted. Processing..." << endl;

	// Cast to a relevant pointer type (from void*)
	Uint8* pixels = reinterpret_cast<Uint8*>(image->pixels); 

	if (SDL_ISPIXELFORMAT_INDEXED(image->format->format)) {
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "Image with indexed colors." << endl;
		cout << "Palette colors number: " << image->format->palette->ncolors << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
	}

	// --------------------------------------------------------------------------------
	// GET THE PALETTE
	// --------------------------------------------------------------------------------

	SDL_Color *colors = nullptr;

	try {
		colors = image->format->palette->colors;
	} catch (bad_alloc e) {
		cout << e.what() << endl;
	}

	if (colors == nullptr) {
		cout << "The color palette could not be obtained." << endl;
		cout << SDL_GetError() << endl;
		return 1;
	}

	// --------------------------------------------------------------------------------
	// CONVERT SDL COLORS TO MASTER SYSTEM 64 COLOR SYSTEM
	// --------------------------------------------------------------------------------

	output_file << "Palette:" << endl;
	output_file << ".db ";

	// Loop through the color palette to convert them to one of the 64 available colors of the SMS.
	// Once done, the data is persisted in the output file, in Z80 Assembly format.
	for (int i = 0; i < image->format->palette->ncolors; i++) {
	  
		SDL_Color color = colors[i];

		// Color convertion to SMS color coding MSB --> |u|u|b|b|g|g|r|r| <--LSB
			
        // R
		if ((int)color.r < 42) color.r = 0;
		if ((int)color.r >= 42 && (int)color.r < 127) color.r = 1;
		if ((int)color.r >= 127 && (int)color.r < 170) color.r = 2;
		if ((int)color.r >= 170) color.r = 3;

		// G
		if ((int)color.g < 42) color.g = 0;
		if ((int)color.g >= 42 && (int)color.g < 127) color.g = 1;
		if ((int)color.g >= 127 && (int)color.g < 170) color.g = 2;
		if ((int)color.g >= 170) color.g = 3;

		// B
		if ((int)color.b < 42) color.b = 0;
		if ((int)color.b >= 42 && (int)color.b < 127) color.b = 1;
		if ((int)color.b >= 127 && (int)color.b < 170) color.b = 2;
		if ((int)color.b >= 170) color.b = 3;

		int r = (int)color.r << 0; // Obviously no shifting here
		int g = (int)color.g << 2; // Shift bits to fit the two green bits at bit 3 and 4
		int b = (int)color.b << 4; // Same, but blue at bit 5 and 6

		// Final color value to convert to a string, with hexadecimal formating. Simple ORing.
		int final_color = r | g | b;

		output_file << "$" << hex << final_color;
		if (i < (image->format->palette->ncolors - 1)) output_file << ",";

	}

	output_file << endl << "PaletteEnd:" << endl;
	
	// --------------------------------------------------------------------------------
	// TILES
	// --------------------------------------------------------------------------------

	unsigned short number_tiles_along_width = image->w / 8;
	unsigned short number_tiles_along_height = image->h / 8;
	unsigned short row[8];

	output_file << endl << "ImageData:" << endl;

	// Double nested loop to go through the 8x8 pixels tiles
	for (unsigned short h = 0; h < number_tiles_along_height; h++) {
	
		for (unsigned short w = 0; w < number_tiles_along_width; w++) {

			// We are now "in" the first tile.
			// W can loop through each pixel of it. The outcome must be 4 bytes per row, storing in "reverse" order, as
			// of LSB first, the bits of each pixel from that row.
			// Hence, a tile must end up in storing 32 (4x8) bytes of data. Each bytes will be stored in the output file stream.

			output_file << "; Tile index " << h * number_tiles_along_width + w << endl;
			matrix<int> M(8, 4);
			output_file << ".db ";
			
			// We go through all pixels of the tile
			for (int y = 0; y < 8; y++) {
				
				// Beginning of the first row --------------------------------------------------------------------------------------
				
				
				for (int x = 0; x < 8; x++) {

					// 1 - Get the first row pixel palette index

					unsigned current_pixel_x = (w * 8) + x;
					unsigned current_pixel_y = (h * 8) + y;

					row[x] = (int)pixels[current_pixel_y * image->w + current_pixel_x];

					// 2- Now that we have the current row of palette color indexes, we can convert into the SMS VDP format.
					// We use linear algebra to store the data, with matrix transpositions to convert to the desired storing method.

					// The row[] array contains now 8 pixels indexes (one index per pixel) referring to the color palette.
					// We create a matrix containing the individual bits, in the original format.
					

					for (int i = 0; i < M.size2(); i++) {
						for (int j = 0; j < M.size1(); j++) {

							// Bit selection
							int mask = 1 << i;
							int mask_n = row[j] & mask;

							int result = mask_n >> i;

							M(j, i) = result;

						}
					}

					

				}

				// We can now transpose the matrix M, to get a matrix representing the pixel indexes bits int the right format.
				matrix<int> T = trans(M);
				int final_int_value;

				// Get and output the values to the file stream, in hex string format
				for (int i = 0; i < T.size1(); i++) {

					string result_string = "";

					for (int j = 0; j < T.size2(); j++) {
						// Create a string made of the bits of the current row, by casting and appending each one of them.
						result_string += to_string(T(i, j));
					}

					// "Cast" to a binary value.
					bitset<8> final_value(result_string);
					final_int_value = static_cast<int>(final_value.to_ulong());

					// TODO Bug: format correctly the output to file (.db $df,$ed... etc.)
					output_file << "$" << hex << final_int_value;
					output_file << " ";

				}




			}

			output_file << endl;

		}

	}
	output_file << "ImageDataEnd:" << endl;

	// TODO Make that integrated and scalable
	output_file << endl << "Image:" << endl;

	for (int i = 0; i < 24; i++) {
		output_file << ".dw ";
		for (int j = 0; j < 32; j++) {
			string value = (i * 32 + j) > 0xff ? "$0" : "$00";
			output_file << value << i * 32 + j << " ";
		}
		output_file << endl;
	}

	output_file << "ImageEnd:" << endl;



	// --------------------------------------------------------------------------------
	// CLEAN MEMORY BEFORE EXITING
	// --------------------------------------------------------------------------------

	output_file.close();
	delete colors;
	delete pixels;
	SDL_FreeSurface(image);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

