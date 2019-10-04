

#include <iostream>
#include <vector>

#ifndef _VOLUME_HPP_
#define _VOLUME_HPP_

class Volume
{
public:

    //*********************************************//
    //*********************************************//
    // CONSTRUCTORS
    //*********************************************//
    //*********************************************//

    /** \brief empty constructor */
    Volume();
    /** \brief destructor */
    ~Volume();

    //*********************************************//
    //*********************************************//
    // Load File
    //*********************************************//
    //*********************************************//

    /** \brief load a .4d volume file */
    static Volume load_v4d(const std::string& filename);


    //*********************************************//
    //*********************************************//
    // Size
    //*********************************************//
    //*********************************************//

    /** \brief resize (fill with zero) */
    void resize(const unsigned int& Nx,const unsigned int& Ny,const unsigned int& Nz);

    /** \brief get size_x */
    unsigned int size_x() const;
    /** \brief get size_y */
    unsigned int size_y() const;
    /** \brief get size_z */
    unsigned int size_z() const;


    //*********************************************//
    //*********************************************//
    // Get/Set value
    //*********************************************//
    //*********************************************//

    /** \brief get the value at position (kx,ky,kz) */
    double get_data(const unsigned int& kx,const unsigned int& ky,const unsigned int& kz) const;
    /** \brief set the value at position (kx,ky,kz) */
    void set_data(const unsigned int& kx,const unsigned int& ky,const unsigned int& kz,const double& value);

    /** \brief get the value at any position (x,y,z) using intepolation */
    double operator()(const double& x,const double& y,const double& z) const;


    //*********************************************//
    //*********************************************//
    // Modifications
    //*********************************************//
    //*********************************************//


    /** \brief resample data to fit into a cube of a given size */
    Volume resampled_square(const unsigned int& N) const;

    /** \brief apply rotation to the data by a fiven angle (radian) around the z direction */
    Volume rotated_z(const double& angle) const;

    /** \brief smoothing */
    Volume smoothed() const;

    //*********************************************//
    //*********************************************//
    // Slicing
    //*********************************************//
    //*********************************************//

    /** \brief extract a slice of data in plane x=kx. Return a texture of size Ny*Nz (access using slice_x(kx)[ky+Ny*kz]) */
    std::vector <float> slice_x(const unsigned& kx) const;
    /** \brief extract a slice of data in plane y=ky. Return a texture of size Nx*Nz (access using slice_x(ky)[kx+Nx*kz]) */
    std::vector <float> slice_y(const unsigned& ky) const;
    /** \brief extract a slice of data in plane z=kz. Return a texture of size Nx*Ny (access using slice_x(kz)[kx+Nx*ky]) */
    std::vector <float> slice_z(const unsigned& kz) const;




    //*********************************************//
    //*********************************************//
    // Visu
    //*********************************************//
    //*********************************************//

    /** \brief Apply MIP projection along the x direction (return b&w texture of size Ny*Nz) */
    std::vector<float> mip() const;
    /** \brief Apply classical ray-casting projection along the x direction (return color texture of size 3*Ny*Nz: access using ray_cast[r=0/g=1/b=2][ky+Ny*kz]) */
    std::vector<std::vector<float> > ray_cast() const;


private:

    /** \brief internal tri-linear interpolation of the value at position (x,y,z). Return 0 if out-of-bounds*/
    double linear_interpolation(const double& x,const double& y,const double& z) const;

    /** \brief size in x direction*/
    unsigned int Nx;
    /** \brief size in y direction*/
    unsigned int Ny;
    /** \brief size in x direction*/
    unsigned int Nz;
    /** \brief internal data as concatenated vector of float */
    std::vector <float> data;
};

#endif
