#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
	//end if not given 2 files
	if(argc < 3) {
		return 1;
	}

	//open file to read and open/create file to write to
	FILE *readFp = fopen(argv[1],"rb");
	FILE *writeFp = fopen(argv[2],"wb");
	//cretae buffer
	char buffer[10];
	
	size_t data;

	//read file and copy to new file
	while((data = fread(buffer,1,sizeof(buffer),readFp)) > 0) {
		fwrite(buffer,1,data,writeFp);
	}

	//close files
	fclose(readFp);
	fclose(writeFp);

	return 0;
}