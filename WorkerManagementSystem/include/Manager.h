#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"

//经理Manager类
class Manager: public Worker
{
    public:

   // 构造函数
    Manager(int id, string name, int deptId);

    //获取岗位名称
    virtual string GetDeptName(); 

    //获取岗位职责
    virtual string GetDeptDuty();

};

