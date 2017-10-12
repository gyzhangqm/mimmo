/*---------------------------------------------------------------------------*\
 * 
 *  mimmo
 *
 *  Copyright (C) 2015-2017 OPTIMAD engineering Srl
 *
 *  -------------------------------------------------------------------------
 *  License
 *  This file is part of mimmo.
 *
 *  mimmo is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License v3 (LGPL)
 *  as published by the Free Software Foundation.
 *
 *  mimmo is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with mimmo. If not, see <http://www.gnu.org/licenses/>.
 *
 \ *---------------------------------------------------------------------------*/

#include "mimmo_iogeneric.hpp"
using namespace std;
using namespace bitpit;
using namespace mimmo;



// =================================================================================== //
/*!
 * Reading a file with MimmoGeometry
 */
int test1() {
	
    MimmoGeometry * reader = new MimmoGeometry();
    reader->setIOMode(IOMode::READ);
    reader->setReadDir("geodata");
    reader->setReadFilename("prism");
    reader->setReadFileType(FileType::STL);
    reader->exec();
    
    bool check = reader->getGeometry()->getNCells() == 12288;
    check = check && reader->getGeometry()->getNVertex() == 6146;

    
    MimmoGeometry * readerCopy = new MimmoGeometry();
    *readerCopy = *reader;
    check = check && (readerCopy->getGeometry() == reader->getGeometry());
    
    std::unique_ptr<MimmoObject> objHC = reader->getGeometry()->clone();
    check = check && objHC->getNCells() == 12288;
    check = check && objHC->getNVertex() == 6146;
    
    std::cout<<"test1 passed :"<<check<<std::endl;
    
    delete reader;
    delete readerCopy;
    return int(!check);
}

/*!
 * Reading mixed type vtu with MimmoGeometry
 */
int test2() {
    
    MimmoGeometry * reader1 = new MimmoGeometry();
    reader1->setIOMode(IOMode::READ);
    reader1->setReadDir("geodata");
    reader1->setReadFilename("mixedP2D");
    reader1->setReadFileType(FileType::SURFVTU);
    reader1->exec();
    
    bool check = reader1->getGeometry()->getNCells() == 20;
    check = check && reader1->getGeometry()->getNVertex() == 19;
    
    reader1->getGeometry()->getPatch()->write("surface");
    
    MimmoGeometry * reader2 = new MimmoGeometry();
    reader2->setIOMode(IOMode::READ);
    reader2->setReadDir("geodata");
    reader2->setReadFilename("mixedP3D");
    reader2->setReadFileType(FileType::VOLVTU);
    reader2->exec();
    
    check = check && (reader2->getGeometry()->getNCells() == 75);
    check = check && (reader2->getGeometry()->getNVertex() == 52);
    
    reader2->getGeometry()->getPatch()->write("volume");
    std::cout<<"test2 passed :"<<check<<std::endl;
    
    delete reader1;
    delete reader2;
    return int(!check);
}


// =================================================================================== //

int main( int argc, char *argv[] ) {

	BITPIT_UNUSED(argc);
	BITPIT_UNUSED(argv);
	
#if ENABLE_MPI==1
	MPI::Init(argc, argv);

	{
#endif
		/**<Calling mimmo Test routines*/

        int val = test1() ;
        val = std::max(val,test2());
#if ENABLE_MPI==1
	}

	MPI::Finalize();
#endif
	
	return val;
}
