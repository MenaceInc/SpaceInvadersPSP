#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <psptypes.h>

#define	PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

typedef u32 Color;
#define A(color) ((u8)(color >> 24 & 0xFF))
#define B(color) ((u8)(color >> 16 & 0xFF))
#define G(color) ((u8)(color >> 8 & 0xFF))
#define R(color) ((u8)(color & 0xFF))

typedef struct
{
	int textureWidth;  // the real width of data, 2^n with n>=0
	int textureHeight;  // the real height of data, 2^n with n>=0
	int imageWidth;  // the image width
	int imageHeight;
	Color* data;
} Image;

/**
 * Load a PNG image.
 *
 * @pre filename != NULL
 * @param filename - filename of the PNG image to load
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadImage(const char* filename);

/**
 * Blit a rectangle part of an image to screen.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= SCREEN_WIDTH && dy + height <= SCREEN_HEIGHT
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 */
extern void blitImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);

/**
 * Blit a rectangle part of an image to screen without alpha pixels in source image.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= SCREEN_WIDTH && dy + height <= SCREEN_HEIGHT
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 */
extern void blitAlphaImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);

/**
 * Frees an allocated image.
 *
 * @pre image != null
 * @param image a pointer to an image struct
 */
extern void freeImage(Image* image);

/**
 * Initialize all pixels of the screen with a color.
 *
 * @param color - new color for the pixels
 */
extern void clearScreen(Color color);

/**
 * Fill a rectangle of the screen with a color.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle in image
 * @param y0 - top position of rectangle in image
 * @param width - width of rectangle in image
 * @param height - height of rectangle in image
 */
extern void fillScreenRect(Color color, int x0, int y0, int width, int height);

/**
 * Set a pixel on screen to the specified color.
 *
 * @pre x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT
 * @param color - new color for the pixels
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 */
extern void putPixelScreen(Color color, int x, int y);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param x - left position of text
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 */
extern void printTextScreen(int x, int y, const char* text, u32 color);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param x - left position of text
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 * @param image - image
 */
extern void printTextImage(int x, int y, const char* text, u32 color, Image* image);

/**
 * Exchange display buffer and drawing buffer.
 */
extern void flipScreen();

/**
 * Initialize the graphics.
 */
extern void initGraphics();

/**
 * Disable graphics, used for debug text output.
 */
extern void disableGraphics();

/**
 * Draw a line to screen.
 *
 * @pre x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT &&
 *      x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT
 * @param x0 - x line start position
 * @param y0 - y line start position
 * @param x1 - x line end position
 * @param y1 - y line end position
 */
void drawLineScreen(int x0, int y0, int x1, int y1, Color color);

/**
 * Get the current draw buffer for fast unchecked access.
 *
 * @return the start address of the current draw buffer
 */
extern Color* getVramDrawBuffer();

/**
 * Get the current display buffer for fast unchecked access.
 *
 * @return the start address of the current display buffer
 */
extern Color* getVramDisplayBuffer();

extern void guStart();

#endif