
#include <stdio.h>
#include <stdlib.h>

#include "tutorial.person.pb.h"
#include "tutorial.info.pb.h"

#include <iostream>
#include <fstream>

typedef unsigned char	uchar_t;


using namespace tutorial;


int main(int argc, char *argv[])
{
    AddressBook addressBook;
	//检验是否已经存在信息接受文件
    std::fstream input("./txt.prototxt", std::ios::in | std::ios::binary);
    if (!input) {
          std::cout << "./txt.prototxt" 
          << ": File not found.  Creating a new file." 
          << std::endl;
        } 
    else if (!addressBook.ParseFromIstream(&input)) {
          std::cerr << "Failed to parse address book." << std::endl;
              return -1;
	}
	
	Person* pi = addressBook.add_people();
	   
	//设置初值
    pi->set_name("aut");
    pi->set_id(1087);
    if (!pi->has_email())
        pi->set_email("autyinjing@126.com");

    Person::PhoneNumber* pn = pi->add_phones();
    pn->set_number("021-8888-8888");
	pn->set_type(Person::HOME);
    pn = pi->add_phones();
    pn->set_number("138-8888-8888");
    pn->set_type(Person::MOBILE);
		
	//打开（新建）文件进行信息输出
    std::fstream output("./txt.prototxt", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!addressBook.SerializeToOstream(&output)) {
        std::cerr << "Failed to write address book." << std::endl;
        return -1;
	}
	
	{
		uint32_t msg_size = addressBook.ByteSize();
		printf("msg_size = %d\n", msg_size);
		uchar_t* szData = new uchar_t[msg_size];
		addressBook.SerializeToArray(szData, msg_size);
	}

	PointLLHA  *point = new PointLLHA;
	point->set_longitude(116.20);
	point->set_latitude(39.56);
	
	VehicleHeartbeat vehicleHeartbeat1;
	vehicleHeartbeat1.set_allocated_vehicle_pose(point);
	
	{
		uint32_t msg_size = vehicleHeartbeat1.ByteSize();
		printf("msg_size = %d\n", msg_size);
		uchar_t* szData = new uchar_t[msg_size];
		vehicleHeartbeat1.SerializeToArray(szData, msg_size);
	}
	
	VehicleHeartbeat vehicleHeartbeat2;
	vehicleHeartbeat2.mutable_vehicle_pose()->CopyFrom(*point);// 这里传入的是一个变量，mutable内部有一个new函数
	
	{
		uint32_t msg_size = vehicleHeartbeat2.ByteSize();
		printf("msg_size = %d\n", msg_size);
		uchar_t* szData = new uchar_t[msg_size];
		vehicleHeartbeat2.SerializeToArray(szData, msg_size);
	}
	
	VehicleRoutingInfo vehicle_routing_info;
	
	// 第一个点
	PointLLHA *way_point = vehicle_routing_info.add_way_points();
	way_point->set_longitude(116.20);
	way_point->set_latitude(39.56);

	// 第二个点
	PointLLHA *way_point1 = vehicle_routing_info.add_way_points();
	way_point1->set_longitude(116.21);
	way_point1->set_latitude(39.57);
	
	{
		uint32_t msg_size = vehicle_routing_info.ByteSize();
		printf("msg_size = %d\n", msg_size);
		uchar_t* szData = new uchar_t[msg_size];
		vehicle_routing_info.SerializeToArray(szData, msg_size);
	}

	
	
    return 0;
}

