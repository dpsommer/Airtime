/*------------------------------------------------------------------------------

    Copyright (c) 2004 Media Development Loan Fund
 
    This file is part of the LiveSupport project.
    http://livesupport.campware.org/
    To report bugs, send an e-mail to bugs@campware.org
 
    LiveSupport is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    LiveSupport is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with LiveSupport; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
    Author   : $Author: maroy $
    Version  : $Revision: 1.2 $
    Location : $Source: /home/paul/cvs2svn-livesupport/newcvsrepo/livesupport/modules/core/src/TestRunnable.h,v $

------------------------------------------------------------------------------*/
#ifndef TestRunnable_h
#define TestRunnable_h

#ifndef __cplusplus
#error This is a C++ include file
#endif


/* ============================================================ include files */

#ifdef HAVE_CONFIG_H
#include "configure.h"
#endif

#include "LiveSupport/Core/RunnableInterface.h"


namespace LiveSupport {
namespace Core {


/* ================================================================ constants */


/* =================================================================== macros */


/* =============================================================== data types */

/**
 *  A sample Runnable object, for testing purposes.
 *
 *  @author  $Author: maroy $
 *  @version $Revision: 1.2 $
 */
class TestRunnable : public virtual RunnableInterface
{
    public:
        /**
         *  An enum signaling the states of the Runnable object.
         */
        typedef enum {  created, running, stopped } State;

    private:
        /**
         *  The time interval the run() method will check if stop()
         *  has been called meanwhile.
         */
        Ptr<time_duration>::Ref     loopTime;

        /**
         *  Flag that marks if the main execution body should be
         *  running.
         */
        bool            shouldRun;

        /**
         *  The state of the object.
         */
        State           state;

        /**
         *  Default constructor.
         */
        TestRunnable(void)                              throw ()
        {
        }


    public:
        /**
         *  Constructor.
         *
         *  @param loopTime the time at which the run() method checks
         *         if it still should run.
         */
        TestRunnable(Ptr<time_duration>::Ref    loopTime)      throw ();

        /**
         *  A virtual destructor, as this class has virtual functions.
         */
        virtual
        ~TestRunnable(void)                             throw ()
        {
        }

        /**
         *  The main execution loop for the thread.
         */
        virtual void
        run(void)                                       throw ();

        /**
         *  Signal the thread to stop, gracefully.
         *  This is just a call to signal the execution to stop, eventually.
         */
        virtual void
        stop(void)                                      throw ()
        {
            shouldRun = false;
        }

        /**
         *  Get the state of the object.
         */
        virtual State
        getState(void) const                            throw ()
        {
            return state;
        }
};


/* ================================================= external data structures */


/* ====================================================== function prototypes */


} // namespace Core
} // namespace LiveSupport


#endif // TestRunnable_h

