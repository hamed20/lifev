/* -*- mode: c++ -*-
   This program is part of the LifeV library

   Autor(s): Alessio Fumagalli <alessio.fumagalli@mail.polimi.it>
       Date:

   Copyright (C) 2001-2006 EPFL, Politecnico di Milano, INRIA
   Copyright (C) 2006-2010 EPFL, Politecnico di Milano

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
/**
  @file dataDarcy.hpp
  @author A. Fumagalli <alessio.fumagalli@mail.polimi.it>
  @date 05/2010

  @brief This file contains the data for all the Darcy solver
*/
#ifndef _DATADARCY_H_
#define _DATADARCY_H_

#include <life/lifemesh/dataMesh.hpp>
#include <life/lifearray/tab.hpp>
#include <life/lifefem/dataTime.hpp>

// LifeV namespace
namespace LifeV
{
/*!
  @class DataDarcy

  This class contain the basic data for the Darcy solver. In particoular it stores...
  @todo class not finished!
 */
template <typename Mesh>
class DataDarcy
{
public:

    // Policies
    //! @name Policies
    //@{

    typedef GetPot                          Data_Type;
    typedef boost::shared_ptr< Data_Type >  Data_ptrType;

    typedef DataTime                        Time_Type;
    typedef boost::shared_ptr< Time_Type >  Time_ptrType;

    typedef DataMesh                        Mesh_Type;
    typedef boost::shared_ptr< Mesh_Type >  Mesh_ptrType;

    //@}

    // Constructors.
	//! @name Constructors
	//@{

    //! Empty Constructor
    DataDarcy();

    /*!
    Constructor using a data file.
      @param dataFile GetPot data file for setup the problem
      @param section the section for the Darcy data
    */
    DataDarcy( const GetPot& dataFile, const std::string& section = "darcy" );

    /*!
    Copy constructor.
      @param dataDarcy object to take a copy
    */
    DataDarcy( const DataDarcy &dataDarcy );

    //@}

    // Set methods
    //! @name Set methods
    //@{

    /*! Set data time container
        @param DataTime Boost shared_ptr to dataTime container
    */
    inline void setDataTime( const Time_ptrType DataTime )
    {
        M_time = DataTime;
    }

    /*! Set mesh container
        @param DataMesh Boost shared_ptr to dataMesh container
    */
    inline void setDataMesh( const Mesh_ptrType DataMesh )
    {
        M_mesh = DataMesh;
    }

    // Get methods.
    //! @name Get methods
    //@{

	//! Get the level of verbosity of the problem.
    inline const UInt verbose( void ) const
    {
        return M_verbose;
    }

    //! Get the main section of the data file.
    inline const std::string section( void ) const
    {
        return M_section;
    }

   	//! Get the data file of the problem.
   	inline Data_ptrType dataFile( void ) const
    {
        return M_data;
    }

    /*! Get data time container.
        @return shared_ptr to dataTime container
    */
    inline Time_ptrType dataTime( void ) const
    {
        return M_time;
    }

    /*! Get mesh container
       @return shared_ptr to dataMesh container
    */
    inline Mesh_ptrType dataMesh( void ) const
    {
        return M_mesh;
    }


    //@}

    // Methods.
	//! @name Methods
	//@{

    /*! Overloading of the operator =
        @param dataDarcy The DataDarcy to be copied.
    */
    DataDarcy& operator=( const DataDarcy& dataDarcy );

   	/*! Print all the data
        @param c the ostream to print the data
    */
    void showMe( std::ostream& c = std::cout );

   	/*! Help method, print all data that can be stored in this class
        @param c the ostream to print the help
    */
    void help( std::ostream& c = std::cout );

    /*! External setup
        @param dataFile The data file with all the data.
        @param section The global section.
    */
    void setup( const Data_Type& dataFile, const std::string& section = "darcy"  );

	//@}



protected:

    //! Data containers for time and mesh
    Data_ptrType      M_data;
    Time_ptrType      M_time;
    Mesh_ptrType      M_mesh;

