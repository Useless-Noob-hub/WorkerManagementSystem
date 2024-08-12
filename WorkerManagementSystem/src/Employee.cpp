#include "Employee.h"

   // 构造函数
    Employee::Employee(int id, string name, int deptId=1)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = deptId;
    }

    
    // 显示个人信息
    // void Emploeey::ShowInfo()
    // {
    //     cout<<"职工编号："<<this->m_Id
    //         <<"\t职工姓名："<<this->m_Name
    //         <<"\t岗位："<<this->GetDeptName()
    //         <<"\t岗位职责："<<this->GetDeptDuty()<<endl;
    // }

    //获取岗位名称
    string Employee::GetDeptName()
    {
        return string("员工");
    }

    //获取岗位职责
    string Employee::GetDeptDuty()
    {
        return string("完成经理交给的任务");
    }