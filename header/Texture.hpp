
#include <iostream>
#include <vector>

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

class Texture
{
public:
    Texture();
    ~Texture();

    /** \brief Export ppm texture
        \param filename: the name of the picture
        \param size_1: size in x direction
        \param size_2: size in y direction
        \param r_channel: red component   (must be of size size_1*size_2)
        \param g_channel: green component (must be of size size_1*size_2)
        \param b_channel: blue component  (must be of size size_1*size_2)

        Values must be between [0,255]. Otherwise clamped.
    */
    static void export_ppm(const std::string& filename,const unsigned int& size_1,const int& size_2,const std::vector <float>& red_channel,const std::vector<float>& green_channel,const std::vector<float>& blue_channel);

private:
};

#endif
