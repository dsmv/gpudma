/*
 * tf_test.h
 *
 *  Created on: Jan 29, 2017
 *      Author: root
 */

#ifndef TF_TEST_H_
#define TF_TEST_H_

class TF_Test
{

public:

	virtual int 	Prepare( int cnt )=0;

	virtual void	Start( void )=0;

	virtual void 	Stop( void ) {};

	virtual int		isComplete( void ) { return 0; };

	virtual void	StepTable( void ) {};


};




#endif /* TF_TEST_H_ */
