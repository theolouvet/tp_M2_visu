
#include <cmath>
#include <iostream>
#include <sstream>
#include <Volume.hpp>
#include <Texture.hpp>

std::string get_string(const int& k);


int main(int argc,char *argv[])
{

  std::cout<<"start "<<argv[0]<<" with "<<argc<<" arg"<<std::endl;

  try
  {

      //************************//
      //Load
      //************************//
      Volume vol=Volume::load_v4d("data/head_ct.4d");
      vol=vol.resampled_square(100);
      for(int k=0;k<2;++k)
          vol=vol.smoothed();



      //************************//
      //export slices
      //************************//
      std::vector<float> sx=vol.slice_x(vol.size_x()/2.0);
      Texture::export_ppm("output/slice_x.ppm",vol.size_y(),vol.size_z(),sx,sx,sx);

      std::vector<float> sy=vol.slice_y(vol.size_y()/2.0);
      Texture::export_ppm("output/slice_y.ppm",vol.size_x(),vol.size_z(),sy,sy,sy);

      std::vector<float> sz=vol.slice_z(vol.size_z()/2.0);
      Texture::export_ppm("output/slice_z.ppm",vol.size_x(),vol.size_y(),sz,sz,sz);






      //************************//
      //Integration
      //************************//

      //number of rotation steps
      int N=10;
      for(int counter=0;counter<N;++counter)
      {
          std::string number=get_string(counter);

          std::cout<<"export file "<<counter+1<<" / "<<N<<std::endl;
          double angle=static_cast<double>(counter)/static_cast<double>(N-1)*M_PI*2+M_PI/2.0;
          Volume vol2=vol.rotated_z(angle);


          //MIP
          std::vector<float> val=vol2.mip();
          Texture::export_ppm("output/mip_"+number+".ppm",vol.size_y(),vol.size_z(),val,val,val);

          //Ray Casting
          std::vector<std::vector<float> > val_couleur=vol2.ray_cast();
          Texture::export_ppm("output/ray_"+number+".ppm",vol.size_y(),vol.size_z(),val_couleur[0],val_couleur[1],val_couleur[2]);
      }


  }
  catch(const std::string& e)
  {
      std::cout<<"================================"<<std::endl;
      std::cout<<"Exception catch"<<std::endl;
      std::cout<<e<<std::endl;
  }

  return 0;
}

std::string get_string(const int& k)
{

    std::stringstream stream_number;stream_number<<k;
    std::string number(stream_number.str());

    if(k<10)
        number="00"+number;
    else if(k<100)
        number="0"+number;
    return number;

}
