/*
 * DBYS.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#ifndef __DBYS_H__
#define __DBYS_H__

#include "YS.h"
#include "Yalone.hpp"
#include "ocicursor.h"
#include "Ymsgtool.h"
#include "Ylog.h"

struct DBEntity_t
{
public:
    COCIDatabase _dataEntity;
    COCICursor _coc;
    bool        _isIng;
    std::shared_ptr<std::thread> _ptr;
    DBEntity_t(Ystring dataBaseSid, Ystring dataBaseUsr, Ystring dataBasePwd)
    {
        _dataEntity.COCIDatabase_init();
        _dataEntity.Open(dataBaseSid.c_str(), dataBaseUsr.c_str(), dataBasePwd.c_str());
        _coc.COCICursor_init(&_dataEntity);
        _isIng = false;
    }
};
//class DBYS : public YS, public alone<DBYS>
class DBYS : public alone<DBYS>
{
public:
    DBYS();
    void Start();
    void Loop(DBEntity_t *dbentiry);
    void HandleWork(msg *_msg);
    void Push(void *_msg);
private:
    std::vector<DBEntity_t *> _dbEntitys;
    std::queue<void *> _que;
    std::mutex _mutex;
};

#define gDBYS DBYS::GetEntity()

#endif // DBYS_H
