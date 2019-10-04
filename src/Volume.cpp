

#include <Volume.hpp>
#include <fstream>
#include <cmath>

Volume::Volume():Nx(0),Ny(0),Nz(0),data(){}
Volume::~Volume(){}

void Volume::resize(const unsigned int& _Nx,const unsigned int& _Ny,const unsigned int& _Nz)
{
    data.resize(_Nx*_Ny*_Nz);
    Nx=_Nx;Ny=_Ny;Nz=_Nz;
}
double Volume::get_data(const unsigned int& kx,const unsigned int& ky,const unsigned int& kz) const
{
    if(kx*ky*kz<Nx*Ny*Nz)
        return data[kx+Nx*(ky+Ny*kz)];
    else
        throw(std::string("Volume::get_data() outside bounds"));
}
void Volume::set_data(const unsigned int& kx,const unsigned int& ky,const unsigned int& kz,const double& value)
{
    if(kx*ky*kz<Nx*Ny*Nz)
        data[kx+Nx*(ky+Ny*kz)]=value;
    else
        throw(std::string("Volume::set_data() outside bounds"));
}


Volume Volume::load_v4d(const std::string& filename)
{

    Volume v;


    std::ifstream stream(filename.c_str(),std::ifstream::in);

    if(!stream.good())
    {throw std::string("Error in Volume::load_v4d("+filename+") : cannot open file \n");}

    std::string buffer;
    unsigned int Nx=0,Ny=0,Nz=0;
    stream>>Nx; stream>>Ny; stream>>Nz;

    std::cout<<" find file "<<filename<<" size=("<<Nx<<","<<Ny<<","<<Nz<<")"<<std::endl;
    v.resize(Nx,Ny,Nz);

    double f;

    for(unsigned int kx=0;stream.good() && kx<Nx;++kx)
    {
        for(unsigned int ky=0;stream.good() && ky<Ny;++ky)
        {
            for(unsigned int kz=0;stream.good() && kz<Nz;++kz)
            {
                stream>>f;
                if(stream.good())
                    v.set_data(kx,ky,kz,f);
            }
        }
    }
    stream.close();
    return v;
}

unsigned int Volume::size_x() const{return Nx;}
unsigned int Volume::size_y() const{return Ny;}
unsigned int Volume::size_z() const{return Nz;}

std::vector <float> Volume::slice_x(const unsigned& kx) const
{
    std::vector <float> slice(Ny*Nz);
    for(unsigned int ky=0;ky<Ny;++ky)
    {
        for(unsigned int kz=0;kz<Nz;++kz)
        {
            slice[ky+Ny*kz]=get_data(kx,ky,kz);
        }
    }
    return slice;
}
std::vector <float> Volume::slice_y(const unsigned& ky) const
{
    std::vector <float> slice(Nx*Nz);
    for(unsigned int kx=0;kx<Nx;++kx)
    {
        for(unsigned int kz=0;kz<Nz;++kz)
        {
            slice[kx+Nx*kz]=get_data(kx,ky,kz);
        }
    }
    return slice;
}
std::vector <float> Volume::slice_z(const unsigned& kz) const
{
    std::vector <float> slice(Nx*Ny);
    for(unsigned int kx=0;kx<Nx;++kx)
    {
        for(unsigned int ky=0;ky<Ny;++ky)
        {
            slice[kx+Nx*ky]=get_data(kx,ky,kz);
        }
    }
    return slice;
}

double Volume::operator()(const double& x,const double& y,const double& z) const
{
    return linear_interpolation(x,y,z);
}

double Volume::linear_interpolation(const double& x,const double& y,const double& z) const
{
    double epsilon=1e-6;
    if(x<0 || y<0 || z<0 || x+epsilon>=size_x() || y+epsilon>=size_y() || z+epsilon>=size_z())
    {
        //outside bounds
        return 0.0;
    }

    int x0=static_cast<int>(x);
    int y0=static_cast<int>(y);
    int z0=static_cast<int>(z);

    double ux;ux=(x-x0);
    double uy;uy=(y-y0);
    double uz;uz=(z-z0);

    double f=0.0;

    //******************************************************//
    //******************************************************//
    //**********  TO DO : Tri-linear interpolation *********//
    //******************************************************//
    //******************************************************//
    f=get_data(x0,y0,z0);
    //******************************************************//
    //******************************************************//
    //**********  /TO DO :                         *********//
    //******************************************************//
    //******************************************************//

    return f;
}

