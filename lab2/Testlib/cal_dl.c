#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
	void *handle;
	int (*add)(int, int);
	int (*subtract)(int, int);
	int (*multiply)(int, int);
	double (*divide)(int, int);
	char *error;
	
	handle = dlopen("./lib/libcalop.so", RTLD_LAZY);
	if(!handle){
		fputs(dlerror(), stderr);
		exit(1);
	}
	
	add = dlsym(handle, "add");
	if((error = dlerror()) != NULL) {
		fprintf(stderr, "%s", error);
		exit(1);
	}
	
	subtract = dlsym(handle, "subtract");
	if((error = dlerror()) != NULL) {
		fprintf(stderr, "%s", error);
		exit(1);
	}
	
	multiply = dlsym(handle, "multiply");
	if((error = dlerror()) != NULL) {
		fprintf(stderr, "%s", error);
		exit(1);
	}
	
	divide = dlsym(handle, "divide");
	if((error = dlerror()) != NULL) {
		fprintf(stderr, "%s", error);
		exit(1);
	}
	
	
        int a,b;
        scanf("%d %d",&a,&b);

        printf("%d + %d = %d\n", a,b,(*add)(a,b));
        printf("%d - %d = %d\n", a,b,(*subtract)(a,b));
        printf("%d * %d = %d\n", a,b,(*multiply)(a,b));
        printf("%d / %d = %f\n", a,b,(*divide)(a,b));
        dlclose(handle);
}
