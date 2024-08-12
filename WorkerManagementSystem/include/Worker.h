#pragma once
#include <iostream>
using namespace std;

//职工抽象类
class Worker
{
    public:


    //获取岗位名称
    virtual string GetDeptName() = 0;

    //获取岗位职责
    virtual string GetDeptDuty()=0;
    
    //显示个人信息
    void ShowInfo();


    int m_Id;   // 员工编号
    string m_Name;  // 员工姓名
    int m_DeptId;   // 部门编号
};

