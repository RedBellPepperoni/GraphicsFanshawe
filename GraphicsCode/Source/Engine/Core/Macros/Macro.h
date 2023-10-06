#pragma once
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Utils/Loading/File.h"

// Ask Mr. Feeney if this is fine?? 
#define CHECKNULL(codeblock)			\
		if(codeblock == nullptr)		\
		{  LOG_ERROR("Null Reference at : {0} | Line {1} ", File::GetFileNameWithExt(__FILE__), __LINE__ ); }  \
		
	    