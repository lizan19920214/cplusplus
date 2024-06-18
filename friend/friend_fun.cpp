/**
 * 友元函数
 * g++ -o friend_fun friend_fun.cpp
*/
#include <iostream>
#include <string>
using namespace std;

//房屋类
class Building
{
public:
    //客厅
    string m_sittingRoom;
    //将室友1设置为友元，这样室友1就可以访问卧室
    friend void RoomMate1(Building* building);
public:
    Building()
    {
        m_sittingRoom = "客厅";
        m_bedRoom = "卧室";
    }
private:
    //卧室
    string m_bedRoom;
};

//全局函数1
void RoomMate1(Building* building)
{
    cout << "室友1正在访问地址 :" << building->m_sittingRoom << endl;
    cout << "室友1正在访问地址 :" << building->m_bedRoom << endl;
}

//全局函数2
void RoomMate2(Building* building)
{
    cout << "室友2正在访问地址 :" << building->m_sittingRoom << endl;
    //因为室友2不是友元，因此访问私有的卧室会报错
    // cout << "室友2正在访问地址 :" << building->m_bedRoom << endl;
}

int main()
{
    Building* building = new Building();
    RoomMate1(building);
    RoomMate2(building);
    return 1;
}