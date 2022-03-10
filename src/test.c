#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t p;
	write(1, "w", 1);
	p = fork();
	write(1, "s", 1);
	
}
