﻿/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This copy of FastCdr is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/*
 * StatelessTest.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *      		grcanosa@gmail.com
 */

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdint>

#include "eprosimartps/rtps_all.h"

#include "ThroughputTypes.h"

#include "ThroughputPublisher.h"
#include "ThroughputSubscriber.h"

using namespace eprosima;
using namespace dds;
using namespace rtps;
using namespace std;


#if defined(__LITTLE_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = LITTLEEND;
#elif defined (__BIG_ENDIAN__)
const Endianness_t DEFAULT_ENDIAN = BIGEND;
#endif

#if defined(_WIN32)
	#define COPYSTR strcpy_s
#else
	#define COPYSTR strcpy
#endif


int main(int argc, char** argv){
	RTPSLog::setVerbosity(EPROSIMA_DEBUGINFO_VERB_LEVEL);
	cout << "Starting "<< endl;
	pInfo("Starting"<<endl)
	int type;
	if(argc > 1)
	{
		if(strcmp(argv[1],"publisher")==0)
			type = 1;
		if(strcmp(argv[1],"subscriber")==0)
			type = 2;
	}
	else
	{
		cout << "NEEDS publisher OR subscriber ARGUMENT"<<endl;
		return 0;
	}

	LatencyDataType latency_t;
	DomainParticipant::registerType((DDSTopicDataType*)&latency_t);

	ThroughputCommandDataType throuputcommand_t;
	DomainParticipant::registerType((DDSTopicDataType*)&throuputcommand_t);

	uint32_t demands[] = {2000,4000,6000,8000,10000};
		vector<uint32_t> demand (demands, demands + sizeof(demands) / sizeof(uint32_t) );

	switch (type)
	{
	case 1:
	{
		ThroughputPublisher tpub;
		tpub.run(demand);
		break;
	}
	case 2:
	{

		ThroughputSubscriber tsub;
		tsub.run(demand);
		break;
	}
	}

	DomainParticipant::stopAll();


	return 0;
}


