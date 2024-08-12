#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"

//员工类
class Employee : public Worker
{
    public:

   // 构造函数
    Employee(int id, string name, int deptId);

    //获取岗位名称
    virtual string GetDeptName(); 

    //获取岗位职责
    virtual string GetDeptDuty();

};

