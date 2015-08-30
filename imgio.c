#include "conf.h"

int png_check(char name){

	/* open the file */
	FILE *fp = fopen(name,"rb");
	if(fp == NULL) {
		printf("image opening failed.\n");
		return 0;
	}

	/* check if the image is png or not */
	char header[8];
	fread(header, 1, 8, fp);
	if(png_sig_cmp(header, 0, 8)){	// return 0 when the first 8 byte match the png head standard
		printf("This is not a png.\n");
		fclose(fp);
		return 1;
	}
}

int png_read(char name){

	/* open the file */
	FILE *fp = fopen(name,"rb");
	if(fp == NULL) {
		printf("image opening failed.\n");
		return 0;
	}

	// ============================================
	// get the parameter (width, height, ... etc.) of PNG
	// ============================================
	// png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)user_error_ptr,user_error_fn, user_warning_fn);
	// this function return NULL if it failed to create the structure.
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	assert(png_ptr);

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr){
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		printf("png_create_info_struct() failed.\n", );
		return 0;
	}

	if (setjmp(png_jmpbuf(png_ptr))){
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		printf("setjmp() failed.\n", );
		fclose(fp);
		return 0;
	}

	png_init_io(png_ptr, fp);

	// we choose to discard the unknown chunk here.
	png_set_keep_unknown_chunks(png_ptr, 1, NULL, 0);
	/* png_set_keep_unknown_chunks(png_ptr, keep, chunk_list, num_chunks);
	keep - 		0: default unknown chunk handling
			1: ignore; do not keep
			2: keep only if safe-to-copy
			3: keep even if unsafe-to-copy
			You can use these definitions:
			PNG_HANDLE_CHUNK_AS_DEFAULT 0
			PNG_HANDLE_CHUNK_NEVER 1
			PNG_HANDLE_CHUNK_IF_SAFE 2
			PNG_HANDLE_CHUNK_ALWAYS 3
	chunk_list - 	list of chunks affected (a byte string, five bytes per chunk, NULL or ’\0’ if num_chunks is 0)
	num_chunks - 	number of chunks affected; if 0, all unknown chunks are affected. If nonzero, only the chunks in the list are affected */
	// except for IHDR and IDAT, if a known chunk is noted on chunk_list, it will be treated as unknown chunk.

	// process all the info about png but not the IDAT
	png_read_info(png_ptr, info_ptr);

//	uint32_t width =0;	
//	uint32_t height = 0;
//	uint32_t bit_depth = 0;
//	uint32_t color_type = 0;
//	// read height, width from IHDR
//	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);
//	// png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_method);
//	/* 	width - 		holds the width of the imagein pixels (up to 2ˆ31).
//		height - 	holds the height of the image in pixels (up to 2ˆ31).
//		bit_depth - 	holds the bit depth of one of the image channels. (valid values are 1, 2, 4, 8, 16 and depend also on the color_type. See also significant bits (sBIT) below).
//		color_type - 	describes which color/alpha channels are present.
//				PNG_COLOR_TYPE_GRAY (bit depths 1, 2, 4, 8, 16)
//				PNG_COLOR_TYPE_GRAY_ALPHA (bit depths 8, 16)
//				PNG_COLOR_TYPE_PALETTE (bit depths 1, 2, 4, 8)
//				PNG_COLOR_TYPE_RGB (bit_depths 8, 16)
//				PNG_COLOR_TYPE_RGB_ALPHA (bit_depths 8, 16)
//				PNG_COLOR_MASK_PALETTE
//				PNG_COLOR_MASK_COLOR
//				PNG_COLOR_MASK_ALPHA
//		filter_method - 	(must be PNG_FILTER_TYPE_BASE for PNG 1.0, and can also be PNG_INTRAPIXEL_DIFFERENCING if the PNG datastream is embedded in a MNG-1.0 datastream)
//		compression_type - (must be PNG_COMPRESSION_TYPE_BASE for PNG 1.0)
//		interlace_type - (PNG_INTERLACE_NONE or PNG_INTERLACE_ADAM7) */
//	//Any or all of interlace_type, compression_type, or filter_method can be NULL if you are not interested in their values.

	width = png_get_image_width(png_ptr,info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);


	// ============================================
	// read  IDAT (image content)
	// ============================================

	// first, we have to deal with the different data type for each color type.
	/*	Color Type    				Allowed Bit Depths   	Interpretation
  	-	0 PNG_COLOR_TYPE_GRAY 		1,2,4,8,16  		Each pixel is a grayscale sample.
   	-	2  PNG_COLOR_TYPE_RGB     		8,16        		Each pixel is an R,G,B triple.
   	-	3  PNG_COLOR_TYPE_PALETTE		1,2,4,8     		Each pixel is a palette index; a PLTE chunk must appear.
   	-	4  PNG_COLOR_TYPE_GRAY_ALPHA     	8,16        		Each pixel is a grayscale sample, followed by an alpha sample.
 	-	6  PNG_COLOR_TYPE_RGB_ALPHA     	8,16        		Each pixel is an R,G,B triple, followed by an alpha sample. */

   	// deal with gray image.====================
   	if ((color_type == PNG_COLOR_TYPE_GRAY) && (bit_depth < 8)) {
   		png_set_expand_gray_1_2_4_to_8(png_ptr);
   		bit_depth = 8;
   	}
	// png_set_expand_gray_1_2_4_to_8 function expandes the sample depth WITHOUT add tRNS data to alpha
	// NOTE : png_set_expand_gray_1_2_4_to_8 only works after libpng ver. 1.2.9 
 	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
 	// add tRNS data to alpha

   	if (color_type == PNG_COLOR_TYPE_GRAY){
   		png_set_gray_to_rgb(png_ptr);
   		color_type = PNG_COLOR_TYPE_RGB;
	}
   	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA){
   		png_set_gray_to_rgb(png_ptr);
   		color_type = PNG_COLOR_TYPE_RGB_ALPHA;
	}

	// deal with palette image.====================
	if (color_type == PNG_COLOR_TYPE_PALETTE)  {
		png_set_palette_to_rgb(png_ptr);
		color_type = PNG_COLOR_TYPE_RGB;
	}

	// add alpha channel ========================
	// we use ARGB here
 	if (color_type == PNG_COLOR_TYPE_RGB) png_set_filler(png_ptr, filler, PNG_FILLER_BEFORE);
 	if (color_type == PNG_COLOR_TYPE_RGB) {
 		png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_BEFORE);
 		color_type = PNG_COLOR_TYPE_RGB_ALPHA;
 	}

 	// turn RGBA into ARGB ======================
 	if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) png_set_swap_alpha(png_ptr);

	// turn 16 byte type data into 8 byte data ====================
	if (bit_depth == 16) {
		png_set_strip_16(png_ptr);
		bit_depth = 8;
	}

	// load IDAT 
	row_pointers = (png_bytep*)calloc(height, sizeof(png_bytep));
	png_read_image(png_ptr, row_pointers);

	fclose(fp);
	return 1;
}