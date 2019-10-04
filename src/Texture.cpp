
#include <fstream>
#include <Texture.hpp>


void Texture::export_ppm(const std::string& filename,const unsigned int& size_1,const int& size_2,const std::vector <float>& red_channel,const std::vector<float>& green_channel,const std::vector<float>& blue_channel)
{
    std::ofstream stream(filename.c_str(),std::ofstream::out);
    if(!stream.good())
        throw std::string("Error in Texture::export_ppm("+filename+"...) : cannot open file \n");

    //magic number
    stream<<"P3 \n";
    //size
    stream<<size_2<<" "<<size_1<<" \n";
    //color number
    stream<<"255"<<std::endl;

                for(int k2=0;k2<size_2;++k2)
    {
    for(unsigned int k1=0;k1<size_1;++k1)
        {
            int r=std::min(std::max(static_cast<int>(red_channel  [k1+size_1*k2]),0),255);
            int g=std::min(std::max(static_cast<int>(green_channel[k1+size_1*k2]),0),255);
            int b=std::min(std::max(static_cast<int>(blue_channel [k1+size_1*k2]),0),255);

            stream<<r<<" "<<g<<" "<<b<<std::endl;
        }
    }
    stream.close();

}
