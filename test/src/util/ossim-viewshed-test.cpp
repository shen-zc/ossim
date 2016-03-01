//---
// File: ossim-chipper-test.cpp
//
// License: MIT
//
// Author:  David Burken
// 
// Description: Test application for ossimChipperUtil class.
//---
// $Id$

#include <ossim/base/ossimException.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimTimer.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/init/ossimInit.h>
#include <ossim/util/ossimViewshedUtil.h>

#include <iostream>
using namespace std;

static void usage( const std::string& app )
{
   cout << app << " <TBD>" << endl;
}

int main(int argc, char* argv[])
{
   int status = -1;

   // Timer for elapsed time:
   ossimTimer::instance()->setStartTick();

   try
   {
      ossimArgumentParser ap(&argc, argv);
      ossimInit::instance()->initialize(ap);
      
      ossimKeywordlist kwl;
      kwl.add("observer", "48.48 -113.79");
      kwl.add("aoi_map_rect", "-12688527.58 6168162.43 -12645531.75 6205998.76");
      kwl.add("visibility_radius", "8000");
      kwl.add("srs", "3857");
      kwl.add("height_of_eye", "5");
      kwl.add("lut_file", "/data/TEST/HLZ/N48W114/vs.lut");

      ossimRefPtr<ossimChipProcUtil> viewshed = new ossimViewshedUtil;
      viewshed->initialize(kwl);

      ossimGrect grect;
      grect.makeNan();
      ossimRefPtr<ossimImageData> tile = viewshed->getChip(grect);
      tile->write("debug_chip.ras");
   }
   catch( const ossimException& e )
   {
      cerr << "Caught exception: " << e.what() << endl;
   }
   catch( ... )
   {
      cerr << "Caught unknown exception!" << endl;
   }
   
   cout << "Elapsed time in seconds: "
        << std::setiosflags(ios::fixed)
        << std::setprecision(3)
        << ossimTimer::instance()->time_s() << "\n";
   
   return status;
   
} // End of main(...)