    //! Miscellaneous
    UInt              M_verbose;
    std::string       M_section;

};

// ===================================================
// Constructors
// ===================================================

template < typename Mesh >
DataDarcy<Mesh>::DataDarcy( ):
    // Data containers
    M_data          ( ),
    M_time          ( ),
    M_mesh          ( ),
    // Miscellaneous
    M_verbose       ( static_cast<UInt>(0) ),
    M_section       ( )
{
    CONSTRUCTOR( "DataDarcy" );
}




// Constructor using a data file
/*template <typename Mesh>
DataDarcy<Mesh>::DataDarcy( const GetPot& dataFile, const std::string& section ):
	// Data
    DataMesh<Mesh>         ( dataFile, section + "/space_discretization" ),
    DataTime               ( dataFile ),
    M_dataFile             ( dataFile ),
    // Miscellaneous
    M_testCase             ( dataFile( ( section + "/miscellaneous/test_case").data(), 1 ) ),
    post_dir               ( dataFile( ( section + "/miscellaneous/post_dir").data(), "./" ) ),
    M_verbose              ( dataFile( ( section + "/miscellaneous/verbose").data(), true ) ),
    post_proc_format       ( dataFile( ( section + "/miscellaneous/post_proc_format").data(), "medit" ) )
{
}
*/

// Copy constructor
template < typename Mesh >
DataDarcy<Mesh>::DataDarcy( const DataDarcy &dataDarcy ):
    // Data containers
    M_data                ( dataDarcy.M_data ),
	M_time                ( dataDarcy.M_time ),
    M_mesh                ( dataDarcy.M_mesh ),
    // Miscellaneous
    M_verbose             ( dataDarcy.M_verbose ),
    M_section             ( dataDarcy.M_section )
{
    CONSTRUCTOR( "DataDarcy" );
}

// Overloading of the operator =
template < typename Mesh >
DataDarcy<Mesh>&
DataDarcy<Mesh>::operator=( const DataDarcy& dataDarcy )
{
    // Avoid auto-copy
    if ( this != &dataDarcy )
    {
        // Data containers
        M_data           = dataDarcy.M_data;
        M_time           = dataDarcy.M_time;
        M_mesh           = dataDarcy.M_mesh;
        // Mescellaneous
        M_verbose       = dataDarcy.M_verbose;
    }

    return *this;

}


// External set up method
template < typename Mesh >
void DataDarcy<Mesh>::setup( const Data_Type& dataFile, const std::string& section )
{
    M_section = section;

    // If data has not been set
    if( !M_data.get() )
        M_data.reset( new Data_Type( dataFile ) );

    // If data time has not been set
    if ( !M_time.get() )
        M_time.reset( new Time_Type( dataFile, M_section + "/time_discretization" ) );

    // If data mesh has not been set
    if ( !M_mesh.get() )
        M_mesh.reset( new Mesh_Type( dataFile, M_section + "/space_discretization" ) );

    // Miscellaneous
    M_verbose      = dataFile( ( M_section + "/miscellaneous/verbose" ).data(), 1 );
}


template <typename Mesh>
void DataDarcy<Mesh>::showMe( std::ostream& c )
{/*
    // Mesh
    c << std::endl << "*** Values for mesh [space_discretization]" << std::endl << std::endl;
    DataMesh<Mesh>::showMe( c );

    // miscellaneous
    c << std::endl << "*** Values for data [miscellaneous]" << std::endl << std::endl
      << "post_dir         = " << post_dir << std::endl
      << "test_case        = " << M_testCase << std::endl
      << "verbose          = " << M_verbose << std::endl
      << "post_proc_format = " << post_proc_format << std::endl;*/
}

template <typename Mesh>
void DataDarcy<Mesh>::help( std::ostream& c )
{/*
    // miscellaneous
    c << std::endl << "*** Help for data [miscellaneous]" << std::endl << std::endl
      << "test_case: a number indicating the test case" << std::endl
      << "post_dir         : the full postprocessing directory (including path)" << std::endl
      << "verbose          : to make the code verbose" << std::endl
      << "post_proc_format : postprocessing format (medit, vtk, ...)" << std::endl;*/
}

}
#endif