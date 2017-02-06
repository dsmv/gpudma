/*
 * TF_TestThread.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: root
 */

#include <sys/types.h>
#include <sys/stat.h>
#include "stdio.h"

#include "tf_testthread.h"



TF_TestThread::TF_TestThread( int argc, char **argv )
{
	// TODO Auto-generated constructor stub

	m_isPrepareComplete=0;
	m_isComplete=0;
	m_isTerminate=0;
	m_CycleCnt=0;

	pthread_mutex_t		m_StartMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t		m_StartCond  = PTHREAD_COND_INITIALIZER;

}

TF_TestThread::~TF_TestThread()
{

}



int 	TF_TestThread::Prepare( int cnt )
{
		if( 0==cnt )
		{
		    int res = pthread_attr_init(&m_attrThread);
		    if(res != 0) {
		        fprintf(stderr, "%s\n", "Stream not started");
		        throw( "Stream not started" );
		    }

		    res = pthread_attr_setdetachstate(&m_attrThread, PTHREAD_CREATE_JOINABLE);
		    if(res != 0) {
		        fprintf(stderr, "%s\n", "Stream not started");
		        throw( "Stream not started" );
		    }

		    res = pthread_create(&m_hThread, &m_attrThread, ThreadFunc, this);
		    if(res != 0) {
		        fprintf(stderr, "%s\n", "Stream not started");
		        throw( "Stream not started" );
		    }
		}

		int ret=m_isPrepareComplete;
		if( ret )
		{
			printf( "Prepare - Ok\n");
			//fprintf( stderr, "Prepare - Ok\n");

		}

		return ret;
}

void* TF_TestThread::ThreadFunc( void* lpvThreadParm )
{
	TF_TestThread *test=(TF_TestThread*)lpvThreadParm;
    void* ret;
    if( !test )
        return 0;
    ret=test->Execute();
    return ret;
}

void* TF_TestThread::Execute( void )
{
		PrepareInThread();
		m_isPrepareComplete=1;

		// Wait for Start function
		pthread_mutex_lock( &m_StartMutex );
		pthread_cond_wait( &m_StartCond, &m_StartMutex );
		pthread_mutex_unlock( &m_StartMutex );

		fprintf( stderr, "Run\n");
		Run();

		CleanupInThread();

		m_isComplete=1;
		return NULL;
}

void	TF_TestThread::Start( void )
{

	// Start Thread
	pthread_mutex_lock( &m_StartMutex );
	pthread_cond_signal( &m_StartCond );
	pthread_mutex_unlock( &m_StartMutex );
}

void 	TF_TestThread::Stop( void )
{
	m_isTerminate=1;
	//fprintf( stderr, "%s - Ok\n", __FUNCTION__ );
}

int		TF_TestThread::isComplete( void )
{
		return m_isComplete;
}




