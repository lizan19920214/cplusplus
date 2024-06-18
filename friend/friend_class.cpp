/**
 * 友元类
 * g++ -o friend_class friend_class.cpp
*/
#include <iostream>
#include <string>
using namespace std;

class Building;

class RoomMate
{
public:
    RoomMate();
    void visit();
private:
    Building* m_building;
};

class Building
{
public:
    //声明室友为友元
    friend class RoomMate;
    string m_settingRoom;
public:
    Building();
private:
    string m_bedRoom;
};

RoomMate::RoomMate()
{
    m_building = new Building();
}

void RoomMate::visit()
{
    cout << "visit building" << endl;
    cout << "室友参观:" << m_building->m_settingRoom << endl;
    //因为室友为建筑的友元，因此可以访问建筑的私用成员
    cout << "室友参观:" << m_building->m_bedRoom << endl;
}

Building::Building()
{
    m_bedRoom = "卧室";
    m_settingRoom = "客厅";
}

void Test()
{
    RoomMate* r = new RoomMate();
    r->visit();

    delete r;
    r = nullptr;
}

int main()
{
    Test();
    return 0;
}

