#include "Manager.h"

   // 构造函数
    Manager::Manager(int id, string name, int deptId=2)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = deptId;
    }

    
    // 显示个人信息
    // void Manager::ShowInfo()
    // {
    //     cout<<"职工编号："<<this->m_Id
    //         <<"\t职工姓名："<<this->m_Name
    //         <<"\t岗位："<<this->GetDeptName()
    //         <<"\t岗位职责："<<this->GetDeptDuty()<<endl;
    // }

    //获取岗位名称
    string Manager::GetDeptName()
    {
        return string("经理");
    }

    //获取岗位职责
    string Manager::GetDeptDuty()
    {
        return string("完成老板交给的事务");
    }