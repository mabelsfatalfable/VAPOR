#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv)
{
	char path[PATH_MAX];
	readlink("/proc/self/exe", path, PATH_MAX);
	char *p = &path[strlen(path)-1];
	int up = 2;
	while (p != path && up) {
		if (*p == '/') {
			*p = 0;
			up--;
		}
		p--;
	}

	setenv("VAPOR_HOME", path, 1);

	strcat(path, "/lib");
	char *oldLibPath = getenv("LD_LIBRARY_PATH");
	char *newLibPath = malloc(strlen(oldLibPath) + strlen(path) + 2);
	strcpy(newLibPath, path);
	strcat(newLibPath, ":");
	strcat(newLibPath, oldLibPath);
	setenv("LD_LIBRARY_PATH", newLibPath, 1);
	free(newLibPath);

	argv[0] = "@TARGET_NAME@";

	strcat(path, "/@TARGET_NAME@");

	if (access(path, X_OK) == -1) {
		fprintf(stderr, "Failed to run \"%s\"\n", path);
		exit(1);
	}

	execv(path, argv);
	return 0;
}