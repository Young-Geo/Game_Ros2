/*
 * DBYS.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "DBYS.h"
#include "DBconfig.h"
#include "Ypackage.h"
#include "work.h"
#include "YSocketClient.h"
#include <functional>


DBYS::DBYS(){}

/*
void    DBYS::Start()
{
    YSOCKET::sock_addr_t addr;
    addr._ip    = gDBconfig->GetDBServerIp();
    addr._port  = gDBconfig->GetDBServerPort();
    YS::Start(addr);//start

    auto func_r = [=] (SocketClient sockClient, Ychain_t &chain, void *arg) ->void
    {
        DBEntity_t *_dbEntity = NULL;
        msg *_msg = NULL;

        Yassert(_dbEntity = (DBEntity_t *)arg);

        _msg = gPACKAGE->ParseBuf(chain, sockClient);
        if (!_msg) {
            return;
        }
        //gWORK->Push(new workStruct(_msg, _dbEntity));
        gWORK->HandleWork(new workStruct(_msg, _dbEntity));
        // delete _ws->_msg
    };

    for (Yint i = 0; i < gDBconfig->GetNumDB(); ++i)
    {
        DBEntity_t * dbEntity = nullptr;
        Yassert(dbEntity = new DBEntity_t(gDBconfig->GetDBSID(), gDBconfig->GetDBUSR(), gDBconfig->GetDBPWD()));
        _dbEntitys.push_back(dbEntity);

        this->AddWorkEvent(func_r, NULL, NULL, dbEntity);
    }
    //
}
*/


void    DBYS::Start()
{
    for (Yint i = 0; i < gDBconfig->GetNumDB(); ++i)
    {
        DBEntity_t * dbEntity = nullptr;
        Yassert(dbEntity = new DBEntity_t(gDBconfig->GetDBSID(), gDBconfig->GetDBUSR(), gDBconfig->GetDBPWD()));
        _dbEntitys.push_back(dbEntity);
        dbEntity->_ptr = std::make_shared<std::thread>(std::thread(std::bind(&DBYS::Loop, this, dbEntity)));
        dbEntity->_ptr->detach();
    }
}

void DBYS::Push(void *_msg)
{
    Yassert(_msg);
    std::lock_guard<std::mutex> lo(this->_mutex);
    this->_que.push(_msg);
}

void DBYS::Loop(DBEntity_t *dbentiry)
{
    msg *_msg = NULL;

    Yassert(dbentiry);
    while (true)
    {
        //
        if (this->_que.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        _msg = (msg *)this->_que.front();

        if (!this->_mutex.try_lock()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        this->_que.pop();
        this->_mutex.unlock();
        if (!_msg) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }

        dbentiry->_isIng = true;
        HandleWork(_msg);
        dbentiry->_isIng = false;
    }
}
void DBYS::HandleWork(msg *_msg)
{
}
