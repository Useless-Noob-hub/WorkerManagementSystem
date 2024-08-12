#include "Boss.h"

   // 构造函数
    Boss::Boss(int id, string name, int deptId=3)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = deptId;
    }

    
    // 显示个人信息
    // void Boss::ShowInfo()
    // {
    //     cout<<"职工编号："<<this->m_Id
    //         <<"\t职工姓名："<<this->m_Name
    //         <<"\t岗位："<<this->GetDeptName()
    //         <<"\t岗位职责："<<this->GetDeptDuty()<<endl;
    // }

    //获取岗位名称
    string Boss::GetDeptName()
    {
        return string("老板");
    }

    //获取岗位职责
    string Boss::GetDeptDuty()
    {
        return string("管理公司大大小小事务");
    }