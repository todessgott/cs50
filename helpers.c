#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float shadeValue;
    float unroundedShadeValue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            unroundedShadeValue = image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue;
            shadeValue = roundf(unroundedShadeValue / 3);
            image[h][w].rgbtRed = shadeValue;
            image[h][w].rgbtBlue = shadeValue;
            image[h][w].rgbtGreen = shadeValue;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double unroundedSepiaRed, unroundedSepiaGreen, unroundedSepiaBlue;
    float sepiaRed, sepiaGreen, sepiaBlue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            unroundedSepiaRed = (0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) + (0.189 * image[h][w].rgbtBlue);
            sepiaRed = roundf(unroundedSepiaRed);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            unroundedSepiaGreen = (0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) + (0.168 * image[h][w].rgbtBlue);
            sepiaGreen = roundf(unroundedSepiaGreen);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;

            }

            unroundedSepiaBlue = (0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) + (0.131 * image[h][w].rgbtBlue);
            sepiaBlue = roundf(unroundedSepiaBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;

            }

            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image1[h][w].rgbtRed = image[h][w].rgbtRed;
            image1[h][w].rgbtBlue = image[h][w].rgbtBlue;
            image1[h][w].rgbtGreen = image[h][w].rgbtGreen;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0, w1 = width - 1; w < width || w1 >= 0; w++, w1--)
        {
            image[h][w].rgbtRed = image1[h][w1].rgbtRed;
            image[h][w].rgbtBlue = image1[h][w1].rgbtBlue;
            image[h][w].rgbtGreen = image1[h][w1].rgbtGreen;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image1[h][w].rgbtRed = image[h][w].rgbtRed;
            image1[h][w].rgbtBlue = image[h][w].rgbtBlue;
            image1[h][w].rgbtGreen = image[h][w].rgbtGreen;
        }
    }


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float averageRed = 0, averageBlue = 0, averageGreen = 0;

            //corner case
            if (h == 0)
            {
                if (w == 0)
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h][w + 1].rgbtRed + image1[h + 1][w].rgbtRed + image1[h + 1][w + 1].rgbtRed) /
                                         4.0);
                                        
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h][w + 1].rgbtGreen + image1[h + 1][w].rgbtGreen + image1[h + 1][w +
                                           1].rgbtGreen) /
                                           4.0);
                                            
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h][w + 1].rgbtBlue + image1[h + 1][w].rgbtBlue +
                                          image1[h + 1][w + 1].rgbtBlue) /
                                          4.0);
                }

                else if (w == width - 1)
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h][w - 1].rgbtRed + image1[h + 1][w - 1].rgbtRed + 
                                         image1[h + 1][w].rgbtRed) /
                                         4.0);
                                        
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h][w - 1].rgbtGreen + image1[h + 1][w - 1].rgbtGreen + 
                                           image1[h + 1][w].rgbtGreen) /
                                           4.0);
                                        
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h][w - 1].rgbtBlue + image1[h + 1][w - 1].rgbtBlue + 
                                          image1[h + 1][w].rgbtBlue) /
                                          4.0);
                }
                else //for edge case when h = 0 and w != 0 and w != width-1
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h][w - 1].rgbtRed + image1[h][w + 1].rgbtRed + 
                                         image1[h + 1][w - 1].rgbtRed + image1[h + 1][w].rgbtRed + image1[h + 1][w + 1].rgbtRed) /
                                         6.0);
                                        
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h][w - 1].rgbtGreen + image1[h][w + 1].rgbtGreen +
                                           image1[h + 1][w - 1].rgbtGreen + image1[h + 1][w].rgbtGreen + image1[h + 1][w + 1].rgbtGreen) /
                                           6.0);
                                        
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h][w - 1].rgbtBlue + image1[h][w + 1].rgbtBlue + 
                                          image1[h + 1][w - 1].rgbtBlue + image1[h + 1][w].rgbtBlue + image1[h + 1][w + 1].rgbtBlue) /
                                          6.0);
                }
            }

            if (h == height - 1)
            {
                if (w == 0)
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w].rgbtRed + image1[h - 1][w + 1].rgbtRed + 
                                         image1[h][w + 1].rgbtRed) /
                                         4.0);
                    
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w].rgbtGreen + image1[h - 1][w + 1].rgbtGreen +
                                           image1[h][w + 1].rgbtGreen) /
                                           4.0);
                    
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w].rgbtBlue + image1[h - 1][w + 1].rgbtBlue + 
                                          image1[h][w + 1].rgbtBlue) /
                                          4.0);
                }

                else if (w == width - 1)
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w - 1].rgbtRed + image1[h - 1][w].rgbtRed + 
                                         image1[h][w - 1].rgbtRed) /
                                        4.0);
                                        
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w - 1].rgbtGreen + image1[h - 1][w].rgbtGreen +
                                           image1[h][w - 1].rgbtGreen) /
                                        4.0);
                                        
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w - 1].rgbtBlue + image1[h - 1][w].rgbtBlue + 
                                          image1[h][w - 1].rgbtBlue) /
                                        4.0);
                }
                else
                {
                    averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w - 1].rgbtRed + image1[h - 1][w].rgbtRed + 
                                         image1[h - 1][w + 1].rgbtRed + image1[h][w - 1].rgbtRed + image1[h][w + 1].rgbtRed) / 6.0);
                                        
                    averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w - 1].rgbtGreen + image1[h - 1][w].rgbtGreen + 
                                           image1[h - 1][w + 1].rgbtGreen + image1[h][w - 1].rgbtGreen + image1[h][w + 1].rgbtGreen) / 6.0);
                                        
                    averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w - 1].rgbtBlue + image1[h - 1][w].rgbtBlue + 
                                          image1[h - 1][w + 1].rgbtBlue + image1[h][w - 1].rgbtBlue + image1[h][w + 1].rgbtBlue) / 6.0);

                }
            }

            //edge case
            if (w == 0 && (h != 0 && h != height - 1))
            {
                averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w].rgbtRed + image1[h - 1][w + 1].rgbtRed + image1[h][w + 1].rgbtRed + 
                                     image1[h + 1][w].rgbtRed + image1[h + 1][w + 1].rgbtRed) / 6.0);
                                    
                averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w].rgbtGreen + image1[h - 1][w + 1].rgbtGreen + 
                                       image1[h][w + 1].rgbtGreen + image1[h + 1][w].rgbtGreen + image1[h + 1][w + 1].rgbtGreen) / 6.0);
                
                averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w].rgbtBlue + image1[h - 1][w + 1].rgbtBlue + 
                                      image1[h][w + 1].rgbtBlue + image1[h + 1][w].rgbtBlue + image1[h + 1][w + 1].rgbtBlue) / 6.0);
            }

            if (w == width - 1 && (h != 0 && h != height - 1))
            {
                averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w - 1].rgbtRed + image1[h - 1][w].rgbtRed + image1[h][w - 1].rgbtRed +
                                     image1[h + 1][w - 1].rgbtRed + image1[h + 1][w].rgbtRed) / 6.0);
                                    
                averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w - 1].rgbtGreen + image1[h - 1][w].rgbtGreen + 
                                       image1[h][w - 1].rgbtGreen + image1[h + 1][w - 1].rgbtGreen + image1[h + 1][w].rgbtGreen) / 6.0);
                                     
                averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w - 1].rgbtBlue + image1[h - 1][w].rgbtBlue + 
                                      image1[h][w - 1].rgbtBlue + image1[h + 1][w - 1].rgbtBlue + image1[h + 1][w].rgbtBlue) / 6.0);
            }

            //middle case
            if ((h != 0 && h != height - 1) && (w != 0 && w != width - 1))
            {
                averageRed = roundf((image1[h][w].rgbtRed + image1[h - 1][w - 1].rgbtRed + image1[h - 1][w].rgbtRed + image1[h - 1][w + 1].rgbtRed +
                                     image1[h][w - 1].rgbtRed + image1[h][w + 1].rgbtRed + image1[h + 1][w - 1].rgbtRed + image1[h + 1][w].rgbtRed +
                                     image1[h + 1][w + 1].rgbtRed) / 9.0);
                                    
                averageGreen = roundf((image1[h][w].rgbtGreen + image1[h - 1][w - 1].rgbtGreen + image1[h - 1][w].rgbtGreen +
                                       image1[h - 1][w + 1].rgbtGreen + image1[h][w - 1].rgbtGreen + image1[h][w + 1].rgbtGreen + 
                                       image1[h + 1][w - 1].rgbtGreen + image1[h + 1][w].rgbtGreen + image1[h + 1][w + 1].rgbtGreen) / 9.0);
                                    
                averageBlue = roundf((image1[h][w].rgbtBlue + image1[h - 1][w - 1].rgbtBlue + image1[h - 1][w].rgbtBlue + 
                                      image1[h - 1][w + 1].rgbtBlue + image1[h][w - 1].rgbtBlue + image1[h][w + 1].rgbtBlue + 
                                      image1[h + 1][w - 1].rgbtBlue + image1[h + 1][w].rgbtBlue + image1[h + 1][w + 1].rgbtBlue) / 9.0);
            }
            image[h][w].rgbtRed = averageRed;
            image[h][w].rgbtBlue = averageBlue;
            image[h][w].rgbtGreen = averageGreen;
        }
    }
    return;
}