Volume Volume::resampled_square(const unsigned int& N) const
{
    Volume vol2;vol2.resize(N,N,N);


    for(unsigned int k0=0;k0<N;++k0)
    {
        double ux=static_cast<double>(k0)/static_cast<double>(N-1);
        double x0=ux*(size_x()-1);
        for(unsigned int k1=0;k1<N;++k1)
        {
            double uy=static_cast<double>(k1)/static_cast<double>(N-1);
            double y0=uy*(size_y()-1);
            for(unsigned int k2=0;k2<N;++k2)
            {
                double uz=static_cast<double>(k2)/static_cast<double>(N-1);
                double z0=uz*(size_z()-1);

                vol2.set_data(k0,k1,k2,(*this)(x0,y0,z0));
            }
        }
    }

    return vol2;

}

Volume Volume::rotated_z(const double& angle) const
{
    unsigned int N=std::max(size_x(),size_y());
    Volume v2;v2.resize(N,N,size_z());

    double cos_a;cos_a=cos(angle);
    double sin_a;sin_a=sin(angle);

    for(unsigned int kx=0;kx<N;++kx)
    {
        for(unsigned int ky=0;ky<N;++ky)
        {
            for(unsigned int kz=0;kz<size_z();++kz)
            {


                //******************************************************//
                //******************************************************//
                //**********  TO DO : Rotation                 *********//
                //******************************************************//
                //******************************************************//
                double x0=kx;
                double y0=ky;
                double z0=kz;
                //******************************************************//
                //******************************************************//
                //**********  /TO DO :                         *********//
                //******************************************************//
                //******************************************************//

                double f=(*this)(x0,y0,z0);
                v2.set_data(kx,ky,kz,f);
            }
        }
    }

    return v2;

}


std::vector<float> Volume::mip() const
{
    std::vector<float> proj(size_y()*size_z());
    for(unsigned int ky=0;ky<size_y();++ky)
    {
        for(unsigned int kz=0;kz<size_z();++kz)
        {
            //******************************************************//
            //******************************************************//
            //**********  TO DO : MIP                      *********//
            //******************************************************//
            //******************************************************//
            proj[ky+size_y()*kz]=get_data(size_x()/2.0,ky,kz);
            //******************************************************//
            //******************************************************//
            //**********  /TO DO :                         *********//
            //******************************************************//
            //******************************************************//
        }
    }
    return proj;
}

std::vector<std::vector<float> > Volume::ray_cast() const
{
    std::vector<std::vector<float> >proj;

    proj.resize(3);
    proj[0].resize(size_y()*size_z());
    proj[1].resize(size_y()*size_z());
    proj[2].resize(size_y()*size_z());

    //******************************************************//
    //******************************************************//
    //**********  TO DO : Ray Casting              *********//
    //******************************************************//
    //******************************************************//
    for(unsigned int ky=0;ky<size_y();++ky)
    {
        for(unsigned int kz=0;kz<size_z();++kz)
        {
            proj[0][ky+size_y()*kz]=get_data(size_x()/2.0-2,ky,kz);
            proj[1][ky+size_y()*kz]=get_data(size_x()/2.0,ky,kz);
            proj[2][ky+size_y()*kz]=get_data(size_x()/2.0+2,ky,kz);
        }
    }
    //******************************************************//
    //******************************************************//
    //**********  /TO DO :                         *********//
    //******************************************************//
    //******************************************************//

    return proj;
}

Volume Volume::smoothed() const
{
    Volume v2;v2.resize(size_x(),size_y(),size_z());

    for(unsigned int kx=1;kx<size_x()-1;++kx)
    {
        for(unsigned int ky=1;ky<size_y()-1;++ky)
        {
            for(unsigned int kz=1;kz<size_z()-1;++kz)
            {
                double f=get_data(kx  ,ky,kz);

                double fx0=get_data(kx-1,ky,kz);
                double fx2=get_data(kx+1,ky,kz);

                double fy0=get_data(kx,ky-1,kz);
                double fy2=get_data(kx,ky+1,kz);

                double fz0=get_data(kx,ky,kz-1);
                double fz2=get_data(kx,ky,kz+1);

                double v=1/12.0*(6*f+fx0+fx2+fy0+fy2+fz0+fz2);

                v2.set_data(kx,ky,kz,v);
            }
        }
    }
    return v2;
}

