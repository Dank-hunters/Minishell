#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[200];
	int fd = open("test", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(fd, "0123456789", 10);
	close(fd);
	fd = open("test", O_RDWR | O_CREAT | O_APPEND, 0666);
	unlink("test");
	read(fd, buf, 199);
	buf[199] = 0;
	write(1, buf, strlen(buf));
	return 0;
}
