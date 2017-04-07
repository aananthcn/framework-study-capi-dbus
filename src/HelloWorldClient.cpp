#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldProxy.hpp>

using namespace v1_0::commonapi;
#define BUF_SIZE	(256)


void send_bytes(char *buf, int bytes, int loops)
{
	timeval tv;
	double t1, t2;
	int i;
	char dbuf[BUF_SIZE];

	if ((bytes > BUF_SIZE) | (loops < 1) || (loops > 256)) {
		std::cout << "Error: send_bytes can't handle this input\n";
	    return;
	}

	std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
	std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>("local", "test");

	for (i = 0; i < bytes; i++) {
	    dbuf[i] = buf[i];
	}
	dbuf[i-1] = '\0';

	CommonAPI::CallStatus callStatus;
	std::string returnMessage;

	for (i = 0; i < loops; i++) {
	    std::cout << "Sending" << bytes << " bytes";
	    gettimeofday(&tv, 0);
	    t1 = tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
	    myProxy->sayHello(dbuf, callStatus, returnMessage);
	    gettimeofday(&tv, 0);
	    t2 = tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;

	    std::cout << "Got message: '" << returnMessage << "'\n";
	    std::cout << "Loop back time: " << t2 - t1 << "ms\n";
	    std::cout << "Message size: " << bytes << "bytes\n";
	}
}

int main()
{
	char sbuf[BUF_SIZE];


	// Initialize sbuffer with printable characters
	for (int i = 0; i < BUF_SIZE; i++) {
		sbuf[i] = (i % (126-32)) + 32;
	}
	sbuf[BUF_SIZE-1] = '\0';


	std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
	std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>("local", "test");

	std::cout << "Checking availability!" << std::endl;
	while (!myProxy->isAvailable())
		usleep(10);
	std::cout << "Available..." << std::endl;

	send_bytes(sbuf, 2, 100);
	send_bytes(sbuf, 4, 100);
	send_bytes(sbuf, 8, 100);
	send_bytes(sbuf, 16, 100);
	send_bytes(sbuf, 32, 100);
	send_bytes(sbuf, 64, 100);
	send_bytes(sbuf, 128, 100);
	send_bytes(sbuf, 256, 100);

	return 0;
}
