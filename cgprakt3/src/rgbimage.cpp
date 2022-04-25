#include <cstring>
#include "rgbimage.h"
#include "color.h"
#include "assert.h"


RGBImage::RGBImage( unsigned int Width, unsigned int Height)
{
    this->m_Height = Height;
    this->m_Width = Width;
    this->m_Image = new Color[Width * Height];
}

RGBImage::~RGBImage()
{
    delete m_Image;
    delete this;
}

void RGBImage::setPixelColor( unsigned int x, unsigned int y, const Color& c)
{
    if( x > this->m_Width && y > this->m_Height) {
        std::cout << "Werte liegen nicht im Wertebereich" << std::endl;
    } else {
        this->m_Image[y * m_Width + x] = c;
    }

}

const Color& RGBImage::getPixelColor( unsigned int x, unsigned int y) const
{
    if( x > this->m_Width && y > this->m_Height) {
        std::cout << "Werte liegen nicht im Wertebereich" << std::endl;
    } else {
        return this->m_Image[y * m_Width + x];
    }
}

unsigned int RGBImage::width() const {
    return this->m_Width;
}

unsigned int RGBImage::height() const {
    return this->m_Height;
}

unsigned char RGBImage::convertColorChannel( float v) {
    if(v > 1.0f) {
        v = 1;
    }
    else if(v < 0.0f) {
        v = 0;
    }
    else {return v * 255;}
    return (unsigned char) v;
}


/* Quellen:
 *https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
 *https://www.youtube.com/watch?v=vqT5j38bWGg
 */
bool RGBImage::saveToDisk( const char* Filename) {

    FILE *f;
    unsigned char *image = NULL;
    unsigned char bmpPad[3] = { 0, 0, 0 };
    unsigned int r, g, b;

    int filesize = 54 + 3 * m_Width * m_Height;
    image = (unsigned char *)malloc(3 * m_Width * m_Height);
    std::memset(image, 0, 3 * m_Width * m_Height);

    f = fopen(Filename, "wb");

    if (f != NULL) {
        for (int x = 0; x < m_Height; x++) {
            for (int y= 0; y < m_Width; y++) {
                r = convertColorChannel(this->getPixelColor(y, x).R);
                g = convertColorChannel(this->getPixelColor(y, x).G);
                b = convertColorChannel(this->getPixelColor(y, x).B);

                image[(y + (x * m_Width)) * 3 + 2] = (unsigned char) r;
                image[(y + (x * m_Width)) * 3 + 1] = (unsigned char) g;
                image[(y + (x * m_Width)) * 3 + 0] = (unsigned char) b;
            }
        }

        unsigned char fileHeader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
        unsigned char informationHeader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };


        fileHeader[2] = (unsigned char)(filesize);
        fileHeader[3] = (unsigned char)(filesize >> 8);
        fileHeader[4] = (unsigned char)(filesize >> 16);
        fileHeader[5] = (unsigned char)(filesize >> 24);


        informationHeader[4] = (unsigned char)(m_Width);
        informationHeader[5] = (unsigned char)(m_Width >> 8);
        informationHeader[6] = (unsigned char)(m_Width >> 16);
        informationHeader[7] = (unsigned char)(m_Width >> 24);

        informationHeader[8] = (unsigned char)(m_Height);
        informationHeader[9] = (unsigned char)(m_Height >> 8);
        informationHeader[10] = (unsigned char)(m_Height >> 16);
        informationHeader[11] = (unsigned char)(m_Height >> 24);

        fwrite(fileHeader, 1, 14, f);
        fwrite(informationHeader, 1, 40, f);

        for (int i = 0; i < m_Height; i++) {
            fwrite(image + (m_Width * (m_Height - i - 1) * 3), 3, m_Width, f);
            fwrite(bmpPad, 1, (4- (m_Width * 3) % 4) % 4, f);
        }
        free(image);
        fclose(f);
        return true;
    }
    else
    {
        free(image);
        std::cerr << "Fehler beim Speichern" << std::endl;
        return false;
    }
}