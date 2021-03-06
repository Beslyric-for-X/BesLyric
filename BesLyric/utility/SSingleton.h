/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       Singleton.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI系统中使用的单件模块
*/

#pragma once

#include <assert.h>

namespace SOUI
{

    /**
    * @class      Singleton
    * @brief      单件模板
    * 
    * Describe    
    */
    template <typename T> 
    class Singleton
    {
    public:
        static T& getSingleton( void )
        {
			static T ms_Singleton;
			return ms_Singleton;
        }
	protected:
        Singleton( void )
        {
        }
        virtual ~Singleton( void )
        {
        }
    private:
        Singleton& operator=(const Singleton&)
        {
            return *this;
        }
        Singleton(const Singleton&) {}
    };

}//namespace SOUI