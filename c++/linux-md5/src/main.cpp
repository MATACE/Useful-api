#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <iomanip>
#include <sstream>

using namespace std;

# include "md5.h"

void SetIpAddress(string if_name, string ip_addr)
{
	int fd;
	struct ifreq ifr;
	struct sockaddr_in *addr;

	/*AF_INET - to define network interface IPv4*/
	/*Creating soket for it.*/
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	/*AF_INET - to define IPv4 Address type.*/
	ifr.ifr_addr.sa_family = AF_INET;
	/*eth0 - define the ifr_name - port name where network attached.*/
	memcpy(ifr.ifr_name, if_name.c_str(), IFNAMSIZ - 1);
	/*defining the sockaddr_in*/
	addr = (struct sockaddr_in *)&ifr.ifr_addr;
	/*convert ip address in correct format to write*/
	inet_pton(AF_INET, ip_addr.c_str(), &addr->sin_addr);
	/*Setting the Ip Address using ioctl*/
	ioctl(fd, SIOCSIFADDR, &ifr);
	/*closing fd*/
	close(fd);

	cout << "IP Address " << ip_addr << " updated sucessfully." << endl;
}

string GetIpAddress(string if_name)
{
	int fd;
	struct ifreq ifr;
	string ip_address;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;
	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, if_name.c_str(), IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);

	ip_address = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	/* display result */
	cout << ip_address << endl;

	return ip_address;
}

string GetMacAddress(string if_name)
{
	int fd;
	int i;
	struct ifreq ifr;
	std::stringstream ss;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;
	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, if_name.c_str(), IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);
	close(fd);

	for (i = 0; i < 6; i++) {
		ss << std::setfill('0') << std::setw(2) << std::hex << (int)ifr.ifr_addr.sa_data[i];
		if (i < 5) {
			ss << ":";
		}
	}

	/* display result */
    cout << ss.str() << endl;

	return ss.str();
}

string Md5Sum(string file_path)
{
	int i;
	int fd;
	md5_state_t state;
	uint8_t buf[1024];
	uint8_t md5_calc[16];

	md5_init(&state);

	fd = open(file_path.c_str(), O_RDWR | O_APPEND);
	if (fd < 0) {
		cout << "Open file error..." << endl;
		return "";
	}

	while (1) {
		i = read(fd, buf, 1024);
		if (i <= 0)
			break;
		md5_append(&state, buf, i);
	}

	md5_finish(&state, md5_calc);
	close(fd);

	std::stringstream ss;
	for (i = 0; i < 16; i++)
		ss << std::setfill('0') << std::setw(2) << std::hex << (int)md5_calc[i];

	return ss.str();
}

int main(int argc, char const *argv[])
{
    string path = "./hello";
    cout << Md5Sum(path) << endl;
    return 0;
}
