
#ifndef __CPUTGPUTimer_h__
#define __CPUTGPUTimer_h__

#include "CPUT.h"
#include "CPUTGPUTimer.h"

#include <vector>
#include <map>


class CPUTGPUTimerOGL : public CPUTGPUTimer
{

protected:
                                              CPUTGPUTimerOGL();
public:
	
private:	

    static const int                        c_dataQueryMaxLag       = 2;                       // in frames
    static const int                        c_historyLength         = 1+c_dataQueryMaxLag;   
    static unsigned int                     s_lastFrameID;
    static bool                             s_frameActive;
	static std::vector<CPUTGPUTimerOGL*>		s_instances;

    static std::vector<GLuint>				s_timerQueries;

    public:

    static void                               OnFrameStart();
    static void                               OnFrameEnd();


	static void                               OnDeviceAndContextCreated( );
    static void                               OnDeviceAboutToBeDestroyed( );

private:
    static void                               FrameFinishQueries( bool forceAll );
	GLuint									  GetTimerQuery2();
public:
   
    // NON-STATIC bit
    struct GPUTimerInfo
    {
        unsigned int							FrameID;
       GLuint									StartQuery;
       GLuint									StartQuery2;
       GLuint									StopQuery2;
	   GLuint									StartDataSize;
	   void*		StartData;
	   void*		StopData;
       GLuint									StopQuery;
       bool										QueryActive;
       double									TimingResult;
    };
   
    int                                       m_historyLastIndex;
    GPUTimerInfo                              m_history[c_historyLength];
    bool                                      m_active;
   
    double                                    m_lastTime;
    double                                    m_avgTime;
	unsigned int							  m_lastFrameID;
	unsigned int							  m_NewRetires;
   
   
                                              ~CPUTGPUTimerOGL();

    double                                    GetAvgTime( ) const     { return m_avgTime; }
   
    void                                      Start();
    void                                      Stop();
   
private:
    void                                      FinishQueries( bool forceAll );
};




class CPUTGPUProfilerOGL_AutoScopeProfile
{
    CPUTGPUTimerOGL &                    m_profiler;
    const bool                          m_doProfile;

public:
    CPUTGPUProfilerOGL_AutoScopeProfile(CPUTGPUTimerOGL & profiler, bool doProfile = true) : m_profiler(profiler), m_doProfile(doProfile)
    { 
        if( m_doProfile ) m_profiler.Start(); 
    }
    ~CPUTGPUProfilerOGL_AutoScopeProfile( )                                             
    { 
        if( m_doProfile ) m_profiler.Stop(); 
    }
};

#endif // __CPUTGPUTimer_h__
