#include "Worker.h"

// 工人公共方法
// 显示个人信息
void Worker::ShowInfo()
{
    cout<<"职工编号："<<this->m_Id
        <<"\t职工姓名："<<this->m_Name
        <<"\t岗位："<<this->GetDeptName()
        <<"\t岗位职责："<<this->GetDeptDuty()<<endl;
}